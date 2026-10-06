#ifndef ECODANDECODER_h
#define ECODANDECODER_h

#include <stdint.h>
#include <time.h>
#include <string.h>
#include "proxy.h"

#define PACKET_SYNC 0xFC
#define SET_REQUEST 0x41
#define SET_RESPONSE 0x61
#define GET_REQUEST 0x42
#define GET_RESPONSE 0x62
#define GET_ABOUT_RESPONSE 0x7B
#define CONNECT_REQUEST 0x5A
#define CONNECT_RESPONSE 0x7A
#define EXCONNECT_REQUEST 0x5B
#define EXCONNECT_RESPONSE 0x7B
#define CONNECT_MEL_REQUEST 0xFF

#define TX_MESSAGE_BASIC 0x032
#define TX_MESSAGE_CONTROLLER 0x034
#define TX_MESSAGE_ROOM_STAT 0x035

#define TX_MESSAGE_SETTING_DHW_Flag 0x01
#define TX_MESSAGE_SETTING_HOL_Flag 0x02
#define TX_MESSAGE_SETTING_DHW_INH_Flag 0x04
#define TX_MESSAGE_SETTING_HEAT_Z1_INH_Flag 0x08
#define TX_MESSAGE_SETTING_COOL_Z1_INH_Flag 0x10
#define TX_MESSAGE_SETTING_HEAT_Z2_INH_Flag 0x20
#define TX_MESSAGE_SETTING_COOL_Z2_INH_Flag 0x40
#define TX_MESSAGE_SETTING_SRV_Flag 0x80

#define COMMANDSIZE 22  // 5 Byte Header + 16 Byte Payload  + 1 Byte Checksum
#define HEADERSIZE 5
#define MAXDATABLOCKSIZE 16

#define PREAMBLESIZE 2

#define HOT_WATER_BOOST_OFF 0
#define HOT_WATER_BOOST_ON 1
const char HotWaterBoostStr[2][4] = { "Off", "On" };

#define TEMP_DROP_MODE_OFF 0
#define TEMP_DROP_MODE_ON 7

#define HOT_WATER_PHASE_OFF 0
#define HOT_WATER_PHASE_HP 1
#define HOT_WATER_PHASE_Heater 2
const char DHWPhaseString[3][10] = { "Off", "Heat Pump", "Heater" };

#define DEFROST_OFF 0
#define DEFROST_STANDBY 1
#define DEFROST_ON 2
#define DEFROST_AWAIT 3
const char DefrostModeString[4][16] = { "Off", "Standby", "Defrosting", "Waiting Restart" };

#define SYSTEM_POWER_MODE_STANDBY 0
#define SYSTEM_POWER_MODE_ON 1
const char SystemPowerModeString[2][8] = { "Standby", "On" };

#define SYSTEM_OPERATION_MODE_OFF 0
#define SYSTEM_OPERATION_MODE_HOT_WATER 1
#define SYSTEM_OPERATION_MODE_HEATING 2
#define SYSTEM_OPERATION_MODE_COOLING 3
#define SYSTEM_OPERATION_MODE_ZERO_V 4
#define SYSTEM_OPERATION_MODE_FROST_PROTECT 5
#define SYSTEM_OPERATION_MODE_LEGIONELLA 6
#define SYSTEM_OPERATION_MODE_HEATING_ECO 7
const char SystemOperationModeString[8][14] = { "Off", "Hot Water", "Heating", "Cooling", "Zero V", "Frost Protect", "Legionella", "Heating Eco" };

const int HeatingRunningBinary[] = { 0, 0, 1, 0, 0, 0, 0, 0 };
const int CoolingRunningBinary[] = { 0, 0, 0, 1, 0, 0, 0, 0 };

#define HOT_WATER_CONTROL_MODE_NORMAL 0
#define HOT_WATER_CONTROL_MODE_ECO 1
const char HotWaterControlModeString[2][7] = { "Normal", "Eco" };

const char HPControlModeString[2][5] = { "Heat", "Cool" };
const char ShortCycleReason[3][33] = { "", "Flow Temp Exceeded Flow Setpoint", "Thermostat Demand" };


#define HEATING_CONTROL_MODE_ZONE_TEMP 0x00
#define HEATING_CONTROL_MODE_FLOW_TEMP 0x01
#define HEATING_CONTROL_MODE_COMPENSATION 0x02
#define HEATING_CONTROL_MODE_COOL_ZONE_TEMP 0x03
#define HEATING_CONTROL_MODE_COOL_FLOW_TEMP 0x04
#define HEATING_CONTROL_MODE_DRY_UP 0x05
#define HEATING_CONTROL_MODE_COOL_COMPENSATION 0x06
const char HeatingControlModeString[7][18] = { "Temp", "Flow", "Compensation", "Cool", "Cool Flow", "Dry Up", "Cool Compensation" };
const char ThermostatString[16][4] = { "MRC", "RC1", "RC2", "RC3", "RC4", "RC5", "RC6", "RC7", "RC8", "", "", "", "", "", "", "TH1" };

#define HOLIDAY_MODE_OFF 0
#define HOLIDAY_MODE_ON 1
const char HolidayModetString[2][4] = { "Off", "On" };

#define ITEM_OFF 0
#define ITEM_ON 1
const char OFF_ON_String[2][4] = { "Off", "On" };
const char MELCloudStatusString[2][8] = { "Online", "Offline" };

#define COMPRESSOR_NORMAL 0
#define COMPRESSOR_STANDBY 1
#define COMPRESSOR_DEFROST 2
#define COMPRESSOR_WAIT 3
const char COMPRESSORString[4][8] = { "Normal", "Standby", "Defrost", "Wait" };

const char RefrigeFltCodeString[4][12] = { "Normal", "System", "Startup", "Maintenance" };
const char FltCodeLetterOne[8][2] = { "A", "b", "E", "F", "J", "L", "P", "U" };
const char FltCodeLetterTwo[22][2] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F", "0", "H", "J", "L", "P", "U" };

#define FTC2B 0
#define FTC4 1
#define FTC5 2
#define FTC6 3
#define FTC7 5
const char FTCString[6][6] = { "FTC2B", "FTC4", "FTC5", "FTC6", "", "FTC7" };


// System Flags

#define SET_ZONE_SETPOINT 0x80
#define UNKNOWN1 0x40
#define SET_HOT_WATER_SETPOINT 0x20
#define UNKNOWN2 0x10
#define SET_HEATING_CONTROL_MODE_Z1 0x08
#define SET_HEATING_CONTROL_MODE_Z2 0x10
#define SET_HOT_WATER_MODE 0x04
#define UNKNOWN3 0x02
#define SET_SYSTEM_POWER 0x01
#define SET_HOT_WATER_BOOST 0x01

#define ZONE1 0x00        // Zone1
#define ZONE1_TSTAT 0x02  // Zone 1 Thermostat
#define ZONE2 0x02        // Zone2
#define ZONE2_TSTAT 0x08  // Zone 2 Thermostat
#define BOTH 0x03         // BOTH



typedef struct _MessgeStruct {
  uint8_t SyncByte;
  uint8_t PacketType;
  uint8_t Preamble[PREAMBLESIZE];
  uint8_t PayloadSize;
  uint8_t Payload[MAXDATABLOCKSIZE];
  uint8_t Checksum;
} MessageStruct;

typedef struct _EcodanStatus {
  //From Message 0x01
  struct tm DateTimeStamp;
  char FTCSoftware[6];
  bool SyncTime;

  //From Message 0x02
  uint8_t Defrost, LastDefrost, ThermostatZ1, ThermostatZ2;

  //From Message 0x03
  uint8_t RefrigeFltCode, ErrCode1, ErrCode2, FltCode1, FltCode2;
  uint8_t TwoZone_Z1Working, TwoZone_Z2Working;
  uint8_t Compressor1Freq, Compressor2Freq, Compressor3Freq, Compressor4Freq;

  // From Message 0x04
  uint8_t CompressorFrequency;

  // From Message 0x05
  uint8_t DHWActive;
  uint8_t DHWHeatSourcePhase;

  // From Message 0x07
  uint8_t InputPower, OutputPower;
  float EnergyConsumedIncreasing;

  // From Message 0x08


  //From Message 0x09
  float Zone1TemperatureSetpoint;
  float Zone2TemperatureSetpoint;
  float Zone1FlowTemperatureSetpoint;
  float Zone2FlowTemperatureSetpoint;
  float LegionellaSetpoint;
  float HotWaterMaximumTempDrop;
  float FlowTempMax;
  float FlowTempMin;

  //From Message 0x0B
  float Zone1Temperature, Zone2Temperature, OutsideTemperature;
  float RefrigeTemp;

  //From Message 0x0C
  float HeaterOutputFlowTemperature, HeaterReturnFlowTemperature, HeaterDeltaT;
  float HotWaterTemperature, HotWaterTemperatureTHW5A;

  //From Message 0x0D
  float Zone1FlowTemperature, Zone1ReturnTemperature;
  float Zone2FlowTemperature, Zone2ReturnTemperature;

  //From Message 0x0E
  float ExternalBoilerFlowTemperature, ExternalBoilerReturnTemperature;

  //From Message 0x0F
  float MixingTemperature, CondensingTemp;
  bool OutdoorExtendedSensors;

  //From Message 0x10
  uint8_t Zone1ThermostatDemand, Zone2ThermostatDemand, OutdoorThermostatDemand;

  //From Message 0x11
  uint8_t DipSwitch1, DipSwitch2, DipSwitch3, DipSwitch4, DipSwitch5, DipSwitch6, DipSwitch7;
  bool HasCooling, Has2Zone, Simple2Zone, HasAnsweredDips, HasGeodan, HasR290DualComp;

  //From Message 0x13
  uint32_t RunHours;
  bool CompressorRunning;

  //From Message 0x14
  uint8_t PrimaryFlowRate;
  uint8_t Booster1Active, Booster2Active, Booster2PlusActive, ImmersionActive;

  //From Message 0x15
  uint8_t PrimaryWaterPump, PrimaryWaterPumpSpeed, PumpPower, WaterPump2, WaterPump3a, ThreeWayValve, ThreeWayValve2, MixingStep;

  //From Message 0x16
  uint8_t WaterPump4, WaterPump3b, WaterPump13;

  //From Message 0x26
  uint8_t SystemPowerMode, SystemOperationMode, LastSystemOperationMode, HotWaterControlMode;
  uint8_t HeatingControlModeZ1, HeatingControlModeZ2;
  float HotWaterSetpoint;

  //From Message 0x28
  uint8_t HotWaterBoostActive, HolidayModeActive, ProhibitDHW;
  uint8_t ProhibitHeatingZ1, ProhibitHeatingZ2;
  uint8_t ProhibitCoolingZ1, ProhibitCoolingZ2;
  uint8_t SvrControlMode;

  //From Message 0x29
  uint8_t HeatCool;
  //float Zone1TemperatureSetpoint;  Already Defined Above
  //float Zone2TemperatureSetpoint;  Already Defined Above

  //From Message 0xa1
  struct tm ConsumedDateTimeStamp;
  float ConsumedHeatingEnergy;
  float ConsumedCoolingEnergy;
  float ConsumedHotWaterEnergy;

  //From Message 0xa2
  struct tm DeliveredDateTimeStamp;
  float DeliveredHeatingEnergy;
  float DeliveredCoolingEnergy;
  float DeliveredHotWaterEnergy;

  //From Message 0xa3
  int16_t Fan1RPM, Fan2RPM, LEVA, LEVB, LEVC, LiquidTemp, TH4Discharge, CompOpTimes, Subcool, TH8HeatSink, TH6Pipe, TH32Pipe, TH32, TH33, TH34, Superheat, ServiceCodeReply;
  uint8_t LastServiceCodeNumber, OutdoorUnitCapacity;
  char OutdoorFirmware[6];

  //From Message 0xc9
  uint8_t FTCVersion, RefrigerantType;

  // From Message 0x61
  bool Write_To_Ecodan_OK;


} EcodanStatus;


class ECODANDECODER {
public:
  ECODANDECODER(void);
  uint8_t Process(uint8_t c);

  void CreateBlankTxMessage(uint8_t PacketType, uint8_t PayloadSize);
  void PayloadWipe(void);
  void SetPayloadByte(uint8_t Data, uint8_t Location);
  uint8_t PrepareTxCommand(uint8_t *Buffer);
  void EncodePower(uint8_t Power);
  void EncodeControlMode(uint8_t ControlMode, uint8_t Zone);
  void EncodeDHWMode(uint8_t HotWaterMode);
  void EncodeDHWSetpoint(float HotWaterSetpoint);
  void EncodeRoomThermostat(float Setpoint, uint8_t ControlMode, uint8_t Zone);
  void EncodeFlowTemperature(float Setpoint, uint8_t ControlMode, uint8_t Zone, float SetpointDHW);
  void EncodeForcedDHW(uint8_t OnOff);
  void EncodeHolidayMode(uint8_t OnOff);
  void EncodeFTCVersion(void);
  void EncodeServerControlMode(uint8_t OnOff, uint8_t DHW, uint8_t Z1H, uint8_t Z1C, uint8_t Z2H, uint8_t Z2C);
  void EncodeProhibit(uint8_t Flags, uint8_t OnOff);
  void EncodeMELCloud(uint8_t cmd);
  void TransfertoBuffer(uint8_t msgtype, uint8_t bufferposition);
  uint8_t ReturnNextCommandType(uint8_t bufferposition);
  void EncodeNextCommand(uint8_t bufferposition);

  EcodanStatus Status;
protected:

private:
  MessageStruct RxMessage;
  MessageStruct TxMessage;

  bool IS_BIT_SET(uint8_t value, uint8_t bit);

  uint8_t Preamble[PREAMBLESIZE];

  uint8_t BuildRxMessage(MessageStruct *Message, uint8_t c);

  void CreateBlankMessageTemplate(MessageStruct *Message, uint8_t PacketType, uint8_t PayloadSize);
  uint8_t PrepareCommand(MessageStruct *Message, uint8_t *Buffer);


  uint16_t ExtractUInt16(uint8_t *Buffer, uint8_t Index);
  uint16_t ExtractUInt16_v2(uint8_t *Buffer, uint8_t Index);
  int16_t ExtractInt16_v2_Signed(uint8_t *Buffer, uint8_t Index);
  float Extract_Float_24(uint8_t *Buffer, uint8_t Index);
  float ExtractUInt16_Signed(uint8_t *Buffer, uint8_t Index);
  float ExtractUInt8_v1(uint8_t *Buffer, uint8_t Index);
  float ExtractUInt8_v2(uint8_t *Buffer, uint8_t Index);
  float ExtractUInt8_v3(uint8_t *Buffer, uint8_t Index);
  float ExtractUInt8_v4(uint8_t *Buffer, uint8_t Index);
  float ExtractUInt8_v5(uint8_t *Buffer, uint8_t Index);
  float ExtractEnergy(uint8_t *Buffer, uint8_t index);


  uint8_t CheckSum(uint8_t *Buffer, uint8_t len);

  void Process0x01(uint8_t *Payload, EcodanStatus *Status);
  void Process0x02(uint8_t *Payload, EcodanStatus *Status);
  void Process0x03(uint8_t *Payload, EcodanStatus *Status);
  void Process0x04(uint8_t *Payload, EcodanStatus *Status);
  void Process0x05(uint8_t *Payload, EcodanStatus *Status);
  void Process0x06(uint8_t *Payload, EcodanStatus *Status);
  void Process0x07(uint8_t *Payload, EcodanStatus *Status);
  void Process0x08(uint8_t *Payload, EcodanStatus *Status);
  void Process0x09(uint8_t *Payload, EcodanStatus *Status);
  void Process0x0B(uint8_t *Payload, EcodanStatus *Status);
  void Process0x0C(uint8_t *Payload, EcodanStatus *Status);
  void Process0x0D(uint8_t *Payload, EcodanStatus *Status);
  void Process0x0E(uint8_t *Payload, EcodanStatus *Status);
  void Process0x0F(uint8_t *Payload, EcodanStatus *Status);
  void Process0x10(uint8_t *Payload, EcodanStatus *Status);
  void Process0x11(uint8_t *Payload, EcodanStatus *Status);
  void Process0x12(uint8_t *Payload, EcodanStatus *Status);
  void Process0x13(uint8_t *Payload, EcodanStatus *Status);
  void Process0x14(uint8_t *Payload, EcodanStatus *Status);
  void Process0x15(uint8_t *Payload, EcodanStatus *Status);
  void Process0x16(uint8_t *Payload, EcodanStatus *Status);
  void Process0x17(uint8_t *Payload, EcodanStatus *Status);
  void Process0x18(uint8_t *Payload, EcodanStatus *Status);
  void Process0x19(uint8_t *Payload, EcodanStatus *Status);
  void Process0x1a(uint8_t *Payload, EcodanStatus *Status);
  void Process0x1b(uint8_t *Payload, EcodanStatus *Status);
  void Process0x1c(uint8_t *Payload, EcodanStatus *Status);
  void Process0x1d(uint8_t *Payload, EcodanStatus *Status);
  void Process0x1e(uint8_t *Payload, EcodanStatus *Status);
  void Process0x1f(uint8_t *Payload, EcodanStatus *Status);
  void Process0x20(uint8_t *Payload, EcodanStatus *Status);
  void Process0x26(uint8_t *Payload, EcodanStatus *Status);
  void Process0x27(uint8_t *Payload, EcodanStatus *Status);
  void Process0x28(uint8_t *Payload, EcodanStatus *Status);
  void Process0x29(uint8_t *Payload, EcodanStatus *Status);
  void Process0xA1(uint8_t *Payload, EcodanStatus *Status);
  void Process0xA2(uint8_t *Payload, EcodanStatus *Status);
  void Process0xA3(uint8_t *Payload, EcodanStatus *Status);
  void Process0xC9(uint8_t *Payload, EcodanStatus *Status);

  void WriteOK(uint8_t *Payload, EcodanStatus *Status);
};



#endif
