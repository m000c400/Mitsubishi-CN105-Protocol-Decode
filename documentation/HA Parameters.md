# Home Assistant Parameters Detailed Explanations

# Control
| Name | Options      | Description of Function      |
|-------|------------------|----------------|
|  DHW Boost | On/Off      |  The Ecodan will perform a Normal or Eco Hot Water run at the transition of any prohibited to not prohibited, regardless of the temperature drop, this switch utilises this function to run |
|  Fast DHW Boost | On/Off      | This is the Ecodan's Forced Hot Water mode, compressor frequency and output power are maximum - compromising efficiency for speed to heat hot water at maximum speed |
|  Glycol Strength | 0%/10%/20%/30%  | The heat coefficient of water varies with the strength of glycol used, the sensor "Computed Heat Output" will use this variable to determine the coefficient of water to be used  |
|  Outdoor Unit Size (kW) | Various  | The Computed Input Power varies depending on the outdoor unit size, to determine a suitable multiplier this value is used  |
|  Zone Operation Mode | Heating Temperature (Heating Auto Adapt), Heating Flow (Heating Fixed Flow), Heating Compensation (Heating Weather Compensation), Cooling Temperature (Cooling Auto Adapt), Cooling Flow (Cooling Fixed Flow), Dry Up  | Some configurations require Zone1 & Zone2 to be fixed to the same control mode, Zone2 may not be possible to modify if this is your case |
|  Server Control Mode | On/Off  | Server Control Mode is required to control the Prohibits over this protocol, entering Server Control Mode will ignore any schedules for prohibits in the FTC. A globe symbol appears on your Main controller |
|  Flow Thermostats | On/Off  | You must be in a Flow control Mode to change flow thermostats, current temperature can be obtained from the sensors |

# Sensors
| Name | Unit      | Description of Function      |
|-------|------------------|----------------|
|   Heat Pump Input Power | kW (floor/ceiling)      | The value provided by the FTC for input power (to 0 d.p)    |
|   Heat Pump Computed Input Power | kW      | The estimated power input calculated by the bridge controller, based on the unit size set in the control section    |
|   Heat Pump Output Power | kW (floor/ceiling)      | The value provided by the FTC for output power (to 0 d.p)    |
|   Heat Pump Computed Heat Output Power | kW       | The estimated Heating power output calculated by the bridge controller, based on the glycol strngth set in the control section   |
|   Heat Pump Computed Cool Output Power | kW       | The estimated Cooling power output calculated by the bridge controller, based on the glycol strngth set in the control section  |
|   Instant CoP | n/a       | The estimated Instant CoP computed by the bridge, based on Computed Input & Output Power  |
|   "Yesterday" figures | n/a       | The energy consumed/delivered & CoP, estimated by the FTC and matching the stats on the Main Controller |

# Service Codes
These depend on your outdoor unit and can be located within the [Service Manuals specific to your unit](https://www.manualslib.com/manual/795612/Mitsubishi-Electric-Par-21maa.html?page=51)

*Using MQTT Explorer or Home Assistant Automations, you can publish Service Codes to: Ecodan/ASHP/Command/System/Svc*

*Results will be allocated to their standard topic location, or for ones not published the topic: Ecodan/ASHP/Status/AdvancedTwo under "LastSvc": 995 and "LastSvcReply": 0*

This can be used to poll certain outdoor sensors at an increased rate, warning, this may reduce the speed of other operations



| Request Code | Name | Unit      | Description of Function      |
|-------|------------------|----------------|----|
| 3 |   Compressor-Number of operation times      | 100 Times  |  |
| 4 | Discharge temperature (TH4) | degC      |     |
| 5 | Outdoor unit -Liquid pipe 1 temperature (TH3) | degC      |     |
| 6 | Water inlet temperature (TH32) - ONLY AVAILABLE IN MQTT Explorer | degC      |     |
| 7 | Outdoor unit-Plate HEX pipe temperature (TH6)  | degC      |     |
| 8 | Outdoor unit-Suction pipe temperature (TH33) | degC      |     |
| 9 | Outdoor unit-Ambient temperature (TH7) | degC      |     |
| 10 | Outdoor unit-Heatsink temperature (TH8) | degC      |     |
| 12 | Discharge superheat (SHd) - ONLY AVAILABLE IN MQTT Explorer | degC      |     |
| 13 | Sub-cool (SC) | degC      |     |
| 14 | Condensing temperature (T63HS) | degC      |     |
| 19 | Outdoor unit-Fan 1 speed | rpm      |     |
| 20 | Outdoor unit-Fan 2 speed | rpm      |     |
| 22 | LEV (A) opening | Pulses  |     |
| 23 | LEV (B) opening | Pulses      |     |

# Adapter Special Service Codes
In addition, there are special service codes
| Request Code | Name |  Description of Function      | Applicable Firmware | 
|-------|------------------|-----------|---------|
| 999 |   Restart Adapter      |  The Adapter will perform a restart  | All|
| 998 |   Disconnect from FTC      |  The Adapter will close connection gracefully with the FTC  |Home Assistant Only|
| 997 |   Block Write Requests from MELCloud      |  The Adapter will not pass on any write requests from MELCloud to the FTC  | All (In MELPump, Code 997 toggles this both on/off)|
| 996 |   Enable Write Requests from MELCloud      |  The Adapter will allow any write requests from MELCloud to the FTC (Default Action)  | Home Assistant|
| 994 |   Check for OTA Updates      |  The Adapter will Check the Server for any Updates | MELPump |
| 993 |   Poll FTC For Version Information      |  Normally performed at the start, this ad-hoc method can be used to call the FTC for version information | All |
| 992 |   Short Cycle Protection      |  Toggles the Short Cycle Protection (Onboard Compensation Curve Mode) On/Off | MELPump |
| 880 to 900 |   Short Cycle Protection Max. Flow. Overshoot      |  The Maximum Permitted Overshoot when running Short Cycle Protection where 880 = 0C and 900 = 20C | MELPump |
