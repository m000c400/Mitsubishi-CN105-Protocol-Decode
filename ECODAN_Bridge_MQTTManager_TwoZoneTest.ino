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
void AdvancedReport(void);
void TestReport(void);

TimerCallBack HeatPumpQuery1(500, HeatPumpQueryStateEngine);
TimerCallBack HeatPumpQuery2(60 * 1000, HeatPumpKeepAlive);


unsigned long wifipreviousMillis = 0;  // variable for comparing millis counter
int WiFiOneShot = 1;
int Zone1_Update_in_Progress = 0;
int Zone2_Update_in_Progress = 0;
float Zone1TemperatureSetpoint_UpdateValue, Zone2TemperatureSetpoint_UpdateValue;
int Zone1FlowSetpoint_UpdateValue, Zone2FlowSetpoint_UpdateValue;



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
      wifipreviousMillis = millis();
      WiFiOneShot = 0;
    }  // Oneshot to start the timer
    if (millis() - wifipreviousMillis >= 300000) {
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
    analogWrite(Green_RGB_LED, 30);  // Green LED on, 25% brightness
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
    if (Zone1_Update_in_Progress == 1) { Zone1_Update_in_Progress = 0; }
    if (Zone2_Update_in_Progress == 1) { Zone2_Update_in_Progress = 0; }

    digitalWrite(Green_RGB_LED, HIGH);  // Flash the Green LED full brightness
    delay(10);                          // Hold for 10ms then WiFi brightness will return it to 25%
    if (MQTTReconnect()) {
      Zone1Report();
      Zone2Report();
      HotWaterReport();
      SystemReport();
      AdvancedReport();
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

  DEBUG_PRINT("\nReceived MQTT Message on topic ");
  DEBUG_PRINT(Topic.c_str());
  DEBUG_PRINT(" with Payload ");
  DEBUG_PRINTLN(Payload.c_str());


  // Heating Zone 1 Commands
  if (Topic == MQTTCommandZone1TempSetpoint) {
    DEBUG_PRINTLN("MQTT Set Zone1 Temperature Setpoint");
    if (Zone2_Update_in_Progress == 1) {
      DEBUG_PRINTLN("Zone2 Update is currently in progress");
      HeatPump.SetZoneTempSetpoint(Payload.toFloat(), Zone2TemperatureSetpoint_UpdateValue, BOTH);  // Set the Payload and to BOTH Zones as both are requiring update
    } else {
      HeatPump.SetZoneTempSetpoint(Payload.toFloat(), HeatPump.Status.Zone2TemperatureSetpoint, ZONE1);  // Set the new value and the current value of the other zone
    }
    Zone1TemperatureSetpoint_UpdateValue = Payload.toFloat();
    Zone1_Update_in_Progress = 1;
  }
  if (Topic == MQTTCommandZone1FlowSetpoint) {
    DEBUG_PRINTLN("MQTT Set Zone1 Flow Setpoint");
    if (Zone2_Update_in_Progress == 1) {
      DEBUG_PRINTLN("Zone2 Update is currently in progress");
      HeatPump.SetZoneTempSetpoint(Payload.toInt(), Zone1FlowSetpoint_UpdateValue, BOTH);  // Set the Payload and the Zone2 value that is in progress of being written
    } else {
      HeatPump.SetZoneTempSetpoint(Payload.toInt(), HeatPump.Status.Zone2FlowTemperatureSetpoint, ZONE1);  // Set the new value and the current value of the other zone
    }
    Zone1FlowSetpoint_UpdateValue = Payload.toInt();
    Zone1_Update_in_Progress = 1;
  }
  if (Topic == MQTTCommandZone1CurveSetpoint) {
    HeatPump.SetZoneCurveSetpoint(Payload.toInt(), Payload.toInt(), ZONE1);
  }


  // Heating Zone 2 Commands
  if (Topic == MQTTCommandZone2TempSetpoint) {
    DEBUG_PRINTLN("MQTT Set Zone2 Temperature Setpoint");
    if (Zone1_Update_in_Progress == 1) {
      DEBUG_PRINTLN("Zone1 Update is currently in progress");
      HeatPump.SetZoneTempSetpoint(Zone1TemperatureSetpoint_UpdateValue, Payload.toFloat(), BOTH);  // Set the Payload and the Zone2 value that is in progress of being written
    } else {
      HeatPump.SetZoneTempSetpoint(HeatPump.Status.Zone1TemperatureSetpoint, Payload.toFloat(), ZONE2);  // Set the new value and the current value of the other zone
    }
    Zone2TemperatureSetpoint_UpdateValue = Payload.toFloat();
    Zone2_Update_in_Progress = 1;
  }
  if (Topic == MQTTCommandZone2FlowSetpoint) {
    DEBUG_PRINTLN("MQTT Set Zone2 Flow Setpoint");
    if (Zone1_Update_in_Progress == 1) {
      DEBUG_PRINTLN("Zone1 Update is currently in progress");
      HeatPump.SetZoneTempSetpoint(Zone1FlowSetpoint_UpdateValue, Payload.toInt(), BOTH);  // Set the Payload and the Zone2 value that is in progress of being written
    } else {
      HeatPump.SetZoneTempSetpoint(HeatPump.Status.Zone1FlowTemperatureSetpoint, Payload.toInt(), ZONE2);  // Set the new value and the current value of the other zone
    }
    Zone2FlowSetpoint_UpdateValue = Payload.toInt();
    Zone2_Update_in_Progress = 1;
  }
  if (Topic == MQTTCommandZone2CurveSetpoint) {
    HeatPump.SetZoneCurveSetpoint(Payload.toInt(), Payload.toInt(), ZONE2);
  }


  // Other Commands
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

  HeatPump.TriggerStatusStateMachine();  // Trigger update of heat pump
}


void Zone1Report(void) {
  StaticJsonDocument<512> doc;
  char Buffer[512];

  doc[F("Temperature")] = HeatPump.Status.Zone1Temperature;
  doc[F("Setpoint")] = HeatPump.Status.Zone1TemperatureSetpoint;
  doc["HeatingControlMode"] = HeatingControlModeString[HeatPump.Status.HeatingControlModeZ1];
  doc["FSP"] = HeatPump.Status.Zone1FlowTemperatureSetpoint;

  serializeJson(doc, Buffer);

  MQTTClient.publish(MQTT_STATUS_ZONE1, Buffer, true);
  //DEBUG_PRINTLN(Buffer);
}

void Zone2Report(void) {
  StaticJsonDocument<512> doc;
  char Buffer[512];

  doc[F("Temperature")] = HeatPump.Status.Zone2Temperature;
  doc[F("Setpoint")] = HeatPump.Status.Zone2TemperatureSetpoint;
  doc["HeatingControlMode"] = HeatingControlModeString[HeatPump.Status.HeatingControlModeZ2];
  doc["FSP"] = HeatPump.Status.Zone2FlowTemperatureSetpoint;

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
  StaticJsonDocument<512> doc;
  char Buffer[512];

  doc["HeaterFlow"] = HeatPump.Status.HeaterOutputFlowTemperature;
  doc["HeaterReturn"] = HeatPump.Status.HeaterReturnFlowTemperature;
  doc["HeaterSetpoint"] = HeatPump.Status.HeaterFlowSetpoint;
  doc["OutsideTemp"] = HeatPump.Status.OutsideTemperature;
  doc["Defrost"] = HeatPump.Status.Defrost;
  doc["HeaterPower"] = HeatPump.Status.OutputPower;
  doc["Compressor"] = HeatPump.Status.CompressorFrequency;
  doc["SystemPower"] = SystemPowerModeString[HeatPump.Status.SystemPowerMode];
  doc["SystemOperationMode"] = SystemOperationModeString[HeatPump.Status.SystemOperationMode];
  doc["FlowRate"] = HeatPump.Status.PrimaryFlowRate;
  doc["RunHours"] = HeatPump.Status.RunHours;

  serializeJson(doc, Buffer);
  MQTTClient.publish(MQTT_STATUS_SYSTEM, Buffer, true);
  //DEBUG_PRINTLN(Buffer);
}


void AdvancedReport(void) {
  StaticJsonDocument<512> doc;
  char Buffer[512];

  doc["CHEAT"] = HeatPump.Status.ConsumedHeatingEnergy;
  doc["CDHW"] = HeatPump.Status.ConsumedHotWaterEnergy;
  doc["DHEAT"] = HeatPump.Status.DeliveredHeatingEnergy;
  doc["DDHW"] = HeatPump.Status.DeliveredHotWaterEnergy;
  doc["FlowTMax"] = HeatPump.Status.FlowTempMax;
  doc["FlowTMin"] = HeatPump.Status.FlowTempMin;
  doc["PrimaryFlowRate"] = HeatPump.Status.PrimaryFlowRate;
  doc["BoilerFlow"] = HeatPump.Status.ExternalBoilerFlowTemperature;
  doc["BoilerReturn"] = HeatPump.Status.ExternalBoilerReturnTemperature;

  serializeJson(doc, Buffer);
  MQTTClient.publish(MQTT_STATUS_ADVANCED, Buffer, true);
  //DEBUG_PRINTLN(Buffer);
}

void TestReport(void) {
  StaticJsonDocument<512> doc;
  char Buffer[512];

  doc["Unknown1"] = HeatPump.Status.Unknown1Active;
  doc["Unknown2"] = HeatPump.Status.Unknown2Active;
  doc["Unknown3"] = HeatPump.Status.Unknown3Active;
  doc["Unknown4"] = HeatPump.Status.Unknown4Active;
  doc["Unknown5"] = HeatPump.Status.Unknown5Active;
  doc["Unknown6"] = HeatPump.Status.Unknown6Active;
  doc["Unknown7"] = HeatPump.Status.Unknown7Active;
  doc["Unknown8"] = HeatPump.Status.Unknown8Active;
  doc["Unknown9"] = HeatPump.Status.Unknown9Active;
  doc["Unknown10"] = HeatPump.Status.Unknown10Active;
  doc["Unknown11"] = HeatPump.Status.Unknown11Active;

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
