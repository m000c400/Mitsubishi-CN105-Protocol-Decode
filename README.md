# Mitsubishi-CN105-Protocol-Decode
For Ecodan ASHP Units
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
## Checksum
Checksum = 0xfc - Sum ( PacketBytes[0..20]) ;
# Get Request - Packet Type 0x41
## Payload
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|---|---|---|---|---|---|---|---|---|---|----|----|----|----|----|----|----|
| Command | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0  | 0  |  0 |  0 |  0 |  0 |  0 |
## Available Commands 
Active commands so far identified, 0x00 to 0xff. Commands not listed appear to generate no resaponse. Some command listed have empty, payload 0x00, response.
| Command | Brief Description |
| ------- | ----------- |
| 0x00 | Unknown |
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

# Get Response - Packet Type 0x62
## Payload
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|---|---|---|---|---|---|---|---|---|---|----|----|----|----|----|----|----|
| Command | . | . | . | . | . | . | . | . | . | .  | .  |  . |  . |  . |  . |  . |
## Available Commands 
Responses so far identified.
| Command | Brief Description |
| ------- | ----------- |
| 0x01 | Time & Date |
| 0x05 | Various Flags |
| 0x09 | Zone 1 & 2 Temperatures and Setpoints, Hot Water Setpoint |
| 0x0b | Zone 1 & 2 and Outside |Temperature
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
### 0x05 - Varoius Flags
|   0   | 1 | 2 | 3 | 4 | 5 | 6 |  7  | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|-------|---|---|---|---|---|---|-----|---|---|----|----|----|----|----|----|----|
| 0x01  |   |   |   |   |   |   | HWB |   |   |    |    |    |    |    |    |    |  
* HWB : Hot Water Boost
### 0x09 - Zone 1 & 2 Temperatures and Setpoints, Hot Water Setpoint
| 0    | 1    | 2    | 3    | 4    | 5    | 6    | 7    | 8    | 9    | 10   | 11 | 12 | 13 | 14 | 15 | 16 |
|------|------|------|------|------|------|------|------|------|------|------|----|----|----|----|----|----|
| 0x09 | Z1T  | Z1T  | Z2T  | Z2T  | Z1ST | Z1SP | Z2SP | Z2SP | HWSP | HWSP |    |    |    |    |    |    |
* Z1T : Zone1 Target Temperature * 100
* Z2T : Zone2 Target Temperature * 100;
* Z1SP : Zone 1 Flow SetFlow Setpoint * 100
* Z2SP : Zone 3 Flow SetFlow Setpoint * 100
* HWSP : Hot Water Setpoint * 100;
### 0x0b
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|---|---|---|---|---|---|---|---|---|---|----|----|----|----|----|----|----|
| 0x0b | Z1.u | Z1.l |    |    |   |  | Z2.u | Z2.l |  |  | O | |  |   |    |    |    |    |    |   |
* Zone1 Temperature:  ((Z1.u <<8 ) + Z1.l) / 100;
* Zone2 Temperature:  ((Z2.u <<8 ) + Z2.l) / 100;
* Outside Temp     :  (O/2) -40; 
### 0x0c
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|---|---|---|---|---|---|---|---|---|---|----|----|----|----|----|----|----|
| 0x0c | F.u | F.l |  | R.u |R.l |  | Hw.u | Hw.l |   |   |    |    |    |    |    |
* Water Out Temperature  :  ((F.u <<8 ) + F.l) / 100;
* Water Return Temperature:  ((R.u <<8 ) + R.l) / 100;
* Hot Water Temperature              :  ((HW.u <<8 ) + HW.l) / 100;
### 0x0d
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|---|---|---|---|---|---|---|---|---|---|----|----|----|----|----|----|----|
| 0x0d| F.u | F.l |  | R.u |R.l |  |  |  |   |   |    |    |    |    |    |
* Boiler Flow Temperature  :  ((F.u <<8 ) + F.l) / 100;
* Boiler Return Temperature:  ((R.u <<8 ) + R.l) / 100;
### 0x26
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 |
|---|---|---|---|---|---|---|---|---|---|----|----|----|----|----|
|  |  |  | Pwr| OM | HW | Op  |  | HWPS | HWSP | EXTSP |  EXTSP | EXTFL   | EXTFL |    |

* HotWater SetPoint  :  (( <<8 ) + F.l) / 100;
* External Flow SetPoint:  (( <<8 ) + R.l) / 100;
* External Flow Temp:
* Pwr - Power
  * 0 : Standby
  * 1 : On
* OM Operation Mode
  * 0 : Off
  * 1 : Hot Water On
  * 2 : Heating On
  * 5 : Possibly Frost Protect
* HW - Hot Water Mode
  * 0 : Normal
  * 1 : Economy
* Op - Operation Mode: 
  * 0 : Temperature Mode
  * 1 : Flow Control Mode
  * 2 : Compensation Curve Mode

 



