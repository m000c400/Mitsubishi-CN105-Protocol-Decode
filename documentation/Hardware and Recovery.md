# First Flash, Hardware and Recovery Information



M5Stack Atom S3 Lite

1. Download the .merged.bin from the [/build](https://github.com/F1p/Mitsubishi-CN105-Protocol-Decode/tree/master/build/esp32.esp32.m5stack_atoms3) folder.

2. Connect your board and install [ESPHome](https://web.esphome.io/?dashboard_install) from ESP Tool
   <img width="356" height="186" alt="image" src="https://github.com/user-attachments/assets/c5eef9c6-e3bc-4adc-9414-a4529ce760de" />

4. Select Install and upload the .merged.bin
 

6. The Pins on the M5Stack are: 1 = Tx, 2 = Rx (Onboard Grove Port)

On Proxy Carrier Boards: 38 = Rx from FTC, 39 = Tx from FTC, 8 = Rx from MELCloud, 7 = Tx from MELCloud




Wemos D1 Mini

1. Download the files from the [/build](https://github.com/F1p/Mitsubishi-CN105-Protocol-Decode/tree/master/build/esp8266.esp8266.d1_mini) folder.

2. Connect your board and install [ESPHome](https://web.esphome.io/?dashboard_install) from ESP Tool

3. The Pins on the Wemos D1 Mini are: D0 = Tx, D5 = Rx



Gen 1 ESP8266 (Generic)

1. Download the files from the [/build](https://github.com/F1p/Mitsubishi-CN105-Protocol-Decode/tree/master/build/esp8266.esp8266.generic) folder.

2. Connect your board and install [ESPHome](https://web.esphome.io/?dashboard_install) from ESP Tool

3. The Pins on the Wemos D1 Mini are: D0 = Tx, D5 = Rx


# Compile from scratch 
ESP32


I am using IDE: 2.3.5

Boards Manager > ESP32 by Espressif 

<img width="373" height="186" alt="Image" src="https://github.com/user-attachments/assets/5a85eaf1-67d7-45ba-a148-2a27988d00b7" />


Library Manager: 
ArduinoJson v7.4.3 by Benoit Blanchon

AsyncTCP v3.4.10 by ESP32Async

ESP Async WebServer v3.8.1 by ESP32Async

ESPAysncTCP v1.2.4 by dvarrel

ESP Telnet v2.2.3 by Lennart Hennigs

LiteLED v3.0.1 by Xylopyrographer

PubSubClient v2.8 by Nick O'Leary

WiFiManager v2.0.17 by tzapu


Compiled with M5Stack settings:

<img width="425" height="591" alt="Image" src="https://github.com/user-attachments/assets/2a693718-001a-486e-af43-db72ed0cfeb8" />






ESP8266

Boards Manager > ESP8266 by ESP8266 Community (v3.1.2)

Library Manager (Same as ESP32 above): ArduinoJson v7.4.3 by Benoit Blanchon 

AsyncTCP v3.4.10 by ESP32Async 

ESP Async WebServer v3.8.1 by ESP32Async 

ESPAysncTCP v1.2.4 by dvarrel 

ESP Telnet v2.2.3 by Lennart Hennigs 

LiteLED v3.0.1 by Xylopyrographer 

PubSubClient v2.8 by Nick O'Leary 

WiFiManager v2.0.17 by tzapu


Compiled with settings: 160MHz CPU, 4M (1M FS, 1M OTA), Balanced MMU
