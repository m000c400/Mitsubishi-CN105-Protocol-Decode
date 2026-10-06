#include "EcodanDecoder.h"
#include <cstdio>
#include <ESPTelnet.h>
extern ESPTelnet TelnetServer;
#include "Debug.h"


uint8_t Array0x01[] = {};
uint8_t Array0x02[] = {};
uint8_t Array0x03[] = {};
uint8_t Array0x04[] = {};
uint8_t Array0x05[] = {};
uint8_t Array0x06[] = {};
uint8_t Array0x07[] = {};
uint8_t Array0x08[] = {};
uint8_t Array0x09[] = {};
uint8_t Array0x0b[] = {};
uint8_t Array0x0c[] = {};
uint8_t Array0x0d[] = {};
uint8_t Array0x0e[] = {};
uint8_t Array0x0f[] = {};
uint8_t Array0x10[] = {};
uint8_t Array0x11[] = {};
uint8_t Array0x12[] = {};
uint8_t Array0x13[] = {};
uint8_t Array0x14[] = {};
uint8_t Array0x15[] = {};
uint8_t Array0x16[] = {};
uint8_t Array0x17[] = {};
uint8_t Array0x18[] = {};
uint8_t Array0x19[] = {};
uint8_t Array0x1a[] = {};
uint8_t Array0x1b[] = {};
uint8_t Array0x1c[] = {};
uint8_t Array0x1d[] = {};
uint8_t Array0x1e[] = {};
uint8_t Array0x1f[] = {};
uint8_t Array0x20[] = {};
uint8_t Array0x26[] = {};
uint8_t Array0x27[] = {};
uint8_t Array0x28[] = {};
uint8_t Array0x29[] = {};
uint8_t Array0xa1[] = {};
uint8_t Array0xa2[] = {};
uint8_t Array0xa3[] = {};
uint8_t Array0xc9[] = {};
uint8_t Array0x32[] = {};
uint8_t Array0x33[] = {};
uint8_t Array0x34[] = {};
uint8_t Array0x35[] = {};

uint8_t BufferArray[][17] = { {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {} };


ECODANDECODER::ECODANDECODER(void) {
  memset(&RxMessage, 0, sizeof(MessageStruct));
  memset(&Status, 0, sizeof(EcodanStatus));

  Preamble[0] = 0x02;
  Preamble[1] = 0x7a;
}


uint8_t ECODANDECODER::Process(uint8_t c) {
  uint8_t ReturnValue = false;

  if (BuildRxMessage(&RxMessage, c)) {
    ReturnValue = true;
    if (RxMessage.PacketType == GET_RESPONSE) {
      switch (RxMessage.Payload[0]) {
        case 0x01:
          Process0x01(RxMessage.Payload, &Status);
          break;
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
        case 0x07:
          Process0x07(RxMessage.Payload, &Status);
          break;
        case 0x08:
          Process0x08(RxMessage.Payload, &Status);
          break;
        case 0x09:
          Process0x09(RxMessage.Payload, &Status);
          break;
        case 0x0b:
          Process0x0B(RxMessage.Payload, &Status);
          break;
        case 0x0c:
          Process0x0C(RxMessage.Payload, &Status);
          break;
        case 0x0d:
          Process0x0D(RxMessage.Payload, &Status);
          break;
        case 0x0e:
          Process0x0E(RxMessage.Payload, &Status);
          break;
        case 0x0f:
          Process0x0F(RxMessage.Payload, &Status);
          break;
        case 0x10:
          Process0x10(RxMessage.Payload, &Status);
          break;
        case 0x11:
          Process0x11(RxMessage.Payload, &Status);
          break;
        case 0x12:
          Process0x12(RxMessage.Payload, &Status);
          break;
        case 0x13:
          Process0x13(RxMessage.Payload, &Status);
          break;
        case 0x14:
          Process0x14(RxMessage.Payload, &Status);
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
        case 0x1a:
          Process0x1a(RxMessage.Payload, &Status);
          break;
        case 0x1b:
          Process0x1b(RxMessage.Payload, &Status);
          break;
        case 0x1c:
          Process0x1c(RxMessage.Payload, &Status);
          break;
        case 0x1d:
          Process0x1d(RxMessage.Payload, &Status);
          break;
        case 0x1e:
          Process0x1e(RxMessage.Payload, &Status);
          break;
        case 0x1f:
          Process0x1f(RxMessage.Payload, &Status);
          break;
        case 0x20:
          Process0x20(RxMessage.Payload, &Status);
          break;
        case 0x26:
          Process0x26(RxMessage.Payload, &Status);
          break;
        case 0x27:
          Process0x27(RxMessage.Payload, &Status);
          break;
        case 0x28:
          Process0x28(RxMessage.Payload, &Status);
          break;
        case 0x29:
          Process0x29(RxMessage.Payload, &Status);
          break;
        case 0xa1:
          Process0xA1(RxMessage.Payload, &Status);
          break;
        case 0xa2:
          Process0xA2(RxMessage.Payload, &Status);
          break;
        case 0xa3:
          Process0xA3(RxMessage.Payload, &Status);
          break;
      }
    } else if (RxMessage.PacketType == GET_ABOUT_RESPONSE) {
      switch (RxMessage.Payload[0]) {
        case 0xc9:
          Process0xC9(RxMessage.Payload, &Status);
          break;
      }
    } else if (RxMessage.PacketType == SET_RESPONSE) {
      WriteOK(RxMessage.Payload, &Status);
    }
  }
  return ReturnValue;
}

uint8_t ECODANDECODER::BuildRxMessage(MessageStruct *Message, uint8_t c) {
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
            //DEBUG_PRINTLN("Unknown PacketType");
            BufferPos = 0;
            return false;  // Unknown Packet Type
        }
        break;

      case 2:
        if (c != Preamble[0]) {
          //DEBUG_PRINTLN("Preamble 1 Error");
          BufferPos = 0;
          return false;
        }
        break;

      case 3:
        if (c != Preamble[1]) {
          //DEBUG_PRINTLN("Preamble 1 Error");
          BufferPos = 0;
          return false;
        }
        break;

      case 4:
        PayloadSize = c;
        if (c > MAXDATABLOCKSIZE) {
          //DEBUG_PRINTLN("Oversize Payload");
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
      //DEBUG_PRINTLN("CS OK");
      Message->SyncByte = Buffer[0];
      Message->PacketType = Buffer[1];
      Message->Preamble[0] = Buffer[2];
      Message->Preamble[1] = Buffer[3];
      Message->PayloadSize = Buffer[4];
      Message->Checksum = c;
      memcpy(Message->Payload, &Buffer[5], Message->PayloadSize);
      return true;
    } else {
      //DEBUG_PRINTLN("Checksum Fail");
      return false;
    }
  }
  return false;
}


void ECODANDECODER::Process0x01(uint8_t *Buffer, EcodanStatus *Status) {
  uint8_t Year, Month, Day;
  uint8_t Hour, Min, Sec;

  for (int i = 1; i < 16; i++) {
    Array0x01[i] = Buffer[i];
  }

  Year = Buffer[1];
  Month = Buffer[2];
  Day = Buffer[3];
  Hour = Buffer[4];
  Min = Buffer[5];
  Sec = Buffer[6];

  Status->DateTimeStamp.tm_year = 100 + Year;
  Status->DateTimeStamp.tm_mon = Month - 1;
  Status->DateTimeStamp.tm_mday = Day;
  Status->DateTimeStamp.tm_hour = Hour;
  Status->DateTimeStamp.tm_min = Min;
  Status->DateTimeStamp.tm_sec = Sec;

  snprintf(Status->FTCSoftware, 6, "%02X.%02X", Buffer[7], Buffer[8]);
  Status->SyncTime = true;  // Allow Time to Sync with ESP
}

void ECODANDECODER::Process0x02(uint8_t *Buffer, EcodanStatus *Status) {
  uint8_t Defrost, ThermostatZ1, ThermostatZ2;

  Status->LastDefrost = Status->Defrost;

  for (int i = 1; i < 16; i++) {
    Array0x02[i] = Buffer[i];
  }

  ThermostatZ1 = Buffer[1];
  ThermostatZ2 = Buffer[2];
  Defrost = Buffer[3];

  Status->ThermostatZ1 = ThermostatZ1;
  Status->ThermostatZ2 = ThermostatZ2;
  Status->Defrost = Defrost;
}

void ECODANDECODER::Process0x03(uint8_t *Buffer, EcodanStatus *Status) {
  uint8_t RefrigeFltCode, ErrCode1, ErrCode2, FltCode1, FltCode2;
  uint8_t TwoZone_Z1Working, TwoZone_Z2Working;
  for (int i = 1; i < 16; i++) {
    Array0x03[i] = Buffer[i];
  }

  RefrigeFltCode = Buffer[1];
  ErrCode1 = Buffer[2];
  ErrCode2 = Buffer[3];
  FltCode1 = Buffer[4];
  FltCode2 = Buffer[5];

  if (Buffer[8] == 1) {
    TwoZone_Z1Working = 1;
    TwoZone_Z2Working = 1;
  } else if (Buffer[8] == 2) {
    TwoZone_Z1Working = 1;
    TwoZone_Z2Working = 0;
  } else if (Buffer[8] == 3) {
    TwoZone_Z1Working = 0;
    TwoZone_Z2Working = 1;
  } else {
    TwoZone_Z1Working = 0;
    TwoZone_Z2Working = 0;
  }

  Status->RefrigeFltCode = RefrigeFltCode;
  Status->ErrCode1 = ErrCode1;
  Status->ErrCode2 = ErrCode2;
  Status->FltCode1 = FltCode1;
  Status->FltCode2 = FltCode2;
  Status->TwoZone_Z1Working = TwoZone_Z1Working;
  Status->TwoZone_Z2Working = TwoZone_Z2Working;
}


void ECODANDECODER::Process0x04(uint8_t *Buffer, EcodanStatus *Status) {
  uint8_t CompressorFrequency;

  for (int i = 1; i < 16; i++) {
    Array0x04[i] = Buffer[i];
  }

  CompressorFrequency = Buffer[1];

  Status->CompressorFrequency = CompressorFrequency;
  Status->Compressor1Freq = Buffer[2];
  Status->Compressor2Freq = Buffer[3];
  Status->Compressor3Freq = Buffer[4];
  Status->Compressor4Freq = Buffer[5];
}


void ECODANDECODER::Process0x05(uint8_t *Buffer, EcodanStatus *Status) {
  uint8_t HotWaterBoost, DHWActive;
  uint8_t DHWHeatSourcePhase;

  for (int i = 1; i < 16; i++) {
    Array0x05[i] = Buffer[i];
  }

  //if (Buffer[5] == 7)         // Eco Hot Water Running
  //HeatSource = Buffer[6];     // 0 = H/P, 1 = IH, 2 = BH, 3 = IH + BH, 4 = Boiler but doesn't seem to change
  DHWHeatSourcePhase = Buffer[7];  // Heat Source Phase for DHW (0 = Normal, 1 = HP, 2 = Immersion or Booster)
  if (DHWHeatSourcePhase != 0) {
    DHWActive = 1;
  } else {
    DHWActive = 0;
  }
  //Unknown = Buffer[9];        // Always 6?

  //Status->HeatSource = HeatSource;
  Status->DHWHeatSourcePhase = DHWHeatSourcePhase;
  Status->DHWActive = DHWActive;
}


void ECODANDECODER::Process0x06(uint8_t *Buffer, EcodanStatus *Status) {
  for (int i = 1; i < 16; i++) {
    Array0x06[i] = Buffer[i];
  }
}


void ECODANDECODER::Process0x07(uint8_t *Buffer, EcodanStatus *Status) {
  uint8_t InputPower, OutputPower;
  float EnergyConsumedIncreasing;

  for (int i = 1; i < 16; i++) {
    Array0x07[i] = Buffer[i];
  }

  InputPower = Buffer[4];
  OutputPower = Buffer[6];
  EnergyConsumedIncreasing = ExtractUInt16(Buffer, 11) / 10.0f;

  Status->InputPower = InputPower;
  Status->OutputPower = OutputPower;
  Status->EnergyConsumedIncreasing = EnergyConsumedIncreasing;
}


void ECODANDECODER::Process0x08(uint8_t *Buffer, EcodanStatus *Status) {
  for (int i = 1; i < 16; i++) {
    Array0x08[i] = Buffer[i];
  }

  // To be confirmed - LEVA & LEVB for FTC7
}


void ECODANDECODER::Process0x09(uint8_t *Buffer, EcodanStatus *Status) {
  float Zone1TempSetpoint, Zone2TempSetpoint;
  float Z1FlowSetpoint, Z2FlowSetpoint, LegionellaSetpoint;
  float HWTempDrop, FlowTempMax, FlowTempMin;

  for (int i = 1; i < 16; i++) {
    Array0x09[i] = Buffer[i];
  }

  Zone1TempSetpoint = ((float)ExtractUInt16(Buffer, 1) / 100);
  Zone2TempSetpoint = ((float)ExtractUInt16(Buffer, 3) / 100);
  Z1FlowSetpoint = ((float)ExtractUInt16(Buffer, 5) / 100);
  Z2FlowSetpoint = ((float)ExtractUInt16(Buffer, 7) / 100);
  LegionellaSetpoint = ((float)ExtractUInt16(Buffer, 9) / 100);

  HWTempDrop = ExtractUInt8_v2(Buffer, 11);
  FlowTempMax = ExtractUInt8_v2(Buffer, 12);
  FlowTempMin = ExtractUInt8_v2(Buffer, 13);

  Status->Zone1TemperatureSetpoint = Zone1TempSetpoint;
  Status->Zone2TemperatureSetpoint = Zone2TempSetpoint;
  Status->Zone1FlowTemperatureSetpoint = Z1FlowSetpoint;
  Status->Zone2FlowTemperatureSetpoint = Z2FlowSetpoint;
  Status->LegionellaSetpoint = LegionellaSetpoint;
  Status->HotWaterMaximumTempDrop = HWTempDrop;
  Status->FlowTempMax = FlowTempMax;
  Status->FlowTempMin = FlowTempMin;
}

void ECODANDECODER::Process0x0B(uint8_t *Buffer, EcodanStatus *Status) {
  float fZone1, fZone2, fOutside;
  float RefrigeTemp, LiquidTemp;

  for (int i = 1; i < 16; i++) {
    Array0x0b[i] = Buffer[i];
  }

  if (Buffer[1] != 0xf0) {  // Extract if zone connected (not default value)
    fZone1 = ((float)ExtractUInt16(Buffer, 1) / 100);
  } else {
    fZone1 = 0;
  }
  if (Buffer[3] != 0xf0) {  // Extract if zone connected (not default value)
    fZone2 = ((float)ExtractUInt16(Buffer, 3) / 100);
  } else {
    fZone2 = 0;
  }

  //Unknown = ((float)ExtractUInt16(Buffer, 5) / 100);
  RefrigeTemp = ((float)ExtractUInt16_Signed(Buffer, 8) / 100);
  //LiquidTemp = ExtractUInt8_v1(Buffer, 10);
  fOutside = ExtractUInt8_v1(Buffer, 11);

  Status->Zone1Temperature = fZone1;
  Status->Zone2Temperature = fZone2;
  Status->OutsideTemperature = fOutside;  // TH7
  //Status->LiquidTemp = LiquidTemp;        // TH2
  Status->RefrigeTemp = RefrigeTemp;  //
}

void ECODANDECODER::Process0x0C(uint8_t *Buffer, EcodanStatus *Status) {
  float fWaterHeatingFeed, fWaterHeatingReturn, fHotWater, fHotWaterTHW5A;

  for (int i = 1; i < 16; i++) {
    Array0x0c[i] = Buffer[i];
  }

  fWaterHeatingFeed = ((float)ExtractUInt16(Buffer, 1) / 100);
  fWaterHeatingReturn = ((float)ExtractUInt16(Buffer, 4) / 100);
  fHotWater = ((float)ExtractUInt16(Buffer, 7) / 100);
  fHotWaterTHW5A = ((float)ExtractUInt16(Buffer, 10) / 100);

  Status->HeaterOutputFlowTemperature = fWaterHeatingFeed;         // THW1
  Status->HeaterReturnFlowTemperature = fWaterHeatingReturn;       // THW2
  Status->HeaterDeltaT = fWaterHeatingFeed - fWaterHeatingReturn;  // Flow - Return Temp
  Status->HotWaterTemperature = fHotWater;                         // THW5
  Status->HotWaterTemperatureTHW5A = fHotWaterTHW5A;               // THW5A
}

void ECODANDECODER::Process0x0D(uint8_t *Buffer, EcodanStatus *Status) {
  float Zone1FlowTemperature, Zone1ReturnTemperature, Zone2FlowTemperature, Zone2ReturnTemperature;

  for (int i = 1; i < 16; i++) {
    Array0x0d[i] = Buffer[i];
  }

  Zone1FlowTemperature = ((float)ExtractUInt16(Buffer, 1) / 100);     // Zone 1 Flow (THW6)
  Zone1ReturnTemperature = ((float)ExtractUInt16(Buffer, 4) / 100);   // Zone 1 Return (THW7)
  Zone2FlowTemperature = ((float)ExtractUInt16(Buffer, 7) / 100);     // Zone 2 Flow (THW8)
  Zone2ReturnTemperature = ((float)ExtractUInt16(Buffer, 10) / 100);  // Zone 2 Return (THW9)

  Status->Zone1FlowTemperature = Zone1FlowTemperature;
  Status->Zone1ReturnTemperature = Zone1ReturnTemperature;
  Status->Zone2FlowTemperature = Zone2FlowTemperature;
  Status->Zone2ReturnTemperature = Zone2ReturnTemperature;
}

void ECODANDECODER::Process0x0E(uint8_t *Buffer, EcodanStatus *Status) {
  float ExternalBoilerFlowTemperature, ExternalBoilerReturnTemperature;

  for (int i = 1; i < 16; i++) {
    Array0x0e[i] = Buffer[i];
  }

  ExternalBoilerFlowTemperature = ((float)ExtractUInt16(Buffer, 1) / 100);    // Suspected (THWB1)
  ExternalBoilerReturnTemperature = ((float)ExtractUInt16(Buffer, 4) / 100);  // Suspected (THWB2)

  Status->ExternalBoilerFlowTemperature = ExternalBoilerFlowTemperature;
  Status->ExternalBoilerReturnTemperature = ExternalBoilerReturnTemperature;
}


void ECODANDECODER::Process0x0F(uint8_t *Buffer, EcodanStatus *Status) {  // FTC6 & 7 Only Parameters
  float MixingTemperature, CondensingTemp;
  bool OutdoorExtendedSensors = false;

  for (int i = 1; i < 16; i++) {
    Array0x0f[i] = Buffer[i];
  }

  MixingTemperature = ((float)ExtractUInt16(Buffer, 1) / 100);      // Mixing Tank Temperature (THW10)
  CondensingTemp = ((float)ExtractUInt16_Signed(Buffer, 4) / 100);  // Condensing Temperature
  //Unknown = ExtractUInt8_v1(Buffer, 6);

  Status->MixingTemperature = MixingTemperature;
  Status->CondensingTemp = CondensingTemp;

  for (int j = 7; j < 15; j++) {
    if (Buffer[j] != 0x00) {
      OutdoorExtendedSensors = true;
      Status->OutdoorExtendedSensors = OutdoorExtendedSensors;
    }
  }
  if (Status->FTCVersion == FTC7 && OutdoorExtendedSensors) {  // FTC7 with Extended Outdoor Unit Sensors Parameters
    Status->TH4Discharge = ExtractUInt8_v4(Buffer, 7);         // FTC7 Only Parameters
    Status->LiquidTemp = ExtractUInt8_v3(Buffer, 8);           // FTC7 Only Parameters
    Status->TH6Pipe = ExtractUInt8_v3(Buffer, 9);              // FTC7 Only Parameters
    Status->TH32Pipe = ExtractUInt8_v3(Buffer, 10);            // FTC7 Only Parameters
    Status->TH8HeatSink = ExtractUInt8_v5(Buffer, 11);         // FTC7 Only Parameters
    Status->TH33 = ExtractUInt8_v5(Buffer, 12);                // FTC7 Only Parameters
    Status->Superheat = ExtractUInt8_v4(Buffer, 13);           // FTC7 Only Parameters
    Status->Subcool = ExtractUInt8_v3(Buffer, 14);             // FTC7 Only Parameters
  }
}

void ECODANDECODER::Process0x10(uint8_t *Buffer, EcodanStatus *Status) {
  uint8_t Zone1ThermostatDemand, Zone2ThermostatDemand, OutdoorThermostatDemand;

  for (int i = 1; i < 16; i++) {
    Array0x10[i] = Buffer[i];
  }

  Zone1ThermostatDemand = Buffer[1];
  Zone2ThermostatDemand = Buffer[2];
  OutdoorThermostatDemand = Buffer[3];

  Status->Zone1ThermostatDemand = Zone1ThermostatDemand;
  Status->Zone2ThermostatDemand = Zone2ThermostatDemand;
  Status->OutdoorThermostatDemand = OutdoorThermostatDemand;
}


void ECODANDECODER::Process0x11(uint8_t *Buffer, EcodanStatus *Status) {
  uint8_t DipSwitch1, DipSwitch2, DipSwitch3, DipSwitch4, DipSwitch5, DipSwitch6, DipSwitch7;
  bool HasCooling, Has2Zone, Simple2Zone;

  for (int i = 1; i < 16; i++) {
    Array0x11[i] = Buffer[i];
  }

  DipSwitch1 = Buffer[1];
  DipSwitch2 = Buffer[3];
  DipSwitch3 = Buffer[5];
  DipSwitch4 = Buffer[7];
  DipSwitch5 = Buffer[9];
  DipSwitch6 = Buffer[11];
  DipSwitch7 = Buffer[13];  // FTC7 only

  // Bitmask Translation
  if (IS_BIT_SET(DipSwitch2, 3)) {  // SW2-4
    HasCooling = true;
  } else {
    HasCooling = false;
  }

  if (IS_BIT_SET(DipSwitch3, 5) && !IS_BIT_SET(DipSwitch2, 6)) {  // SW3-6 True, SW2-7 False
    Has2Zone = true;
    Simple2Zone = true;
  } else if (IS_BIT_SET(DipSwitch2, 5) || IS_BIT_SET(DipSwitch2, 6)) {  // SW2-6 or SW2-7 True
    Has2Zone = true;
    Simple2Zone = false;
  } else {
    Has2Zone = false;
    Simple2Zone = false;
  }

  Status->DipSwitch1 = DipSwitch1;
  Status->DipSwitch2 = DipSwitch2;
  Status->DipSwitch3 = DipSwitch3;
  Status->DipSwitch4 = DipSwitch4;
  Status->DipSwitch5 = DipSwitch5;
  Status->DipSwitch6 = DipSwitch6;
  Status->DipSwitch7 = DipSwitch7;
  Status->Has2Zone = Has2Zone;
  Status->Simple2Zone = Simple2Zone;
  Status->HasCooling = HasCooling;
  Status->HasAnsweredDips = true;
}

void ECODANDECODER::Process0x12(uint8_t *Buffer, EcodanStatus *Status) {
  for (int i = 1; i < 16; i++) {
    Array0x12[i] = Buffer[i];
  }
}


void ECODANDECODER::Process0x13(uint8_t *Buffer, EcodanStatus *Status) {
  uint32_t RunHours;
  bool CompressorRunning;

  for (int i = 1; i < 16; i++) {
    Array0x13[i] = Buffer[i];
  }

  CompressorRunning = Buffer[1];  // 0 When off, on/off 1's when running

  RunHours = Buffer[4];
  RunHours = RunHours << 8;
  RunHours += Buffer[5];
  RunHours *= 100;
  RunHours += Buffer[3];

  Status->CompressorRunning = CompressorRunning;
  Status->RunHours = RunHours;
}


void ECODANDECODER::Process0x14(uint8_t *Buffer, EcodanStatus *Status) {
  uint8_t FlowRate;
  uint8_t Booster1Active, Booster2Active, Booster2PlusActive, ImmersionActive;

  for (int i = 1; i < 16; i++) {
    Array0x14[i] = Buffer[i];
  }

  Booster1Active = Buffer[2];
  Booster2Active = Buffer[3];
  Booster2PlusActive = Buffer[4];
  ImmersionActive = Buffer[5];
  FlowRate = Buffer[12];

  Status->Booster1Active = Booster1Active;
  Status->Booster2Active = Booster2Active;
  Status->Booster2PlusActive = Booster2PlusActive;
  Status->ImmersionActive = ImmersionActive;
  Status->PrimaryFlowRate = FlowRate;
}


void ECODANDECODER::Process0x15(uint8_t *Buffer, EcodanStatus *Status) {
  uint8_t PrimaryWaterPump, PrimaryWaterPumpSpeed, PumpPower, WaterPump2, WaterPump3a, ThreeWayValve, ThreeWayValve2, MixingStep;

  for (int i = 1; i < 16; i++) {
    Array0x15[i] = Buffer[i];
  }

  PrimaryWaterPump = Buffer[1];  // 01 when running (Primary Water Pump)

  if (Buffer[2] == 0x34) {
    PrimaryWaterPumpSpeed = 1;
  } else if (Buffer[2] == 0x29) {
    PrimaryWaterPumpSpeed = 2;
  } else if (Buffer[2] == 0x1F) {
    PrimaryWaterPumpSpeed = 3;
  } else if (Buffer[2] == 0x14) {
    PrimaryWaterPumpSpeed = 4;
  } else if (Buffer[2] == 0x0) {
    PrimaryWaterPumpSpeed = 5;
  } else if (Buffer[2] == 0x64) {
    PrimaryWaterPumpSpeed = 0;
  }

  PumpPower = Buffer[3];  // Primary Power Power Est.
  // 74-76 = Warning
  // 84-86 = Electrical Error
  // 89-91 = Blockage
  // 255 = Stopped


  WaterPump2 = Buffer[4];      // Water Pump 2 Active
  WaterPump3a = Buffer[5];     // Complex Zone2 Water Pump OUT3
  ThreeWayValve = Buffer[6];   // 3 Way Valve Position
  ThreeWayValve2 = Buffer[7];  // 3 Way Valve 2 Position
  MixingStep = Buffer[10];     // Mixing Valve Step

  Status->PrimaryWaterPump = PrimaryWaterPump;
  Status->PrimaryWaterPumpSpeed = PrimaryWaterPumpSpeed;
  Status->PumpPower = PumpPower;
  Status->WaterPump2 = WaterPump2;
  Status->WaterPump3a = WaterPump3a;
  Status->ThreeWayValve = ThreeWayValve;
  Status->ThreeWayValve2 = ThreeWayValve2;
  Status->MixingStep = MixingStep;
}


void ECODANDECODER::Process0x16(uint8_t *Buffer, EcodanStatus *Status) {
  uint8_t WaterPump4, WaterPump3b, WaterPump13;

  for (int i = 1; i < 16; i++) {
    Array0x16[i] = Buffer[i];
  }

  WaterPump4 = Buffer[1];   // DHW Pump connected to CPN4
  WaterPump13 = Buffer[2];  // Zone Pump connected to OUT13
  WaterPump3b = Buffer[3];  // Zone Pump connected to OUT3

  Status->WaterPump4 = WaterPump4;
  Status->WaterPump3b = WaterPump3b;
  Status->WaterPump13 = WaterPump13;
}

void ECODANDECODER::Process0x17(uint8_t *Buffer, EcodanStatus *Status) {
  for (int i = 1; i < 16; i++) {
    Array0x17[i] = Buffer[i];
  }
}

void ECODANDECODER::Process0x18(uint8_t *Buffer, EcodanStatus *Status) {
  for (int i = 1; i < 16; i++) {
    Array0x18[i] = Buffer[i];
  }
}

void ECODANDECODER::Process0x19(uint8_t *Buffer, EcodanStatus *Status) {
  for (int i = 1; i < 16; i++) {
    Array0x19[i] = Buffer[i];
  }
}

void ECODANDECODER::Process0x1a(uint8_t *Buffer, EcodanStatus *Status) {
  for (int i = 1; i < 16; i++) {
    Array0x1a[i] = Buffer[i];
  }
}

void ECODANDECODER::Process0x1b(uint8_t *Buffer, EcodanStatus *Status) {
  for (int i = 1; i < 16; i++) {
    Array0x1b[i] = Buffer[i];
  }
}

void ECODANDECODER::Process0x1c(uint8_t *Buffer, EcodanStatus *Status) {
  for (int i = 1; i < 16; i++) {
    Array0x1c[i] = Buffer[i];
  }
}

void ECODANDECODER::Process0x1d(uint8_t *Buffer, EcodanStatus *Status) {
  for (int i = 1; i < 16; i++) {
    Array0x1d[i] = Buffer[i];
  }
}

void ECODANDECODER::Process0x1e(uint8_t *Buffer, EcodanStatus *Status) {
  for (int i = 1; i < 16; i++) {
    Array0x1e[i] = Buffer[i];
  }
}

void ECODANDECODER::Process0x1f(uint8_t *Buffer, EcodanStatus *Status) {
  for (int i = 1; i < 16; i++) {
    Array0x1f[i] = Buffer[i];
  }
}

void ECODANDECODER::Process0x20(uint8_t *Buffer, EcodanStatus *Status) {
  for (int i = 1; i < 16; i++) {
    Array0x20[i] = Buffer[i];
  }
}

void ECODANDECODER::Process0x26(uint8_t *Buffer, EcodanStatus *Status) {
  float DHWSetpoint;
  uint8_t SystemPowerMode, SystemOperationMode, HotWaterPowerMode;
  uint8_t HeatingControlModeZone1, HeatingControlModeZone2, HotWaterControlMode;

  for (int i = 1; i < 16; i++) {
    Array0x26[i] = Buffer[i];
  }

  Status->LastSystemOperationMode = Status->SystemOperationMode;

  SystemPowerMode = Buffer[3];
  SystemOperationMode = Buffer[4];
  HotWaterControlMode = Buffer[5];
  HeatingControlModeZone1 = Buffer[6];
  HeatingControlModeZone2 = Buffer[7];
  DHWSetpoint = ((float)ExtractUInt16(Buffer, 8) / 100);
  //Zone1FlowSetpoint = ((float)ExtractUInt16(Buffer, 10) / 100);   // Duplicate of 0x09
  //Zone2FlowSetpoint = ((float)ExtractUInt16(Buffer, 12) / 100);   // Duplicate of 0x09
  //MRCProhibit = Buffer[14];

  Status->SystemPowerMode = SystemPowerMode;
  Status->SystemOperationMode = SystemOperationMode;
  Status->HotWaterControlMode = HotWaterControlMode;
  Status->HeatingControlModeZ1 = HeatingControlModeZone1;
  Status->HeatingControlModeZ2 = HeatingControlModeZone2;
  Status->HotWaterSetpoint = DHWSetpoint;
}

void ECODANDECODER::Process0x27(uint8_t *Buffer, EcodanStatus *Status) {
  for (int i = 1; i < 16; i++) {
    Array0x27[i] = Buffer[i];
  }
}


void ECODANDECODER::Process0x28(uint8_t *Buffer, EcodanStatus *Status) {
  uint8_t HotWaterBoostActive, HolidayModeActive, ProhibitDHW;
  uint8_t ProhibitHeatingZ1, ProhibitHeatingZ2;
  uint8_t ProhibitCoolingZ1, ProhibitCoolingZ2;
  uint8_t SvrControlMode;

  for (int i = 1; i < 16; i++) {
    if (i == 10) {
      Array0x28[i] = 0;
    } else {
      Array0x28[i] = Buffer[i];
    }
  }

  HotWaterBoostActive = Buffer[3];  //Forced DHW Mode (Booster)
  HolidayModeActive = Buffer[4];    // Holiday Mode
  ProhibitDHW = Buffer[5];          //Prohibit DHW (by Timer or Manually)
  ProhibitHeatingZ1 = Buffer[6];    //Prohibit Heating Zone1
  ProhibitCoolingZ1 = Buffer[7];    //Prohibit Cooling Zone1
  ProhibitHeatingZ2 = Buffer[8];    //Prohibit Heating Zone2
  ProhibitCoolingZ2 = Buffer[9];    //Prohibit Cooling Zone2
  SvrControlMode = Buffer[10];      //Server Control Mode

  Status->HotWaterBoostActive = HotWaterBoostActive;  // Hot Water Forced (Boost) Active
  Status->HolidayModeActive = HolidayModeActive;
  Status->ProhibitDHW = ProhibitDHW;  // Check if inhibit or Timer
  Status->ProhibitHeatingZ1 = ProhibitHeatingZ1;
  Status->ProhibitCoolingZ1 = ProhibitCoolingZ1;
  Status->ProhibitHeatingZ2 = ProhibitHeatingZ2;
  Status->ProhibitCoolingZ2 = ProhibitCoolingZ2;
  Status->SvrControlMode = SvrControlMode;
}

void ECODANDECODER::Process0x29(uint8_t *Buffer, EcodanStatus *Status) {
  uint8_t HeatCool;
  //float fZone1TempSetpoint, fZone2TempSetpoint;

  for (int i = 1; i < 16; i++) {
    Array0x29[i] = Buffer[i];
  }

  HeatCool = Buffer[3];
  //fZone1TempSetpoint = ((float)ExtractUInt16(Buffer, 4) / 100);
  //fZone2TempSetpoint = ((float)ExtractUInt16(Buffer, 6) / 100);

  Status->HeatCool = HeatCool;
  //Status->Zone1TemperatureSetpoint = fZone1TempSetpoint;
  //Status->Zone2TemperatureSetpoint = fZone2TempSetpoint;
}

void ECODANDECODER::Process0xA1(uint8_t *Buffer, EcodanStatus *Status) {
  uint8_t Year, Month, Day;
  float ConsumedHeating, ConsumedCooling, ConsumedHotWater;

  for (int i = 1; i < 16; i++) {
    Array0xa1[i] = Buffer[i];
  }

  Year = Buffer[1];
  Month = Buffer[2];
  Day = Buffer[3];

  ConsumedHeating = ExtractEnergy(Buffer, 4);
  ConsumedCooling = ExtractEnergy(Buffer, 7);
  ConsumedHotWater = ExtractEnergy(Buffer, 10);

  Status->ConsumedDateTimeStamp.tm_year = 100 + Year;
  Status->ConsumedDateTimeStamp.tm_mon = Month - 1;
  Status->ConsumedDateTimeStamp.tm_mday = Day;

  Status->ConsumedHeatingEnergy = ConsumedHeating;
  Status->ConsumedCoolingEnergy = ConsumedCooling;
  Status->ConsumedHotWaterEnergy = ConsumedHotWater;
}

void ECODANDECODER::Process0xA2(uint8_t *Buffer, EcodanStatus *Status) {
  uint8_t Year, Month, Day;
  float DeliveredHeating, DeliveredCooling, DeliveredHotWater;

  for (int i = 1; i < 16; i++) {
    Array0xa2[i] = Buffer[i];
  }

  Year = Buffer[1];
  Month = Buffer[2];
  Day = Buffer[3];

  DeliveredHeating = ExtractEnergy(Buffer, 4);
  DeliveredCooling = ExtractEnergy(Buffer, 7);
  DeliveredHotWater = ExtractEnergy(Buffer, 10);

  Status->DeliveredDateTimeStamp.tm_year = 100 + Year;
  Status->DeliveredDateTimeStamp.tm_mon = Month - 1;
  Status->DeliveredDateTimeStamp.tm_mday = Day;

  Status->DeliveredHeatingEnergy = DeliveredHeating;
  Status->DeliveredCoolingEnergy = DeliveredCooling;
  Status->DeliveredHotWaterEnergy = DeliveredHotWater;
}


void ECODANDECODER::Process0xA3(uint8_t *Buffer, EcodanStatus *Status) {
  uint8_t ServiceCode;
  bool Write_To_Ecodan_OK;

  for (int i = 1; i < 16; i++) {
    Array0xa3[i] = Buffer[i];
  }
  if (Buffer[3] == 1 || Buffer[3] == 2) {  // Valid Reply is "1" or "2" (result)
    Write_To_Ecodan_OK = true;             // For de-queue
    Status->Write_To_Ecodan_OK = Write_To_Ecodan_OK;

    // Data Packets
    Status->LastServiceCodeNumber = ServiceCode = Buffer[2];  // Decode the reply to Update the correct Value

    // Process into the correct locations
    if (ServiceCode == 3) {
      Status->CompOpTimes = ExtractInt16_v2_Signed(Buffer, 4);  // Safe to parse as ExtractUInt16_v2 or *100 outside ESP
    } else if (ServiceCode == 4) {
      Status->TH4Discharge = ExtractInt16_v2_Signed(Buffer, 4);  // TH4
    } else if (ServiceCode == 5) {
      Status->LiquidTemp = ExtractInt16_v2_Signed(Buffer, 4);  //TH3
    } else if (ServiceCode == 6) {
      Status->TH32Pipe = ExtractInt16_v2_Signed(Buffer, 4);
    } else if (ServiceCode == 7) {
      Status->TH6Pipe = ExtractInt16_v2_Signed(Buffer, 4);
    } else if (ServiceCode == 8) {
      Status->TH33 = ExtractInt16_v2_Signed(Buffer, 4);
    } else if (ServiceCode == 10) {
      Status->TH8HeatSink = ExtractInt16_v2_Signed(Buffer, 4);
    } else if (ServiceCode == 12) {
      Status->Superheat = ExtractInt16_v2_Signed(Buffer, 4);
    } else if (ServiceCode == 13) {
      Status->Subcool = ExtractInt16_v2_Signed(Buffer, 4);
    } else if (ServiceCode == 14) {
      Status->CondensingTemp = ExtractInt16_v2_Signed(Buffer, 4);
    } else if (ServiceCode == 19) {
      Status->Fan1RPM = ExtractInt16_v2_Signed(Buffer, 4);  //Little endian
    } else if (ServiceCode == 20) {
      Status->Fan2RPM = ExtractInt16_v2_Signed(Buffer, 4);  //Little endian
    } else if (ServiceCode == 22) {
      Status->LEVA = ExtractInt16_v2_Signed(Buffer, 4);
    } else if (ServiceCode == 23) {
      Status->LEVB = ExtractInt16_v2_Signed(Buffer, 4);
    } else if (ServiceCode == 24) {
      Status->LEVC = ExtractInt16_v2_Signed(Buffer, 4);
      if (Status->LEVC != 5) {
        Status->HasR290DualComp = true;
      } else {
        Status->HasR290DualComp = false;
      }
    } else if (ServiceCode == 27) {
      Status->TH32 = ExtractInt16_v2_Signed(Buffer, 4);
      Status->HasGeodan = true;
    } else if (ServiceCode == 28) {
      Status->TH34 = ExtractInt16_v2_Signed(Buffer, 4);
      Status->HasGeodan = true;
    } else if (ServiceCode == 70) {
      Status->OutdoorUnitCapacity = Buffer[4];
    } else if (ServiceCode == 90) {
      snprintf(Status->OutdoorFirmware, 6, "%02X.%02X", Buffer[5], Buffer[4]);
    }
    Status->ServiceCodeReply = ExtractInt16_v2_Signed(Buffer, 4);
  } else if (Buffer[3] != 0) {  // FTC side done but response is Done (7) or Unknown (6)
    Write_To_Ecodan_OK = true;  // For de-queue
    Status->Write_To_Ecodan_OK = Write_To_Ecodan_OK;
  }
}


void ECODANDECODER::Process0xC9(uint8_t *Buffer, EcodanStatus *Status) {
  uint8_t FTCVersion, RefrigerantType;

  for (int i = 1; i < 16; i++) {
    Array0xc9[i] = Buffer[i];
  }

  FTCVersion = Buffer[6];
  RefrigerantType = Buffer[10];

  Status->FTCVersion = FTCVersion;
  Status->RefrigerantType = RefrigerantType;
}


void ECODANDECODER::WriteOK(uint8_t *Buffer, EcodanStatus *Status) {
  bool Write_To_Ecodan_OK;
  Write_To_Ecodan_OK = true;
  Status->Write_To_Ecodan_OK = Write_To_Ecodan_OK;
}


float ECODANDECODER::ExtractEnergy(uint8_t *Buffer, uint8_t index) {
  float Energy;

  Energy = (float)Buffer[index + 2];
  Energy = Energy / (float)100;
  Energy += (float)ExtractUInt16(Buffer, index);

  return Energy;
}

int16_t ECODANDECODER::ExtractInt16_v2_Signed(uint8_t *Buffer, uint8_t Index) {
  int16_t Value = (Buffer[Index + 1] << 8) + Buffer[Index];
  return Value;
}

float ECODANDECODER::ExtractUInt16_Signed(uint8_t *Buffer, uint8_t Index) {
  float Value = int16_t(Buffer[Index] << 8) + Buffer[Index + 1];
  return Value;
}

uint16_t ECODANDECODER::ExtractUInt16(uint8_t *Buffer, uint8_t Index) {
  uint16_t Value = (Buffer[Index] << 8) + Buffer[Index + 1];
  return Value;
}

uint16_t ECODANDECODER::ExtractUInt16_v2(uint8_t *Buffer, uint8_t Index) {  // Little Endian
  uint16_t Value = (Buffer[Index + 1] << 8) + Buffer[Index];
  return Value;
}

// Used for most single-byte floating point values
float ECODANDECODER::ExtractUInt8_v1(uint8_t *Buffer, uint8_t Index) {
  float Value = (Buffer[Index] / 2) - 40.0f;
  return Value;
}

float ECODANDECODER::ExtractUInt8_v2(uint8_t *Buffer, uint8_t Index) {
  float Value = (Buffer[Index] - 40.0f) / 2;
  return Value;
}

float ECODANDECODER::ExtractUInt8_v3(uint8_t *Buffer, uint8_t Index) {
  float Value = (Buffer[Index] / 2) - 39.0f;
  return Value;
}

float ECODANDECODER::ExtractUInt8_v4(uint8_t *Buffer, uint8_t Index) {
  float Value = Buffer[Index];
  return Value;
}

float ECODANDECODER::ExtractUInt8_v5(uint8_t *Buffer, uint8_t Index) {
  float Value = Buffer[Index] - 40.0f;
  return Value;
}

void ECODANDECODER::CreateBlankTxMessage(uint8_t PacketType, uint8_t PayloadSize) {
  CreateBlankMessageTemplate(&TxMessage, PacketType, PayloadSize);
}


void ECODANDECODER::PayloadWipe(void) {
  for (int i = 0; i < 16; i++) {
    TxMessage.Payload[i] = 0;
  }
}


void ECODANDECODER::CreateBlankMessageTemplate(MessageStruct *Message, uint8_t PacketType, uint8_t PayloadSize) {
  uint8_t i;

  memset((void *)Message, 0, sizeof(MessageStruct));

  Message->SyncByte = PACKET_SYNC;
  Message->PacketType = PacketType;
  Message->PayloadSize = PayloadSize;
  for (i = 0; i < PREAMBLESIZE; i++) {
    Message->Preamble[i] = Preamble[i];
  }
}

void ECODANDECODER::SetPayloadByte(uint8_t Data, uint8_t Location) {
  TxMessage.Payload[Location] = Data;
}

uint8_t ECODANDECODER::PrepareTxCommand(uint8_t *Buffer) {
  return PrepareCommand(&TxMessage, Buffer);
}

uint8_t ECODANDECODER::PrepareCommand(MessageStruct *Message, uint8_t *Buffer) {
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


uint8_t ECODANDECODER::CheckSum(uint8_t *Buffer, uint8_t len) {
  uint8_t sum = 0;
  uint8_t i;

  for (i = 0; i < len; i++) {
    sum += Buffer[i];
  }

  sum = 0xfc - sum;
  sum = sum & 0xff;

  return sum;
}



void ECODANDECODER::EncodeDHWSetpoint(float Setpoint) {
  uint8_t UpperByte, LowerByte;
  uint16_t ScaledTarget;

  TxMessage.Payload[0] = TX_MESSAGE_BASIC;
  TxMessage.Payload[1] = SET_HOT_WATER_SETPOINT;

  ScaledTarget = Setpoint * 100;
  UpperByte = (uint8_t)(ScaledTarget >> 8);
  LowerByte = (uint8_t)(ScaledTarget & 0x00ff);

  TxMessage.Payload[8] = UpperByte;
  TxMessage.Payload[9] = LowerByte;
}


void ECODANDECODER::EncodeControlMode(uint8_t ControlMode, uint8_t Zone) {
  TxMessage.Payload[0] = TX_MESSAGE_BASIC;
  TxMessage.Payload[1] = Zone;
  if (SET_HEATING_CONTROL_MODE_Z1 == Zone) {
    TxMessage.Payload[6] = ControlMode;
  }
  if (SET_HEATING_CONTROL_MODE_Z2 == Zone) {
    TxMessage.Payload[7] = ControlMode;
  }
}


void ECODANDECODER::EncodePower(uint8_t Power) {
  TxMessage.Payload[0] = TX_MESSAGE_BASIC;
  TxMessage.Payload[1] = SET_SYSTEM_POWER;
  TxMessage.Payload[3] = Power;
}


void ECODANDECODER::EncodeRoomThermostat(float Setpoint, uint8_t ControlMode, uint8_t Zone) {
  uint8_t UpperByte, LowerByte;
  uint16_t ScaledTarget;

  ScaledTarget = Setpoint * 100;
  UpperByte = (uint8_t)(ScaledTarget >> 8);
  LowerByte = (uint8_t)(ScaledTarget & 0x00ff);

  TxMessage.Payload[0] = TX_MESSAGE_ROOM_STAT;
  TxMessage.Payload[3] = (ControlMode == HEATING_CONTROL_MODE_COOL_ZONE_TEMP || ControlMode == HEATING_CONTROL_MODE_COOL_FLOW_TEMP || ControlMode == HEATING_CONTROL_MODE_COOL_COMPENSATION) ? 1 : 0;

  if (Zone == ZONE1) {
    TxMessage.Payload[1] = ZONE1_TSTAT;
    TxMessage.Payload[4] = UpperByte;
    TxMessage.Payload[5] = LowerByte;
  } else if (Zone == ZONE2) {
    TxMessage.Payload[1] = ZONE2_TSTAT;
    TxMessage.Payload[6] = UpperByte;
    TxMessage.Payload[7] = LowerByte;
  }
}


void ECODANDECODER::EncodeFlowTemperature(float Setpoint, uint8_t ControlMode, uint8_t Zone, float SetpointDHW) {
  uint8_t UpperByte, LowerByte;
  uint16_t ScaledTarget;

  TxMessage.Payload[0] = TX_MESSAGE_BASIC;
  TxMessage.Payload[1] = 0x00;
  TxMessage.Payload[2] = Zone;

  // DHW Anti 0 Setpoint
  ScaledTarget = SetpointDHW * 100;
  UpperByte = (uint8_t)(ScaledTarget >> 8);
  LowerByte = (uint8_t)(ScaledTarget & 0x00ff);

  TxMessage.Payload[8] = UpperByte;
  TxMessage.Payload[9] = LowerByte;


  if (Zone == ZONE1) {
    TxMessage.Payload[1] = 0x80;
    TxMessage.Payload[6] = ControlMode;  // Thermostat or Flow Setpoint Flag (Thermostat = 0x00, Flow = 0x01/0x03 for Cooling)

    ScaledTarget = Setpoint * 100;
    UpperByte = (uint8_t)(ScaledTarget >> 8);
    LowerByte = (uint8_t)(ScaledTarget & 0x00ff);

    TxMessage.Payload[10] = UpperByte;
    TxMessage.Payload[11] = LowerByte;

  } else if (Zone == ZONE2) {
    TxMessage.Payload[7] = ControlMode;  // Thermostat or Flow Setpoint Flag

    ScaledTarget = Setpoint * 100;
    UpperByte = (uint8_t)(ScaledTarget >> 8);
    LowerByte = (uint8_t)(ScaledTarget & 0x00ff);

    TxMessage.Payload[12] = UpperByte;
    TxMessage.Payload[13] = LowerByte;
  }
}


void ECODANDECODER::EncodeDHWMode(uint8_t Mode) {
  // DHW Mode Normal/Eco
  TxMessage.Payload[0] = TX_MESSAGE_BASIC;
  TxMessage.Payload[1] = SET_HOT_WATER_MODE;
  TxMessage.Payload[5] = Mode;
}

void ECODANDECODER::EncodeForcedDHW(uint8_t OnOff) {
  // DHW Boost Active
  TxMessage.Payload[0] = TX_MESSAGE_CONTROLLER;
  TxMessage.Payload[1] = TX_MESSAGE_SETTING_DHW_Flag;
  TxMessage.Payload[3] = OnOff;
}

void ECODANDECODER::EncodeHolidayMode(uint8_t OnOff) {
  // Holiday Mode Active
  TxMessage.Payload[0] = TX_MESSAGE_CONTROLLER;
  TxMessage.Payload[1] = TX_MESSAGE_SETTING_HOL_Flag;
  TxMessage.Payload[4] = OnOff;
  TxMessage.Payload[5] = OnOff;
}

void ECODANDECODER::EncodeFTCVersion() {
  // Get FTC Version
  TxMessage.Payload[0] = 0xC9;
  TxMessage.Payload[1] = 0x5F;
}


void ECODANDECODER::EncodeServerControlMode(uint8_t OnOff, uint8_t DHW, uint8_t Z1H, uint8_t Z1C, uint8_t Z2H, uint8_t Z2C) {
  TxMessage.Payload[0] = TX_MESSAGE_CONTROLLER;
  TxMessage.Payload[1] = TX_MESSAGE_SETTING_SRV_Flag | TX_MESSAGE_SETTING_DHW_INH_Flag | TX_MESSAGE_SETTING_HEAT_Z1_INH_Flag | TX_MESSAGE_SETTING_COOL_Z1_INH_Flag | TX_MESSAGE_SETTING_HEAT_Z2_INH_Flag | TX_MESSAGE_SETTING_COOL_Z2_INH_Flag;  // Write the flags where Zones are to be enabled
  TxMessage.Payload[5] = DHW;                                                                                                                                                                                                                    // Write the current status of DHW
  TxMessage.Payload[6] = Z1H;                                                                                                                                                                                                                    // Write the current status of Z1 Heating
  TxMessage.Payload[7] = Z1C;                                                                                                                                                                                                                    // Write the current status of Z1 Cooling
  TxMessage.Payload[8] = Z2H;                                                                                                                                                                                                                    // Write the current status of Z2 Heating
  TxMessage.Payload[9] = Z2C;                                                                                                                                                                                                                    // Write the current status of Z2 Cooling
  TxMessage.Payload[10] = OnOff;                                                                                                                                                                                                                 // Enter or Exit SCM Mode
}


void ECODANDECODER::EncodeProhibit(uint8_t Flags, uint8_t OnOff) {
  // Heating & DHW Inhibit "Server Control" Mode
  TxMessage.Payload[0] = TX_MESSAGE_CONTROLLER;
  TxMessage.Payload[1] = Flags;

  if ((Flags & TX_MESSAGE_SETTING_DHW_INH_Flag) == TX_MESSAGE_SETTING_DHW_INH_Flag) {
    TxMessage.Payload[5] = OnOff;
  }
  if ((Flags & TX_MESSAGE_SETTING_HEAT_Z1_INH_Flag) == TX_MESSAGE_SETTING_HEAT_Z1_INH_Flag) {
    TxMessage.Payload[6] = OnOff;
  }
  if ((Flags & TX_MESSAGE_SETTING_COOL_Z1_INH_Flag) == TX_MESSAGE_SETTING_COOL_Z1_INH_Flag) {
    TxMessage.Payload[7] = OnOff;
  }
  if ((Flags & TX_MESSAGE_SETTING_HEAT_Z2_INH_Flag) == TX_MESSAGE_SETTING_HEAT_Z2_INH_Flag) {
    TxMessage.Payload[8] = OnOff;
  }
  if ((Flags & TX_MESSAGE_SETTING_COOL_Z2_INH_Flag) == TX_MESSAGE_SETTING_COOL_Z2_INH_Flag) {
    TxMessage.Payload[9] = OnOff;
  }
}


void ECODANDECODER::EncodeMELCloud(uint8_t cmd) {
  TxMessage.Payload[0] = cmd;
  for (int i = 1; i < 16; i++) {
    if (cmd == 0x32) {
      TxMessage.Payload[i] = Array0x32[i];
    } else if (cmd == 0x33) {
      TxMessage.Payload[i] = Array0x33[i];
    } else if (cmd == 0x34) {
      //if (i == 1) { Array0x34[i] = Array0x34[i] & 0x74; }
      TxMessage.Payload[i] = Array0x34[i];
    } else if (cmd == 0x35) {
      TxMessage.Payload[i] = Array0x35[i];
    }
  }
}


void ECODANDECODER::TransfertoBuffer(uint8_t msgtype, uint8_t bufferposition) {
  BufferArray[bufferposition][0] = msgtype;
  for (int i = 1; i < 17; i++) {
    BufferArray[bufferposition][i] = TxMessage.Payload[i - 1];
  }
}

uint8_t ECODANDECODER::ReturnNextCommandType(uint8_t bufferposition) {
  return BufferArray[bufferposition][0];
}

void ECODANDECODER::EncodeNextCommand(uint8_t bufferposition) {
  for (int i = 1; i < 17; i++) {
    TxMessage.Payload[i - 1] = BufferArray[bufferposition][i];
  }
}

bool ECODANDECODER::IS_BIT_SET(uint8_t value, uint8_t bit) {
  return (((value) & (1U << (bit))) != 0);
}