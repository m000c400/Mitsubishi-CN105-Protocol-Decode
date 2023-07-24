/*
    Copyright (C) <2023>  <Phil Thomson>

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



#include <FS.h>           //this needs to be first
#include <ESP8266WiFi.h>  // needed for EPS8266
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h>  //https://github.com/tzapu/WiFiManager
#include <PubSubClient.h>
#include <ArduinoOTA.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <ESPTelnet.h>
#include "Ecodan.h"

int RxPin = 14;  //Rx
int TxPin = 16;  //Tx
int Activity_LED = 2;
int Reset_Button = 4;
int LDR = A0;
int Red_RGB_LED = 15;
int Green_RGB_LED = 12;
int Blue_RGB_LED = 13;

ECODAN HeatPump;
SoftwareSerial SwSerial;
WiFiClient NetworkClient;
PubSubClient MQTTClient(NetworkClient);
ESPTelnet TelnetServer;
WiFiManager MyWifiManager;

#include "config.h"
#include "TimerCallBack.h"
#include "Debug.h"
#include "OTA.h"
#include "MQTTConfig.h"



void HeatPumpQueryStateEngine(void);
void HeatPumpKeepAlive(void);
void Zone1Report(void);
void Zone1Report(void);
void HotWaterReport(void);
void SystemReport(void);
void TestReport(void);

TimerCallBack HeatPumpQuery1(500, HeatPumpQueryStateEngine);
TimerCallBack HeatPumpQuery2(60 * 1000, HeatPumpKeepAlive);


unsigned long previousMillis = 0;  // variable for comparing millis counter
int WiFiOneShot = 1;


void setup() {
  //DEBUGPORT.begin(DEBUGBAUD);
  HEATPUMP_STREAM.begin(SERIAL_BAUD, SERIAL_CONFIG, RxPin, TxPin);  // Rx, Tx
  //pinMode(RxPin, INPUT_PULLUP);  // Commented out for testing because we get nothing :(
  pinMode(Activity_LED, OUTPUT);   // Onboard LED
  pinMode(Reset_Button, INPUT);    // Pushbutton
  pinMode(LDR, INPUT);             // LDR
  pinMode(Red_RGB_LED, OUTPUT);    // Red (RGB) LED
  pinMode(Green_RGB_LED, OUTPUT);  // Green (RGB) LED
  pinMode(Blue_RGB_LED, OUTPUT);   // Blue (RGB) LED

  digitalWrite(Activity_LED, HIGH);
  digitalWrite(Red_RGB_LED, LOW);
  digitalWrite(Green_RGB_LED, LOW);
  digitalWrite(Blue_RGB_LED, LOW);

  HeatPump.SetStream(&HEATPUMP_STREAM);

  readSettingsFromConfig();
  initializeWifiManager();

  if (shouldSaveConfig) {
    saveConfig();
  }

  initializeMqttClient();

  setupTelnet();

  OTASetup(HostName.c_str());
  MQTTClient.setCallback(MQTTonData);
}

void loop() {

  handleMqttState();
  TelnetServer.loop();

  HeatPumpQuery1.Process();
  HeatPumpQuery2.Process();

  HeatPump.Process();
  ArduinoOTA.handle();

  if (WiFi.status() != WL_CONNECTED) {
    digitalWrite(Green_RGB_LED, LOW);  // Turn the Green LED Off
    if (WiFiOneShot == 1) {
      previousMillis = millis();
      WiFiOneShot = 0;
    }  // Oneshot to start the timer
    if (millis() - previousMillis >= 300000) {
      digitalWrite(Red_RGB_LED, HIGH);  // Flash the Red LED
      delay(500);
      digitalWrite(Red_RGB_LED, LOW);
      delay(500);
      digitalWrite(Red_RGB_LED, HIGH);
      delay(500);
      digitalWrite(Red_RGB_LED, LOW);
      delay(500);
      digitalWrite(Red_RGB_LED, HIGH);
      ESP.reset();
    }  // Wait for 5 mins to try reconnects then force restart
  } else {
    analogWrite(Green_RGB_LED, 64);  // Green LED on, 25% brightness
  }

  if (digitalRead(Reset_Button) == LOW) {  // Inverted (Pushed is LOW)
    digitalWrite(Red_RGB_LED, HIGH);       // Flash the Red LED
    delay(500);
    digitalWrite(Red_RGB_LED, LOW);
    delay(500);
    digitalWrite(Red_RGB_LED, HIGH);
    delay(500);
    digitalWrite(Red_RGB_LED, LOW);
    delay(500);
    digitalWrite(Red_RGB_LED, HIGH);
    ESP.reset();  // Then reset
  }
}


void HeatPumpKeepAlive(void) {
  HeatPump.KeepAlive();
  HeatPump.TriggerStatusStateMachine();
}

void HeatPumpQueryStateEngine(void) {
  HeatPump.StatusStateMachine();
  if (HeatPump.UpdateComplete()) {
    DEBUG_PRINTLN("Update Complete");
    digitalWrite(Green_RGB_LED, HIGH);  // Flash the Green LED full brightness
    delay(10);
    digitalWrite(Green_RGB_LED, LOW);
    if (MQTTReconnect()) {
      Zone1Report();
      Zone2Report();
      HotWaterReport();
      SystemReport();
      TestReport();
      StatusReport();
    }
  }
}


void MQTTonDisconnect(void* response) {
}

void MQTTonData(char* topic, byte* payload, unsigned int length) {
  payload[length] = 0;
  String Topic = topic;
  String Payload = (char*)payload;

  DEBUG_PRINT("Recieved ");
  DEBUG_PRINT(Topic.c_str());
  DEBUG_PRINT("Payload ");
  DEBUG_PRINTLN(Payload.c_str());

  if (Topic == MQTTCommandZone1TempSetpoint){HeatPump.SetZoneTempSetpoint(Payload.toFloat(), HeatPump.Status.Zone2TemperatureSetpoint, ZONE1);}
  if (Topic == MQTTCommandZone1FlowSetpoint){HeatPump.SetZoneFlowSetpoint(Payload.toInt(), ZONE1);}
  if (Topic == MQTTCommandZone1CurveSetpoint){HeatPump.SetZoneCurveSetpoint(Payload.toInt(), ZONE1);}

  if (Topic == MQTTCommandZone2TempSetpoint){HeatPump.SetZoneTempSetpoint(HeatPump.Status.Zone1TemperatureSetpoint, Payload.toFloat(), ZONE2);}
  if (Topic == MQTTCommandZone2FlowSetpoint){HeatPump.SetZoneFlowSetpoint(Payload.toInt(), ZONE2);}
  if (Topic == MQTTCommandZone2CurveSetpoint){HeatPump.SetZoneCurveSetpoint(Payload.toInt(), ZONE2);}


  if (Topic == MQTTCommandHotwaterBoost) {
    DEBUG_PRINTLN("MQTT Set HW Boost");
    HeatPump.ForceDHW(Payload.toInt());
  }

  if (Topic == MQTTCommandHotwaterSetpoint) {
    DEBUG_PRINTLN("MQTT Set HW Setpoint");
    HeatPump.SetHotWaterSetpoint(Payload.toInt());
  }

  if (Topic == MQTTCommandSystemHeatingMode) {
    DEBUG_PRINTLN("MQTT Set Heating Mode");
    HeatPump.SetHeatingControlMode(&Payload, BOTH);
  }
  if (Topic == MQTTCommandSystemPower) {
    DEBUG_PRINTLN("MQTT Set System Power Mode");
    HeatPump.SetSystemPowerMode(&Payload);
  }
  if (Topic == MQTTCommandSystemTemp) {
    DEBUG_PRINTLN("Temp Trigger");
    HeatPump.Scratch(Payload.toInt());
  }
  HeatPump.TriggerStatusStateMachine();       // Trigger update of heat pump 
}

void Zone1Report(void) {
  StaticJsonDocument<256> doc;
  char Buffer[256];

  doc[F("Temperature")] = HeatPump.Status.Zone1Temperature;
  doc[F("Setpoint")] = HeatPump.Status.Zone1TemperatureSetpoint;

  serializeJson(doc, Buffer);

  MQTTClient.publish(MQTT_STATUS_ZONE1, Buffer, true);
  //DEBUG_PRINTLN(Buffer);
}

void Zone2Report(void) {
  StaticJsonDocument<256> doc;
  char Buffer[256];

  doc[F("Temperature")] = HeatPump.Status.Zone2Temperature;
  doc[F("Setpoint")] = HeatPump.Status.Zone2TemperatureSetpoint;

  serializeJson(doc, Buffer);
  MQTTClient.publish(MQTT_STATUS_ZONE2, Buffer, true);
  //DEBUG_PRINTLN(Buffer);
}

void HotWaterReport(void) {
  StaticJsonDocument<512> doc;
  char Buffer[512];

  doc["Temperature"] = HeatPump.Status.HotWaterTemperature;
  doc["Setpoint"] = HeatPump.Status.HotWaterSetpoint;
  doc["HotWaterBoostActive"] = HeatPump.Status.HotWaterBoostActive;  // Use HotWaterBoostStr[HeatPump.Status.HotWaterBoostActive] for On/Off instead of 1/0
  doc["HotWaterTimerActive"] = HeatPump.Status.HotWaterTimerActive;
  doc["HotWaterControlMode"] = HowWaterControlModeString[HeatPump.Status.HotWaterControlMode];
  doc["LegionellaSetpoint"] = HeatPump.Status.LegionellaSetpoint;
  doc["HotWaterMaximumTempDrop"] = HeatPump.Status.HotWaterMaximumTempDrop;

  serializeJson(doc, Buffer);
  MQTTClient.publish(MQTT_STATUS_HOTWATER, Buffer, true);
  //DEBUG_PRINTLN(Buffer);
}

void SystemReport(void) {
  StaticJsonDocument<256> doc;
  char Buffer[256];

  doc["HeaterFlow"] = HeatPump.Status.HeaterOutputFlowTemperature;
  doc["HeaterReturn"] = HeatPump.Status.HeaterReturnFlowTemperature;
  doc["HeaterSetpoint"] = HeatPump.Status.HeaterFlowSetpoint;
  doc["OutsideTemp"] = HeatPump.Status.OutsideTemperature;
  doc["HeaterPower"] = HeatPump.Status.OutputPower;
  doc["SystemPower"] = SystemPowerModeString[HeatPump.Status.SystemPowerMode];
  doc["SystemOperationMode"] = SystemOperationModeString[HeatPump.Status.SystemOperationMode];
  doc["HeatingControlMode"] = HeatingControlModeString[HeatPump.Status.HeatingControlMode];
  doc["FlowRate"] = HeatPump.Status.PrimaryFlowRate;

  serializeJson(doc, Buffer);
  MQTTClient.publish(MQTT_STATUS_SYSTEM, Buffer, true);
  //DEBUG_PRINTLN(Buffer);
}

void TestReport(void) {
  StaticJsonDocument<512> doc;
  char Buffer[512];

  doc["Z1FSP"] = HeatPump.Status.Zone1FlowTemperatureSetpoint;
  doc["CHEAT"] = HeatPump.Status.ConsumedHeatingEnergy;
  doc["CDHW"] = HeatPump.Status.ConsumedHotWaterEnergy;
  doc["DHEAT"] = HeatPump.Status.DeliveredHeatingEnergy;
  doc["DDHW"] = HeatPump.Status.DeliveredHotWaterEnergy;
  doc["Compressor"] = HeatPump.Status.CompressorFrequency;
  doc["RunHours"] = HeatPump.Status.RunHours;
  doc["FlowTMax"] = HeatPump.Status.FlowTempMax;
  doc["FlowTMin"] = HeatPump.Status.FlowTempMin;
  doc["Defrost"] = HeatPump.Status.Defrost;

  serializeJson(doc, Buffer);
  MQTTClient.publish(MQTT_STATUS_TEST, Buffer, true);
  //DEBUG_PRINTLN(Buffer);
}

void StatusReport(void) {
  StaticJsonDocument<256> doc;
  char Buffer[256];

  doc["SSID"] = WiFi.SSID();
  doc["RSSI"] = WiFi.RSSI();
  doc["IP"] = WiFi.localIP().toString();

  serializeJson(doc, Buffer);
  MQTTClient.publish(MQTT_STATUS_WIFISTATUS, Buffer, true);
  //DEBUG_PRINTLN(Buffer);
}


void setupTelnet() {
  TelnetServer.onConnect(onTelnetConnect);
  TelnetServer.onConnectionAttempt(onTelnetConnectionAttempt);
  TelnetServer.onReconnect(onTelnetReconnect);
  TelnetServer.onDisconnect(onTelnetDisconnect);


  DEBUG_PRINT("Telnet: ");
  if (TelnetServer.begin()) {
    DEBUG_PRINTLN("running");
  } else {
    DEBUG_PRINTLN("error.");
    //errorMsg("Will reboot...");
  }
}

void onTelnetConnect(String ip) {
  DEBUG_PRINT("Telnet: ");
  DEBUG_PRINT(ip);
  DEBUG_PRINTLN(" connected");
  TelnetServer.println("\nWelcome " + TelnetServer.getIP());
  TelnetServer.println("(Use ^] + q  to disconnect.)");
}

void onTelnetDisconnect(String ip) {
  DEBUG_PRINT("Telnet: ");
  DEBUG_PRINT(ip);
  DEBUG_PRINTLN(" disconnected");
}

void onTelnetReconnect(String ip) {
  DEBUG_PRINT("Telnet: ");
  DEBUG_PRINT(ip);
  DEBUG_PRINTLN(" reconnected");
}

void onTelnetConnectionAttempt(String ip) {
  DEBUG_PRINT("Telnet: ");
  DEBUG_PRINT(ip);
  DEBUG_PRINTLN(" tried to connected");
}