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
#include "Ecodan.h"

#include <ESPTelnet.h>
extern ESPTelnet TelnetServer;
#include "Debug.h"

//[CONNECT_LEN] = {0xfc, 0x5a, 0x02, 0x7a, 0x02, 0xca, 0x01, 0x5d};

// Initialisation Commands

uint8_t Init1[] = {0x02, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x02};
uint8_t Init2[] = {0x02, 0xff, 0xff, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00};
uint8_t Init3[] = {0xfc, 0x5a, 0x02, 0x7a, 0x02, 0xca, 0x01, 0x5d};
uint8_t Init4[] = {0xfc, 0x5b, 0x02, 0x7a, 0x01, 0xc9, 0x5f};
uint8_t Init5[] = {0xfc, 0x41, 0x02, 0x7a, 0x10, 0x34, 0x00, 0x01, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0xfd};

/*
  #define NUMBER_COMMANDS 35
  uint8_t ActiveCommand[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x09, 0x0B, 0x0C, 0x0D, 0x0E,
                            0x10, 0x11, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1C, 0x1D, 0x1E, 0x1F,
                            0x20, 0x26, 0x27, 0x28, 0x29,
                            0xA1, 0xA2, 0xA3
                          };
*/

#define NUMBER_COMMANDS 21
uint8_t ActiveCommand[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x07, 0x09, 0x0B, 0x0C, 0x0D, 0x0E,
                            0x11, 0x13, 0x14, 0x15,
                            0x26, 0x28, 0x29,
                            0xA1, 0xA2,
                            0x00
                          };

ECODAN::ECODAN(void): ECODANDECODER()
{
  CurrentMessage = 0;
  UpdateFlag = 0;
  Connected = false;
}


void ECODAN::Process(void)
{
  uint8_t c;

  while (DeviceStream->available())
  {
    c = DeviceStream->read();

    if(c == 0) 
      DEBUG_PRINT("__, ");
    else 
    {
      if (c < 0x10 ) DEBUG_PRINT("0");
      DEBUG_PRINT( String(c, HEX));
      DEBUG_PRINT(", ");
    }
    
    if(ECODANDECODER::Process(c))
    {
      DEBUG_PRINTLN();
      Connected = true;
    }
  }
}

void ECODAN::SetStream(Stream *HeatPumpStream)
{
  DeviceStream = HeatPumpStream;
  Connect();
}


void ECODAN::TriggerStatusStateMachine(void)
{
  DEBUG_PRINT("\e[1;1H\e[2J");
  //DEBUG_PRINT("\e[1;1H");
  DEBUG_PRINTLN("Triggering HeatPump Query");
  if(!Connected)
  {
    Connect();
  }
  CurrentMessage = 1;
  Connected = false;
}

void ECODAN::StatusStateMachine(void)
{
  uint8_t Buffer[COMMANDSIZE];
  uint8_t CommandSize;

  if (CurrentMessage != 0)
  {
    DEBUG_PRINT("Send Message "); DEBUG_PRINTLN(CurrentMessage);
    ECODANDECODER::CreateBlankTxMessage(GET_REQUEST, 0x10);
    ECODANDECODER::SetPayloadByte(ActiveCommand[CurrentMessage], 0);
    CommandSize = ECODANDECODER::PrepareTxCommand(Buffer);

    DeviceStream->write(Buffer, CommandSize);

    CurrentMessage++;
    CurrentMessage %= NUMBER_COMMANDS;

    if (CurrentMessage == 0)
    {
      UpdateFlag = 1;
    }
  }
  else
  {
    PrintTumble();
  }
}

void ECODAN::Connect(void)
{
  DEBUG_PRINTLN("Init 3");
  DeviceStream->write(Init3, 8);
  Process();
  DEBUG_PRINTLN();
}

uint8_t ECODAN::UpdateComplete(void)
{
  if (UpdateFlag)
  {
    UpdateFlag = 0;
    return 1;
  }
  else
  {
    return 0;
  }
}

void ECODAN::KeepAlive(void)
{
  uint8_t CommandSize;
  uint8_t Buffer[COMMANDSIZE];

  ECODANDECODER::CreateBlankTxMessage(SET_REQUEST, 0x10);
  ECODANDECODER::SetPayloadByte(0x34, 0);
  ECODANDECODER::SetPayloadByte(0x02, 1);
  CommandSize = ECODANDECODER::PrepareTxCommand(Buffer);
  DeviceStream->write(Buffer, CommandSize);
}

void ECODAN::SetZoneTempSetpoint(uint8_t Zone1Target, uint8_t Zone2Target, uint8_t Zones)
{
  uint8_t Buffer[COMMANDSIZE];
  uint8_t CommandSize = 0;
  
  ECODANDECODER::CreateBlankTxMessage(SET_REQUEST, 0x10);
  ECODANDECODER::EncodeSystemUpdate(SET_ZONE_SETPOINT | SET_HEATING_CONTROL_MODE, Zone1Target, Zone2Target, Zones, 0, HEATING_CONTROL_MODE_ZONE_TEMP, HEATING_CONTROL_MODE_ZONE_TEMP, 0, 1);
  CommandSize = ECODANDECODER::PrepareTxCommand(Buffer);
  DeviceStream->write(Buffer, CommandSize);
}

void ECODAN::SetZoneFlowSetpoint(uint8_t Zone1Target, uint8_t Zone2Target, uint8_t Zones)
{
  uint8_t Buffer[COMMANDSIZE];
  uint8_t CommandSize = 0;
  
  ECODANDECODER::CreateBlankTxMessage(SET_REQUEST, 0x10);
  ECODANDECODER::EncodeSystemUpdate(SET_ZONE_SETPOINT | SET_HEATING_CONTROL_MODE, Zone1Target, Zone2Target, Zones, 0, HEATING_CONTROL_MODE_FLOW_TEMP, HEATING_CONTROL_MODE_FLOW_TEMP, 0, 1);
  CommandSize = ECODANDECODER::PrepareTxCommand(Buffer);
  DeviceStream->write(Buffer, CommandSize);
}

void ECODAN::SetZoneCurveSetpoint(uint8_t Zone1Target, uint8_t Zone2Target, uint8_t Zones)
{
  uint8_t Buffer[COMMANDSIZE];
  uint8_t CommandSize = 0;
  
  ECODANDECODER::CreateBlankTxMessage(SET_REQUEST, 0x10);
  ECODANDECODER::EncodeSystemUpdate(SET_ZONE_SETPOINT | SET_HEATING_CONTROL_MODE, Zone1Target, Zone2Target, Zones, 0, HEATING_CONTROL_MODE_COMPENSATION, HEATING_CONTROL_MODE_COMPENSATION, 0, 1);
  CommandSize = ECODANDECODER::PrepareTxCommand(Buffer);
  DeviceStream->write(Buffer, CommandSize);
}

void ECODAN::ForceDHW(uint8_t OnOff)
{
  uint8_t Buffer[COMMANDSIZE];
  uint8_t CommandSize = 0;
  
  ECODANDECODER::CreateBlankTxMessage(SET_REQUEST, 0x10);
  ECODANDECODER::EncodeDHW(OnOff);
  CommandSize = ECODANDECODER::PrepareTxCommand(Buffer);
  DeviceStream->write(Buffer, CommandSize);
}

void ECODAN::SetHotWaterSetpoint(uint8_t Target)
{
  uint8_t Buffer[COMMANDSIZE];
  uint8_t CommandSize = 0;
  
  ECODANDECODER::CreateBlankTxMessage(SET_REQUEST, 0x10);
  ECODANDECODER::EncodeSystemUpdate(SET_HOT_WATER_SETPOINT, 0, 0, BOTH, Target, 0, 0, 0, 1);
  CommandSize = ECODANDECODER::PrepareTxCommand(Buffer);
  DeviceStream->write(Buffer, CommandSize);
}

void ECODAN::SetHeatingControlMode(String *Mode, uint8_t Zones)
{
  uint8_t Buffer[COMMANDSIZE];
  uint8_t CommandSize = 0;
  uint8_t i;

  ECODANDECODER::CreateBlankTxMessage(SET_REQUEST, 0x10);

  if (*Mode == String("Temperature Control"))
  {
    ECODANDECODER::EncodeSystemUpdate(SET_HEATING_CONTROL_MODE, 0, 0, Zones, 0, HEATING_CONTROL_MODE_ZONE_TEMP, HEATING_CONTROL_MODE_ZONE_TEMP, 0, 1);
    CommandSize = ECODANDECODER::PrepareTxCommand(Buffer);
    DeviceStream->write(Buffer, CommandSize);
  }
  else if (*Mode == String("Fixed Flow"))
  {
    ECODANDECODER::EncodeSystemUpdate(SET_HEATING_CONTROL_MODE, 0, 0, Zones, 0, HEATING_CONTROL_MODE_FLOW_TEMP, HEATING_CONTROL_MODE_FLOW_TEMP, 0, 1);
    CommandSize = ECODANDECODER::PrepareTxCommand(Buffer);
    DeviceStream->write(Buffer, CommandSize);
  }
  if (*Mode == String("Compensation Flow"))
  {
    ECODANDECODER::EncodeSystemUpdate(SET_HEATING_CONTROL_MODE, 0, 0, Zones, 0, HEATING_CONTROL_MODE_COMPENSATION, HEATING_CONTROL_MODE_COMPENSATION, 0, 1);
    CommandSize = ECODANDECODER::PrepareTxCommand(Buffer);
    DeviceStream->write(Buffer, CommandSize);
  }
  for (i = 0; i < CommandSize; i++)
  {
    if (Buffer[i] < 0x10 ) Serial.print("0");
    Serial.print(String(Buffer[i], HEX));
    Serial.print(", ");
  }
  Serial.println();
}

void ECODAN::SetSystemPowerMode(String *Mode)
{
  uint8_t Buffer[COMMANDSIZE];
  uint8_t CommandSize = 0;
  uint8_t i;

  ECODANDECODER::CreateBlankTxMessage(SET_REQUEST, 0x10);

  if (*Mode == String("On"))
  {
    ECODANDECODER::EncodeSystemUpdate(SET_SYSTEM_POWER, 0, 0, 0, 0, 0, 0, 0, SYSTEM_POWER_MODE_ON);
    CommandSize = ECODANDECODER::PrepareTxCommand(Buffer);
    DeviceStream->write(Buffer, CommandSize);
  }
  else if (*Mode == String("Standby"))
  {
    ECODANDECODER::EncodeSystemUpdate(SET_SYSTEM_POWER, 0, 0, 0, 0, 0, 0, 0, SYSTEM_POWER_MODE_STANDBY);
    CommandSize = ECODANDECODER::PrepareTxCommand(Buffer);
    DeviceStream->write(Buffer, CommandSize);
  }
  for (i = 0; i < CommandSize; i++)
  {
    if (Buffer[i] < 0x10 ) Serial.print("0");
    Serial.print(String(Buffer[i], HEX));
    Serial.print(", ");
  }
  Serial.println();
}

// 
void ECODAN::Scratch(uint8_t Target)
{
  uint8_t CommandSize;
  uint8_t Buffer[COMMANDSIZE];
  int i;

  ECODANDECODER::CreateBlankTxMessage(SET_REQUEST, 0x10);
  ECODANDECODER::SetPayloadByte(TX_MESSAGE_SETTINGS, 0);
  ECODANDECODER::SetPayloadByte(UNKNOWN3 | UNKNOWN2 | UNKNOWN1  , 1);
  ECODANDECODER::SetPayloadByte(Target, 4);
  ECODANDECODER::SetPayloadByte(Target, 14);
  ECODANDECODER::SetPayloadByte(Target, 15);
  
  //ECODANDECODER::SetPayloadByte(0x01, Target);

  CommandSize = ECODANDECODER::PrepareTxCommand(Buffer);
  DeviceStream->write(Buffer, CommandSize);
  
  for (i = 0; i < CommandSize; i++)
  {
    if (Buffer[i] < 0x10 ) Serial.print("0");
    Serial.print(String(Buffer[i], HEX));
    Serial.print(",");
  }
  Serial.println();
}

void ECODAN::PrintTumble(void)
{
  static char tumble[] = "|/-\\";
  static uint8_t i = 0;
  char c;

  DEBUG_PRINT('\b');
  c = tumble[i];
  DEBUG_PRINT(c);

  i++; i %= 4;
}
