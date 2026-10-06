
# Detailed Setup Instructions


### Home Assistant Setup

In Home Assistant, first we must install the MQTT Server. 
Visit Settings > Add-ons > Add-on Store > Search/select “Mosquitto broker” and install:
![MosquittoInstall](https://github.com/F1p/Mitsubishi-CN105-Protocol-Decode/blob/master/documentation/images/Setup_Mosquitto.png)


Install the MQTT Integration
Visit Settings > Devices & services > Add Integration > MQTT
![MQTTInstall](https://github.com/F1p/Mitsubishi-CN105-Protocol-Decode/blob/master/documentation/images/Setup_MQTT.png)



By default the MQTT Username & Password will be the same as your Home Assistant login, you will need this in later steps too
Configure the MQTT Integration: 

![MQTTInstall1](https://github.com/F1p/Mitsubishi-CN105-Protocol-Decode/blob/master/documentation/images/Setup_MQTT_1.png)

Enter details on the first page, no changes required on the second page of options.
![MQTTInstall2](https://github.com/F1p/Mitsubishi-CN105-Protocol-Decode/blob/master/documentation/images/Setup_MQTT_2.png)




### Physical Connection


For your safety, Power down via the controller & isolate the electricity supply prior to opening covers!
Remove the screws, slide & remove the cover to expose the Circuit Board of the **indoor unit**
![RemoveCover](https://github.com/F1p/Mitsubishi-CN105-Protocol-Decode/blob/master/documentation/images/Setup_Covers.png)

Route the cable through holes, then connect the dongle to the CN105 RED connector on your heat pump board:
![InstallPlug](https://github.com/F1p/Mitsubishi-CN105-Protocol-Decode/blob/master/documentation/images/Setup_CN105.png)



### Adapter Setup

Restore power to your Heat Pump, the LED will show blue on the Ecodan Bridge device yet and an access point “Ecodan Bridge AP” should be visible

Connect to the network and in a web browser, visit the address http://192.168.4.1 to Select “Configure":
![MainMenu](https://github.com/F1p/Mitsubishi-CN105-Protocol-Decode/blob/master/documentation/images/Setup_MainMenu.png)



Enter WiFi Details and scroll down to configure your Home Assistant Settings in the highlighted fields. You will need your Home Assistant IP address (e.g. 192.168.0.1) or use "homeassistant.local":

![Fields](https://github.com/F1p/Mitsubishi-CN105-Protocol-Decode/blob/master/documentation/images/Setup_Fields.png)



Press Save, the unit will restart - 
When connected to WiFi & MQTT the LED on the unit will display Green
When connected to WiFi, but not MQTT the LED on the unit will display Orange 


If you need to make changes to MQTT settings, you can now visit the IP address or http://heatpump.local of the unit to make configuration changes. 



Once both units are displaying the Green LED, values should be populating within Home Assistant.

![Discovery](https://github.com/F1p/Mitsubishi-CN105-Protocol-Decode/blob/master/documentation/images/Setup_MQTT_Devices.png)

It can be helpful to check with a program such as: mqtt-explorer.com 

You can configure your dashboards with cards such as climate, flow, hot water boost etc.

![UnitDiscovered](https://github.com/F1p/Mitsubishi-CN105-Protocol-Decode/blob/master/documentation/images/Setup_UnitDiscoveredinHA.png)





### Firmware Updates


Visit the "[Releases](https://github.com/F1p/Mitsubishi-CN105-Protocol-Decode/releases)" page on GitHub

Check the adapter type you have, and download the matching ".bin" file:
![Update_MatchType](https://github.com/F1p/Mitsubishi-CN105-Protocol-Decode/blob/master/documentation/images/Update_MatchType.png)




Visit the Adapter local webpage, e.g. via http://heatpump.local/update Or via the main menu

Select the file you download, and press "Update"

![Update_MatchType](https://github.com/F1p/Mitsubishi-CN105-Protocol-Decode/blob/master/documentation/images/Update_Upload.png)


