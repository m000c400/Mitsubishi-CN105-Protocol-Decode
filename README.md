# Mitsubishi-CN105-Protocol-Decode
- [Physical](#physical)
- [Command Format](#command-format)
  * [Checksum](#checksum)
  * [Preamble](#preamble)
    + [Query Preamble](#query-preamble)
    + [Response Preamble](#response-preamble)
- [Commands](#commands)
  * [0x01](#0x01)
  * [0x09](#0x09)
  


# Physical
Serial, 2400, 8, E, 1

# Command Format

| Preamble | Command | Payload | Checksum |
| --- | --- | --- | --- |
| 5 Bytes | 1 Byte | 15 Bytes | 1 Byte |

## Checksum

Checksum = 0xfc - Sum ( PacketBytes[0..20]) ;
## Preamble
### Query Preamble
| 0 | 1 | 2 | 3 | 4 |
| ---  | ---  | ---  | ---  | ---  |
| 0xfc | 0x42 | 0x02 | 0x7a | 0x10 |

### Response Preamble

| 0 | 1 | 2 | 3 | 4 |
| ---  | ---  | ---  | ---  | ---  |
| 0xfc | 0x62 | 0x02 | 0x7a | 0x10 |

# Commands
| Command | Description |
| ------- | ----------- |
| 0x00 |     |
| [0x01](#0x01) | Time & Date |
| 0x02 |     |
| 0x03 |     |
| 0x04 |     |
| 0x05 |     |
| 0x06 |     |
| 0x07 |     |
| 0x08 |     |
| [0x09](#0x09) | Zone1, Zone2, FlowSetPoint, FlowTemp, WaterSetPoint |
| 0x0a |     |
| 0x0b | Zone1, Outside |
| 0x0c | WaterHeatingFeed, WaterHeatingReturn, HotWater |
| 0x0d | fBoilerFlow,  fBoilerReturn |
| 0x0e |     |
| 0x0f |     |
| 0x10 |     |
| 0x11 |     |
| 0x12 |     |
| 0x13 |     |
| 0x0e |     |
| 0x0f |     |
| 0x10 |     |
| 0x11 |     |
| 0x12 |     |
| 0x13 |     |
| 0x14 |     |
| 0x15 |     |
| 0x16 |     |
| 0x17 |     |
| 0x18 |     |
| 0x19 |     |
| 0x1a |     |
| 0x1b |     |
| 0x1c |     |
| 0x1d |     |
| 0x1e |     |
| 0x1f |     |
| 0x20 |     |
| 0x21 |     |
| 0x22 |     |
| 0x23 |     |
| 0x24 |     |
| 0x25 |     |
| 0x26 | HWSetPoint, ExternalSetPoint, ExternalFlowTemp, Operation Mode |

## 0x01
### Query
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 |
|---|---|---|---|---|---|---|---|---|---|----|----|----|----|----|
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0  | 0  |  0 |  0 |  0 |

### Response
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 |
|---|---|---|---|---|---|---|---|---|---|----|----|----|----|----|
| Y | M | D | h | m | s |   |   |   |   |    |    |    |    |    |

* Y: Year
* M: Month
* D: Day
* h: Hour
* m: Minute
* s: Second

## 0x09
### Query
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 |
|---|---|---|---|---|---|---|---|---|---|----|----|----|----|----|
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0  | 0  |  0 |  0 |  0 |

### Response
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 |
|---|---|---|---|---|---|---|---|---|---|----|----|----|----|----|
| Z1.u | Z1.l | Z2.u | Z2.l | SP.u | SP.l | FT.u | FT.l | HWSP.u  | HWSP.l  |    |    |    |    |    |

* Zone1 Temperature:  ((Z1.u * 256 ) + Z1.l) / 100;
* Zone2 Temperature:  ((Z2.u * 256 ) + Z2.l) / 100;
* Flow Setpoint    :  ((SP.u * 256 ) + SP.l) / 100;
* Flow Temperature :  ((FT.u * 256 ) + FT.l) / 100;
* Hot Water Temp   :  ((HW.u * 256 ) + HW.l) / 100;


