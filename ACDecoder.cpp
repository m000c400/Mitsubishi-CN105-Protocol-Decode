#include "ACDecoder.h"
#include <Arduino.h>
#include <cstdio>
#include <ESPTelnet.h>
extern ESPTelnet TelnetServer;
#include "Debug.h"

uint8_t ACWriteArray0x01[] = {};  // Write CMDs
uint8_t ACWriteArray0x07[] = {};
uint8_t ACWriteArray0x30[] = {};
uint8_t Array0xcd[] = {};
uint8_t Array0xce[] = {};

uint8_t ACBufferArray[][17] = { {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {} };


ACDECODER::ACDECODER(void) {
  memset(&RxMessage, 0, sizeof(ACMessageStruct));
  memset(&Status, 0, sizeof(ACStatus));

  Preamble[0] = 0x01;
  Preamble[1] = 0x30;
}


uint8_t ACDECODER::Process(uint8_t c) {
  uint8_t ReturnValue = false;

  if (BuildRxMessage(&RxMessage, c)) {
    ReturnValue = true;
    if (RxMessage.PacketType == GET_RESPONSE) {
      switch (RxMessage.Payload[0]) {
        case 0x02:
          Process0x02(RxMessage.Payload, &Status);
          break;
        case 0x03:
          Process0x03(RxMessage.Payload, &Status);
          break;
        case 0x04:
          Process0x04(RxMessage.Payload, &Status);
          break;
        case 0x05:
          Process0x05(RxMessage.Payload, &Status);
          break;
        case 0x06:
          Process0x06(RxMessage.Payload, &Status);
          break;
        case 0x09:
          Process0x09(RxMessage.Payload, &Status);
          break;
        case 0x15:
          Process0x15(RxMessage.Payload, &Status);
          break;
        case 0x16:
          Process0x16(RxMessage.Payload, &Status);
          break;
        case 0x17:
          Process0x17(RxMessage.Payload, &Status);
          break;
        case 0x18:
          Process0x18(RxMessage.Payload, &Status);
          break;
        case 0x19:
          Process0x19(RxMessage.Payload, &Status);
          break;
      }
    } else if (RxMessage.PacketType == SET_RESPONSE) {
      WriteOK(RxMessage.Payload, &Status);
    } else if (RxMessage.PacketType == CONNECT_RESPONSE) {
    } else if (RxMessage.PacketType == GET_ABOUT_RESPONSE) {
      switch (RxMessage.Payload[0]) {
        case 0xcd:
          Process0xCD(RxMessage.Payload, &Status);
          break;
        case 0xce:
          Process0xCE(RxMessage.Payload, &Status);
          break;
        case 0xc9:
          Process0xC9(RxMessage.Payload, &Status);
          break;
      }
    }
  }
  return ReturnValue;
}

uint8_t ACDECODER::BuildRxMessage(ACMessageStruct *Message, uint8_t c) {
  static uint8_t Buffer[COMMANDSIZE];
  static uint8_t BufferPos = 0;
  static uint8_t PayloadSize = 0;
  uint8_t i;

  if (BufferPos < HEADERSIZE) {
    switch (BufferPos) {
      case 0:
        if (c != PACKET_SYNC) return false;
        break;

      case 1:
        switch (c) {
          case SET_REQUEST:
            break;
          case SET_RESPONSE:
            break;
          case GET_REQUEST:
            break;
          case GET_RESPONSE:
            break;
          case CONNECT_REQUEST:
            break;
          case CONNECT_RESPONSE:
            break;
          case EXCONNECT_REQUEST:
            break;
          case EXCONNECT_RESPONSE:
            break;
          default:
            DEBUG_PRINTLN("Unknown PacketType");
            BufferPos = 0;
            return false;  // Unknown Packet Type
        }
        break;

      case 2:
        if (c != Preamble[0]) {
          DEBUG_PRINTLN("Preamble 1 Error");
          BufferPos = 0;
          return false;
        }
        break;

      case 3:
        if (c != Preamble[1]) {
          DEBUG_PRINTLN("Preamble 1 Error");
          BufferPos = 0;
          return false;
        }
        break;

      case 4:
        PayloadSize = c;
        if (c > MAXDATABLOCKSIZE) {
          DEBUG_PRINTLN("Oversize Payload");
          BufferPos = 0;
          return false;
        }
        break;
    }

    Buffer[BufferPos] = c;
    BufferPos++;
    return false;
  } else if (BufferPos < (PayloadSize + HEADERSIZE)) {
    Buffer[BufferPos] = c;
    BufferPos++;
  }

  else if (BufferPos == (PayloadSize + HEADERSIZE)) {
    Buffer[BufferPos] = c;
    BufferPos = 0;
    if (CheckSum(Buffer, PayloadSize + HEADERSIZE) == c) {
      DEBUG_PRINTLN("CS OK");
      Message->SyncByte = Buffer[0];
      Message->PacketType = Buffer[1];
      Message->Preamble[0] = Buffer[2];
      Message->Preamble[1] = Buffer[3];
      Message->PayloadSize = Buffer[4];
      Message->Checksum = c;
      memcpy(Message->Payload, &Buffer[5], Message->PayloadSize);
      return true;
    } else {
      DEBUG_PRINTLN("Checksum Fail");
      return false;
    }
  }
  return false;
}


void ACDECODER::WriteOK(uint8_t *Buffer, ACStatus *Status) {
  bool Write_To_Ecodan_OK;
  Write_To_Ecodan_OK = true;
  Status->Write_To_Ecodan_OK = Write_To_Ecodan_OK;
}



// Optimistic-write reconcile guard: after MQTTonData writes a commanded value into
// ACStatus, a read cycle already in flight can return the pre-write value and would
// briefly publish stale state. Hold the commanded value until the unit reads it back
// (clears the hold) or AC_PENDING_HOLD_MS lapses (unit clamped/rejected - accept truth).
static bool holdPending(uint8_t decoded, uint8_t pending, unsigned long *until) {
  if (*until == 0) return false;
  if (decoded == pending) { *until = 0; return false; }  // unit confirmed the write
  if ((long)(millis() - *until) < 0) return true;        // still settling - hold commanded value
  *until = 0;                                            // window lapsed - accept the unit's value
  return false;
}

static bool holdPendingFloat(float decoded, float pending, unsigned long *until) {
  if (*until == 0) return false;
  if (decoded == pending) { *until = 0; return false; }
  if ((long)(millis() - *until) < 0) return true;
  *until = 0;
  return false;
}

void ACDECODER::Process0x02(uint8_t *Buffer, ACStatus *Status) {
  for (int i = 1; i < 16; i++) {
    Array0x02[i] = Buffer[i];
  }

  //fc, 62, 01, 30, 10, 02, 00, 00, 01, 03, 0d, 00, 00, 00, 00, 85, a4, 46, 00, 00, 00, db,
  //                                [3] [4][5]                 [10][11][12]

  if (!holdPending(Buffer[3], Status->PendingPower, &Status->PendingPowerUntil)) {
    Status->SystemPowerMode = Buffer[3];  // Power
  }
  // Mode compares i-See-normalised base codes; isee and Buffer04 are held as a pair
  // so the report's (Buffer04 - 0x08 when isee) decode stays consistent.
  if (!holdPending(Buffer[4] > 0x08 ? Buffer[4] - 0x08 : Buffer[4], Status->PendingMode, &Status->PendingModeUntil)) {
    Status->isee = Buffer[4] > 0x08 ? true : false;  // Op Mode
    Status->Buffer04 = Buffer[4];                    // Op Mode
  }
  //Status->legacyTargetTemp = Buffer[5];               // Legacy Target Temperature
  if (!holdPending(Buffer[6], Status->PendingFan, &Status->PendingFanUntil)) {
    Status->fan = Buffer[6];  // Fan Speed
  }
  if (!holdPending(Buffer[7], Status->PendingVane, &Status->PendingVaneUntil)) {
    Status->vane = Buffer[7];  // Vertical Vane
  }
  Status->remoteProhibit = Buffer[8];  // Remote Prohibit
  if (!holdPending(Buffer[10] & 0x0F, Status->PendingWideVane & 0x0F, &Status->PendingWideVaneUntil)) {
    Status->wideVane = Buffer[10];  // Horizonal Vane
  }
  if (Buffer[11] != 0x00) {  // Target Temperature
    int temp = Buffer[11];
    temp -= 128;
    if (!holdPendingFloat((float)temp / 2, Status->PendingTemperature, &Status->PendingTempUntil)) {
      Status->Temperature = (float)temp / 2;
      Status->tempMode = true;  // FloatMode
    }
  } else {
    if (!holdPendingFloat((float)Buffer[5], Status->PendingTemperature, &Status->PendingTempUntil)) {
      Status->Temperature = Buffer[5];
    }
  }
  //Buffer[12];                                         // (UNCONFIRMED) Target Humidity
  //Buffer[13];                                         // (UNCONFIRMED) Power Saving Mode
  //Buffer[14];                                         // Airflow control mode (i-See) E.g MSZ-LN25VG2W
}

void ACDECODER::Process0x03(uint8_t *Buffer, ACStatus *Status) {
  for (int i = 1; i < 16; i++) {
    Array0x03[i] = Buffer[i];
  }

  //fc, 62, 01, 30, 10, 03, 00, 00, 06, 00, c2, a0, a0, fe, 42, 00, 14, 85, 3d, 00, 00, 3c,
  //                                [3] [4][5]  [6] [7] [8] [9][10][11][12][13]

  Status->OAT = (Buffer[5] - 128) / 2;  // Outdoor Unit Temperature (value-128)/2
  if (Buffer[6] != 0x00) {
    int temp = Buffer[6];
    temp -= 128;
    Status->RoomTempFloat = (float)temp / 2;  // Current Temperature
  } else {
    Status->RoomTemp = Buffer[3];  // Current Temperature
    Status->RmtempMode = true;
  }
  Status->Runtime = Buffer[11] + Buffer[12] + Buffer[13];  // Runtime Appears to be minutes the unit was active.
}


void ACDECODER::Process0x04(uint8_t *Buffer, ACStatus *Status) {

  for (int i = 1; i < 16; i++) {
    Array0x04[i] = Buffer[i];
  }

  // AC
  // fc, 62, 01, 30, 10, 04, 00, 00, 00, 80, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, d9,
  //                                 [3] [4][5]  [6] [7] [8] [9][10][11][12][13]

  Status->ErrCode1 = Buffer[4];
  Status->ErrCode2 = Buffer[5];
  Status->FltCode1 = Buffer[6];
  Status->FltCode2 = Buffer[7];
}


void ACDECODER::Process0x05(uint8_t *Buffer, ACStatus *Status) {

  for (int i = 1; i < 16; i++) {
    Array0x05[i] = Buffer[i];
  }

  //fc, 62, 01, 30, 10, 05, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 58, CS OK
  //                                [3] [4][5]  [6] [7] [8] [9][10][11][12][13]


  Status->Timermode = Buffer[3];
  Status->onMinutesSet = Buffer[4];
  Status->offMinutesSet = Buffer[5];
  Status->onMinutesRemaining = Buffer[6];
  Status->offMinutesRemaining = Buffer[7];
}


void ACDECODER::Process0x06(uint8_t *Buffer, ACStatus *Status) {
  for (int i = 1; i < 16; i++) {
    Array0x06[i] = Buffer[i];
  }

  // AC Packet
  // fc, 62, 01, 30, 10, 06, 00, 00, 00, 01, 02, 4c, 4c, 36, 00, 00, 42, 00, 00, 00, 00, 44,
  //                                [3] [4][5]  [6] [7] [8] [9][10][11][12][13]

  Status->CompressorFrequency = Buffer[3];
  Status->Operating = Buffer[4];

  Status->InputPower = ((float)ExtractUInt16(Buffer, 5) / 1000);
  Status->InputPower1 = Buffer[5];  // Input Power (W)
  Status->InputPower2 = Buffer[6];  // Input Power (W)
  Status->LifePower = ((float)ExtractUInt16(Buffer, 7) / 100);
  Status->LifePower1 = Buffer[7];  // Input Power (100Wh) Lifetime
  Status->LifePower2 = Buffer[8];  // Input Power (100Wh) Lifetime
}



void ACDECODER::Process0x09(uint8_t *Buffer, ACStatus *Status) {
  for (int i = 1; i < 16; i++) {
    Array0x09[i] = Buffer[i];
  }

  //fc, 62, 01, 30, 10, 09, 00, 00, 00, 02, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 52, CS OK
  //                                [3] [4][5]  [6] [7] [8] [9][10][11][12][13]
  Status->Status = Buffer[3];     // Status Flags (0x00 Normal, 0x01 Filter Service, 0x02 Defrost, 0x04 Preheat, 0x08 Standby)
  Status->FanActual = Buffer[4];  // Actual Fan Speed (Not set)
  Status->AutoMode = Buffer[5];   // Auto Mode
}

void ACDECODER::Process0x15(uint8_t *Buffer, ACStatus *Status) {
  for (int i = 1; i < 16; i++) {
    Array0x15[i] = Buffer[i];
  }
}

void ACDECODER::Process0x16(uint8_t *Buffer, ACStatus *Status) {
  for (int i = 1; i < 16; i++) {
    Array0x16[i] = Buffer[i];
  }
}

void ACDECODER::Process0x17(uint8_t *Buffer, ACStatus *Status) {
  for (int i = 1; i < 16; i++) {
    Array0x17[i] = Buffer[i];
  }
}

void ACDECODER::Process0x18(uint8_t *Buffer, ACStatus *Status) {
  for (int i = 1; i < 16; i++) {
    Array0x18[i] = Buffer[i];
  }
}

void ACDECODER::Process0x19(uint8_t *Buffer, ACStatus *Status) {
  for (int i = 1; i < 16; i++) {
    Array0x19[i] = Buffer[i];
  }
}

void ACDECODER::Process0xCD(uint8_t *Buffer, ACStatus *Status) {
  // Sample Data
  // fc, 7b, 01, 30, 10, cd, a0, be, a0, be, a0, be, 04, 11, 02, ff, ff, 00, 00, 00, 00, 48, CS OK with wide vane
  // fc, 7b, 01, 30, 10, cd, a0, be, a0, be, a0, be, 84, 11, 00, b4, 0a, 00, 00, 00, 00, 0a, CS OK with No Wide Vane
  //                                                 [7]     [9][10][11]

  Status->CD = true;  // Arbitary to know its been read at least once

  for (int i = 1; i < 16; i++) {
    Array0xcd[i] = Buffer[i];
  }


  //Status->SupportsHozVane = !(Buffer[7] & 0x80);
  Status->SupportsHozVane = true;
}

void ACDECODER::Process0xCE(uint8_t *Buffer, ACStatus *Status) {
  // Sample Data
  // [AC > Bridge] fc, 7b, 01, 30, 10, ce, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 76, CS OK
  //               fc, 7b, 01, 30, 10, ce, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 76, CS OK


  Status->CE = true;  // Arbitary to know its been read at least once

  for (int i = 1; i < 16; i++) {
    Array0xce[i] = Buffer[i];
  }
}


void ACDECODER::Process0xC9(uint8_t *Buffer, ACStatus *Status) {
  // Sample Data
  // fc, 7b, 01, 30, 10, c9, 03, 00, 20, 00, 14, 07, f5, 8c, 25, a0, be, 94, be, a0, be, 89, CS OK
  // fc, 7b, 01, 30, 10, c9, 03, 00, 20, 00, 14, 07, f5, 8c, 25, a0, be, 94, be, a0, be, 89 (AP15)

  Status->C9 = true;  // Arbitary to know its been read at least once
  Status->FanBitA = ((Buffer[7] & 0x10) == 0x10);
  Status->FanBitB = ((Buffer[7] & 0x10) == 0x10);
  Status->FanBitC = ((Buffer[7] & 0x10) == 0x10);

  for (int i = 1; i < 16; i++) {
    Array0xc9[i] = Buffer[i];
  }
}



void ACDECODER::EncodePower(uint8_t OnOff) {
  // Sample Data
  // fc, 41, 01, 30, 10, 01, 01, __, __, __, __, __, __, __, __, __, __, __, __, __, __, 7c,
  //[MEL > Bridge] fc, 41, 01, 30, 10, 01, 01, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 7c, CS OK (Off)

  PayloadWipe();
  TxMessage.Payload[0] = 0x01;
  TxMessage.Payload[1] = 0x01;   // Power
  TxMessage.Payload[3] = OnOff;  // On/Off
}

void ACDECODER::EncodeSetMode(uint8_t setting) {
  // Sample Data
  //fc, 41, 01, 30, 10, 01, 02, 00, 01, 07, 00, 00, 00, 00, 00, 00, 00, 00, 05, 00, 00, 6e, // fan
  //Payload Wipe

  PayloadWipe();
  TxMessage.Payload[0] = 0x01;
  TxMessage.Payload[1] = 0x02;  // Mode
  TxMessage.Payload[4] = setting;
}

void ACDECODER::EncodeSetpoint(uint8_t setting, bool floatMode) {
  // Sample Data
  // fc, 41, 01, 30, 10, 01, 04, __, __, __, 02, __, __, __, __, __, __, __, __, __, __, 77,  // 29C
  // [MEL > Bridge] fc, 41, 01, 30, 10, 01, 04, 00, 00, 00, 0e, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 6b, CS OK  // 17C
  // [MELCloud Write] fc, 41, 01, 30, 10, 01, 04, 00, 00, 03, 0e, 00, 00, 00, 00, 00, 00, 00, 03, 00, 00, 65, CS OK


  PayloadWipe();
  TxMessage.Payload[0] = 0x01;
  TxMessage.Payload[1] = 0x04;  // Temp
  if (floatMode) {
    TxMessage.Payload[5] = setting;
  } else {
    TxMessage.Payload[14] = (int)setting;
  }
}


void ACDECODER::EncodeFanSpeed(uint8_t setting) {
  // Sample Data
  //fc, 41, 01, 30, 10, 01, 04, __, __, __, 02, __, __, __, __, __, __, __, __, __, __, 77,

  PayloadWipe();
  TxMessage.Payload[0] = 0x01;
  TxMessage.Payload[1] = 0x08;  // Fan
  TxMessage.Payload[6] = setting;
}

void ACDECODER::EncodeVane(uint8_t setting) {
  // Sample Data

  PayloadWipe();
  TxMessage.Payload[0] = 0x01;
  TxMessage.Payload[1] = 0x10;  // Vane
  TxMessage.Payload[7] = setting;
}

void ACDECODER::EncodeWideVane(uint8_t setting) {
  // Sample Data
  //fc, 41, 01, 30, 10, 01, 10, __, __, __, __, __, __, __, __, __, __, __, __, __, __, 6d,

  // [MEL > Bridge] fc, 41, 01, 30, 10, 30, 3f, 00, 08, 18, 0c, 10, df, 00, 00, 00, 00, 00, 00, 00, 00    // UNKNOWN TYPE?


  // [MEL > Bridge] fc, 41, 01, 30, 10, 01, 00, 01, 01, 03, 00, 00, 00, 00, 00, 00, 00, 00, 02, 00, 00, 76, CS OK
  // [MEL > Bridge] fc, 41, 01, 30, 10, 01, 00, 01, 01, 03, 00, 00, 00, 00, 00, 00, 00, 00, 04, 00, 00, 74, CS OK
  //                                                                                        []


  TxMessage.Payload[0] = 0x01;
  TxMessage.Payload[1] = 0x00;
  TxMessage.Payload[2] = 0x01;
  TxMessage.Payload[13] = setting;
}


void ACDECODER::EncodeRemoteTemperature(float RemoteTemperature) {

  TxMessage.Payload[0] = 0x07;  // CMD Type

  if (RemoteTemperature > 0) {    
    TxMessage.Payload[1] = 0x01;  // Enabled
    float setting = RemoteTemperature * 2;
    setting = round(setting);
    setting = setting / 2;
    float temp1 = 3 + ((setting - 10) * 2);
    TxMessage.Payload[2] = (int)temp1;
    float temp2 = (setting * 2) + 128;
    TxMessage.Payload[3] = (int)temp2;
  } else {
    TxMessage.Payload[1] = 0x00;  // Disabled
    TxMessage.Payload[3] = 0x80;
  }
}


void ACDECODER::EncodeVersion(uint8_t type) {
  // Get FTC Version
  PayloadWipe();
  TxMessage.Payload[0] = type;
  //TxMessage.Payload[1] = 0x5F;
}


void ACDECODER::EncodeMELCloud(uint8_t cmd) {
  if (cmd == 0x40) {
    TxMessage.Payload[0] = 0x01;
  } else if (cmd == 0x41) {
    TxMessage.Payload[0] = 0x07;
  } else {
    TxMessage.Payload[0] = cmd;
  }

  for (int i = 1; i < 16; i++) {
    if (cmd == 0x40) {
      TxMessage.Payload[i] = ACWriteArray0x01[i];
    } else if (cmd == 0x41) {
      TxMessage.Payload[i] = ACWriteArray0x07[i];
    } else if (cmd == 0x30) {
      TxMessage.Payload[i] = ACWriteArray0x30[i];
    }
  }
}

void ACDECODER::PayloadWipe(void) {
  for (int i = 0; i < 16; i++) {
    TxMessage.Payload[i] = 0;
  }
}


void ACDECODER::TransfertoBuffer(uint8_t msgtype, uint8_t bufferposition) {
  BufferArray[bufferposition][0] = msgtype;
  for (int i = 1; i < 17; i++) {
    BufferArray[bufferposition][i] = TxMessage.Payload[i - 1];
  }
}

uint8_t ACDECODER::ReturnNextCommandType(uint8_t bufferposition) {
  return BufferArray[bufferposition][0];
}

void ACDECODER::EncodeNextCommand(uint8_t bufferposition) {
  for (int i = 1; i < 17; i++) {
    TxMessage.Payload[i - 1] = BufferArray[bufferposition][i];
  }
}

void ACDECODER::CreateBlankTxMessage(uint8_t PacketType, uint8_t PayloadSize) {
  CreateBlankMessageTemplate(&TxMessage, PacketType, PayloadSize);
}

void ACDECODER::CreateBlankMessageTemplate(ACMessageStruct *Message, uint8_t PacketType, uint8_t PayloadSize) {
  uint8_t i;

  memset((void *)Message, 0, sizeof(ACMessageStruct));

  Message->SyncByte = PACKET_SYNC;
  Message->PacketType = PacketType;
  Message->PayloadSize = PayloadSize;
  for (i = 0; i < PREAMBLESIZE; i++) {
    Message->Preamble[i] = Preamble[i];
  }
}

void ACDECODER::SetPayloadByte(uint8_t Data, uint8_t Location) {
  TxMessage.Payload[Location] = Data;
}

uint8_t ACDECODER::PrepareTxCommand(uint8_t *Buffer) {
  return PrepareCommand(&TxMessage, Buffer);
}

uint8_t ACDECODER::PrepareCommand(ACMessageStruct *Message, uint8_t *Buffer) {
  uint8_t MessageChecksum;
  uint8_t MessageSize;
  uint8_t i;

  Buffer[0] = Message->SyncByte;
  Buffer[1] = Message->PacketType;
  Buffer[2] = Message->Preamble[0];
  Buffer[3] = Message->Preamble[1];
  Buffer[4] = Message->PayloadSize;

  memcpy(&Buffer[5], Message->Payload, Message->PayloadSize);

  MessageSize = HEADERSIZE + Message->PayloadSize;

  MessageChecksum = CheckSum(Buffer, MessageSize);

  Buffer[MessageSize] = MessageChecksum;

  return MessageSize + 1;
}


uint8_t ACDECODER::CheckSum(uint8_t *Buffer, uint8_t len) {
  uint8_t sum = 0;
  uint8_t i;

  for (i = 0; i < len; i++) {
    sum += Buffer[i];
  }

  sum = 0xfc - sum;
  sum = sum & 0xff;

  return sum;
}

bool ACDECODER::IS_BIT_SET(uint8_t value, uint8_t bit) {
  return (((value) & (1U << (bit))) != 0);
}


uint16_t ACDECODER::ExtractUInt16(uint8_t *Buffer, uint8_t Index) {
  uint16_t Value = (Buffer[Index] << 8) + Buffer[Index + 1];
  return Value;
}