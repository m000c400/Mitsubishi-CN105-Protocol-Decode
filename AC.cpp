#include "AC.h"

#include <ESPTelnet.h>
extern ESPTelnet TelnetServer;
#include "Debug.h"

// Initialisation Commands
uint8_t Init5[] = { 0xfc, 0x5a, 0x01, 0x30, 0x02, 0xca, 0x01, 0xa8 };  // Air to Air Connect
uint8_t Init6[] = { 0xfc, 0x5a, 0x01, 0x30, 0x02, 0xca, 0x02, 0xa7 };  // Air to Air Disconnect



#define NUMBER_COMMANDS 50
int ACActiveCommand[] = {
  0x00,
  0x02, 0x03, 0x06, 0x04, 0x05, 0x09, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e,
  0x02, 0x03, 0x06, 0x04, 0x05, 0x09, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e,
  0x02, 0x03, 0x06, 0x04, 0x05, 0x09, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e,
  0x00  // End
};

unsigned long AClastmsgdispatchedMillis = 0;  // variable for comparing millis counter
int ac_cmd_queue_length = 0;
int ac_cmd_queue_position = 1;
int ACCurrentWriteAttempt = 0;
bool ACWriteInProgress = false;

AC::AC(void)
  : ACDECODER() {
  CurrentMessage = 0;
  CurrentCommand = 0;
  UpdateFlag = 0;
  ProcessFlag = false;
  Connected = false;
  PauseStateMachine = false;
  msbetweenmsg = 0;
  PrevConnected = false;
}


void AC::Process(void) {
  uint8_t c;

  while (DeviceStream->available()) {
    if (!ProcessFlag) {
      printCurrentTime();
      DEBUG_PRINT("[AC > Bridge] ");
      ProcessFlag = true;
    }
    c = DeviceStream->read();

    if (c == 0)
      DEBUG_PRINT("00, ");
    else {
      if (c < 0x10) DEBUG_PRINT("0");
      DEBUG_PRINT(String(c, HEX));
      DEBUG_PRINT(", ");
    }

    if (ACDECODER::Process(c)) {
      ProcessFlag = false;
      msbetweenmsg = millis() - AClastmsgdispatchedMillis;
      DEBUG_PRINTLN();
      if (!Connected) { DEBUG_PRINTLN("A2A Connected!"); }
      Connected = true;
      PrevConnected = true;
    }
  }
}

void AC::SetStream(Stream* ACStream) {
  DeviceStream = ACStream;  // Must set stream first
  Connect();
}


void AC::TriggerStatusStateMachine(void) {
  if (!Connected) {
    Connect();
  }
  CurrentMessage = 1;  // This triggers the run
  Connected = false;
}


void AC::StopStateMachine(void) {
  if (CurrentMessage != 0) {
    printCurrentTime();
    DEBUG_PRINTLN(F("Pausing Read Operation to AC"));
    PauseStateMachine = true;
  }
}



void AC::StatusStateMachine(void) {
  uint8_t Buffer[COMMANDSIZE];
  uint8_t CommandSize;
  uint8_t i;

  if (CurrentMessage != 0 && !PauseStateMachine) {
    printCurrentTime();
    DEBUG_PRINT("[Bridge > AC] ");
    ACDECODER::CreateBlankTxMessage(GET_REQUEST, 0x10);

    ACDECODER::SetPayloadByte(ACActiveCommand[CurrentMessage], 0);

    CommandSize = ACDECODER::PrepareTxCommand(Buffer);
    DeviceStream->write(Buffer, CommandSize);
    AClastmsgdispatchedMillis = millis();
    DeviceStream->flush();

    for (i = 0; i < CommandSize; i++) {
      if (Buffer[i] < 0x10) DEBUG_PRINT("0");
      DEBUG_PRINT(String(Buffer[i], HEX));
      DEBUG_PRINT(", ");
      Buffer[i] = 0x00;
    }
    DEBUG_PRINTLN();

    CurrentMessage++;

    CurrentMessage %= NUMBER_COMMANDS;  // Once none left

    // Straight to end
    if (CurrentMessage == 0) {
      UpdateFlag = 1;
    }
  }
}




void AC::WriteStateMachine(void) {
  uint8_t Buffer[COMMANDSIZE];
  uint8_t CommandSize;
  uint8_t i;

  if (ac_cmd_queue_length > 0 && ac_cmd_queue_length < 11) {
    ACCurrentWriteAttempt++;
    StopStateMachine();
    printCurrentTime();
    DEBUG_PRINT(F("Writing msg at position: "));
    DEBUG_PRINT(ac_cmd_queue_position);
    DEBUG_PRINT(F(", attempt: "));
    DEBUG_PRINTLN(ACCurrentWriteAttempt);

    printCurrentTime();
    DEBUG_PRINT(F("[Bridge > AC] "));
    ACDECODER::CreateBlankTxMessage(ACDECODER::ReturnNextCommandType(ac_cmd_queue_position), 0x10);
    ACDECODER::EncodeNextCommand(ac_cmd_queue_position);
    CommandSize = ACDECODER::PrepareTxCommand(Buffer);
    DeviceStream->write(Buffer, CommandSize);
    AClastmsgdispatchedMillis = millis();
    DeviceStream->flush();

    for (i = 0; i < CommandSize; i++) {
      if (Buffer[i] < 0x10) DEBUG_PRINT(F("0"));
      DEBUG_PRINT(String(Buffer[i], HEX));
      DEBUG_PRINT(F(", "));
      Buffer[i] = 0x00;
    }
    DEBUG_PRINTLN();

    ACWriteInProgress = true;
  } /*else {
    printCurrentTime();
    DEBUG_PRINTLN(F("Removing Read Pause [Loc1]"));
    PauseStateMachine = false;
  }*/
}



void AC::Connect(void) {
  DEBUG_PRINTLN("Connecting to A2A Devices...");
  DeviceStream->write(Init5, 8);
  DeviceStream->flush();
  delay(1000);  // Await Reply
  Process();
}

void AC::Disconnect(void) {
  StopStateMachine();
  DEBUG_PRINTLN("Clearing previous A2A Connections...");
  DeviceStream->write(Init6, 8);
  DeviceStream->flush();
  delay(1000);  // Await Reply
  Process();
  Connected = false;
}

void AC::GetVersion(uint8_t type) {
  uint8_t Buffer[COMMANDSIZE];
  uint8_t CommandSize = 0;
  uint8_t i;

  printCurrentTime();
  DEBUG_PRINT(F("[Bridge > AC] "));
  StopStateMachine();
  ACDECODER::CreateBlankTxMessage(0x5B, 0x01);
  ACDECODER::EncodeVersion(type);
  CommandSize = ACDECODER::PrepareTxCommand(Buffer);
  DeviceStream->write(Buffer, CommandSize);
  AClastmsgdispatchedMillis = millis();
  DeviceStream->flush();

  for (i = 0; i < CommandSize; i++) {
    if (Buffer[i] < 0x10) DEBUG_PRINT(F("0"));
    DEBUG_PRINT(String(Buffer[i], HEX));
    DEBUG_PRINT(F(", "));
    Buffer[i] = 0x00;
  }
  DEBUG_PRINTLN();
}


uint8_t AC::HeatPumpConnected(void) {
  return Connected;
}

uint8_t AC::UpdateComplete(void) {
  if (UpdateFlag) {
    UpdateFlag = 0;
    return 1;
  } else {
    return 0;
  }
}


uint8_t AC::Lastmsbetweenmsg(void) {
  return msbetweenmsg;
}



void AC::SetTempSetpoint(float setting, bool floatMode) {

  if (floatMode) {
    ACDECODER::EncodeSetpoint(lookupByteMapIndex(TEMP_MAP, 16, setting), floatMode);
  } else {
    ACDECODER::EncodeSetpoint((setting * 2) + 128, floatMode);
  }



  if (ac_cmd_queue_length < 10) {
    ac_cmd_queue_length++;
    ACDECODER::TransfertoBuffer(SET_REQUEST, ac_cmd_queue_length);
    printTransferMsg(ac_cmd_queue_length);
  }
}


void AC::SetRemoteTemp(float setting) {

  ACDECODER::EncodeRemoteTemperature(setting);


  if (ac_cmd_queue_length < 10) {
    ac_cmd_queue_length++;
    ACDECODER::TransfertoBuffer(SET_REQUEST, ac_cmd_queue_length);
    printTransferMsg(ac_cmd_queue_length);
  }
}


void AC::SetMode(const char* setting) {
  int index = lookupByteMapIndex(MODE_MAP, 5, setting);
  ACDECODER::EncodeSetMode(MODE[index]);


  if (ac_cmd_queue_length < 10) {
    ac_cmd_queue_length++;
    ACDECODER::TransfertoBuffer(SET_REQUEST, ac_cmd_queue_length);
    printTransferMsg(ac_cmd_queue_length);
  }
}


void AC::SetFanSpeed(const char* setting) {
  int index = lookupByteMapIndex(FAN_MAP, 6, setting);
  ACDECODER::EncodeFanSpeed(FAN[index]);

  if (ac_cmd_queue_length < 10) {
    ac_cmd_queue_length++;
    ACDECODER::TransfertoBuffer(SET_REQUEST, ac_cmd_queue_length);
    printTransferMsg(ac_cmd_queue_length);
  }
}


void AC::SetVane(const char* setting) {
  int index = lookupByteMapIndex(VANE_MAP, 7, setting);
  ACDECODER::EncodeVane(VANE[index]);

  if (ac_cmd_queue_length < 10) {
    ac_cmd_queue_length++;
    ACDECODER::TransfertoBuffer(SET_REQUEST, ac_cmd_queue_length);
    printTransferMsg(ac_cmd_queue_length);
  }
}


void AC::SetWideVane(const char* setting) {
  int index = lookupByteMapIndex(WIDEVANE_MAP, 7, setting);
  ACDECODER::EncodeWideVane(WIDEVANE[index]);


  if (ac_cmd_queue_length < 10) {
    ac_cmd_queue_length++;
    ACDECODER::TransfertoBuffer(SET_REQUEST, ac_cmd_queue_length);
    printTransferMsg(ac_cmd_queue_length);
  }
}


void AC::SetSystemPowerMode(bool setting) {
  if (setting) {
    ACDECODER::EncodePower(1);
  } else {
    ACDECODER::EncodePower(0);
  }

  if (ac_cmd_queue_length < 10) {
    ac_cmd_queue_length++;
    ACDECODER::TransfertoBuffer(SET_REQUEST, ac_cmd_queue_length);
    printTransferMsg(ac_cmd_queue_length);
  }
}


void AC::WriteMELCloudCMD(uint8_t cmd) {
  ACDECODER::EncodeMELCloud(cmd);
  if (ac_cmd_queue_length < 10) {
    ac_cmd_queue_length++;
    ACDECODER::TransfertoBuffer(SET_REQUEST, ac_cmd_queue_length);
    printTransferMsg(ac_cmd_queue_length);
  }
}


int AC::lookupByteMapIndex(const int valuesMap[], int len, int lookupValue) {
  for (int i = 0; i < len; i++) {
    if (valuesMap[i] == lookupValue) {
      return i;
    }
  }
  return -1;
}


int AC::lookupByteMapIndex(const char* valuesMap[], int len, const char* lookupValue) {
  for (int i = 0; i < len; i++) {
    if (strcasecmp(valuesMap[i], lookupValue) == 0) {
      return i;
    }
  }
  return -1;
}


const char* AC::lookupByteMapValue(const char* valuesMap[], const byte byteMap[], int len, byte byteValue) {
  for (int i = 0; i < len; i++) {
    if (byteMap[i] == byteValue) {
      return valuesMap[i];
    }
  }
  return "N/A";
}


int AC::lookupByteMapValue(const int valuesMap[], const byte byteMap[], int len, byte byteValue) {
  for (int i = 0; i < len; i++) {
    if (byteMap[i] == byteValue) {
      return valuesMap[i];
    }
  }
  return -1;
}


void AC::printCurrentTime(void) {
  time_t now;
  struct tm timeinfo;
  char TimeBuffer[32];

  time(&now);
  localtime_r(&now, &timeinfo);

  strftime(TimeBuffer, sizeof(TimeBuffer), "%F %T -> ", &timeinfo);
  DEBUG_PRINT(TimeBuffer);
}


void AC::printTransferMsg(int length) {
  DEBUG_PRINT(F("Transferred msg to position: "));
  DEBUG_PRINTLN(length);
}