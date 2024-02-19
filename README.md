# Mitsubishi-CN105-Protocol-Decode
For Ecodan ASHP Units
I have included my reference implemenataion, but all very much work in progress

https://gitter.im/Mitsubishi-CN105-Protocol-Decode/community

# Physical
Serial, 2400, 8, E, 1
# Command Format
| Header | Payload | Checksum |
|--------|---------|----------|
| 5 Bytes | 16 Bytes | 1 Byte |
## Header
| Sync Byte | Packet Type | Uknown | Unknown | Payload Size |
|---|---|--|---|---|
| 0xfc | Type | 0x02 | 0x7a | Length |
### Sync Byte 
0xfc
### Packet Types
| Value | Packet Type      | Direction      |
|-------|------------------|----------------|
|  0x41 | Set Request      | To Heat Pump   |
|  0x61 | Set Response     | From Heat Pump |
|  0x42 | Get Request      | To Heat Pump   |
|  0x62 | Get Response     | From Heat Pump |
|  0x5A | Connect Request  | To Heat Pump   |
|  0x7A | Connect Response | From Heat Pump |
|  0x5B | Extended Connect Request  | To Heat Pump   |
|  0x7B | Extended Connect Responce | To Heat Pump   |
### Length
Payload Size (Bytes)
## Payload
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|---|---|---|---|---|---|---|---|---|---|----|----|----|----|----|----|----|
| Command | x | x | x | x | x | x | x | x | x | x  | x  |  x |  x |  x |  x |  x |
## Checksum
Checksum = 0xfc - Sum ( PacketBytes[0..20]) ;
# Set Request - Packet Type 0x41
## Available Commands 
Active commands so far identified.
| Command | Brief Description |
| ------- | ----------- |
| 0x32 |  Update Settings |
| 0x34 | Hot Water |
| 0x35 | Unknown |
### 0x32 - Set Options
|   0   |   1   | 2 | 3 | 4 |  5  |  6  |  7  |   8   |   9   |  10  |  11  |  12  |  13  | 14 | 15 | 16 |
|-------|-------|---|---|---|-----|-----|-----|-------|-------|------|------|------|------|----|----|----|
| 0x32  | Flags | Z | P |   | DHW | HC1 | HC2 | DHWSP | DHWSP | Z1SP | Z1SP | Z2SP | Z2SP |    |    |    |  

* Flags : Flags to Indicate which fields are active
  * 0x80 : Set Zone Setpoints, Byte[2] determines which Zones 
  * 0x40 : Unknown 
  * 0x20 : Set Hotwater Setpoint
  * 0x10 : Unknown
  * 0x08 : Set Heating Control Mode
  * 0x04 : Set Hot Water Mode
  * 0x02 : Unknown
  * 0x01 : Set System Power Power
* Z : Zones the Command Applies to
  * 0x00 : Zone 1
  * 0x01 : Zone 2 ( Probably )
  * 0x02 : Both
* P : System Power
  * 0x00 : Standby
  * 0x01 : Power On
* DHW : Hot Water Mode
  * 0x00 : Normal
  * 0x01 : Eco
* HC1 : Heating Control Mode Zone 1
  * 0 : Temperature Mode
  * 1 : Flow Control Mode
  * 2 : Compensation Curve Mode
* HC2 : Heating Control Mode Zone 2
  * 0 : Temperature Mode
  * 1 : Flow Control Mode
  * 2 : Compensation Curve Mode
* DHWSP : Hot Water Setpoint (Temperature * 100)
* Z1SP : Zone 1 Setpoint (* 100)
* Z2SP : Zone 1 Setpoint (* 100)
### 0x35 - Set Zone 1 Setpoint 
Identified so far, this must do far more that this!
|   0   |   1  | 2 | 3 |   4  |  5   | 6 |  7  |   8   |   9   |  10  |  11  |  12  |  13  | 14 | 15 | 16 |
|-------|------|---|---|------|------|---|-----|-------|-------|------|------|------|------|----|----|----|
| 0x35  | 0x02 |   |   | Z1SP | Z1SP |   |     |       |       |      |      |      |      |    |    |    |  
* Z1SP : Zone 1 Setpoint (* 100)
# Get Request - Packet Type 0x42
## Available Commands 
Active commands so far identified, 0x00 to 0xff. Commands not listed appear to generate no resaponse. Some command listed have empty, payload 0x00, response.
| Command | Brief Description |
| ------- | ----------- |
| 0x01 | Time & Date |
| 0x02 | Unknown |
| 0x03 | Unknown |
| 0x04 | Unknown - Empty Response |
| 0x05 | Hot Water Boot Flag |
| 0x06 | Unknown - Empty Response |
| 0x06 | Unknown - Empty Response |
| 0x07 | Unknown |
| 0x08 | Unknown |
| 0x09 | Zone 1 & 2 Temperatures and Setpoints, Hot Water Setpoint |
| 0x0b | Zone 1 & 2 and Outside |Temperature
| 0x0c | Water Flow Temperatures |
| 0x0d | Boiler Flow Temperatures |
| 0x0e | Unknown |
| 0x10 | Unknown |
| 0x11 | Unknown |
| 0x13 | Unknown |
| 0x14 | Unknown |
| 0x15 | Unknown |
| 0x16 | Unknown - Empty Response |
| 0x17 | Unknown - Empty Response |
| 0x18 | Unknown - Empty Response |
| 0x19 | Unknown - Empty Response |
| 0x1a | Unknown - Empty Response |
| 0x1c | Unknown - Empty Response |
| 0x1d | Unknown - Empty Response |
| 0x1e | Unknown - Empty Response |
| 0x1f | Unknown - Empty Response |
| 0x20 | Unknown - Empty Response |
| 0x26 | Various Operantion Mode Flags |
| 0x27 | Unknown |
| 0x28 | Various Operantion Mode Flags |
| 0x29 | Zone 1 & 2 Temperatures |
| 0xa1 | Unknown |
| 0xa2 | Unknown |
| 0xa3 | Unknown - Empty Response |
### Payload - All Commands
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|---|---|---|---|---|---|---|---|---|---|----|----|----|----|----|----|----|
| Command | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0  | 0  |  0 |  0 |  0 |  0 |  0 |
# Set Response - Packet Type 0x61
## Available Commands 
Active commands so far identified.
| Command | Brief Description |
| ------- | ----------- |
| 0x00 |  OK |
### 0x00 - OK , Command OK, or Just Format?
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|---|---|---|---|---|---|---|---|---|---|----|----|----|----|----|----|----|
| Command | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0  | 0  |  0 |  0 |  0 |  0 |  0 |
# Get Response - Packet Type 0x62
## Resposes 
Responses so far identified.
| Command | Brief Description |
| ------- | ----------- |
| 0x01 | Time & Date |
| 0x05 | Various Flags |
| 0x09 | Zone 1 & 2 Temperatures and Setpoints, Hot Water Setpoint |
| 0x0b | Zone 1 & 2 and Outside Temperature |
| 0x0c | Water Flow Temperatures |
| 0x0d | Boiler Flow Temperatures |
| 0x26 | Various Operantion Mode Flags |
| 0x28 | Various Operantion Mode Flags |
| 0x29 | Zone 1 & 2 Temperatures |
### 0x01 - Time & Date
|   0   | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|-------|---|---|---|---|---|---|---|---|---|----|----|----|----|----|----|----|
| 0x01  | Y | M | D | h | m | s |   |   |   |    |    |    |    |    |    |    |  
* Y: Year
* M: Month
* D: Day
* h: Hour
* m: Minute
* s: Second
### 0x04 - Various Flags
|   0   | 1  | 2 | 3 | 4 | 5 | 6 |  7  | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|-------|----|---|---|---|---|---|---|---|---|----|----|----|----|----|----|----|
| 0x04  | CF |   |   |   |   |   |   |   |   |    |    |    |    |    |    |    |  
* CF : Compressor Frequency
### 0x05 - Various Flags
|   0  | 1 | 2 | 3 | 4 | 5 | 6 |  7  | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|------|---|---|---|---|---|---|-----|---|---|----|----|----|----|----|----|----|
| 0x05 |   |   |   |   |   |   | HWB |   |   |    |    |    |    |    |    |    |  
* HWB : Hot Water Boost
### 0x07 
|   0   | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|-------|---|---|---|---|---|---|---|---|---|----|----|----|----|----|----|----|
| 0x07  |   |   |   |   |   |   |   |   | P  |    |    |    |    |    |    |    |  
* P : Heater Power (kW)
### 0x09 - Zone 1 & 2 Temperatures and Setpoints, Hot Water Setpoint
| 0    |   1  |   2  | 3    | 4    | 5    | 6    | 7    | 8    |  9  |  10 |  11 | 12 | 13 | 14 | 15 | 16 |
|------|------|------|------|------|------|------|------|------|-----|-----|-----|----|----|----|----|----|
| 0x09 | Z1T  | Z1T  | Z2T  | Z2T  | Z1ST | Z1SP | Z2SP | Z2SP | LSP | LSP | HWD |  ? | ?  |    |    |    |
* Z1T  : Zone1 Target Temperature * 100
* Z2T  : Zone2 Target Temperature * 100;
* Z1SP : Zone 1 Flow SetFlow Setpoint * 100
* Z2SP : Zone 3 Flow SetFlow Setpoint * 100
* LSP  : Legionella Setpoint * 100;
* HWD  : DHW Max Temp Drop;
### 0x0b - Zone 1 & 2 and Outside Temperature
|   0  |  1  |  2  | 3 | 4 | 5 | 6 |  7  |  8  | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|------|-----|-----|---|---|---|---|-----|-----|---|----|----|----|----|----|----|----|
| 0x0b | Z1T | Z1T | ? | ? |   |   | Z2T | Z2T |   |    | O  |    |    |    |    |    |
* Z1T : Zone1 Temperature * 100
* Z2T : Zone2 Temperature * 100
* O : Outside Temp  +40 x 2 
### 0x0c - Heater Flow Temps
|  0   | 1  | 2  | 3 | 4  | 5  | 6 | 7  |  8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|------|----|----|---|----|----|---|----|----|---|----|----|----|----|----|----|----|
| 0x0c | OF | OF |   | RF | RF |   | HW | HW |   |    |    |    |    |    |    |    |
* OF : Heater Water Out Flow  * 100
* RF : Heater Return Flow Temperature * 100
* HW : Hot Water Temperature * 100
### 0x0d - Boiler Temps
|  0   | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|------|---|---|---|---|---|---|---|---|---|----|----|----|----|----|----|----|
| 0x0d | F | F |   | R | R |   |   |   |   |    |    |    |    |    |    |    |
* F : Boiler Flow Temperature * 100;
* R : Boiler Return Temperature * 100;
### 0x0e - Unknown Temps
|  0   | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|------|---|---|---|---|---|---|---|---|---|----|----|----|----|----|----|----|
| 0x0e |   |   |   |   |   |   |   |   |   |    |    |    |    |    |    |    |
Several Unknown Temperatures
### 0x14 - Primary Cct Flow Rate
|   0   | 1  | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|-------|----|---|---|---|---|---|---|---|---|----|----|----|----|----|----|----|
| 0x14  |    |   |   |   |   |   |   |   |   |    | PF |    |    |    |    |    |  
* PF : Primary Flow Rate (l/min)
### 0x26
| 0 | 1 | 2 |  3  | 4  | 5  | 6  |  7 |   8  |  9   |  10 |  11 | 12 | 13 | 14 |
|---|---|---|-----|----|----|----|----|------|------|-----|-----|----|----|----|
|   |   |   | Pwr | OM | HW |OpZ1|OpZ2| HWPS | HWSP | HSP | HSP | SP | SP |    |
* Pwr - Power
  * 0 : Standby
  * 1 : On
* OM Operation Mode
  * 0 : Off
  * 1 : Hot Water On
  * 2 : Heating On
  * 5 : Frost Protect
* HW - Hot Water Mode
  * 0 : Normal
  * 1 : Economy
* Op - Operation Mode (Zone 1 / Zone 2): 
  * 0 : Temperature Mode
  * 1 : Flow Control Mode
  * 2 : Compensation Curve Mode
* HWSP : HotWater SetPoint * 100;
* HSP : Heating Flow SetPoint * 100;
* SP : Unknown Setpoint:
### 0x28 - Various Flags
|   0   | 1 | 2 | 3 | 4  | 5  | 6 |  7  | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|-------|---|---|---|----|----|---|---|---|---|----|----|----|----|----|----|----|
| 0x28  |   |   |   | HM | HT |   |   |   |   |    |    |    |    |    |    |    |  
* HM : Holiday Mode
* HT : Hot Water Timer
### 0x29 - 
|   0   | 1 | 2 | 3 |  4  |  5  |  6  |  7  | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|-------|---|---|---|-----|-----|-----|-----|---|---|----|----|----|----|----|----|----|
| 0x29  |   |   |   | Z1T | Z1T | Z2T | Z2T |   |   |    |    |    |    |    |    |    |  
* Z1T : Zone1 Temperature * 100
* Z2T : Zone2 Temperature * 100
### 0xA1 - Consumed Energy
|   0   | 1 | 2 | 3 |  4  |  5  |  6  |  7  | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|-------|---|---|---|-----|-----|-----|-----|---|---|----|----|----|----|----|----|----|
| 0xA1  | Y | M | D | Heat|     |     |Cool |   |   |DHW |    |    |    |    |    |    |  
* Y: Year
* M: Month
* D: Day
### 0xA2 - Delivered Energy
|   0   | 1 | 2 | 3 |  4   |  5  |  6  |  7   | 8 | 9 | 10  | 11 | 12 | 13 | 14 | 15 | 16 |
|-------|---|---|---|------|-----|-----|------|---|---|-----|----|----|----|----|----|----|
| 0xA2  | Y | M | D | Heat |     |     | Cool |   |   | DHW |    |    |    |    |    |    |  
* Y: Year
* M: Month
* D: Day
