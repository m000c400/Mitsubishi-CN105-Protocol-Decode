/*
    Copyright (C) <2020>  <Mike Roberts>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ECODANDECODER_h
#define ECODANDECODER_h

#include <stdint.h>
#include <time.h>
#include <string.h>


#define PACKET_SYNC        0xFC
#define SET_REQUEST        0x41
#define SET_RESPONSE       0x61
#define GET_REQUEST        0x42
#define GET_RESPONSE       0x62
#define CONNECT_REQUEST    0x5A
#define CONNECT_RESPONSE   0x7A
#define EXCONNECT_REQUEST  0x5B
#define EXCONNECT_RESPONSE 0x7B

#define TX_MESSAGE_SETTINGS 0x032

#define COMMANDSIZE 22 // 5 Byte Header + 16 Byte Payload  + 1 Byte Checksum
#define HEADERSIZE 5
#define MAXDATABLOCKSIZE 16

#define PREAMBLESIZE 2

#define HOT_WATER_BOOST_OFF 0
#define HOT_WATER_BOOST_OON 1
const char HotWaterBoostStr[2][4] = {"Off", "On"};

#define SYSTEM_POWER_MODE_STANDBY 0
#define SYSTEM_POWER_MODE_ON 1
const char SystemPowerModeString[2][8] = {"Standby", "On"};

#define SYSTEM_OPERATION_MODE_OFF 0
#define SYSTEM_OPERATION_MODE_HOT_WATER 1
#define SYSTEM_OPERATION_MODE_HEATING 2
#define SYSTEM_OPERATION_MODE_COOLING 3
#define SYSTEM_OPERATION_MODE_ZERO_V 4
#define SYSTEM_OPERATION_MODE_FROST_PROTECT 5
#define SYSTEM_OPERATION_MODE_LEGIONELLA 6
#define SYSTEM_OPERATION_MODE_HEATING_ECO 7
const char SystemOperationModeString[8][14] = {"Off", "Hot Water", "Heating", "Cooling", "Zero V", "Frost Protect", "Legionella", "Heating Eco"};

#define HOT_WATER_CONTROL_MODE_NORMAL 0
#define HOT_WATER_CONTROL_MODE_ECO 1
const char HowWaterControlModeString[2][7] = {"Normal", "Eco"};

#define HEATING_CONTROL_MODE_ZONE_TEMP 0x00
#define HEATING_CONTROL_MODE_FLOW_TEMP 0x01
#define HEATING_CONTROL_MODE_COMPENSATION 0x02
#define HEATING_CONTROL_MODE_COOL_ZONE_TEMP 0x03
#define HEATING_CONTROL_MODE_COOL_FLOW_TEMP 0x044
#define HEATING_CONTROL_MODE_DRY_UP 0x05
const char HeatingControlModeString[6][13] = {"Temp", "Flow", "Compensation", "Cool", "Cool Flow", "Dry Up"};

#define HOLIDAY_MODE_OFF 0
#define HOLIDAY_MODE_ON 1
const char HolidayModetString[2][4] = {"Off", "On"};

#define HOT_WATER_TIMER_ON 0
#define HOT_WATER_TIMER_OFF 1
const char HotWaterTimerString[2][4] = {"On", "Off"};

#define COMPRESSOR_NORMAL 0
#define COMPRESSOR_STANDBY 1
#define COMPRESSOR_DEFROST 2
#define COMPRESSOR_WAIT 3
const char COMPRESSORString[4][8] = {"Normal", "Standby", "Defrost", "Wait"};


// System Flags
 
#define SET_ZONE_SETPOINT        0x80
#define UNKNOWN1                 0x40 
#define SET_HOT_WATER_SETPOINT   0x20
#define UNKNOWN2                 0x10
#define SET_HEATING_CONTROL_MODE 0x08 
#define SET_HOT_WATER_MODE       0x04
#define UNKNOWN3                 0x02
#define SET_SYSTEM_POWER         0x01

#define ZONE1 0x00
#define ZONE2 0x01
#define BOTH  0x02




typedef struct _MessgeStruct
{
    uint8_t SyncByte;
    uint8_t PacketType;
    uint8_t Preamble[PREAMBLESIZE];
    uint8_t PayloadSize;
    uint8_t Payload[MAXDATABLOCKSIZE];
    uint8_t Checksum;
} MessageStruct;

typedef struct _EcodanStatus
{
  //From Message 0x01
  struct tm DateTimeStamp;

  //From Message 0x02
  uint8_t Defrost;
  
  // From Message 0x04
  uint8_t CompressorFrequency;
  
  // From Message 0x05
  uint8_t HotWaterBoostActive;
  uint8_t UnknownMSG5;
  
  // From Message 0x07
  uint8_t OutputPower;  
  
  //From Message 0x09
  float Zone1TemperatureSetpoint; 
  float Zone2TemperatureSetpoint;
  float Zone1FlowTemperatureSetpoint;
  float Zone2FlowTemperatureSetpoint;
  float LegionellaSetpoint;
  float HotWaterMaximumTempDrop;
  float FlowTempMax;
  float FlowTempMin;
  
  //From Message 0x0b
  float Zone1Temperature;
  float Zone2Temperature;
  float OutsideTemperature;
  
  //From Message 0x0c
  float HeaterOutputFlowTemperature;
  float HeaterReturnFlowTemperature;
  float HotWaterTemperature;
  
  //From Message 0x0d
  float ExternalBoilerFlowTemperature;
  float ExternalBoilerReturnTemperature;
  // Plus Several Outher unused
  
  //From Message 0x0e
  // Several Unused Temperatures
  
  //From Message 0x14
  uint32_t RunHours;
  
  //From Message 0x14
  uint8_t PrimaryFlowRate;
  
  //From Message 0x26
  uint8_t SystemPowerMode;
  uint8_t SystemOperationMode;
  uint8_t HotWaterControlMode;
  uint8_t HeatingControlMode;
  float HotWaterSetpoint;
  float HeaterFlowSetpoint;
  
  //From Message 0x28
  uint8_t HotWaterTimerActive;
  uint8_t HolidayModeActive;
  
  //From Message 0x29
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
  
} EcodanStatus;


class ECODANDECODER
{
public:
    ECODANDECODER(void);
    uint8_t Process(uint8_t c);

    void CreateBlankTxMessage(uint8_t PacketType, uint8_t PayloadSize);
    void SetPayloadByte(uint8_t Data, uint8_t Location);
    uint8_t PrepareTxCommand(uint8_t *Buffer);
    
    void EncodeSystemUpdate(uint8_t Flags, float Zone1TempSetpoint, float Zone2TempSetpoint, 
                            uint8_t Zones, 
                            float HotWaterSetpoint, 
                            uint8_t HeatingControlModeZ1, uint8_t HeatingControlModeZ2, 
                            uint8_t HotWaterMode, uint8_t Power);
    EcodanStatus Status;
protected:
    
private:
    MessageStruct RxMessage;
    MessageStruct TxMessage;
    
    

    uint8_t Preamble[PREAMBLESIZE];

    uint8_t  BuildRxMessage(MessageStruct *Message, uint8_t c);

    void CreateBlankMessageTemplate(MessageStruct *Message, uint8_t PacketType, uint8_t PayloadSize);
    uint8_t PrepareCommand(MessageStruct *Message, uint8_t *Buffer);

    
    uint16_t ExtractUInt16(uint8_t *Buffer, uint8_t Index);
    float    ExtractEnergy(uint8_t *Buffer, uint8_t index);
    
    
    uint8_t  CheckSum(uint8_t *Buffer, uint8_t len);

    void Process0x01(uint8_t *Payload, EcodanStatus *Status);
    void Process0x02(uint8_t *Payload, EcodanStatus *Status);
    void Process0x04(uint8_t *Payload, EcodanStatus *Status);
    void Process0x05(uint8_t *Payload, EcodanStatus *Status);
    void Process0x07(uint8_t *Payload, EcodanStatus *Status);
    void Process0x09(uint8_t *Payload, EcodanStatus *Status);
    void Process0x0B(uint8_t *Payload, EcodanStatus *Status);
    void Process0x0C(uint8_t *Payload, EcodanStatus *Status);
    void Process0x0D(uint8_t *Payload, EcodanStatus *Status);
    void Process0x0E(uint8_t *Payload, EcodanStatus *Status);
    void Process0x13(uint8_t *Payload, EcodanStatus *Status);
    void Process0x14(uint8_t *Payload, EcodanStatus *Status);
    void Process0x26(uint8_t *Payload, EcodanStatus *Status);
    void Process0x28(uint8_t *Payload, EcodanStatus *Status);
    void Process0x29(uint8_t *Payload, EcodanStatus *Status);
    void Process0xA1(uint8_t *Payload, EcodanStatus *Status);
    void Process0xA2(uint8_t *Payload, EcodanStatus *Status);
};

#endif
