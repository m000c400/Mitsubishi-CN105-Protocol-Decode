# Hardware

Supported Hardware is ESP8266 ebay sold hardware: https://www.ebay.co.uk/itm/325967595655



# ESP8266 Ebay Hardware Recovery (Gen1)


1. Download the files from the [/build](https://github.com/F1p/Mitsubishi-CN105-Protocol-Decode/tree/master/build/esp8266.esp8266.generic/) folder.

2. Disconnect from CN105, Unclip the lid, slide out the circuit board

3. Plug the pins into the programming board, both USB ports at the same side

4. Connect the USB cable to the bottom board (programming carrier board), locate the COM port your device is

5. Hold the flash button down, while holding then press "reset". You can then release both buttons.

6. Visit [https://web.esphome.io/?dashboard_install](https://web.esphome.io/?dashboard_install) and connect to device and upload/install file.
   You can do WiFi setup via onboard Access Point, while setting MQTT server




# M5Stack Atom S3 Lite (Gen2)

1. Download the files from the [/build](https://github.com/F1p/Mitsubishi-Ecodan-Bridge-CN105/tree/master/build/esp32.esp32.m5stack-atoms3) folder.

2. Visit [https://web.esphome.io/?dashboard_install](https://web.esphome.io/?dashboard_install) and connect to USB-C device and upload/install the *.merged.bin file.
   You can do WiFi setup via onboard Access Point, while setting MQTT server




# Wemos D1 Mini

1. Download the files from the [/build](https://github.com/F1p/Home-Assistant-Mitsubishi-Ecodan-CN105-to-MQTT/tree/master/build/esp8266.esp8266.d1_mini) folder.

2. Visit [https://web.esphome.io/?dashboard_install](https://web.esphome.io/?dashboard_install) and connect to USB-C device and upload/install file.
   You can do WiFi setup via onboard Access Point, while setting MQTT server

5. The Pins on the Wemos D1 Mini are: D0 = Tx, D5 = Rx
