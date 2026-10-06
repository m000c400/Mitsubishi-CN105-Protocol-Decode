#include "Melcloud.h"

#include <ESPTelnet.h>
extern ESPTelnet TelnetServer;
#include "Debug.h"

uint8_t MELCloudInit3[] = { 0xfc, 0x7a, 0x02, 0x7a, 0x01, 0x00, 0x09 };                                                                    // A2W Specific
uint8_t MELCloudInit4[] = { 0xfc, 0x7a, 0x01, 0x30, 0x01, 0x00, 0x54 };                                                                    // A2A Specific
uint8_t MELCloudInit5[] = { 0x02, 0xff, 0xff, 0x80, 0x00, 0x00, 0x0A, 0x01, 0x00, 0x40, 0x00, 0x00, 0x06, 0x01, 0x30, 0x00, 0x00, 0x00 };  // A2A Specific
uint8_t MELCloudInit6[] = { 0x02, 0xff, 0xff, 0x80, 0x00, 0x00, 0x0A, 0x01, 0x00, 0x40, 0x00, 0x00, 0x06, 0x02, 0x7A, 0x00, 0x00, 0xB5 };  // A2W Specific
uint8_t MELCloudInit7[] = { 0x02, 0xff, 0xff, 0x81, 0x00, 0x00, 0x00, 0x81 };                                                              // General



bool PrintMELStart = false;
bool FirstReadAfterConnect = false;
unsigned long lastMELCloudMillis = 0;

MELCLOUD::MELCLOUD(void)
  : MELCLOUDDECODER() {
  UpdateFlag = 0;
  Connected = false;
  msbetweenmsg = 0;
}


void MELCLOUD::Process(void) {
  uint8_t c;

  while (DeviceStream->available()) {
    if (!PrintMELStart) {
      printCurrentTime();
      DEBUG_PRINT("[MEL > Bridge] ");
      PrintMELStart = true;
    }
    c = DeviceStream->read();

    if (c == 0)
      DEBUG_PRINT("00, ");
    else {
      if (c < 0x10) DEBUG_PRINT("0");
      DEBUG_PRINT(String(c, HEX));
      DEBUG_PRINT(", ");
    }

    if (MELCLOUDDECODER::Process(c)) {
      DEBUG_PRINTLN();
      PrintMELStart = false;
      Connected = true;
      lastMELCloudMillis = millis();
    }
  }
}

void MELCLOUD::SetStream(Stream* MELCloudStream) {
  DeviceStream = MELCloudStream;
}



void MELCLOUD::ReplyStatus(uint8_t TargetMessage) {
  uint8_t Buffer[COMMANDSIZE];
  uint8_t CommandSize;
  uint8_t i;

  printCurrentTime();
  DEBUG_PRINT("[Bridge > MEL] ");

  if ((TargetMessage >= 0x32 && TargetMessage <= 0x35) || TargetMessage == 0x30 || TargetMessage == 0x40) {
    MELCLOUDDECODER::CreateBlankTxMessage(SET_RESPONSE, 0x10);
  } else if ((TargetMessage == 0xC9) || (TargetMessage == 0xCD) || (TargetMessage == 0xCE)) {
    MELCLOUDDECODER::CreateBlankTxMessage(EXCONNECT_RESPONSE, 0x10);
  } else {
    MELCLOUDDECODER::CreateBlankTxMessage(GET_RESPONSE, 0x10);
  }

  MELCLOUDDECODER::SetPayloadByte(TargetMessage, 0);
  // 1. Create a pointer to hold the specific array we want to use
  const uint8_t* sourceArray = NULL;

  switch (TargetMessage) {
    // Group all the straightforward array mappings
    case 0x01: sourceArray = Array0x01; break;
    case 0x02: sourceArray = Array0x02; break;
    case 0x03: sourceArray = Array0x03; break;
    case 0x04: sourceArray = Array0x04; break;
    case 0x05: sourceArray = Array0x05; break;
    case 0x06: sourceArray = Array0x06; break;
    case 0x07: sourceArray = Array0x07; break;
    case 0x08: sourceArray = Array0x08; break;
    case 0x09: sourceArray = Array0x09; break;
    case 0x0B: sourceArray = Array0x0b; break;
    case 0x0C: sourceArray = Array0x0c; break;
    case 0x0D: sourceArray = Array0x0d; break;
    case 0x0E: sourceArray = Array0x0e; break;
    case 0x0F: sourceArray = Array0x0f; break;
    case 0x10: sourceArray = Array0x10; break;
    case 0x11: sourceArray = Array0x11; break;
    case 0x12: sourceArray = Array0x12; break;
    case 0x13: sourceArray = Array0x13; break;
    case 0x14: sourceArray = Array0x14; break;
    case 0x15: sourceArray = Array0x15; break;
    case 0x16: sourceArray = Array0x16; break;
    case 0x17: sourceArray = Array0x17; break;
    case 0x18: sourceArray = Array0x18; break;
    case 0x19: sourceArray = Array0x19; break;
    case 0x1A: sourceArray = Array0x1a; break;
    case 0x1B: sourceArray = Array0x1b; break;
    case 0x1C: sourceArray = Array0x1c; break;
    case 0x1D: sourceArray = Array0x1d; break;
    case 0x1E: sourceArray = Array0x1e; break;
    case 0x1F: sourceArray = Array0x1f; break;
    case 0x20: sourceArray = Array0x20; break;
    case 0x26: sourceArray = Array0x26; break;
    case 0x27: sourceArray = Array0x27; break;
    case 0x29: sourceArray = Array0x29; break;
    case 0xA1: sourceArray = Array0xa1; break;
    case 0xA2: sourceArray = Array0xa2; break;
    case 0xC9: sourceArray = Array0xc9; break;
    case 0xCD: sourceArray = Array0xcd; break;
    case 0xCE: sourceArray = Array0xce; break;

    case 0x28:
      sourceArray = Array0x28;
      if (FirstReadAfterConnect) {
        FirstReadAfterConnect = false;
        MELCLOUDDECODER::SetPayloadByte(0x01, 11);
      }
      break;

    case 0x32 ... 0x35:  // A2W
    case 0x40 ... 0x41:  // A2A
      MELCLOUDDECODER::SetPayloadByte(0x00, 0);  // For A2W set Byte 0 for the reply format
      break;

    default:
      break;
  }

  if (sourceArray != NULL) {
    for (int i = 1; i < 16; i++) {
      MELCLOUDDECODER::SetPayloadByte(sourceArray[i], i);
    }
  }


  CommandSize = MELCLOUDDECODER::PrepareTxCommand(Buffer);
  DeviceStream->write(Buffer, CommandSize);
  DeviceStream->flush();


  for (i = 0; i < CommandSize; i++) {
    if (Buffer[i] < 0x10) DEBUG_PRINT("0");
    DEBUG_PRINT(String(Buffer[i], HEX));
    DEBUG_PRINT(", ");
    Buffer[i] = 0x00;
  }
  DEBUG_PRINTLN();
}


void MELCLOUD::ConnectA2W(void) {
  printCurrentTime();
  DEBUG_PRINTLN("[Bridge > MEL] Connecting to MELCloud Device as A2W...");
  FirstReadAfterConnect = true;
  MELCLOUDDECODER::SetTypeA2W();
  DeviceStream->write(MELCloudInit3, 7);
  DeviceStream->flush();
  Process();
}

void MELCLOUD::ConnectA2A(void) {
  printCurrentTime();
  DEBUG_PRINTLN("[Bridge > MEL] Connecting to MELCloud Device as A2A...");
  MELCLOUDDECODER::SetTypeA2A();
  DeviceStream->write(MELCloudInit4, 7);
  DeviceStream->flush();
  Process();
}


void MELCLOUD::MELNegotiate1(bool A2A) {
  printCurrentTime();
  DEBUG_PRINTLN("[Bridge > MEL] Negotiating First with MELCloud Device...");
  if (A2A) {
    DeviceStream->write(MELCloudInit5, 18);
  } else {
    DeviceStream->write(MELCloudInit6, 18);
  }
  DeviceStream->flush();
  Process();
}


void MELCLOUD::MELNegotiate2(void) {
  printCurrentTime();
  DEBUG_PRINTLN("[Bridge > MEL] Negotiating Second with MELCloud Device...");
  DeviceStream->write(MELCloudInit7, 8);
  DeviceStream->flush();
  Process();
}


uint8_t MELCLOUD::UpdateComplete(void) {
  if (UpdateFlag) {
    UpdateFlag = 0;
    return 1;
  } else {
    return 0;
  }
}

uint8_t MELCLOUD::Lastmsbetweenmsg(void) {
  return msbetweenmsg;
}

unsigned long MELCLOUD::LastMELCloudMessage(void) {
  return lastMELCloudMillis;
}

void MELCLOUD::printCurrentTime(void) {
  time_t now;
  struct tm timeinfo;
  char TimeBuffer[32];

  time(&now);
  localtime_r(&now, &timeinfo);

  strftime(TimeBuffer, sizeof(TimeBuffer), "%F %T -> ", &timeinfo);
  DEBUG_PRINT(TimeBuffer);
}