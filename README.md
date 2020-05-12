# Mitsubishi-CN105-Protocol-Decode
For Ecodan ASHP Units
- [Physical](#physical)
- [Command Format](#command-format)
- [Header](#Header)
  * [Sync Byte](#sync-byte)
  * [Packet Type](#packet-type)
  * [Length](#length)
- [Checksum](#checksum)
- Set Request
- Set Response
- Get Request
- Get Response
  
# Physical
Serial, 2400, 8, E, 1
# Command Format
| Header | Payload | Checksum |
|--------|---------|----------|
| 5 Bytes | 16 Bytes | 1 Byte |
# Header
| Sync Byte | Packet Type | Uknown | Unknown | Payload Size |
|---|---|--|---|---|
| 0xfc | Type | 0x02 | 0x7a | Length |
## Sync Byte 
0xfc
## Packet Type
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
##Length
Payload Size (Bytes)
# Checksum
Checksum = 0xfc - Sum ( PacketBytes[0..20]) ;
# Set Request
## Payload
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|---|---|---|---|---|---|---|---|---|---|----|----|----|----|----|----|----|
| Command | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0  | 0  |  0 |  0 |  0 |  0 |  0 |
# Set Response

# Get Request
## Payload
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|---|---|---|---|---|---|---|---|---|---|----|----|----|----|----|----|----|
| Command | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0  | 0  |  0 |  0 |  0 |  0 |  0 |
### Command 
| Command | Description |
| ------- | ----------- |
| 0x00 |     |
| 0x01 | Time & Date |
| 0x09 | Zone1, Zone2, FlowSetPoint, FlowTemp, WaterSetPoint |
| 0x0b | Zone1, Outside |
| 0x0c | WaterHeatingFeed, WaterHeatingReturn, HotWater |
| 0x0d | fBoilerFlow,  fBoilerReturn |
| 0x26 | HWSetPoint, ExternalSetPoint, ExternalFlowTemp, Operation Mode |
# Get Reponse
## Payload
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|---|---|---|---|---|---|---|---|---|---|----|----|----|----|----|----|----|
| Command | . | . | . | . | . | . | . | . | . | .  | .  |  . |  . |  . |  . |  . |
### Command 
| Command | Description |
| ------- | ----------- |
| 0x00 |     |
| [0x01](#0x01) | Time & Date |
| [0x09](#0x09) | Zone1, Zone2, FlowSetPoint, FlowTemp, WaterSetPoint |
| [0x0b](#0x0b) | Zone1, Outside |
| [0x0c](#0x0c) | WaterHeatingFeed, WaterHeatingReturn, HotWater |
| [0x0d](#0x0d) | fBoilerFlow,  fBoilerReturn |
| [0x26](#0x26) | HWSetPoint, ExternalSetPoint, ExternalFlowTemp, Operation Mode |
### 0x01
|   0   | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|-------|---|---|---|---|---|---|---|---|---|----|----|----|----|----|----|----|
| 0x01  | Y | M | D | h | m | s |   |   |   |    |    |    |    |    |    |    |  
* Y: Year
* M: Month
* D: Day
* h: Hour
* m: Minute
* s: Second
### 0x09
| 0    | 1    | 2    | 3    | 4    | 5    | 6    | 7    | 8    | 9       | 10      | 11 | 12 | 13 | 14 | 15 | 16 |
|------|------|------|------|------|------|------|------|------|---------|---------|----|----|----|----|----|----|
| 0x09 | Z1.u | Z1.l | Z2.u | Z2.l | SP.u | SP.l | FT.u | FT.l | HWSP.u  | HWSP.l  |    |    |    |    |    |    |
* Zone1 Temperature:  ((Z1.u <<8 ) + Z1.l) / 100;
* Zone2 Temperature:  ((Z2.u <<8 ) + Z2.l) / 100;
* Flow Setpoint    :  ((SP.u <<8 ) + SP.l) / 100;
* Flow Temperature :  ((FT.u <<8 ) + FT.l) / 100;
* Hot Water Temp   :  ((HW.u <<8 ) + HW.l) / 100;
### 0x0b
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 |
|---|---|---|---|---|---|---|---|---|---|----|----|----|----|----|----|----|
| 0x0b | Z1.u | Z1.l |    |    |   |  | Z2.u | Z2.l |  |  | O | |  |   |    |    |    |    |    |   |
* Zone1 Temperature:  ((Z1.u <<8 ) + Z1.l) / 100;
* Zone2 Temperature:  ((Z2.u <<8 ) + Z2.l) / 100;
* Outside Temp     :  (O/2) -39; 

## 0x0c
### Query
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 |
|---|---|---|---|---|---|---|---|---|---|----|----|----|----|----|
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0  | 0  |  0 |  0 |  0 |

### Response
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 |
|---|---|---|---|---|---|---|---|---|---|----|----|----|----|----|
| F.u | F.l |  | R.u |R.l |  | Hw.u | Hw.l |   |   |    |    |    |    |    |

* Water Heater Feed Temperature  :  ((F.u <<8 ) + F.l) / 100;
* Water Heater Return Temperature:  ((R.u <<8 ) + R.l) / 100;
* Water Temperature              :  ((HW.u <<8 ) + HW.l) / 100;

## 0x0d
### Query
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 |
|---|---|---|---|---|---|---|---|---|---|----|----|----|----|----|
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0  | 0  |  0 |  0 |  0 |

### Response
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 |
|---|---|---|---|---|---|---|---|---|---|----|----|----|----|----|
| F.u | F.l |  | R.u |R.l |  |  |  |   |   |    |    |    |    |    |

* Boiler Flow Temperature  :  ((F.u <<8 ) + F.l) / 100;
* Boiler Return Temperature:  ((R.u <<8 ) + R.l) / 100;

## 0x26
### Query
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 |
|---|---|---|---|---|---|---|---|---|---|----|----|----|----|----|
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0  | 0  |  0 |  0 |  0 |

### Response
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 |
|---|---|---|---|---|---|---|---|---|---|----|----|----|----|----|
|  |  |  |  | |  |  |  |   |   |    |    |    |    |    |

* HotWater SetPoint  :  (( <<8 ) + F.l) / 100;
* External Flow SetPoint:  (( <<8 ) + R.l) / 100;
* External Flow Temp:
* Operation Mode: 
  * 0 : Temperature Mode
  * 1 : Flow Control Mode
  * 2 : Compensation Curve Mode


