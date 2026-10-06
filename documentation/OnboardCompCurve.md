# Using the onboard Compensation Curve



### About
The software has the ability to store a custom compensation curve onboard - this overcomes some limitations with the Ecodan and allows advanced features to be input.

* The Ecodan Main Room Controller (MRC) has the ability to design a curve with a maximum of 3 points, there is no limit to the number of points which can be sent to the CN105 Ecodan Bridge device.
* There is also no ability to add an +/- offset to the current curve remotely, only by adjusting on the the controller screen. By moving the curve onto the CN105 Ecodan Bridge, an offset can be adjusted remotely.
* The Ecodan uses the Outside Air Temperature (OAT) sensor located on the back of the outdoor unit, this sensor can be influenced by the likes of direct sunlight. By moving the curve onto the CN105 Ecodan Bridge it's possible to use another temperature source to determine the flow temperature.
* The Ecodan cannot automatically adjust for other influencing factors, such as heat loss due to wind or solar gain. By moving the curve onto the CN105 Ecodan Bridge it's possible to automate the offset when conditions may influence the building.


The device can continue to calculate and input to the curve if the connection is broken.



### How to Design, Modify and Operate

The Ecodan is to be placed in Fixed Flow mode, as the value is calculated by the device it will then adjust the flow temperature setpoint automatically which recreates the method the Ecodan uses.
By activating the onboard compensation curve, if not already in Fixed Flow the software will change your Ecodan to this mode.



### Designing a Curve

Similar to the main controller screen, there is a flow temperature and an outside temperature:
![Comp Curve Graph](https://github.com/F1p/Mitsubishi-CN105-Protocol-Decode/blob/master/documentation/images/Curve_Points.png)

The corrosponding data points are:

| Outside Temperature (C) | Flow Temperature (C) |
|--------|---------|
| -10 | 60 |
| 0 | 40 |
| +5 | 35 |
| +10 | 27 |
| +15 | 32 |



The design for Zone1 can be different to Zone2, if your system has suitable Complex 2 Zone hardware (i.e. mixing) to support different flow temperatures on different zones

The Curve is recorded and sent as JSON to be saved on the device, using the example above, the JSON would look like so:

```javascript
{
  "base": {
    "zone1": {
      "curve": [
        {
          "flow": 60,
          "outside": -10
        },
        {
          "flow": 35,
          "outside": 0
        },
        {
          "flow": 27,
          "outside": 10
        },
        {
          "flow": 32,
          "outside": 15
        }
      ]
    },
    "zone2": {
      "curve": [
        {
          "flow": 60,
          "outside": -10
        },
        {
          "flow": 35,
          "outside": 0
        },
        {
          "flow": 27,
          "outside": 10
        },
        {
          "flow": 32,
          "outside": 15
        }
      ]
    }
  }
}
```


### Programming or Modifying the Curve (Base)

Using MQTT Explorer, we can send our design, in JSON to the topic: Ecodan/ASHP/**Command**/System/CompCurve



```javascript
{
  "base": {
    "zone1": {
      "curve": [
        {
          "flow": 60,
          "outside": -10
        },
        {
          "flow": 35,
          "outside": 0
        },
        {
          "flow": 20,
          "outside": 15
        },
        {
          "flow": 10,
          "outside": 20
        }
      ]
    },
    "zone2": {
      "curve": [
        {
          "flow": 60,
          "outside": -10
        },
        {
          "flow": 35,
          "outside": 0
        },
        {
          "flow": 20,
          "outside": 15
        }
      ]
    }
  }
}
```

![Publish Config](https://github.com/F1p/Mitsubishi-CN105-Protocol-Decode/blob/master/documentation/images/Publish_Curve.png)




You can verify the curve has been saved, looking at the Ecodan/ASHP/**Status**/CompCurve topic:
![Config Readback](https://github.com/F1p/Mitsubishi-CN105-Protocol-Decode/blob/master/documentation/images/Curve_Status.png)





### Enable or Disable the Mode
In JSON to the topic: Ecodan/ASHP/**Command**/System/CompCurve

```javascript
{   
    "zone1": {
        "active": true
    }
}
```

### Using Room Influence, Setpoint & Temperatures

It is possible to send Room Influence values, which will influence the flow setpoint based on the difference between current temperature and setpoint of a room sensor.
You can use both Local Ecodan measurements and External temperature sensors & setpoint.

For "local" system temperature setpoint and temperature feedback, e.g. from the Main Room Controller (MRC) or Wireless Controllers set "use_local_tsensor": true and the setpoint and current temperature will be used
For "remote" system temperature setpoint and temperature feedback, e.g. from another sensor is default "use_local_tsensor": false


In JSON to the topic same: Ecodan/ASHP/**Command**/System/CompCurve

```javascript
{   
    "zone1": {
      "room_influence_active": true,
      "use_local_tsensor": false,
      "room_setpoint": 21,
      "room_temperature": 19.3,
  }
}
```

Publish Internal Temperatures from Extenal Sensors on change with Automations:


```yaml
alias: Publish Zone 1 Temperature from HA to Bridge
description: ""
triggers:
  - trigger: state
    entity_id:
      - sensor.bedroom_temperature
conditions: []
actions:
  - action: mqtt.publish
    metadata: {}
    data:
      evaluate_payload: false
      qos: "0"
      topic: Ecodan/ASHP/Command/System/CompCurve
      payload: >-
        { "zone1": {"room_temperature": {{ states('sensor.bedroom_temperature')|float(0) }} }}
mode: single
```


Additionally, you can by-pass Home Assistant automations if your temperature sensor supports sending HTTP requests (e.g. Shelly devices with Automations) directly.
Sending the payload to the following endpoints, for either current temperature zXtemp or zXsetpoint:

```http://heatpump.local/webhook?z1temp=22.1```
```http://heatpump.local/webhook?z1setpoint=22.0```
```http://heatpump.local/webhook?z2temp=22.1```
```http://heatpump.local/webhook?z2setpoint=22.1```
![Publish Parameters](https://github.com/F1p/Mitsubishi-CN105-Protocol-Decode/blob/master/documentation/images/shelly_H&t.png)


### AC Remote Thermostat Reading
#For AC Users, you can send "Remote Temperature Sensor" probe readings from 3rd party thermostats, e.g. Shelly H&T to act as your current room temperature within HA or directly using webhooks:

```http://heatpump.local/webhook?actemp=22.1```


### Sending Offsets & Outdoor Temperatures

In a similar way, you can make modification to the Offsets (+/- of the calculated Flow Setpoint) by sending JSON: 

Up to three Offsets exist, all act in the same way by adding or subtracting to the Flow Setpoint calculated on the base curve.
* Manual Offset is intended for users to adjust via a Dashboard
* Wind Offset is intended if you require additional heat at higher windspeed, usually calculated from an automation
* Temp Offset is intended if you reduce flow when solar gain is high, usually calculated from an automation


In JSON to the topic same: Ecodan/ASHP/**Command**/System/CompCurve

```javascript
{   
    "zone1": {
        "manual_offset": 0,
        "wind_offset": 1,
        "temp_offset": -2
  }
}
```

It might be helpful to add a number entity to configuration.yaml, to adjust this offset from within HA, like so:

```yaml
mqtt:
  number:
    - name: "Zone 1 Compensation Curve Offset"
      state_topic: "Ecodan/ASHP/Status/CompCurve"
      value_template: "{{ value_json.zone1.manual_offset }}"
      command_topic: "Ecodan/ASHP/Command/System/CompCurve"
      command_template: >
        {
          "zone1":
            {
              "manual_offset": {{ value }} 
            }
        }
      unit_of_measurement: "°C"
      min: -5
      max: 5
      step: 0.5
      unique_id: "ecodan_ashp_z1_comp_curve_offset"
```


![Publish Parameters](https://github.com/F1p/Mitsubishi-CN105-Protocol-Decode/blob/master/documentation/images/Partial_Publish_Curve.png)



The value of Outside Air Temperature (OAT) used in the curve calculation by default is from the sensor located on the unit itself, however you can choose to use your own value for Outdoor Air Temperature in the following way:


In JSON to the topic same: Ecodan/ASHP/**Command**/System/CompCurve

Set Use Local Outdoor as False:
```javascript
{   
    "use_local_outdoor": false
}
```

Provide a regularly updating Outdoor Air Temperature Value and ensure it is published when home assistant starts for example:
```javascript
{   
    "cloud_outdoor": 14.3
}
```    
![Publish Parameters](https://github.com/F1p/Mitsubishi-CN105-Protocol-Decode/blob/master/documentation/images/CompCurve_Automation.png)


```yaml
alias: Publish Temperature from HA Weather to Bridge
description: ""
triggers:
  - trigger: state
    entity_id:
      - weather.forecast_home
    attribute: temperature
conditions: []
actions:
  - action: mqtt.publish
    metadata: {}
    data:
      evaluate_payload: false
      qos: "0"
      topic: Ecodan/ASHP/Command/System/CompCurve
      payload: >-
        { "cloud_outdoor":{{ state_attr('weather.forecast_home','temperature')
        }} }
mode: single
```


![Publish Parameters](https://github.com/F1p/Mitsubishi-CN105-Protocol-Decode/blob/master/documentation/images/Data_Transfer.png)





If the MQTT connection is lost, the Bridge device will revert to using the local sensor.

NOTE: The FTC may still use the OAT sensor in it's processes, such as defrosting or frequency limiting - this value cannot influence those actions but only determining a Flow Temperature


