/*
    Copyright (C) <2020>  <Mike Roberts>

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


//#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
//#include <DNSServer.h>
//#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
#include <PubSubClient.h>
#include <ArduinoOTA.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <ESPTelnet.h>


#include "Ecodan.h"
#include "config.h"
#include "MQTTConfig.h"
#include "TimerCallBack.h"
#include "Debug.h"
#include "OTA.h"



ECODAN HeatPump;

SoftwareSerial SwSerial;
WiFiClient NetworkClient;
PubSubClient MQTTClient(NetworkClient);
ESPTelnet TelnetServer;
String HostName;

void HeatPumpQueryStateEngine(void);
void HeatPumpKeepAlive(void);
void Zone1Report(void);
void Zone1Report(void);
void HotWaterReport(void);
void SystemReport(void);
void TestReport(void);

TimerCallBack HeatPumpQuery1(500, HeatPumpQueryStateEngine);
TimerCallBack HeatPumpQuery2(60 *  1000, HeatPumpKeepAlive);

String MQTTCommandZone1TempSetpoint = MQTT_COMMAND_ZONE1_TEMP_SETPOINT;
String MQTTCommandZone1FlowSetpoint = MQTT_COMMAND_ZONE1_FLOW_SETPOINT;
String MQTTCommandZone1CurveSetpoint = MQTT_COMMAND_ZONE1_CURVE_SETPOINT;

String MQTTCommandZone2TempSetpoint = MQTT_COMMAND_ZONE2_TEMP_SETPOINT;
String MQTTCommandZone2FlowSetpoint = MQTT_COMMAND_ZONE2_FLOW_SETPOINT;
String MQTTCommandZone2CurveSetpoint = MQTT_COMMAND_ZONE2_CURVE_SETPOINT;

String MQTTCommandHotwaterSetpoint = MQTT_COMMAND_HOTWATER_SETPOINT;
String MQTTCommandHotwaterBoost = MQTT_COMMAND_HOTWATER_BOOST;

String MQTTCommandSystemHeatingMode = MQTT_COMMAND_SYSTEM_HEATINGMODE;
String MQTTCommandSystemPower = MQTT_COMMAND_SYSTEM_POWER;
String MQTTCommandSystemTemp = MQTT_COMMAND_SYSTEM_TEMP;

int RxPin = 14; //Rx
int TxPin = 16; //Tx
int Activity_LED = 2;   // Fancy Extras
int Red_RGB_LED = 15;
int Green_RGB_LED = 12;
int Blue_RGB_LED = 13;

void setup()
{
  //DEBUGPORT.begin(DEBUGBAUD);
  HEATPUMP_STREAM.begin(SERIAL_BAUD, SERIAL_CONFIG, RxPin, TxPin); // Rx, Tx
  //pinMode(RxPin, INPUT_PULLUP);    // Not required on ESP8266 Witty, not sure on others
  pinMode(Activity_LED,OUTPUT);   // Onboard LED
  pinMode(Red_RGB_LED,OUTPUT);    // Red (RGB) LED
  pinMode(Green_RGB_LED,OUTPUT);  // Green (RGB) LED
  pinMode(Blue_RGB_LED,OUTPUT);   // Blue (RGB) LED

  digitalWrite(Activity_LED, HIGH);
  digitalWrite(Red_RGB_LED, LOW);
  digitalWrite(Green_RGB_LED, LOW);
  digitalWrite(Blue_RGB_LED, LOW);

  HeatPump.SetStream(&HEATPUMP_STREAM);

  WiFiManager MyWifiManager;

  //wifiManager.resetSettings(); //reset settings - for testing

  MyWifiManager.setTimeout(180);

  if (!MyWifiManager.autoConnect("Ecodan Bridge AP"))
  {
    ESP.reset();
    delay(5000);
  }
  HostName = "EcodanBridge-";
  HostName += String(ESP.getChipId(), HEX);
  WiFi.hostname(HostName);

  setupTelnet();

  OTASetup(HostName.c_str());
  MQTTClient.setServer(MQTT_SERVER, MQTT_PORT);
  MQTTClient.setCallback(MQTTonData);
}

void loop()
{
  if (!MQTTReconnect())
  {
    return;
  }
  MQTTClient.loop();
  TelnetServer.loop();

  
  HeatPumpQuery1.Process();
  HeatPumpQuery2.Process();

  HeatPump.Process();
  ArduinoOTA.handle();
}


void HeatPumpKeepAlive(void)
{
  HeatPump.KeepAlive();
  HeatPump.TriggerStatusStateMachine();
}

void HeatPumpQueryStateEngine(void)
{
  HeatPump.StatusStateMachine();
  if (HeatPump.UpdateComplete())
  {
    DEBUG_PRINTLN("Update Complete");
    digitalWrite(Green_RGB_LED, HIGH);    // Flash the Green LED
    delay(10);
    digitalWrite(Green_RGB_LED, LOW);
    if (MQTTReconnect())
    {
      Zone1Report();
      Zone2Report();
      HotWaterReport();
      SystemReport();
      TestReport();
    }
  }
}


uint8_t MQTTReconnect()
{
  if (MQTTClient.connected())
  {
    return 1;
  }

  DEBUG_PRINTLN("Attempting MQTT connection...");
  if (MQTTClient.connect(HostName.c_str(), MQTT_USER, MQTT_PASS, MQTT_LWT, 0, true, "offline" ))
  {
    DEBUG_PRINTLN("MQTT Connected");
    MQTTonConnect();
    return 1;
  }
  else
  {
    switch (MQTTClient.state())
    {
      case -4 :
        DEBUG_PRINTLN("MQTT_CONNECTION_TIMEOUT");
        break;
      case -3 :
        DEBUG_PRINTLN("MQTT_CONNECTION_LOST");
        break;
      case -2 :
        DEBUG_PRINTLN("MQTT_CONNECT_FAILED");
        break;
      case -1 :
        DEBUG_PRINTLN("MQTT_DISCONNECTED");
        break;
      case 0 :
        DEBUG_PRINTLN("MQTT_CONNECTED");
        break;
      case 1 :
        DEBUG_PRINTLN("MQTT_CONNECT_BAD_PROTOCOL");
        break;
      case 2 :
        DEBUG_PRINTLN("MQTT_CONNECT_BAD_CLIENT_ID");
        break;
      case 3 :
        DEBUG_PRINTLN("MQTT_CONNECT_UNAVAILABLE");
        break;
      case 4 :
        DEBUG_PRINTLN("MQTT_CONNECT_BAD_CREDENTIALS");
        break;
      case 5 :
        DEBUG_PRINTLN("MQTT_CONNECT_UNAUTHORIZED");
        break;
    }
    return 0;
  }
  return 0;
}


void MQTTonConnect(void)
{
  DEBUG_PRINTLN("MQTT ON CONNECT");
  MQTTClient.publish(MQTT_LWT, "online");
  MQTTClient.subscribe(MQTTCommandZone1TempSetpoint.c_str());
  MQTTClient.subscribe(MQTTCommandZone1FlowSetpoint.c_str());
  MQTTClient.subscribe(MQTTCommandZone1CurveSetpoint.c_str());
  MQTTClient.subscribe(MQTTCommandZone2TempSetpoint.c_str());
  MQTTClient.subscribe(MQTTCommandZone2FlowSetpoint.c_str());
  MQTTClient.subscribe(MQTTCommandZone2CurveSetpoint.c_str());
  MQTTClient.subscribe(MQTTCommandSystemHeatingMode.c_str());

  MQTTClient.subscribe(MQTTCommandHotwaterSetpoint.c_str());
  MQTTClient.subscribe(MQTTCommandHotwaterBoost.c_str());

  MQTTClient.subscribe(MQTTCommandSystemPower.c_str());
  MQTTClient.subscribe(MQTTCommandSystemTemp.c_str());
}

void MQTTonDisconnect(void* response)
{
  
}

void MQTTonData(char* topic, byte* payload, unsigned int length)
{
  payload[length] = 0;
  String Topic = topic;
  String Payload = (char *)payload;

  DEBUG_PRINT("Recieved "); DEBUG_PRINT(Topic.c_str());
  DEBUG_PRINT("Payload "); DEBUG_PRINTLN(Payload.c_str());

  if (Topic == MQTTCommandZone1TempSetpoint) HeatPump.SetZoneTempSetpoint(Payload.toInt(), ZONE1);
  if (Topic == MQTTCommandZone1FlowSetpoint) HeatPump.SetZoneFlowSetpoint(Payload.toInt(), ZONE1);
  if (Topic == MQTTCommandZone1CurveSetpoint)HeatPump.SetZoneCurveSetpoint(Payload.toInt(), ZONE1);

  if (Topic == MQTTCommandZone2TempSetpoint) HeatPump.SetZoneTempSetpoint(Payload.toInt(), ZONE2);
  if (Topic == MQTTCommandZone2FlowSetpoint) HeatPump.SetZoneFlowSetpoint(Payload.toInt(), ZONE2);
  if (Topic == MQTTCommandZone2CurveSetpoint)HeatPump.SetZoneCurveSetpoint(Payload.toInt(), ZONE2);


  if (Topic == MQTTCommandHotwaterBoost)
  {
    DEBUG_PRINTLN("MQTT Set HW Boost");
    HeatPump.ForceDHW(Payload.toInt());
  }

  if (Topic == MQTTCommandHotwaterSetpoint)
  {
    DEBUG_PRINTLN("MQTT Set HW Setpoint");
    HeatPump.SetHotWaterSetpoint(Payload.toInt());
  }

  if (Topic == MQTTCommandSystemHeatingMode)
  {
    DEBUG_PRINTLN("MQTT Set Heating Mode");
    HeatPump.SetHeatingControlMode(&Payload, BOTH);
  }
  if (Topic == MQTTCommandSystemPower)
  {
    DEBUG_PRINTLN("MQTT Set System Power Mode");
    HeatPump.SetSystemPowerMode(&Payload);
  }
  if (Topic == MQTTCommandSystemTemp)
  {
    DEBUG_PRINTLN("Temp Trigger");
    HeatPump.Scratch(Payload.toInt());
  }
  //HeatPump.TriggerStatusStateMachine();
}

void Zone1Report(void)
{
  StaticJsonDocument<256> doc;
  char Buffer[256];

  doc[F("Temperature")] = HeatPump.Status.Zone1Temperature;
  doc[F("Setpoint")] = HeatPump.Status.Zone1TemperatureSetpoint;

  serializeJson(doc, Buffer);

  MQTTClient.publish(MQTT_STATUS_ZONE1, Buffer);
  //DEBUG_PRINTLN(Buffer);
}

void Zone2Report(void)
{
  StaticJsonDocument<256> doc;
  char Buffer[256];

  doc[F("Temperature")] = HeatPump.Status.Zone2Temperature;
  doc[F("Setpoint")] = HeatPump.Status.Zone2TemperatureSetpoint;

  serializeJson(doc, Buffer);
  MQTTClient.publish(MQTT_STATUS_ZONE2, Buffer);
  //DEBUG_PRINTLN(Buffer);
}

void HotWaterReport(void)
{
  StaticJsonDocument<512> doc;
  char Buffer[512];

  doc["Temperature"] = HeatPump.Status.HotWaterTemperature;
  doc["Setpoint"] = HeatPump.Status.HotWaterSetpoint;
  doc["HotWaterBoostActive"] = HotWaterBoostStr[HeatPump.Status.HotWaterBoostActive];
  doc["HotWaterTimerActive"] = HeatPump.Status.HotWaterTimerActive;
  doc["HotWaterControlMode"] = HowWaterControlModeString[HeatPump.Status.HotWaterControlMode];
  doc["LegionellaSetpoint"] = HeatPump.Status.LegionellaSetpoint;
  doc["HotWaterMaximumTempDrop"] = HeatPump.Status.HotWaterMaximumTempDrop;

  serializeJson(doc, Buffer);
  MQTTClient.publish(MQTT_STATUS_HOTWATER, Buffer);
  //DEBUG_PRINTLN(Buffer);
}

void SystemReport(void)
{
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
  MQTTClient.publish(MQTT_STATUS_SYSTEM, Buffer);
  //DEBUG_PRINTLN(Buffer);
}

void TestReport(void)
{
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
  doc["HotWaterBoostActive"] = HeatPump.Status.HotWaterBoostActive;
  doc["Defrost"] = HeatPump.Status.Defrost;

  serializeJson(doc, Buffer);
  MQTTClient.publish(MQTT_STATUS_TEST, Buffer);
  //DEBUG_PRINTLN(Buffer);
}


void setupTelnet()
{
  TelnetServer.onConnect(onTelnetConnect);
  TelnetServer.onConnectionAttempt(onTelnetConnectionAttempt);
  TelnetServer.onReconnect(onTelnetReconnect);
  TelnetServer.onDisconnect(onTelnetDisconnect);


  DEBUG_PRINT("Telnet: ");
  if (TelnetServer.begin())
  {
    DEBUG_PRINTLN("running");
  }
  else
  {
    DEBUG_PRINTLN("error.");
    //errorMsg("Will reboot...");
  }
}

void onTelnetConnect(String ip)
{
  DEBUG_PRINT("Telnet: ");
  DEBUG_PRINT(ip);
  DEBUG_PRINTLN(" connected");
  TelnetServer.println("\nWelcome " + TelnetServer.getIP());
  TelnetServer.println("(Use ^] + q  to disconnect.)");
}

void onTelnetDisconnect(String ip)
{
  DEBUG_PRINT("Telnet: ");
  DEBUG_PRINT(ip);
  DEBUG_PRINTLN(" disconnected");
}

void onTelnetReconnect(String ip)
{
  DEBUG_PRINT("Telnet: ");
  DEBUG_PRINT(ip);
  DEBUG_PRINTLN(" reconnected");
}

void onTelnetConnectionAttempt(String ip)
{
  DEBUG_PRINT("Telnet: ");
  DEBUG_PRINT(ip);
  DEBUG_PRINTLN(" tried to connected");
}
