/*
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

// -- Supported Hardware -- //
/* As sold Witty ESP8266 based               / Core 3.1.2 / Flash 4MB (1MB FS / 1MB OTA - 16KB Cache/48KB IRAM not shared) */
/* ESP32 AtomS3 Lite (ESP32S3 Dev Module)    / Core 3.1.1 / Flash 8M with SPIFFS (3MB APP / 1.5MB SPIFFS)                  */
/* ESP32 Ethernet WT32-ETH01                 / Core 3.1.1 / Flash 4MB (1.9MB APP / 180KB SPIFFS)                           */

#define LANG_EN


#if defined(ESP8266) || defined(ESP32)

// ==========================================
// FILE SYSTEM & CORE LIBRARIES
// ==========================================
#include <FS.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <WiFiManager.h>
#include <ESPTelnet.h>

// ==========================================
// ESP8266 SPECIFIC
// ==========================================
#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>
#include <sys/time.h>
#endif

// ==========================================
// ESP32 SPECIFIC (AtomS3 & WT32 Ethernet)
// ==========================================
#ifdef ESP32
#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>
#include <WiFiClientSecure.h>
#include "HttpsOTAUpdate.h"

#ifdef ARDUINO_WT32_ETH01
#include <Arduino.h>
#include <ETH.h>
#endif

// ==========================================
// ASYNC WEB SERVER (Excluded for WT32)
// ==========================================
#ifndef ARDUINO_WT32_ETH01
// If ESPAsyncWebServer conflicts with WebServer.h on your setup,
// ensure your libraries are updated rather than using macro hacks.
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#endif
#endif

// ==========================================
// LOCAL PROJECT HEADERS
// ==========================================
#include "Ecodan.h"
#include "AC.h"
#include "Melcloud.h"



#endif  // ESP8266 || ESP32

String FirmwareVersion = "7.0.33";
String LatestFirmwareVersion;

// Language for OTA Check
#if defined(LANG_FR)
String Language = "_FR";
#elif defined(LANG_EN)
String Language = "_EN";
#elif defined(LANG_DE)
String Language = "_DE";
#elif defined(LANG_NL)
String Language = "_NL";
#elif defined(LANG_ES)
String Language = "_ES";
#elif defined(LANG_IT)
String Language = "_IT";
#elif defined(LANG_FI)
String Language = "_FI";
#elif defined(LANG_SE)
String Language = "_SE";
#elif defined(LANG_PL)
String Language = "_PL";
#else
String Language = "_EN";
#endif


bool update_in_progress = false;
String update_summary = "";

#ifdef ARDUINO_M5STACK_ATOMS3
String OTADeviceType = "Gen2";
#endif
#ifdef ARDUINO_WT32_ETH01
String OTADeviceType = "Ethernet";
#endif

#ifdef ESP8266  // Define the Witty ESP8266 Serial Pins
#define HEATPUMP_STREAM SwSerial1
#define MEL_STREAM SwSerial2
#define SERIAL_CONFIG SWSERIAL_8E1
int LDR = A0;
#define FTCCable_TxPin 16
#define FTCCable_RxPin 14
#define MEL_TxPin 1
#define MEL_RxPin 3
int Activity_LED = 2;
int Reset_Button = 4;
int Green_RGB_LED = 12;
int Blue_RGB_LED = 13;
int Red_RGB_LED = 15;
#endif

#ifdef ESP32  // Define the M5Stack Serial Pins
#define HEATPUMP_STREAM Serial1
#define MEL_STREAM Serial2
#define SERIAL_CONFIG SERIAL_8E1

#ifdef ARDUINO_M5STACK_ATOMS3
#include <LiteLED.h>
#define LED_TYPE LED_STRIP_WS2812
#define LED_TYPE_IS_RGBW 0
int LED_GPIO = 35;
#define LED_BRIGHT 100
static const crgb_t L_RED = 0xff0000;
static const crgb_t L_GREEN = 0x00ff00;
static const crgb_t L_BLUE = 0x0000ff;
static const crgb_t L_ORANGE = 0xffa500;
LiteLED myLED(LED_TYPE, LED_TYPE_IS_RGBW);
int Reset_Button = 41;
#define FTCCable_RxPin 2
#define FTCCable_TxPin 1
#define FTCProxy_RxPin 38
#define FTCProxy_TxPin 39
#define MEL_RxPin 8
#define MEL_TxPin 7
#endif

#ifdef ARDUINO_WT32_ETH01
#define FTCCable_RxPin 4
#define FTCCable_TxPin 2
#define MEL_RxPin 14
#define MEL_TxPin 12
#ifndef ETH_PHY_TYPE
#define ETH_PHY_TYPE ETH_PHY_LAN8720
#define ETH_PHY_ADDR 0
#define ETH_PHY_MDC 23
#define ETH_PHY_MDIO 18
#define ETH_PHY_POWER -1
#define ETH_CLK_MODE ETH_CLOCK_GPIO0_IN
#endif
#endif
#endif


#define Heartbeat_Range 99  // Heatbeat Max value
int Heart_Value = 0;        // Heatbeat ID

unsigned long SERIAL_BAUD = 2400;
bool shouldSaveConfig = false;
const int deviceId_max_length = 15;
const int hostname_max_length = 200;
const int port_max_length = 10;
const int user_max_length = 30;
const int password_max_length = 50;
const int basetopic_max_length = 30;
bool ShortCycleProtectionActive = false;
bool FlowFollowingActive = false;
bool DHWFlowFollowingActive = false;
bool MELCloud_Adapter_Connected = false;
float Z1_CurveFSP = 30;
float Z2_CurveFSP = 30;
float FlowTemp_Last = 0;
float FlowTemp_Target = 0;
int Flow_Inc_Count = 0;
// Flow-following persistence gate (see Flow Temperature Overshoot Hysterisis in loop())
const uint32_t FF_RAISE_PERSIST_MS = 60000;   // Reading must hold above the trigger this long before the setpoint is raised
const uint32_t FF_LOWER_PERSIST_MS = 120000;  // Reading must hold below the release level this long before the setpoint is lowered
const float FF_FASTPATH_EXC = 1.5;            // At or above this excess (C) skip the gate: too close to the 2.0C outdoor unit stop
bool FF_RaiseArmed = false, FF_LowerArmed = false;
uint32_t FF_RaiseArmedMs = 0, FF_LowerArmedMs = 0;
int lastResetDay = -1;
const int OAT_Window_Size = 300;
int OAT_readings[OAT_Window_Size];
int OAT_readIndex = 0;
int OAT_total = 0;
float OAT_average = 0;
bool OAT_isFull = false;
bool inDefrostWindow = false;
bool A2APrevConnectedLastLoop = false;
bool A2WPrevConnectedLastLoop = false;
int Connection_attempt_counter = 0;
bool Reset_Button_pressed_at_boot = false;

#ifdef ESP32  // Define the M5Stack AtomS3
const char* ISGR_root_ca =
  "-----BEGIN CERTIFICATE-----\n"
  "MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw\n"
  "TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh\n"
  "cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMTUwNjA0MTEwNDM4\n"
  "WhcNMzUwNjA0MTEwNDM4WjBPMQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJu\n"
  "ZXQgU2VjdXJpdHkgUmVzZWFyY2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBY\n"
  "MTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAK3oJHP0FDfzm54rVygc\n"
  "h77ct984kIxuPOZXoHj3dcKi/vVqbvYATyjb3miGbESTtrFj/RQSa78f0uoxmyF+\n"
  "0TM8ukj13Xnfs7j/EvEhmkvBioZxaUpmZmyPfjxwv60pIgbz5MDmgK7iS4+3mX6U\n"
  "A5/TR5d8mUgjU+g4rk8Kb4Mu0UlXjIB0ttov0DiNewNwIRt18jA8+o+u3dpjq+sW\n"
  "T8KOEUt+zwvo/7V3LvSye0rgTBIlDHCNAymg4VMk7BPZ7hm/ELNKjD+Jo2FR3qyH\n"
  "B5T0Y3HsLuJvW5iB4YlcNHlsdu87kGJ55tukmi8mxdAQ4Q7e2RCOFvu396j3x+UC\n"
  "B5iPNgiV5+I3lg02dZ77DnKxHZu8A/lJBdiB3QW0KtZB6awBdpUKD9jf1b0SHzUv\n"
  "KBds0pjBqAlkd25HN7rOrFleaJ1/ctaJxQZBKT5ZPt0m9STJEadao0xAH0ahmbWn\n"
  "OlFuhjuefXKnEgV4We0+UXgVCwOPjdAvBbI+e0ocS3MFEvzG6uBQE3xDk3SzynTn\n"
  "jh8BCNAw1FtxNrQHusEwMFxIt4I7mKZ9YIqioymCzLq9gwQbooMDQaHWBfEbwrbw\n"
  "qHyGO0aoSCqI3Haadr8faqU9GY/rOPNk3sgrDQoo//fb4hVC1CLQJ13hef4Y53CI\n"
  "rU7m2Ys6xt0nUW7/vGT1M0NPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNV\n"
  "HRMBAf8EBTADAQH/MB0GA1UdDgQWBBR5tFnme7bl5AFzgAiIyBpY9umbbjANBgkq\n"
  "hkiG9w0BAQsFAAOCAgEAVR9YqbyyqFDQDLHYGmkgJykIrGF1XIpu+ILlaS/V9lZL\n"
  "ubhzEFnTIZd+50xx+7LSYK05qAvqFyFWhfFQDlnrzuBZ6brJFe+GnY+EgPbk6ZGQ\n"
  "3BebYhtF8GaV0nxvwuo77x/Py9auJ/GpsMiu/X1+mvoiBOv/2X/qkSsisRcOj/KK\n"
  "NFtY2PwByVS5uCbMiogziUwthDyC3+6WVwW6LLv3xLfHTjuCvjHIInNzktHCgKQ5\n"
  "ORAzI4JMPJ+GslWYHb4phowim57iaztXOoJwTdwJx4nLCgdNbOhdjsnvzqvHu7Ur\n"
  "TkXWStAmzOVyyghqpZXjFaH3pO3JLF+l+/+sKAIuvtd7u+Nxe5AW0wdeRlN8NwdC\n"
  "jNPElpzVmbUq4JUagEiuTDkHzsxHpFKVK7q4+63SM1N95R1NbdWhscdCb+ZAJzVc\n"
  "oyi3B43njTOQ5yOf+1CceWxG1bQVs5ZufpsMljq4Ui0/1lvh+wjChP4kqKOJ2qxq\n"
  "4RgqsahDYVvTH9w7jXbyLeiNdd8XM2w9U/t7y0Ff/9yi0GE44Za4rF2LN9d11TPA\n"
  "mRGunUHBcnWEvgJBQl9nJEiU0Zsnvgc/ubhPgXRR4Xq37Z0j4r7g1SgEEzwxA57d\n"
  "emyPxgcYxn/eR44/KJ4EBs+lVDR3veyJm+kXQ99b21/+jh5Xos1AnX5iItreGCc=\n"
  "-----END CERTIFICATE-----\n";

static HttpsOTAStatus_t otastatus;
#endif


// The extra parameters to be configured (can be either global or just in the setup)
// After connecting, parameter.getValue() will get you the configured value
// id/name placeholder/prompt default length
// Here you can pre-set the settings for the MQTT connection. The settings can later be changed via Wifi Manager.
struct MqttSettings {
  // These are the placeholder objects for the custom fields
  char deviceId[deviceId_max_length] = "000000000000";
  char wm_device_id_identifier[10] = "device_id";

  // Client 1
  char hostname[hostname_max_length] = "homeassistant.local";
  char user[user_max_length] = "Username";
  char password[password_max_length] = "Password";
  char port[port_max_length] = "1883";
  char baseTopic[basetopic_max_length] = "ASHP";
  char wm_mqtt_hostname_identifier[14] = "mqtt_hostname";
  char wm_mqtt_user_identifier[10] = "mqtt_user";
  char wm_mqtt_password_identifier[14] = "mqtt_password";
  char wm_mqtt_port_identifier[10] = "mqtt_port";
  char wm_mqtt_basetopic_identifier[15] = "mqtt_basetopic";

  // Client 2
  char hostname2[hostname_max_length] = "IPorDNS";
  char user2[user_max_length] = "Username";
  char password2[password_max_length] = "Password";
  char port2[port_max_length] = "1883";
  char baseTopic2[basetopic_max_length] = "ASHP";
  char wm_mqtt2_hostname_identifier[15] = "mqtt2_hostname";
  char wm_mqtt2_user_identifier[11] = "mqtt2_user";
  char wm_mqtt2_password_identifier[15] = "mqtt2_password";
  char wm_mqtt2_port_identifier[11] = "mqtt2_port";
  char wm_mqtt2_basetopic_identifier[16] = "mqtt2_basetopic";
};

struct UnitSettings {
  float UnitSize = 8.5;
  float GlycolStrength = 4.18;
  char unitsize_identifier[9] = "unitsize";
  char glycol_identifier[7] = "glycol";
  char compcurve_identifier[10] = "compcurve";
  char act_ctrl_sc_identifier[9] = "shortcyc";
  char mel_block_identifier[10] = "melblock";
  char remote_ac_identifier[10] = "ac_rmt";
  String CompCurve = "{\"base\":{\"zone1\":{\"curve\":[{\"flow\":60,\"outside\":-10},{\"flow\":35,\"outside\":0},{\"flow\":20,\"outside\":15},{\"flow\":10,\"outside\":20}]},\"zone2\":{\"curve\":[{\"flow\":60,\"outside\":-10},{\"flow\":35,\"outside\":0},{\"flow\":20,\"outside\":15}]}},\"zone1\":{\"active\":false,\"manual_offset\":0,\"temp_offset\": 0,\"wind_offset\":0},\"zone2\":{\"active\":false,\"manual_offset\":0,\"temp_offset\": 0,\"wind_offset\":0},\"use_local_outdoor\":true,\"max_flow_overshoot\": 3,\"fixedlockoutduration\": 0}";
  float z1_manual_offset = 0;
  float z1_wind_offset = 0;
  float z1_temp_offset = 0;
  float z2_manual_offset = 0;
  float z2_wind_offset = 0;
  float z2_temp_offset = 0;
  float cloud_outdoor = 0;
  bool use_local_outdoor = true;
  bool z1_active = false;
  bool z2_active = false;
  bool shortcycleprotectionenabled = false;
  bool BlockWriteFromMELCloud = false;
  float max_flow_overshoot = 3;
  float fixedlockoutduration = 0;  // 0 = auto
  bool z1_room_influence_active = false;
  bool z2_room_influence_active = false;
  bool z1_use_local_sensor = false;
  bool z2_use_local_sensor = false;
  float z1_room_setpoint = 0;
  float z1_room_temperature = 0;
  float z2_room_setpoint = 0;
  float z2_room_temperature = 0;
  bool RemoteTempOn = false;
  float ac_remote_room_temp = 0;
  bool ac_remote_val_change = false;
};

#ifdef ESP32
HTTPClient http;
WiFiClientSecure NetworkClient;  // Encryption Support
#endif

MqttSettings mqttSettings;
UnitSettings unitSettings;
ECODAN HeatPump;
MELCLOUD MELCloud;
AC AC;
#ifdef ESP8266
SoftwareSerial SwSerial1;
SoftwareSerial SwSerial2;
#endif
WiFiClient NetworkClient1;
WiFiClient NetworkClient2;
PubSubClient MQTTClient1(NetworkClient1);
PubSubClient MQTTClient2(NetworkClient2);
ESPTelnet TelnetServer;

// Delcare Global Scope for Non-Blocking, always active Portal with "TEMP" placeholder, real values populated later from filesystem
WiFiManagerParameter custom_mqtt_server("server", "<b>Required</b> Primary MQTT Server (IP Address or DNS)", "TEMP", hostname_max_length);
WiFiManagerParameter custom_mqtt_user("user", "Primary MQTT Username", "TEMP", user_max_length);
WiFiManagerParameter custom_mqtt_pass("pass", "Primary MQTT Password", "TEMP", password_max_length);
WiFiManagerParameter custom_mqtt_port("port", "Primary MQTT Server Port (Default: 1883)", "TEMP", port_max_length);
WiFiManagerParameter custom_mqtt_basetopic("basetopic", "Primary MQTT Base Topic<br><font size='0.8em'>A unique topic name</font>", "TEMP", basetopic_max_length);
WiFiManagerParameter custom_mqtt2_server("server2", "<hr><b>Optional</b> Secondary MQTT Server<br><font size='0.8em'>You can send data to a second MQTT broker, <b>leave default or blank if not in use</b></font>", "TEMP", hostname_max_length);
WiFiManagerParameter custom_mqtt2_user("user2", "Secondary MQTT Username", "TEMP", user_max_length);
WiFiManagerParameter custom_mqtt2_pass("pass2", "Secondary MQTT Password", "TEMP", password_max_length);
WiFiManagerParameter custom_mqtt2_port("port2", "Secondary MQTT Server Port", "TEMP", port_max_length);
WiFiManagerParameter custom_mqtt2_basetopic("basetopic2", "Secondary MQTT Base Topic", "TEMP", basetopic_max_length);
WiFiManagerParameter custom_device_id("device_id", "<hr>Device ID<br><font size='0.8em'>Only modify if upgrading or changing hardware, copy your previous device ID over</font>", "TEMP", deviceId_max_length);

WiFiManager wifiManager;

#include "TimerCallBack.h"
#include "Debug.h"
#include "MQTTDiscovery.h"
#include "MQTTConfig.h"


void HeatPumpQueryStateEngine(void);
void WriteStateEngine(void);
void MELCloudQueryReplyEngine(void);
void HeatPumpQuerySVCEngine(void);
void TriggerStateMachines(void);
void Zone1Report(void);
void Zone2Report(void);
void HotWaterReport(void);
void SystemReport(void);
void ConfigurationReport(void);
void AdvancedReport(void);
void AdvancedTwoReport(void);
void EnergyReport(void);
void StatusReport(void);
void CompCurveReport(void);
void ActiveControlReport(void);
void ACReport(void);
void CalculateCompCurve(void);
void FastPublish(void);
void dhw_flow_follower(void);

#ifdef ESP32  // Define the M5Stack AtomS3
void CheckForOTAUpdates(void);
#endif

TimerCallBack HeatPumpQuery1(400, HeatPumpQueryStateEngine);  // Set to 400ms (Safe), 320-350ms best time between messages
TimerCallBack HeatPumpQuery2(30000, TriggerStateMachines);    // Set to 20-30s for heat pump query frequency
TimerCallBack HeatPumpQuery3(30000, handleMQTTState);         // Re-connect attempt timer if MQTT is not online
TimerCallBack HeatPumpQuery4(30000, handleMQTT2State);        // Re-connect attempt timer if MQTT Stream 2 is not online
TimerCallBack HeatPumpQuery5(1000, WriteStateEngine);         // Set to 1000ms (Safe), 320-350ms best time between messages
TimerCallBack HeatPumpQuery6(2000, FastPublish);              // Publish some reports at a faster rate
TimerCallBack HeatPumpQuery7(300000, CalculateCompCurve);     // Calculate the Compensation Curve based on latest data   //300000 = 5min

#ifdef ESP32                                                // Define the M5Stack AtomS3
TimerCallBack HeatPumpQuery8(7200000, CheckForOTAUpdates);  // Set check period to 1hr
#endif

TimerCallBack HeatPumpQuery9(30000, dhw_flow_follower);  // 30s DHW Flow Setpoint Follower

unsigned long looppreviousMicros = 0;            // variable for comparing millis counter
unsigned long ftcpreviousMillis = 0;             // variable for comparing millis counter
unsigned long wifipreviousMillis = 0;            // variable for comparing millis counter
unsigned long postwrpreviousMillis = 0;          // variable for comparing millis counter
unsigned long postdfpreviousMillis = 0;          // variable for comparing millis counter
unsigned long lockoutpreviousMillis = 0;         // variable for comparing millis counter
unsigned long lockoutdurationMillis = 0;         // variable for comparing millis counter
unsigned long compressorrundurationMillis = 0;   // variable for comparing millis counter
unsigned long postdhwfspdurationMillis = 0;      // variable for comparing millis counter
unsigned long lastConsumedEnergyTimestamp = 0;   // variable for comparing millis counter
unsigned long lastDeliveredEnergyTimestamp = 0;  // variable for comparing millis counter
unsigned long buttonPressStartTime = 0;          // variable for comparing millis counter
unsigned long lastBlinkTime = 0;                 // variable for comparing millis counter
unsigned long PortalRetryMillis = 0;             // Last STA retry while the config portal is open
bool buttonWasPressed = false;
bool ledState = false;
int FTCLoopSpeed, CPULoopSpeed;  // variable for holding loop time in ms
uint16_t SvcRequested = 0;
int16_t SvcReply = 0;
bool WiFiOneShot = true;
bool CableConnected = true;
bool WiFiConnectedLastLoop = false;
bool PostWriteTrigger = false;
bool PostDHWTimer = false;
bool CompressorRunningLastLoop = false;
bool shortcycleprotectionexit = false;
int ShortCycleCauseNumber = 0;
uint8_t shortcycleprotection_svc_pre[6] = { 0, 0, 0, 0, 0, 0 };  // Format: SCM, DHW, Z1H, Z1C, Z2H, Z2C
uint8_t dhw_svc_pre[6] = { 0, 0, 0, 0, 0, 0 };                   // Format: SCM, DHW, Z1H, Z1C, Z2H, Z2C
unsigned long CompressorStopStartTimer[2] = { 0, 0 };            // Compressor Last Stop Time, Compressor Last Start Time
unsigned long CompressorPeriodDurations[2] = { 0, 0 };           // Last 2 Compressor Periods

extern int cmd_queue_length;
extern int cmd_queue_position;
extern int ac_cmd_queue_length;
extern int ac_cmd_queue_position;
extern bool WriteInProgress;
extern bool ACWriteInProgress;
extern int CurrentWriteAttempt;
extern int ACCurrentWriteAttempt;
byte NormalHWBoostOperating = 0;
uint8_t FTCVersionLastLoop = 0;
uint8_t ACC9LastLoop = 0;
uint8_t FrequencyLastLoop = 0;
double cumulativeEnergyToday[6] = { 0, 0, 0, 0, 0, 0 };      // Format: Heating Consumed, Cooling Consumed, DHW Consumed, Heating Delivered, Cooling Delivered, DHW Delivered
double cumulativeEnergyYesterday[6] = { 0, 0, 0, 0, 0, 0 };  // Format: Heating Consumed, Cooling Consumed, DHW Consumed, Heating Delivered, Cooling Delivered, DHW Delivered

#ifdef ARDUINO_WT32_ETH01
static bool eth_connected = false;
#endif

#if defined(ESP32) && !defined(ARDUINO_WT32_ETH01)
#define ROAM_CHECK_INTERVAL 300000UL  // Vérification toutes les 5 min
#define ROAM_FIRST_CHECK 20000UL      // Première vérification 20 s après chaque (re)connexion
#define ROAM_WEAK_RSSI -70            // Au-dessus : signal correct, aucun scan
#define ROAM_MIN_GAIN 8               // Gain minimum (dB) pour changer de borne
#define ROAM_UNLOCK_AFTER 30000UL     // Borne choisie injoignable depuis 30 s : on accepte n'importe quelle borne
unsigned long RoamLastCheck = 0;
bool RoamScanRunning = false;
bool RoamBssidLocked = false;
unsigned long RoamCount = 0;  // Number of WiFi reconnection attempts launched by the roam code (AP change + unlock)
String RoamSSID = "";
String RoamPSK = "";
#endif



void setup() {
  LatestFirmwareVersion = FirmwareVersion;

  WiFi.mode(WIFI_STA);         // explicitly set mode, esp defaults to STA+AP
  DEBUGPORT.begin(DEBUGBAUD);  // Start Debug

  HEATPUMP_STREAM.begin(SERIAL_BAUD, SERIAL_CONFIG, FTCCable_RxPin, FTCCable_TxPin);  // Rx, Tx
  HeatPump.SetStream(&HEATPUMP_STREAM);
  AC.SetStream(&HEATPUMP_STREAM);
  MEL_STREAM.begin(SERIAL_BAUD, SERIAL_CONFIG, MEL_RxPin, MEL_TxPin);  // Rx, Tx
  MELCloud.SetStream(&MEL_STREAM);

#ifdef ARDUINO_WT32_ETH01
  // For stability, toggle the Oscillator Clock Synchronization pin
  // 1. Allow 5V rail, 3.3V LDO, and 50MHz crystal to fully stabilize
  delay(250);

  // 2. Drive PHY Hardware Reset (GPIO16) LOW
  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);
  delay(50);  // Holding reset for 50ms ensures PHY internal state clear

  // 3. Drive PHY Hardware Reset (GPIO16) HIGH
  digitalWrite(16, HIGH);
  delay(100);  // Allow PHY MDIO/MDC registers & PLL to lock post-reset

  Network.onEvent(onEvent);
  ETH.begin();
#endif

#ifndef ARDUINO_WT32_ETH01
  pinMode(Reset_Button, INPUT);  // Pushbutton on other modules

  if (digitalRead(Reset_Button) == LOW) {  // Inverted (Button Pushed is LOW at boot)
    LED_GPIO = 42;                         // Change for Asgard Firmware
    Reset_Button_pressed_at_boot = true;   // Ignoring push button state after boot
  }
#endif


// -- Lights for ESP8266 and ESP32 -- //
#ifdef ARDUINO_M5STACK_ATOMS3    // Define the M5Stack LED
  myLED.begin(LED_GPIO, 1);      // initialze the myLED object. Here we have 1 LED attached to the LED_GPIO pin
  myLED.brightness(LED_BRIGHT);  // set the LED photon intensity level
#endif
#ifdef ESP8266                     // Define the Witty ESP8266 Ports
  pinMode(Activity_LED, OUTPUT);   // ESP8266 Onboard LED
  pinMode(LDR, INPUT);             // LDR
  pinMode(Red_RGB_LED, OUTPUT);    // Red (RGB) LED
  pinMode(Green_RGB_LED, OUTPUT);  // Green (RGB) LED
  pinMode(Blue_RGB_LED, OUTPUT);   // Blue (RGB) LED

  digitalWrite(Activity_LED, HIGH);  // Set On (Inverted)
  digitalWrite(Red_RGB_LED, LOW);    // Set Off
  digitalWrite(Green_RGB_LED, LOW);  // Set Off
  digitalWrite(Blue_RGB_LED, LOW);   // Set Off
#endif

  readSettingsFromConfig();
  initializeWifiManager();
  if (shouldSaveConfig) {
    saveConfig();
  }
  setupTelnet();
  startTelnet();  // Enable for Debugging Messages

  MQTTClient1.setBufferSize(2048);  // Increase MQTT Buffer Size
  MQTTClient2.setBufferSize(2048);  // Increase MQTT Buffer Size

  RecalculateMQTTTopics();
  RecalculateMQTT2Topics();

  initializeMQTTClient1();
  MQTTClient1.setCallback(MQTTonData);

  initializeMQTTClient2();
  MQTTClient2.setCallback(MQTTonData);

  wifiManager.setWebPortalAuth("admin", mqttSettings.deviceId, "admin/deviceID (Serial Number in Home Assistant)");
  wifiManager.startWebPortal();

  MDNS.begin("heatpump");
  MDNS.addService("http", "tcp", 80);
#ifdef ESP32
  HttpsOTA.onHttpEvent(HttpEvent);
#endif

  // Reset HeatPump flags
  HeatPump.Status.Write_To_Ecodan_OK = HeatPump.Status.HasAnsweredDips = false;

  // Reset AC flags
  AC.Status.Write_To_Ecodan_OK = AC.Status.tempMode = AC.Status.RmtempMode =
    AC.Status.C9 = AC.Status.CD = AC.Status.CE = HeatPump.PrevConnected = AC.PrevConnected = false;
  AC.Status.SupportsHozVane = true;

#ifdef ESP32
  if (WiFi.status() == WL_CONNECTED) { CheckForOTAUpdates(); }
#endif

  CalculateCompCurve();
  for (int i = 0; i < OAT_Window_Size; i++) { OAT_readings[i] = 0; }
}


void loop() {
  // -- Loop Start -- //
  looppreviousMicros = micros();  // Loop Speed Check

  // -- Process Handlers -- //
  HeatPumpQuery1.Process();
  HeatPumpQuery2.Process();
  HeatPumpQuery3.Process();
  HeatPumpQuery4.Process();
  HeatPumpQuery5.Process();
  HeatPumpQuery6.Process();
  HeatPumpQuery7.Process();
#ifdef ESP32
  HeatPumpQuery8.Process();
#endif
  HeatPumpQuery9.Process();

  // -- Heat Pump Connection Handler -- //
  if (!HeatPump.HeatPumpConnected() && !AC.HeatPumpConnected() && !HeatPump.PrevConnected && !AC.PrevConnected) {
    HandleConnectionAttempts();
  } else {
    Connection_attempt_counter = 0;  // Reset the counter
  }

  MELCloudQueryReplyEngine();
  MQTTClient1.loop();
  MQTTClient2.loop();
  TelnetServer.loop();

  if (HeatPump.PrevConnected) {
    HeatPump.Process();
  } else if (AC.PrevConnected) {
    AC.Process();
  }

  MELCloud.Process();
  wifiManager.process();


#ifdef ESP32
  otastatus = HttpsOTA.status();
  if (otastatus == HTTPS_OTA_SUCCESS) {
    printCurrentTime();
    DEBUG_PRINTLN(F("Firmware updated successfully - Rebooting..."));
    update_summary = "Update Successful - Rebooting";
    UpdateReport();  // Send MQTT Status out
    delay(1000);
    ESP.restart();
  } else if (otastatus == HTTPS_OTA_FAIL) {
    printCurrentTime();
    DEBUG_PRINTLN(F("Firmware Update Failed"));
    update_summary = "Update Failed";
    update_in_progress = false;
    UpdateReport();  // Send MQTT Status out
  }
#endif

  // -- Config Saver -- //
  if (shouldSaveConfig) {
    saveConfig();
    CalculateCompCurve();  // Reload the Comp Curve
  }                        // Handles WiFiManager Settings Changes

  // -- Heat Pump Write Command Handler -- //
  if (HeatPump.Status.Write_To_Ecodan_OK && WriteInProgress) {  // A write command is executing
    DEBUG_PRINTLN(F("Write OK!"));                              // Pause normal processsing until complete
    HeatPump.Status.Write_To_Ecodan_OK = false;                 // Set back to false
    WriteInProgress = false;                                    // Set back to false
    if (cmd_queue_length > cmd_queue_position) {                // If the queue has items
      cmd_queue_position++;                                     // Increment the position
      CurrentWriteAttempt = 0;                                  //
    } else {                                                    // All commands written, reset
      cmd_queue_position = 1;
      cmd_queue_length = 0;
      CurrentWriteAttempt = 0;
      PostWriteTrigger = true;  // Allows 10s to pass, then restarts read operation
      postwrpreviousMillis = millis();
    }  // Dequeue the last message that was written
    // Note: Re-publishes if SVC is successful
    if (MQTTReconnect() || MQTT2Reconnect()) { PublishAllReports(); }  // Publish update to the MQTT Topics
  } else if ((WriteInProgress) && (CurrentWriteAttempt > 10)) {        // After 10 attempts to write
    if (cmd_queue_length > cmd_queue_position) {
      cmd_queue_position++;  // Skip this write + Increment the position
      CurrentWriteAttempt = 0;
    } else {
      cmd_queue_position = 1;  // All commands written, reset
      cmd_queue_length = 0;
      CurrentWriteAttempt = 0;
      PostWriteTrigger = true;  // Allows 10s to pass, then restarts read operation
      postwrpreviousMillis = millis();
    }
  }
  if (AC.Status.Write_To_Ecodan_OK && ACWriteInProgress) {  // A write command is executing
    DEBUG_PRINTLN(F("Write OK!"));                          // Pause normal processsing until complete
    AC.Status.Write_To_Ecodan_OK = false;                   // Set back to false
    ACWriteInProgress = false;                              // Set back to false
    if (ac_cmd_queue_length > ac_cmd_queue_position) {      // If the queue has items
      ac_cmd_queue_position++;                              // Increment the position
      ACCurrentWriteAttempt = 0;                            //
    } else {                                                // All commands written, reset
      ac_cmd_queue_position = 1;
      ac_cmd_queue_length = 0;
      ACCurrentWriteAttempt = 0;
      PostWriteTrigger = true;  // Allows 10s to pass, then restarts read operation
      postwrpreviousMillis = millis();
    }                                                                    // Dequeue the last message that was written
    if (MQTTReconnect() || MQTT2Reconnect()) { PublishAllACReports(); }  // Publish update to the MQTT Topics
  } else if ((ACWriteInProgress) && (ACCurrentWriteAttempt > 10)) {      // After 10 attempts to write
    if (ac_cmd_queue_length > ac_cmd_queue_position) {
      ac_cmd_queue_position++;  // Skip this write + Increment the position
      ACCurrentWriteAttempt = 0;
    } else {
      ac_cmd_queue_position = 1;  // All commands written, reset
      ac_cmd_queue_length = 0;
      ACCurrentWriteAttempt = 0;
      PostWriteTrigger = true;  // Allows 10s to pass, then restarts read operation
      postwrpreviousMillis = millis();
    }
  }


  // -- Read Operation Restart -- //
  if ((PostWriteTrigger) && (millis() - postwrpreviousMillis >= 10000)) {  // Allow 10s to pass before re-starting reads for FTC to process
    printCurrentTime();
    DEBUG_PRINTLN(F("Restarting Read Operations"));
    HeatPump.PauseStateMachine = false;
    AC.PauseStateMachine = false;
    PostWriteTrigger = false;
  }

  // -- Time Sync -- //
  if (HeatPump.Status.SyncTime) { syncCurrentTime(); }

  // -- WiFi Status Handler -- //
  if (WiFi.status() != WL_CONNECTED && !wifiManager.getConfigPortalActive()) {
    if (WiFiOneShot) {
      wifipreviousMillis = millis();
      WiFiOneShot = false;
#ifdef ESP8266                           // Define the Witty ESP8266 Ports
      digitalWrite(Blue_RGB_LED, LOW);   // Turn the Blue LED Off
      digitalWrite(Green_RGB_LED, LOW);  // Turn the Green LED Off
      digitalWrite(Red_RGB_LED, HIGH);   // Turn the Red LED On
#endif
#ifdef ARDUINO_M5STACK_ATOMS3  // Define the M5Stack LED
      myLED.setPixel(0, L_RED, 1);
#endif
    }  // Oneshot to start the timer
    if (millis() - wifipreviousMillis >= 300000) {
#ifdef ESP8266                          // Define the Witty ESP8266 Ports
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
#endif
#ifdef ARDUINO_M5STACK_ATOMS3       // Define the M5Stack LED
      myLED.setPixel(0, L_RED, 1);  // set the LED colour and show it     // Flash the Red LED
      myLED.brightness(LED_BRIGHT, 1);
      delay(500);
      myLED.brightness(0, 1);
      delay(500);
      myLED.brightness(LED_BRIGHT, 1);
      delay(500);
      myLED.brightness(0, 1);
      delay(500);
      myLED.brightness(LED_BRIGHT, 1);
      ESP.restart();
#endif
    }  // Wait for 5 mins to try reconnects then force restart
#if defined(ESP32) && !defined(ARDUINO_WT32_ETH01)
    WiFiRoamUnlock(millis() - wifipreviousMillis);  // Patch local : relâche la borne choisie si elle a disparu
#endif
    WiFiConnectedLastLoop = false;
  } else if (WiFi.status() != WL_CONNECTED && wifiManager.getConfigPortalActive()) {
#ifdef ESP8266                         // Define the Witty ESP8266 Ports
    digitalWrite(Blue_RGB_LED, HIGH);  // Turn the Blue LED On
    analogWrite(Green_RGB_LED, LOW);   // Green LED on, 25% brightness
    digitalWrite(Red_RGB_LED, LOW);    // Turn the Red LED Off
#endif
#ifdef ARDUINO_M5STACK_ATOMS3  // Define the M5Stack LED
    myLED.setPixel(0, L_BLUE, 1);
#endif
#if defined(ESP32) && !defined(ARDUINO_WT32_ETH01)
    // Saved WiFi and nobody on the portal AP: retry the saved network (any AP) every 60 s
    if (wifiManager.getWiFiIsSaved() && WiFi.softAPgetStationNum() == 0 && millis() - PortalRetryMillis >= 60000UL) {
      PortalRetryMillis = millis();
      DEBUG_PRINTLN(F("Config portal active, retrying saved WiFi"));
      WiFi.begin();
    }
#endif
    WiFiConnectedLastLoop = false;
  } else {                              // WiFi is connected
    if (!WiFiConnectedLastLoop) {       // Used to update LEDs only on transition of state
#ifdef ESP8266                          // Define the Witty ESP8266 Ports
      digitalWrite(Blue_RGB_LED, LOW);  // Turn the Blue LED Off
      analogWrite(Green_RGB_LED, 30);   // Green LED on, 25% brightness
      digitalWrite(Red_RGB_LED, LOW);   // Turn the Red LED Off
#endif
#ifdef ARDUINO_M5STACK_ATOMS3  // Define the M5Stack LED
      myLED.setPixel(0, L_GREEN, 1);
#endif
    }
#if defined(ESP32) && !defined(ARDUINO_WT32_ETH01)
    WiFiRoamHandler(!WiFiConnectedLastLoop);    // Connect to a stronger mesh AP
    if (wifiManager.getConfigPortalActive()) {  // Connected while the boot config portal is still open
      DEBUG_PRINTLN(F("WiFi connected, closing config portal"));
      wifiManager.stopConfigPortal();  // Closes the portal AP, but also stops the web server
    }
    if (!wifiManager.getConfigPortalActive() && !wifiManager.getWebPortalActive()) {  // Web server stopped (portal closed or timed out): restart it
      DEBUG_PRINTLN(F("Starting Web Portal"));
      wifiManager.startWebPortal();
    }
#endif
    WiFiOneShot = true;
    WiFiConnectedLastLoop = true;
  }

// -- Push Button Action Handler -- //
#ifndef ARDUINO_WT32_ETH01

  bool buttonIsCurrentlyPressed = (digitalRead(Reset_Button) == LOW) && !Reset_Button_pressed_at_boot;
  unsigned long currentMillis = millis();

  // -------------------------------------------------------------------
  // 1. BUTTON PRESS DETECTED (Transition to LOW)
  // -------------------------------------------------------------------
  if (buttonIsCurrentlyPressed && !buttonWasPressed) {
    buttonPressStartTime = currentMillis;
    buttonWasPressed = true;
    lastBlinkTime = currentMillis;
    ledState = true;
  }

  // -------------------------------------------------------------------
  // 2. BUTTON HELD DOWN (Active Feedback)
  // -------------------------------------------------------------------
  if (buttonIsCurrentlyPressed && buttonWasPressed) {
    unsigned long holdDuration = currentMillis - buttonPressStartTime;

    if (holdDuration < 10000) {
      // --- WHILE HOLDING (< 10s): Flash Red every 250ms --- //
      if (currentMillis - lastBlinkTime >= 250) {
        lastBlinkTime = currentMillis;
        ledState = !ledState;

#ifdef ESP8266
        digitalWrite(Red_RGB_LED, ledState ? HIGH : LOW);
        digitalWrite(Blue_RGB_LED, LOW);
#endif
#ifdef ARDUINO_M5STACK_ATOMS3
        myLED.setPixel(0, L_RED, 1);
        myLED.brightness(ledState ? LED_BRIGHT : 0, 1);
#endif
      }
    } else {
// --- THRESHOLD REACHED (>= 10s): Solid Blue --- //
#ifdef ESP8266
      digitalWrite(Red_RGB_LED, LOW);
      digitalWrite(Blue_RGB_LED, HIGH);
#endif
#ifdef ARDUINO_M5STACK_ATOMS3
      myLED.setPixel(0, L_BLUE, 1);
      myLED.brightness(LED_BRIGHT, 1);
#endif
    }
  }

  // -------------------------------------------------------------------
  // 3. BUTTON RELEASE DETECTED (Transition to HIGH)
  // -------------------------------------------------------------------
  if (!buttonIsCurrentlyPressed && buttonWasPressed) {
    unsigned long pressDuration = currentMillis - buttonPressStartTime;
    buttonWasPressed = false;  // Reset tracking state

    // Run heat pump escape actions on valid press release
    HeatPump.SetSvrControlMode(0, HeatPump.Status.ProhibitDHW, HeatPump.Status.ProhibitHeatingZ1, HeatPump.Status.ProhibitCoolingZ1, HeatPump.Status.ProhibitHeatingZ2, HeatPump.Status.ProhibitCoolingZ2);
    ModifyCompCurveState(1, false, 1, 0);
    ModifyCompCurveState(2, false, 1, 0);

    if (pressDuration >= 10000) {
      // --- LONG PRESS RELEASE (>= 10s): Factory Reset --- //
      delay(500);                   // Keep solid blue visible briefly
      wifiManager.resetSettings();  // Clear WiFi credentials
      LittleFS.format();            // Wipe internal filesystem
    } else {
// --- SHORT PRESS RELEASE (< 10s): Flash Red Once --- //
#ifdef ESP8266
      digitalWrite(Red_RGB_LED, HIGH);
      digitalWrite(Blue_RGB_LED, LOW);
#endif
#ifdef ARDUINO_M5STACK_ATOMS3
      myLED.setPixel(0, L_RED, 1);
      myLED.brightness(LED_BRIGHT, 1);
#endif
      delay(200);  // Brief feedback flash before restart
    }

// --- Perform Board Reboot --- //
#ifdef ESP8266
    ESP.reset();
#elif defined(ESP32)
    ESP.restart();
#endif
  }

#endif

  // -- Normal DHW Boost Handler (Enter SCM > Remove DHW Prohibit > Remain or Exit SCM) -- //
  if ((HeatPump.Status.LastSystemOperationMode == 1 || HeatPump.Status.LastSystemOperationMode == 6) && HeatPump.Status.SystemOperationMode != 1 && NormalHWBoostOperating == 1) {
    HeatPump.SetSvrControlMode(dhw_svc_pre[0], dhw_svc_pre[1], dhw_svc_pre[2], dhw_svc_pre[3], dhw_svc_pre[4], dhw_svc_pre[5]);  // Restore Server Control Mode + Prohibits
    HeatPump.Status.SvrControlMode = dhw_svc_pre[0];
    WriteInProgress = true;      // Wait For OK
    NormalHWBoostOperating = 0;  // Don't enter again
  }
  if ((HeatPump.Status.LastSystemOperationMode == 1 && HeatPump.Status.SystemOperationMode != 1) || (HeatPump.Status.LastSystemOperationMode == 6 && HeatPump.Status.SystemOperationMode != 6) && DHWFlowFollowingActive) {
    PostDHWTimer = true;                                                 // Start timing
    postdhwfspdurationMillis = millis();                                 // Start the post DHW timer
  }                                                                      // For Onboard Comp Curve, recalculate FSP to prevent outdoor stopping
  if (PostDHWTimer && (millis() - postdhwfspdurationMillis >= 60000)) {  // Once 60s after DHW has completed, write flow setpoint back down
    PostDHWTimer = false;                                                // End
    CalculateCompCurve();                                                // Delay this until 60s after mode finished
    Flow_Inc_Count = 0;                                                  // Reset Flow Following Counter
    FF_RaiseArmed = FF_LowerArmed = false;  // Clear flow following persistence timers
  }

  // -- Defrost Handler -- //
  if (HeatPump.Status.Defrost != 0) { inDefrostWindow = true; }                                                  // Start Defrost Window
  if (HeatPump.Status.LastDefrost != 0 && HeatPump.Status.Defrost == 0) { postdfpreviousMillis = millis(); }     // Transitioned from Defrosting Stage to Normal
  if (HeatPump.Status.Defrost == 0 && (millis() - postdfpreviousMillis >= 360000)) { inDefrostWindow = false; }  // End Defrost Window


  // -- Dynamic HA Adjustment -- //
  // -- FTC7 + R290 Outdoor Limit Adjustments -- //
  if (FTCVersionLastLoop != HeatPump.Status.FTCVersion && HeatPump.Status.RefrigerantType == 2) {  // Dynamic Update HA limit for FTC7
    if (MQTTReconnect()) { PublishDiscoveryTopics(1, MQTT_BASETOPIC); }
    if (MQTT2Reconnect()) { PublishDiscoveryTopics(2, MQTT_2_BASETOPIC); }
  }
  if (ACC9LastLoop != AC.Status.C9 && AC.Status.SupportsHozVane) {  // Dynamic Vane & Fan Speeds
    if (MQTTReconnect()) { PublishA2ADiscoveryTopics(1, MQTT_BASETOPIC); }
    if (MQTT2Reconnect()) { PublishA2ADiscoveryTopics(2, MQTT_2_BASETOPIC); }
  }
  FTCVersionLastLoop = HeatPump.Status.FTCVersion;  // On FTC version capture, if criteria met then change
  ACC9LastLoop = AC.Status.C9;


  // -- Auto Discovery Trigger -- //
  if (HeatPump.PrevConnected && !A2WPrevConnectedLastLoop) {
    if (MQTTReconnect()) { PublishDiscoveryTopics(1, MQTT_BASETOPIC); }
    if (MQTT2Reconnect()) { PublishDiscoveryTopics(2, MQTT_2_BASETOPIC); }
  }
  if (AC.PrevConnected && !A2APrevConnectedLastLoop) {
    if (MQTTReconnect()) { PublishA2ADiscoveryTopics(1, MQTT_BASETOPIC); }
    if (MQTT2Reconnect()) { PublishA2ADiscoveryTopics(2, MQTT_2_BASETOPIC); }
  }
  A2WPrevConnectedLastLoop = HeatPump.PrevConnected;
  A2APrevConnectedLastLoop = AC.PrevConnected;


  // -- Outdoor Triggers on Outdoor Unit Change -- //
  if (FrequencyLastLoop > 0 && HeatPump.Status.CompressorFrequency == 0) {                       // Transition of Compressor On to Off
    HeatPump.WriteServiceCodeCMD(19);                                                            // Trigger Fan Speed Request Service Code
    HeatPump.WriteServiceCodeCMD(20);                                                            // Trigger Fan Speed Request Service Code
    if (HeatPump.Status.HasGeodan) { HeatPump.WriteServiceCodeCMD(28); }                         // For Geodan Only
    if (HeatPump.Status.Defrost == 0) {                                                          // If Not Defrosting
      CompressorPeriodDurations[1] = CompressorPeriodDurations[0];                               // Transfer Last Compressor Period to Array Pos 1
      CompressorPeriodDurations[0] = (millis() / 1000) - CompressorStopStartTimer[0];            // Current Time from Stop > Stop (Seconds) to Array Pos 0
      CompressorStopStartTimer[0] = (millis() / 1000);                                           // Last Compressor Stop Time (Seconds)
      compressorrundurationMillis = CompressorStopStartTimer[0] - CompressorStopStartTimer[1];   // Last Compressor Run Duration (Seconds)
      if (Flow_Inc_Count > 0) {                                                                  // If its been manipulated
        HeatPump.SetFlowSetpoint(FlowTemp_Target, HeatPump.Status.HeatingControlModeZ1, ZONE1);  // Need to avoid overwriting by onboard weather curve..
        write_thermostats();                                                                     //
        Flow_Inc_Count = 0;                                                                      // Reset the Flow Temp Incrementer
        FF_RaiseArmed = FF_LowerArmed = false;  // Clear flow following persistence timers
      }                                                                                          //
    }                                                                                            //
  } else if (FrequencyLastLoop == 0 && HeatPump.Status.CompressorFrequency > 0) {                // Transition of Compressor Off to On
    HeatPump.WriteServiceCodeCMD(19);                                                            // Trigger Fan Speed Request Service Code
    HeatPump.WriteServiceCodeCMD(20);                                                            // Trigger Fan Speed Request Service Code
    if (HeatPump.Status.Defrost == 0) {                                                          // If Not Defrosting
      CompressorStopStartTimer[1] = (millis() / 1000);                                           // Last Compressor Start Time (Seconds)
    }
  }
  FrequencyLastLoop = HeatPump.Status.CompressorFrequency;

  // -- AC Webhook Writes -- //
  if (unitSettings.ac_remote_val_change) {
    unitSettings.ac_remote_val_change = false;
    AC.SetRemoteTemp(unitSettings.ac_remote_room_temp);
  }

  // -- Short Cycling Protection -- //
  // Definition of Short Cycle if there is 2 Compressor Periods in less than 20min (Stop > Run > Stop x2)
  if (!ShortCycleProtectionActive && (CompressorPeriodDurations[0] > 0 && CompressorPeriodDurations[1] > 0) && (CompressorPeriodDurations[0] + CompressorPeriodDurations[1] < 1200)) {                                                         // Compressor Period < 20min (6 drops/hr)                                                                                                                                                                  // If enabled, count eq or greater than detection threshold and not active already
    lockoutdurationMillis = map((CompressorPeriodDurations[0] + CompressorPeriodDurations[1]), 0, 1200, 600000, 1200000);                                                                                                                      // 0s Period = 10min lock, 1200s = 20min lockout
    if (unitSettings.fixedlockoutduration > 0) { lockoutdurationMillis = unitSettings.fixedlockoutduration * 60000; }                                                                                                                          // Overwrite auto calculation if fixed duration is specified
    lockoutpreviousMillis = millis();                                                                                                                                                                                                          // Start the timer
    if (unitSettings.shortcycleprotectionenabled && (!HeatPump.Status.ProhibitHeatingZ1 || !HeatPump.Status.ProhibitCoolingZ1 || !HeatPump.Status.ProhibitHeatingZ2 || !HeatPump.Status.ProhibitCoolingZ2 || !HeatPump.Status.ProhibitDHW)) {  // Check if prohibits are already active
      ShortCycleProtectionActive = true;
      std::array<uint8_t, 6> current_svc_state = { HeatPump.Status.SvrControlMode, HeatPump.Status.ProhibitDHW, HeatPump.Status.ProhibitHeatingZ1, HeatPump.Status.ProhibitCoolingZ1, HeatPump.Status.ProhibitHeatingZ2, HeatPump.Status.ProhibitCoolingZ2 };
      std::copy(current_svc_state.begin(), current_svc_state.end(), shortcycleprotection_svc_pre);
      HeatPump.SetSvrControlMode(1, HeatPump.Status.ProhibitDHW, 1, 1, 1, 1);  // Prohibit Everything and keep DHW status the same
      HeatPump.Status.SvrControlMode = 1;                                      // Write Server Control Mode + Prohibits
    }

    if (abs(HeatPump.Status.HeaterOutputFlowTemperature - HeatPump.Status.Zone1TemperatureSetpoint) > 4) {
      ShortCycleCauseNumber = 1;
    } else if (HeatPump.Status.SystemOperationMode == 0) {
      ShortCycleCauseNumber = 2;
    }

    ActiveControlReport();  // Publish MQTT on occurance
  } else if ((ShortCycleProtectionActive && (millis() - lockoutpreviousMillis > lockoutdurationMillis)) || shortcycleprotectionexit) {
    ShortCycleProtectionActive = shortcycleprotectionexit = false;
    HeatPump.SetSvrControlMode(shortcycleprotection_svc_pre[0], shortcycleprotection_svc_pre[1], shortcycleprotection_svc_pre[2], shortcycleprotection_svc_pre[3], shortcycleprotection_svc_pre[4], shortcycleprotection_svc_pre[5]);  // Restore Server Control Mode + Prohibits
    HeatPump.Status.SvrControlMode = shortcycleprotection_svc_pre[0];
    CompressorPeriodDurations[0] = CompressorPeriodDurations[1] = lockoutdurationMillis = ShortCycleCauseNumber = 0;  // Reset the compressor timers, lockout duration and cause factor
    ActiveControlReport();                                                                                            // Publish MQTT on occurance
  }


  // -- Flow Temperature Overshoot Hysterisis (with persistence gate) -- //
  if ((HeatPump.Status.SystemOperationMode == 2 || HeatPump.Status.SystemOperationMode == 3) && unitSettings.shortcycleprotectionenabled) {
    const bool ffHeating = (HeatPump.Status.HeatCool == 0 && HeatPump.Status.HeatingControlModeZ1 == 1);  // Heating and Fixed Flow
    const bool ffCooling = (HeatPump.Status.HeatCool == 1 && HeatPump.Status.HeatingControlModeZ1 == 3);  // Cooling
    if (ffHeating || ffCooling) {
      const float dir = ffHeating ? 1.0f : -1.0f;  // Cooling mirrors every comparison and step
      const float flow = HeatPump.Status.HeaterOutputFlowTemperature;
      const float fsp = HeatPump.Status.Zone1FlowTemperatureSetpoint;
      const float exc = dir * (flow - fsp);                  // Flow excess over setpoint, in the direction that trips the outdoor unit
      const bool moving = dir * (flow - FlowTemp_Last) > 0;  // Reading has just moved further from the setpoint
      bool doRaise = false;

      // Raise: reading must have moved away, then either hold for the persistence time or get close to the 2.0C stop
      if (exc > 1.0f) {
        if (!FF_RaiseArmed && moving) {
          FF_RaiseArmed = true;
          FF_RaiseArmedMs = millis();
        }
        if (exc >= FF_FASTPATH_EXC || (FF_RaiseArmed && (millis() - FF_RaiseArmedMs >= FF_RAISE_PERSIST_MS))) { doRaise = true; }
      } else {
        FF_RaiseArmed = false;  // Reading came back inside the band: forget it
      }

      if (doRaise) {
        FF_LowerArmed = false;
        if (Flow_Inc_Count == 0) {  // On first entry, remember the setpoint before following
          FlowTemp_Target = fsp;
          FlowFollowingActive = false;
        }
        if (Flow_Inc_Count < (unitSettings.max_flow_overshoot / 0.5)) {  // Maximum increases is 0.5C * setting
          HeatPump.SetFlowSetpoint(fsp + dir * 0.5f, HeatPump.Status.HeatingControlModeZ1, ZONE1);
          HeatPump.Status.Zone1FlowTemperatureSetpoint += dir * 0.5f;
          write_thermostats();
          Flow_Inc_Count++;  // This will be cancelled at the next compressor stop
          FlowFollowingActive = true;
          FF_RaiseArmed = false;  // Re-arm only on the next movement of the reading
        }
        if (dir * (HeatPump.Status.Zone1FlowTemperatureSetpoint - Z1_CurveFSP) < 0) {  // Cancel Flow Following once the Comp Curve Target has passed the raised setpoint
          FlowTemp_Target = HeatPump.Status.Zone1FlowTemperatureSetpoint;
          FlowFollowingActive = false;
        }
      } else if (Flow_Inc_Count > 0 && exc < 0.5f) {  // Flow Temp reducer if within 0.5C, only once it has held there
        if (!FF_LowerArmed) {
          FF_LowerArmed = true;
          FF_LowerArmedMs = millis();
        }
        if (millis() - FF_LowerArmedMs >= FF_LOWER_PERSIST_MS) {
          HeatPump.SetFlowSetpoint(fsp - dir * 0.5f, HeatPump.Status.HeatingControlModeZ1, ZONE1);
          HeatPump.Status.Zone1FlowTemperatureSetpoint -= dir * 0.5f;
          write_thermostats();
          Flow_Inc_Count--;
          if (Flow_Inc_Count == 0) { FlowFollowingActive = false; }  // End Flow Following
          FF_LowerArmed = false;
        }
      } else {
        FF_LowerArmed = false;
      }
    } else {
      FF_RaiseArmed = FF_LowerArmed = false;
    }
    FlowTemp_Last = HeatPump.Status.HeaterOutputFlowTemperature;  // Last Loop Flow Temperature
  } else {
    FF_RaiseArmed = FF_LowerArmed = false;
  }

  // -- Exit Onboard Compensation Curve if System Operation Modes Change -- //
  if (unitSettings.z1_active && HeatPump.Status.HasAnsweredDips && (HeatPump.Status.HeatingControlModeZ1 != 1 && HeatPump.Status.HeatingControlModeZ1 != 4)) { ModifyCompCurveState(1, false, 1, 0); }
  if (unitSettings.z2_active && HeatPump.Status.HasAnsweredDips && (HeatPump.Status.HeatingControlModeZ2 != 1 && HeatPump.Status.HeatingControlModeZ2 != 4)) { ModifyCompCurveState(2, false, 1, 0); }

  // -- Energy Cumulative Counter -- //
  if (HeatPump.Status.DateTimeStamp.tm_hour == 0 && HeatPump.Status.DateTimeStamp.tm_mday != lastResetDay) {  // When the day changes (midnight)
    std::array<double, 6> today_energy = { cumulativeEnergyToday[0], cumulativeEnergyToday[1], cumulativeEnergyToday[2], cumulativeEnergyToday[3], cumulativeEnergyToday[4], cumulativeEnergyToday[5] };
    std::copy(today_energy.begin(), today_energy.end(), cumulativeEnergyYesterday);  // Move today into Yeseterday
    std::array<double, 6> clear_energy = { 0, 0, 0, 0, 0, 0 };                       // Set all 0
    std::copy(clear_energy.begin(), clear_energy.end(), cumulativeEnergyToday);      // Move 0 to todays
    lastResetDay = HeatPump.Status.DateTimeStamp.tm_mday;                            // Mark this day as completed
  }

  // -- MELCloud Timeout -- //
  if (MELCloud_Adapter_Connected) {
    if (millis() - MELCloud.LastMELCloudMessage() >= 60000) { MELCloud_Adapter_Connected = false; }  // If there is no MELCloud Message for 60s consider it disconnected
  } else {
    if (MELCloud.Connected) { MELCloud_Adapter_Connected = true; }  // If a MELCloud Message appears, set true again
  }


  // -- CPU Loop Time End -- //
  CPULoopSpeed = micros() - looppreviousMicros;  // Loop Speed End Monitor
}


void HandleConnectionAttempts(void) {
  if (!HeatPump.HeatPumpConnected() && !AC.HeatPumpConnected()) {
    if (Connection_attempt_counter > 20) {  // Request/Attempt disconnect if no reply
      DEBUG_PRINTLN(F("No reply after 20+ attempts, forcing disconnect first..."));
      HeatPump.Disconnect();
      AC.Disconnect();
    }

#ifdef ARDUINO_M5STACK_ATOMS3
    // Swap to the other pins and test the connection
    if (CableConnected) {
      DEBUG_PRINTLN("Trying to connect via Proxy Circuit Board");
      HEATPUMP_STREAM.begin(SERIAL_BAUD, SERIAL_CONFIG, FTCProxy_RxPin, FTCProxy_TxPin);  // Rx, Tx
      HeatPump.SetStream(&HEATPUMP_STREAM);                                               // Set & Connect
      AC.SetStream(&HEATPUMP_STREAM);                                                     // Set & Connect
      CableConnected = false;
    } else {
      DEBUG_PRINTLN("Trying to connect via Cable");
      HEATPUMP_STREAM.begin(SERIAL_BAUD, SERIAL_CONFIG, FTCCable_RxPin, FTCCable_TxPin);  // Rx, Tx
      HeatPump.SetStream(&HEATPUMP_STREAM);
      AC.SetStream(&HEATPUMP_STREAM);
      CableConnected = true;
    }
#else
    // For WT32 Ethernet and ESP8266 Devices switching between A2A and A2W Connect Messages
    HeatPump.Connect();
    if (!HeatPump.HeatPumpConnected()) {  // If the A2W Request was not successful
      AC.Connect();
    }
#endif
    Connection_attempt_counter++;
  }
  TriggerStateMachines();
}


void TriggerStateMachines(void) {
  ftcpreviousMillis = millis();
  if (AC.HeatPumpConnected()) {
    DEBUG_PRINTLN("Trigger AC Status State Machine");
    AC.TriggerStatusStateMachine();
  } else {
    DEBUG_PRINTLN("AC Disconnected");
  }

  if (HeatPump.HeatPumpConnected()) {
    DEBUG_PRINTLN("Trigger A2W Status State Machine");
    HeatPump.TriggerStatusStateMachine();
  } else {
    DEBUG_PRINTLN("A2W Disconnected");
  }

  if (MQTTReconnect()) {
    StatusReport();
  }
}


void HeatPumpQueryStateEngine(void) {
  //DEBUG_PRINTLN("HeatPumpQueryStateEngine");
  if (AC.PrevConnected) {
    if (cmd_queue_length == 0) {  // If there is no commands awaiting written
      //DEBUG_PRINTLN("AC Status State Machine");
      AC.StatusStateMachine();  // Full Read trigged by CurrentMessage
    }
    if (AC.UpdateComplete()) {
      DEBUG_PRINTLN(F("A2A Update Complete"));
      if (!AC.Status.C9) { AC.GetVersion(0xC9); }                  // 0xC9
      if (!AC.Status.CD && AC.Status.C9) { AC.GetVersion(0xCD); }  // 0xCD is requested after C9
      if (!AC.Status.CE && AC.Status.C9) { AC.GetVersion(0xCE); }  // 0xCE - Unknown at the moment who/when this should be requested
      FTCLoopSpeed = millis() - ftcpreviousMillis;                 // Loop Speed End
      PublishAllACReports();
    }
  } else if (HeatPump.PrevConnected) {
    if (cmd_queue_length == 0) {  // If there is no commands awaiting written
      //DEBUG_PRINTLN("A2W Status State Machine");
      HeatPump.StatusStateMachine();  // Full Read trigged by CurrentMessage
    }
    // Call Once Full Update is complete
    if (HeatPump.UpdateComplete()) {
      DEBUG_PRINTLN(F("A2W Update Complete"));
      FTCLoopSpeed = millis() - ftcpreviousMillis;  // Loop Speed End

      bool primaryMQTTok = MQTTReconnect();
      bool secondaryMQTTok = MQTT2Reconnect();

      if (HeatPump.Status.FTCVersion == 0) { HeatPump.GetFTCVersion(); }
      if (!HeatPump.Status.HasAnsweredDips) {
        if (primaryMQTTok || secondaryMQTTok) {
          StatusReport();
          CalculateCompCurve();
        }
      } else {
        HeatPump.SVCUpdateComplete();
        HeatPump.StatusSVCMachine();  // Call service codes
        if (primaryMQTTok || secondaryMQTTok) {
          PublishAllReports();
        }
      }
    }
  }
}


void HeatPumpQuerySVCEngine(void) {
  HeatPump.StatusSVCMachine();
}

void WriteStateEngine(void) {
  if (HeatPump.PrevConnected && HeatPump.Status.HasAnsweredDips) {
    HeatPump.WriteStateMachine();
  } else if (AC.PrevConnected) {
    AC.WriteStateMachine();
  }
}



void MELCloudQueryReplyEngine(void) {
  if (MELCloud.Status.ReplyNow) {
    if (MELCloud.Status.ActiveMessage == 0x28 && MELCloud.Status.MEL_Online) {          // Toggle the Online High (MELCloud Only)
      Array0x28[11] = 1;                                                                // Set the FTC Bit
    } else if (MELCloud.Status.ActiveMessage == 0x28 && !MELCloud.Status.MEL_Online) {  // For other requests, low
      Array0x28[11] = 0;                                                                // Set the FTC Bit
    }
    if (MELCloud.Status.ActiveMessage == 0xCE && !AC.Status.CE) { return; }  // Intercept and return
    MELCloud.ReplyStatus(MELCloud.Status.ActiveMessage);                     // Reply with the OK Message to MELCloud
    MELCloud.Status.ReplyNow = false;
    if (MELCloud.Status.ActiveMessage == 0x32 || MELCloud.Status.ActiveMessage == 0x33 || MELCloud.Status.ActiveMessage == 0x34 || MELCloud.Status.ActiveMessage == 0x35) {  // The write commands for A2W
      if (!unitSettings.BlockWriteFromMELCloud) { HeatPump.WriteMELCloudCMD(MELCloud.Status.ActiveMessage); }
    } else if (MELCloud.Status.ActiveMessage == 0x40 || MELCloud.Status.ActiveMessage == 0x41 || MELCloud.Status.ActiveMessage == 0x3F) {  // A2A Write Commands
      if (!unitSettings.BlockWriteFromMELCloud) { AC.WriteMELCloudCMD(MELCloud.Status.ActiveMessage); }
    }
  } else if ((HeatPump.PrevConnected) && (MELCloud.Status.ConnectRequest) && (HeatPump.Status.FTCVersion != 0) && HeatPump.Status.HasAnsweredDips) {
    MELCloud.ConnectA2W();  // Reply to the connect request
    MELCloud.Status.ConnectRequest = false;
  } else if (AC.PrevConnected && MELCloud.Status.ConnectRequest && AC.Status.C9) {
    MELCloud.ConnectA2A();  // Reply to the connect request
    MELCloud.Status.ConnectRequest = false;
  } else if (MELCloud.Status.MELRequest1) {
    MELCloud.MELNegotiate1(AC.PrevConnected);  // Reply to the connect request
    MELCloud.Status.MELRequest1 = false;
  } else if (MELCloud.Status.MELRequest2) {
    MELCloud.MELNegotiate2();  // Reply to the connect request
    MELCloud.Status.MELRequest2 = false;
    MELCloud_Adapter_Connected = true;          // Mark as in use
  } else if (MELCloud.Status.MEL_HB_Request) {  // Reply to the MELCloud Heartbeat
    MELCloud.ReplyStatus(0x34);
    MELCloud.Status.MEL_HB_Request = false;
  }
}


void MQTTonDisconnect(void* response) {
  DEBUG_PRINTLN(F("MQTT Disconnect"));
}

void MQTTonData(char* topic, byte* payload, unsigned int length) {
  payload[length] = 0;
  String Topic = topic;
  String Payload = (char*)payload;

  DEBUG_PRINT(F("\nReceived MQTT Message on topic: "));
  DEBUG_PRINT(Topic.c_str());
  DEBUG_PRINT(F(" with Payload: "));
  DEBUG_PRINTLN(Payload.c_str());

  // Service Codes
  if ((Topic == MQTTCommandSystemService) || (Topic == MQTTCommand2SystemService)) {
    if (Payload.toInt() == 999) {
      DEBUG_PRINTLN(F("FTC Bridge Restart Request"));
#ifdef ESP8266
      ESP.reset();
#endif
#ifdef ESP32
      ESP.restart();
#endif
    } else if (Payload.toInt() == 998) {
      DEBUG_PRINTLN(F("Disconnecting from FTC"));
      HeatPump.Disconnect();
    } else if (Payload.toInt() == 997) {
      DEBUG_PRINTLN(F("Ignoring Write Requests from MELCloud"));
      unitSettings.BlockWriteFromMELCloud = true;
      shouldSaveConfig = true;
      StatusReport();
    } else if (Payload.toInt() == 996) {
      DEBUG_PRINTLN(F("Allowing Write Requests from MELCloud"));
      unitSettings.BlockWriteFromMELCloud = false;
      shouldSaveConfig = true;
      StatusReport();
    } else if (Payload.toInt() == 995) {
      DEBUG_PRINTLN(F("Requested Bridge Firmware Update"));
      if (WiFi.RSSI() < -75) {
        update_summary = "Warning! WiFi signal weak";
        UpdateReport();  // Send MQTT Status out
      }
      if (NormalHWBoostOperating != 1 && LatestFirmwareVersion != FirmwareVersion) {
#ifdef ESP32  // Define the M5Stack AtomS3
        InstallOTAUpdates();
#endif
      }  // Skip OTA updates when running Norm DHW or this status would be lost mid-run
      else {
        update_summary = "Update blocked during DHW Boost - please try again later";
        UpdateReport();  // Send MQTT Status out
      }
    } else if (Payload.toInt() == 994) {
      DEBUG_PRINTLN(F("Requested Bridge Latest Firmware Available"));
      DEBUG_PRINTLN(F(": UNAVAILABLE"));
#ifdef ESP32  // Define the M5Stack AtomS3
      CheckForOTAUpdates();
#endif
    } else if (Payload.toInt() == 993) {
      DEBUG_PRINTLN(F("Requested FTC/AC Version Information"));
      if (HeatPump.PrevConnected) {
        HeatPump.GetFTCVersion();
      } else if (AC.PrevConnected) {
        AC.GetVersion(0xC9);
        AC.GetVersion(0xCD);
        AC.GetVersion(0xCE);
      }
    } else if (Payload.toInt() == 992) {
      DEBUG_PRINT(F("Short Cycle Protection: "));
      if (!unitSettings.shortcycleprotectionenabled) {
        DEBUG_PRINTLN(F("ENABLED"));
        unitSettings.shortcycleprotectionenabled = true;
        SvcReply = 1;
      } else if (unitSettings.shortcycleprotectionenabled) {
        DEBUG_PRINTLN(F("DISABLED"));
        unitSettings.shortcycleprotectionenabled = false;
        shortcycleprotectionexit = true;
        SvcReply = 0;
      }
      SvcRequested = 992;
      shouldSaveConfig = true;
    } else if (Payload.toInt() >= 880 && Payload.toInt() <= 900) {
      DEBUG_PRINT(F("SCP - Max Flow Overshoot Set: "));
      SvcReply = unitSettings.max_flow_overshoot = Payload.toInt() - 880;
      SvcRequested = Payload.toInt();
      DEBUG_PRINTLN(Payload.toInt());
      shouldSaveConfig = true;
    } else {
      HeatPump.WriteServiceCodeCMD(Payload.toInt());
      SvcRequested = Payload.toInt();
    }
  }

  // Curve or Temp Independent Thermostat Setting
  // Heating & Cooling Zone 1 Commands
  else if ((Topic == MQTTCommandZone1NoModeSetpoint) || (Topic == MQTTCommand2Zone1NoModeSetpoint)) {
    MQTTWriteReceived("MQTT Set Zone1 Temperature Setpoint", 6);
    HeatPump.SetZoneTempSetpoint(Payload.toFloat(), HeatPump.Status.HeatingControlModeZ1, ZONE1);
    HeatPump.Status.Zone1TemperatureSetpoint = Payload.toFloat();
  }
  // Flow Setpoint Commands
  // Heating & Cooling Zone 1 Commands
  else if ((Topic == MQTTCommandZone1FlowSetpoint) || (Topic == MQTTCommand2Zone1FlowSetpoint)) {
    MQTTWriteReceived("MQTT Set Zone1 Flow Setpoint", 6);
    HeatPump.SetFlowSetpoint(Payload.toFloat(), HeatPump.Status.HeatingControlModeZ1, ZONE1);
    FlowFollowingActive = false;
    write_thermostats();
    HeatPump.Status.Zone1FlowTemperatureSetpoint = Payload.toFloat();
  }

  // Thermostat Setpoint
  // Heating & Cooling Zone 2 Commands
  else if ((Topic == MQTTCommandZone2NoModeSetpoint) || (Topic == MQTTCommand2Zone2NoModeSetpoint)) {
    MQTTWriteReceived("MQTT Set Zone2 Temperature Setpoint", 6);
    HeatPump.SetZoneTempSetpoint(Payload.toFloat(), HeatPump.Status.HeatingControlModeZ2, ZONE2);
    HeatPump.Status.Zone2TemperatureSetpoint = Payload.toFloat();
  }
  // Flow Setpoint Commands
  // Heating & Cooling Zone 2 Commands
  else if ((Topic == MQTTCommandZone2FlowSetpoint) || (Topic == MQTTCommand2Zone2FlowSetpoint)) {
    MQTTWriteReceived("MQTT Set Zone2 Flow Setpoint", 6);
    HeatPump.SetFlowSetpoint(Payload.toFloat(), HeatPump.Status.HeatingControlModeZ2, ZONE2);
    FlowFollowingActive = false;
    write_thermostats();
    HeatPump.Status.Zone2FlowTemperatureSetpoint = Payload.toFloat();
  }

  // Prohibits for Server Control Mode
  else if ((Topic == MQTTCommandZone1ProhibitHeating) || (Topic == MQTTCommand2Zone1ProhibitHeating)) {
    MQTTWriteReceived("MQTT Zone 1 Prohibit Heating", 16);
    HeatPump.SetProhibits(TX_MESSAGE_SETTING_HEAT_Z1_INH_Flag, Payload.toInt());
    HeatPump.Status.ProhibitHeatingZ1 = dhw_svc_pre[2] = shortcycleprotection_svc_pre[2] = Payload.toInt();
  } else if ((Topic == MQTTCommandZone1ProhibitCooling) || (Topic == MQTTCommand2Zone1ProhibitCooling)) {
    MQTTWriteReceived("MQTT Zone 1 Prohibit Cooling", 16);
    HeatPump.SetProhibits(TX_MESSAGE_SETTING_COOL_Z1_INH_Flag, Payload.toInt());
    HeatPump.Status.ProhibitCoolingZ1 = dhw_svc_pre[3] = shortcycleprotection_svc_pre[3] = Payload.toInt();
  } else if ((Topic == MQTTCommandZone2ProhibitHeating) || (Topic == MQTTCommand2Zone2ProhibitHeating)) {
    MQTTWriteReceived("MQTT Zone 2 Prohibit Heating", 16);
    HeatPump.SetProhibits(TX_MESSAGE_SETTING_HEAT_Z2_INH_Flag, Payload.toInt());
    HeatPump.Status.ProhibitHeatingZ2 = dhw_svc_pre[4] = shortcycleprotection_svc_pre[4] = Payload.toInt();
  } else if ((Topic == MQTTCommandZone2ProhibitCooling) || (Topic == MQTTCommand2Zone2ProhibitCooling)) {
    MQTTWriteReceived("MQTT Zone 2 Prohibit Cooling", 16);
    HeatPump.SetProhibits(TX_MESSAGE_SETTING_COOL_Z2_INH_Flag, Payload.toInt());
    HeatPump.Status.ProhibitCoolingZ2 = dhw_svc_pre[5] = shortcycleprotection_svc_pre[5] = Payload.toInt();
  } else if ((Topic == MQTTCommandHotwaterProhibit) || (Topic == MQTTCommand2HotwaterProhibit)) {
    MQTTWriteReceived("MQTT DHW Prohibit", 16);
    HeatPump.SetProhibits(TX_MESSAGE_SETTING_DHW_INH_Flag, Payload.toInt());
    HeatPump.Status.ProhibitDHW = Payload.toInt();
  }


  // Other Commands
  else if ((Topic == MQTTCommandHotwaterMode) || (Topic == MQTTCommand2HotwaterMode)) {
    MQTTWriteReceived("MQTT Set HW Mode", 15);
    HeatPump.SetDHWMode(&Payload);
  } else if ((Topic == MQTTCommandHotwaterBoost) || (Topic == MQTTCommand2HotwaterBoost)) {
    MQTTWriteReceived("MQTT Set Forced DHW Boost", 16);
    HeatPump.ForceDHW(Payload.toInt());
    HeatPump.Status.HotWaterBoostActive = Payload.toInt();
  } else if ((Topic == MQTTCommandHotwaterNormalBoost) || (Topic == MQTTCommand2HotwaterNormalBoost)) {
    MQTTWriteReceived("MQTT Set Normal DHW Boost", 16);
    if (Payload.toInt() == 1) {  // Turn ON
      std::array<uint8_t, 6> current_svc_state = { HeatPump.Status.SvrControlMode, HeatPump.Status.ProhibitDHW, HeatPump.Status.ProhibitHeatingZ1, HeatPump.Status.ProhibitCoolingZ1, HeatPump.Status.ProhibitHeatingZ2, HeatPump.Status.ProhibitCoolingZ2 };
      std::copy(current_svc_state.begin(), current_svc_state.end(), dhw_svc_pre);
      if (HeatPump.Status.ProhibitDHW == 0) {  // To boost, must be at transition of On > Off, so if current Prohibit Status if off first Enter SCM with Prohibit On to create a transition for a short interval
        HeatPump.SetSvrControlMode(Payload.toInt(), Payload.toInt(), HeatPump.Status.ProhibitHeatingZ1, HeatPump.Status.ProhibitCoolingZ1, HeatPump.Status.ProhibitHeatingZ2, HeatPump.Status.ProhibitCoolingZ2);
      }
      HeatPump.Status.ProhibitDHW = 1 - Payload.toInt();                                                                                                                                                                     // Hot Water Prohibit is Inverse of request (For Status Indication Only)
      HeatPump.Status.SvrControlMode = 1;                                                                                                                                                                                    // Server Control Mode Enables for this mode (For Status Indication Only)
      HeatPump.SetSvrControlMode(Payload.toInt(), HeatPump.Status.ProhibitDHW, HeatPump.Status.ProhibitHeatingZ1, HeatPump.Status.ProhibitCoolingZ1, HeatPump.Status.ProhibitHeatingZ2, HeatPump.Status.ProhibitCoolingZ2);  // Perform write to FTC
    } else if (Payload.toInt() == 0) {                                                                                                                                                                                       // Turn OFF
      HeatPump.SetSvrControlMode(dhw_svc_pre[0], dhw_svc_pre[1], dhw_svc_pre[2], dhw_svc_pre[3], dhw_svc_pre[4], dhw_svc_pre[5]);                                                                                            // Restore Server Control Mode + Prohibits
      HeatPump.Status.SvrControlMode = dhw_svc_pre[0];                                                                                                                                                                       // Publish the status just written
      HeatPump.Status.ProhibitDHW = dhw_svc_pre[1];                                                                                                                                                                          // Publish the status just written
    }
    NormalHWBoostOperating = Payload.toInt();  // Hot Water Boost Operating is Active/Inactive
  } else if ((Topic == MQTTCommandSystemHolidayMode) || (Topic == MQTTCommand2SystemHolidayMode)) {
    MQTTWriteReceived("MQTT Set Holiday Mode", 16);
    HeatPump.SetHolidayMode(Payload.toInt());
    HeatPump.Status.HolidayModeActive = Payload.toInt();
  } else if ((Topic == MQTTCommandHotwaterSetpoint) || (Topic == MQTTCommand2HotwaterSetpoint)) {
    MQTTWriteReceived("MQTT Set HW Setpoint", 6);
    HeatPump.SetHotWaterSetpoint(Payload.toFloat());
    write_thermostats();
    HeatPump.Status.HotWaterSetpoint = Payload.toFloat();
  } else if ((Topic == MQTTCommandZone1HeatingMode) || (Topic == MQTTCommand2Zone1HeatingMode)) {
    MQTTWriteReceived("MQTT Set Heating Mode Zone 1", 4);
    if (Payload == String("Heating Temperature")) {
      HeatPump.SetHeatingControlMode(HEATING_CONTROL_MODE_ZONE_TEMP, SET_HEATING_CONTROL_MODE_Z1);
      HeatPump.Status.HeatingControlModeZ1 = HEATING_CONTROL_MODE_ZONE_TEMP;
      write_thermostats();
    } else if (Payload == String("Heating Flow")) {
      HeatPump.SetHeatingControlMode(HEATING_CONTROL_MODE_FLOW_TEMP, SET_HEATING_CONTROL_MODE_Z1);
      HeatPump.Status.HeatingControlModeZ1 = HEATING_CONTROL_MODE_FLOW_TEMP;
      HeatPump.SetFlowSetpoint(HeatPump.Status.Zone1FlowTemperatureSetpoint, HeatPump.Status.HeatingControlModeZ1, ZONE1);
      if (unitSettings.z1_active) { ModifyCompCurveState(1, false, 1, 0); }
    } else if (Payload == String("Heating Compensation")) {
      HeatPump.SetHeatingControlMode(HEATING_CONTROL_MODE_COMPENSATION, SET_HEATING_CONTROL_MODE_Z1);
      HeatPump.Status.HeatingControlModeZ1 = HEATING_CONTROL_MODE_COMPENSATION;
    } else if (Payload == String("Cooling Temperature")) {
      HeatPump.SetHeatingControlMode(HEATING_CONTROL_MODE_COOL_ZONE_TEMP, SET_HEATING_CONTROL_MODE_Z1);
      HeatPump.Status.HeatingControlModeZ1 = HEATING_CONTROL_MODE_COOL_ZONE_TEMP;
      write_thermostats();
    } else if (Payload == String("Cooling Flow")) {
      HeatPump.SetHeatingControlMode(HEATING_CONTROL_MODE_COOL_FLOW_TEMP, SET_HEATING_CONTROL_MODE_Z1);
      HeatPump.Status.HeatingControlModeZ1 = HEATING_CONTROL_MODE_COOL_FLOW_TEMP;
      if (unitSettings.z1_active) { ModifyCompCurveState(1, false, 1, 0); }
    } else if (Payload == String("Dry Up")) {
      HeatPump.SetHeatingControlMode(HEATING_CONTROL_MODE_DRY_UP, SET_HEATING_CONTROL_MODE_Z1);
      HeatPump.Status.HeatingControlModeZ1 = HEATING_CONTROL_MODE_DRY_UP;
    } else if (Payload == String("Cool Compensation")) {
      HeatPump.SetHeatingControlMode(HEATING_CONTROL_MODE_COOL_COMPENSATION, SET_HEATING_CONTROL_MODE_Z1);
      HeatPump.Status.HeatingControlModeZ1 = HEATING_CONTROL_MODE_COOL_COMPENSATION;
    }
  } else if ((Topic == MQTTCommandZone2HeatingMode) || (Topic == MQTTCommand2Zone2HeatingMode)) {
    MQTTWriteReceived("MQTT Set Heating Mode Zone 2", 4);
    if (Payload == String("Heating Temperature")) {
      HeatPump.SetHeatingControlMode(HEATING_CONTROL_MODE_ZONE_TEMP, SET_HEATING_CONTROL_MODE_Z2);
      HeatPump.Status.HeatingControlModeZ2 = HEATING_CONTROL_MODE_ZONE_TEMP;
    } else if (Payload == String("Heating Flow")) {
      HeatPump.SetHeatingControlMode(HEATING_CONTROL_MODE_FLOW_TEMP, SET_HEATING_CONTROL_MODE_Z2);
      HeatPump.Status.HeatingControlModeZ2 = HEATING_CONTROL_MODE_FLOW_TEMP;
      HeatPump.SetFlowSetpoint(HeatPump.Status.Zone2FlowTemperatureSetpoint, HeatPump.Status.HeatingControlModeZ2, ZONE2);
      if (unitSettings.z2_active) { ModifyCompCurveState(2, false, 1, 0); }
    } else if (Payload == String("Heating Compensation")) {
      HeatPump.SetHeatingControlMode(HEATING_CONTROL_MODE_COMPENSATION, SET_HEATING_CONTROL_MODE_Z2);
      HeatPump.Status.HeatingControlModeZ2 = HEATING_CONTROL_MODE_COMPENSATION;
    } else if (Payload == String("Cooling Temperature")) {
      HeatPump.SetHeatingControlMode(HEATING_CONTROL_MODE_COOL_ZONE_TEMP, SET_HEATING_CONTROL_MODE_Z2);
      HeatPump.Status.HeatingControlModeZ2 = HEATING_CONTROL_MODE_COOL_ZONE_TEMP;
    } else if (Payload == String("Cooling Flow")) {
      HeatPump.SetHeatingControlMode(HEATING_CONTROL_MODE_COOL_FLOW_TEMP, SET_HEATING_CONTROL_MODE_Z2);
      HeatPump.Status.HeatingControlModeZ2 = HEATING_CONTROL_MODE_COOL_FLOW_TEMP;
      if (unitSettings.z2_active) { ModifyCompCurveState(2, false, 1, 0); }
    } else if (Payload == String("Dry Up")) {
      HeatPump.SetHeatingControlMode(HEATING_CONTROL_MODE_DRY_UP, SET_HEATING_CONTROL_MODE_Z2);
      HeatPump.Status.HeatingControlModeZ2 = HEATING_CONTROL_MODE_DRY_UP;
    } else if (Payload == String("Cool Compensation")) {
      HeatPump.SetHeatingControlMode(HEATING_CONTROL_MODE_COOL_COMPENSATION, SET_HEATING_CONTROL_MODE_Z2);
      HeatPump.Status.HeatingControlModeZ2 = HEATING_CONTROL_MODE_COOL_COMPENSATION;
    }
  } else if ((Topic == MQTTCommandSystemSvrMode) || (Topic == MQTTCommand2SystemSvrMode)) {
    MQTTWriteReceived("MQTT Server Control Mode", 17);
    HeatPump.SetSvrControlMode(Payload.toInt(), HeatPump.Status.ProhibitDHW, HeatPump.Status.ProhibitHeatingZ1, HeatPump.Status.ProhibitCoolingZ1, HeatPump.Status.ProhibitHeatingZ2, HeatPump.Status.ProhibitCoolingZ2);
    HeatPump.Status.SvrControlMode = Payload.toInt();
  } else if ((Topic == MQTTCommandSystemPower) || (Topic == MQTTCommand2SystemPower)) {
    MQTTWriteReceived("MQTT Set System Power Mode", 15);
    if (Payload == String("On")) {
      HeatPump.SetSystemPowerMode(SYSTEM_POWER_MODE_ON);
      HeatPump.Status.SystemPowerMode = SYSTEM_POWER_MODE_ON;
    } else if (Payload == String("Standby")) {
      HeatPump.SetSystemPowerMode(SYSTEM_POWER_MODE_STANDBY);
      HeatPump.Status.SystemPowerMode = SYSTEM_POWER_MODE_STANDBY;
    }
    write_thermostats();
  } else if ((Topic == MQTTCommandSystemUnitSize) || (Topic == MQTTCommand2SystemUnitSize)) {
    MQTTWriteReceived("MQTT Set Unit Size", 15);
    unitSettings.UnitSize = Payload.toFloat();
    shouldSaveConfig = true;  // Write the data to JSON file so if device reboots it is saved
  } else if ((Topic == MQTTCommandSystemGlycol) || (Topic == MQTTCommand2SystemGlycol)) {
    MQTTWriteReceived("MQTT Set Glycol Strength", 15);
    if (Payload == String("0%")) {
      unitSettings.GlycolStrength = 4.18;
    } else if (Payload == String("10%")) {
      unitSettings.GlycolStrength = 4.12;
    } else if (Payload == String("15%")) {
      unitSettings.GlycolStrength = 4.10;
    } else if (Payload == String("20%")) {
      unitSettings.GlycolStrength = 4.07;
    } else if (Payload == String("25%")) {
      unitSettings.GlycolStrength = 3.98;
    } else if (Payload == String("30%")) {
      unitSettings.GlycolStrength = 3.9;
    }
    shouldSaveConfig = true;  // Write the data to JSON file so if device reboots it is saved
  } else if ((Topic == MQTTCommandSystemCompCurve) || (Topic == MQTTCommand2SystemCompCurve)) {
    MQTTWriteReceived("MQTT Set Comp Curve", 15);
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, Payload);
    if (error) {
      DEBUG_PRINT("1 Failed to read: ");
      DEBUG_PRINTLN(error.c_str());
      if (Payload == String("ERASE")) {
        DEBUG_PRINTLN("Erasing Comp Curve");
        unitSettings.CompCurve = "{}";
        shouldSaveConfig = true;
      }  // Method to erase the onboard document for recovery
    } else {

      // Method is to check if JSON key exists, then if not NULL then read it - this allows for some variables to be posted in JSON but not others depending on the request type

      // Base Curve (String)
      JsonVariant baseVariant = doc["base"];
      if (!baseVariant.isNull()) {                                                               // Check if the key exists AND if its value is not explicitly 'null'
        JsonDocument local_stored_doc;                                                           // Variable for the locally decoded JSON
        DeserializationError error = deserializeJson(local_stored_doc, unitSettings.CompCurve);  // Unpack the local stored JSON document
        if (error) {
          DEBUG_PRINT("2 Failed to read: ");
          DEBUG_PRINTLN(error.c_str());
        } else {
          local_stored_doc["base"] = baseVariant;  // Load the new Base into the correct area of the locally stored file
          local_stored_doc.shrinkToFit();
          serializeJson(local_stored_doc, unitSettings.CompCurve);  // Repack the JSON
          shouldSaveConfig = true;                                  // Write the data to onboard JSON file so if device reboots it is saved
        }
      }


      // Activation Of Mode per Zone (Bool)
      if (doc["zone1"]["active"].is<bool>()) {
        bool wc_z1_active = doc["zone1"]["active"];
        if (!unitSettings.z1_active && wc_z1_active) {                                                         // On transition from Inactive > Active
          if (HeatPump.Status.HeatCool == 0 && HeatPump.Status.HeatingControlModeZ1 != 1) {                    // Check if not already in Heating Mode Fixed Flow Mode
            HeatPump.SetHeatingControlMode(HEATING_CONTROL_MODE_FLOW_TEMP, SET_HEATING_CONTROL_MODE_Z1);       // Swap to Fixed Flow for Onboard WC to input the flow temperature
            HeatPump.Status.HeatingControlModeZ1 = HEATING_CONTROL_MODE_FLOW_TEMP;                             // Optimistic Write
          } else if (HeatPump.Status.HeatCool == 1 && HeatPump.Status.HeatingControlModeZ1 != 4) {             // Check if not already in Cooling Mode Fixed Flow Mode
            HeatPump.SetHeatingControlMode(HEATING_CONTROL_MODE_COOL_FLOW_TEMP, SET_HEATING_CONTROL_MODE_Z1);  // Swap to Fixed Flow for Onboard WC to input the flow temperature
            HeatPump.Status.HeatingControlModeZ1 = HEATING_CONTROL_MODE_COOL_FLOW_TEMP;                        // Optimistic Write
          }
        }
        ModifyCompCurveState(1, wc_z1_active, 1, 0);  // State Save
      }
      // Room Influence is Enabled/Disabled
      if (doc["zone1"]["room_influence_active"].is<bool>()) {
        unitSettings.z1_room_influence_active = doc["zone1"]["room_influence_active"];
      }
      if (doc["zone1"]["use_local_tsensor"].is<bool>()) {
        unitSettings.z1_use_local_sensor = doc["zone1"]["use_local_tsensor"];
      }

      if (doc["zone2"]["active"].is<bool>()) {
        bool wc_z2_active = doc["zone2"]["active"];
        if (!unitSettings.z2_active && wc_z2_active) {                                                         // On transition from Inactive > Active
          if (HeatPump.Status.HeatCool == 0 && HeatPump.Status.HeatingControlModeZ2 != 1) {                    // Check if not already in Fixed Flow Mode
            HeatPump.SetHeatingControlMode(HEATING_CONTROL_MODE_FLOW_TEMP, SET_HEATING_CONTROL_MODE_Z2);       // Swap to Fixed Flow for Onboard WC to input the flow temperature
            HeatPump.Status.HeatingControlModeZ2 = HEATING_CONTROL_MODE_FLOW_TEMP;                             // Optimistic Write
          } else if (HeatPump.Status.HeatCool == 1 && HeatPump.Status.HeatingControlModeZ2 != 4) {             // Check if not already in Cooling Mode Fixed Flow Mode
            HeatPump.SetHeatingControlMode(HEATING_CONTROL_MODE_COOL_FLOW_TEMP, SET_HEATING_CONTROL_MODE_Z2);  // Swap to Fixed Flow for Onboard WC to input the flow temperature
            HeatPump.Status.HeatingControlModeZ2 = HEATING_CONTROL_MODE_COOL_FLOW_TEMP;                        // Optimistic Write
          }
        }
        ModifyCompCurveState(2, wc_z2_active, 1, 0);  // State Save
      }
      // Room Influence is Enabled/Disabled
      if (doc["zone2"]["room_influence_active"].is<bool>()) {
        unitSettings.z2_room_influence_active = doc["zone2"]["room_influence_active"];
      }
      if (doc["zone2"]["use_local_tsensor"].is<bool>()) {
        unitSettings.z2_use_local_sensor = doc["zone2"]["use_local_tsensor"];
      }

      // Local or Remote Outdoor Temperature Measurement (Bool)
      if (doc["use_local_outdoor"].is<bool>()) {
        unitSettings.use_local_outdoor = doc["use_local_outdoor"];
        ModifyCompCurveState(1, unitSettings.use_local_outdoor, 5, 0);  // State Save
      }

      // Flow Overshooting (Short Cycle Protection)
      if (doc["max_flow_overshoot"].is<float>()) {
        unitSettings.max_flow_overshoot = doc["max_flow_overshoot"];
        ModifyCompCurveState(1, true, 6, unitSettings.max_flow_overshoot);
      }

      // Fixed Lockout Duration (Short Cycle Protection)
      if (doc["fixedlockoutduration"].is<float>()) {
        unitSettings.fixedlockoutduration = doc["fixedlockoutduration"];
        ModifyCompCurveState(1, true, 7, unitSettings.fixedlockoutduration);
      }

      // Adjustments Pre or Post WC Calculation (Float)
      if (doc["zone1"]["manual_offset"].is<float>()) {
        unitSettings.z1_manual_offset = doc["zone1"]["manual_offset"];
        ModifyCompCurveState(1, true, 2, unitSettings.z1_manual_offset);
      }  // Post Calcuation Zone1 Manual +/- Offset
      if (doc["zone1"]["temp_offset"].is<float>()) {
        unitSettings.z1_temp_offset = doc["zone1"]["temp_offset"];
        ModifyCompCurveState(1, true, 3, unitSettings.z1_temp_offset);
      }  // Post Calcuation Zone1 Temperature (e.g. Solar Gain) +/- Offset
      if (doc["zone1"]["wind_offset"].is<float>()) {
        unitSettings.z1_wind_offset = doc["zone1"]["wind_offset"];
        ModifyCompCurveState(1, true, 4, unitSettings.z1_wind_offset);
      }  // Post Calcuation Zone1 Wind Factor +/- Offset
      if (doc["zone1"]["room_setpoint"].is<float>()) {
        unitSettings.z1_room_setpoint = doc["zone1"]["room_setpoint"];
      }  // Room Influence Temperature Setpoint
      if (doc["zone1"]["room_temperature"].is<float>()) {
        unitSettings.z1_room_temperature = doc["zone1"]["room_temperature"];
      }  // Room Influence Temperature Sensor
      if (doc["zone2"]["manual_offset"].is<float>()) {
        unitSettings.z2_manual_offset = doc["zone2"]["manual_offset"];
        ModifyCompCurveState(2, true, 2, unitSettings.z2_manual_offset);
      }  // Post Calcuation Zone2 Manual +/- Offset
      if (doc["zone2"]["temp_offset"].is<float>()) {
        unitSettings.z2_temp_offset = doc["zone2"]["temp_offset"];
        ModifyCompCurveState(2, true, 3, unitSettings.z2_temp_offset);
      }  // Post Calcuation Zone2 Temperature (e.g. Solar Gain) +/- Offset
      if (doc["zone2"]["wind_offset"].is<float>()) {
        unitSettings.z2_wind_offset = doc["zone2"]["wind_offset"];
        ModifyCompCurveState(2, true, 4, unitSettings.z2_wind_offset);
      }  // Post Calcuation Zone2 Wind Factor +/- Offset
      if (doc["zone2"]["room_setpoint"].is<float>()) {
        unitSettings.z2_room_setpoint = doc["zone2"]["room_setpoint"];
      }  // Room Influence Temperature Setpoint
      if (doc["zone2"]["room_temperature"].is<float>()) {
        unitSettings.z2_room_temperature = doc["zone2"]["room_temperature"];
      }  // Room Influence Temperature Sensor


      if (doc["cloud_outdoor"].is<float>()) { unitSettings.cloud_outdoor = doc["cloud_outdoor"]; }  // Temperature Provided by a remote or cloud source when use_local_outdoor = False


      FlowFollowingActive = false;
      CalculateCompCurve();  // Recalculate after modification
    }
  } else if ((Topic == MQTTCommandSystemActvCtrl) || (Topic == MQTTCommand2SystemActvCtrl)) {
    MQTTWriteReceived("MQTT Set Active Control", 15);
    if (Payload.toInt() == 1) {
      unitSettings.shortcycleprotectionenabled = true;
    } else if (Payload.toInt() == 0) {
      unitSettings.shortcycleprotectionenabled = false;
      shortcycleprotectionexit = true;
    }
    shouldSaveConfig = true;  // Write the data to onboard JSON file so if device reboots it is saved
    ActiveControlReport();
  }
  // Air to Air Commands
  else if ((Topic == MQTTCommandAC) || (Topic == MQTTCommand2AC)) {
    MQTTWriteReceived("MQTT AC Command JSON", 6);
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, Payload);
    if (error) {
      DEBUG_PRINT("Failed to read file: ");
      DEBUG_PRINTLN(error.c_str());
    } else {
      // Air to Air (AC) Commands
      ACWriteInProgress = true;

      if (doc["systempower"].is<bool>()) {
        DEBUG_PRINTLN("SetPower");
        bool systempower = doc["systempower"];
        AC.SetSystemPowerMode(systempower);
        AC.Status.SystemPowerMode = systempower ? 0x01 : 0x00;  // Optimistic HA
        AC.Status.PendingPower = AC.Status.SystemPowerMode;
        AC.Status.PendingPowerUntil = millis() + AC_PENDING_HOLD_MS;
      }
      if (doc["SetMode"].is<const char*>()) {
        DEBUG_PRINTLN("SetMode");
        if (doc["SetMode"] == "off") {  // HA "off" mode = system power off; the unit's mode register is untouched
          AC.SetSystemPowerMode(false);
          AC.Status.SystemPowerMode = 0x00;  // Optimistic HA
          AC.Status.PendingPower = 0x00;
          AC.Status.PendingPowerUntil = millis() + AC_PENDING_HOLD_MS;
        } else {
          if (AC.Status.SystemPowerMode == 0x00) {  // Selecting a mode while off powers the unit on (HA climate semantic)
            AC.SetSystemPowerMode(true);
            AC.Status.SystemPowerMode = 0x01;  // Optimistic HA
            AC.Status.PendingPower = 0x01;
            AC.Status.PendingPowerUntil = millis() + AC_PENDING_HOLD_MS;
          }
          AC.SetMode(doc["SetMode"]);
          AC.Status.PendingMode = AC.MODE[AC.lookupByteMapIndex(AC.MODE_MAP, 5, doc["SetMode"])];
          AC.Status.Buffer04 = AC.Status.isee ? AC.Status.PendingMode + 0x08 : AC.Status.PendingMode;  // Optimistic HA (keep the i-See offset the report decode expects)
          AC.Status.PendingModeUntil = millis() + AC_PENDING_HOLD_MS;
        }
      }
      if (doc["SetFanSpeed"].is<const char*>()) {
        DEBUG_PRINTLN("SetFan");
        AC.SetFanSpeed(doc["SetFanSpeed"]);
        AC.Status.fan = AC.FAN[AC.lookupByteMapIndex(AC.FAN_MAP, 6, doc["SetFanSpeed"])];  // Optimistic HA
        AC.Status.PendingFan = AC.Status.fan;
        AC.Status.PendingFanUntil = millis() + AC_PENDING_HOLD_MS;
      }
      if (doc["SetVane"].is<const char*>()) {
        DEBUG_PRINTLN("SetVane");
        AC.SetVane(doc["SetVane"]);
        AC.Status.vane = AC.VANE[AC.lookupByteMapIndex(AC.VANE_MAP, 7, doc["SetVane"])];  // Optimistic HA
        AC.Status.PendingVane = AC.Status.vane;
        AC.Status.PendingVaneUntil = millis() + AC_PENDING_HOLD_MS;
      }
      if (doc["SetWideVane"].is<const char*>()) {
        DEBUG_PRINTLN("SetWideVane");
        AC.SetWideVane(doc["SetWideVane"]);
        AC.Status.wideVane = AC.WIDEVANE[AC.lookupByteMapIndex(AC.WIDEVANE_MAP, 7, doc["SetWideVane"])];  // Optimistic HA
        AC.Status.PendingWideVane = AC.Status.wideVane;
        AC.Status.PendingWideVaneUntil = millis() + AC_PENDING_HOLD_MS;
      }
      if (doc["SetTempSetpoint"].is<float>()) {
        DEBUG_PRINTLN("SetTempSetpoint");
        AC.SetTempSetpoint(doc["SetTempSetpoint"], AC.Status.tempMode);

        // Optimistic HA
        if (!AC.Status.tempMode) {
          AC.Status.Temperature = AC.lookupByteMapIndex(AC.TEMP_MAP, 16, doc["SetTempSetpoint"]);
        } else {
          AC.Status.Temperature = doc["SetTempSetpoint"].as<float>();
        }
        AC.Status.PendingTemperature = AC.Status.Temperature;
        AC.Status.PendingTempUntil = millis() + AC_PENDING_HOLD_MS;
      }
      if (doc["SetRemoteTemp"].is<float>()) {
        DEBUG_PRINTLN("SetRemoteTemp");
        AC.SetRemoteTemp(doc["SetRemoteTemp"]);
        unitSettings.ac_remote_room_temp = doc["SetRemoteTemp"];  // Optimistic HA
      }
      if (doc["RemoteTempOn"].is<bool>()) {
        DEBUG_PRINTLN("RemoteTempOn");
        unitSettings.RemoteTempOn = doc["RemoteTempOn"];
        if (!unitSettings.RemoteTempOn) {
          AC.SetRemoteTemp(0);  // 0 = Off
        } else {
          AC.SetRemoteTemp(18);  // 18 = Inputting starting figure of 18C
        }
        shouldSaveConfig = true;
      }

      PublishAllACReports();
    }
  }
}


void Zone1Report(void) {
  JsonDocument doc;
  char Buffer[512];

  doc[F("Temperature")] = HeatPump.Status.Zone1Temperature;
  doc[F("Setpoint")] = HeatPump.Status.Zone1TemperatureSetpoint;
  doc[F("HeatingControlMode")] = HeatingControlModeString[HeatPump.Status.HeatingControlModeZ1];
  doc[F("FSP")] = round2(HeatPump.Status.Zone1FlowTemperatureSetpoint);
  if ((!HeatPump.Status.Has2Zone) && (HeatPump.Status.SystemOperationMode == 2 || HeatPump.Status.SystemOperationMode == 3 || HeatPump.Status.SystemOperationMode == 7)) {
    doc[F("TwoZone_Z1Working")] = 1;
  } else {
    doc[F("TwoZone_Z1Working")] = HeatPump.Status.TwoZone_Z1Working;
  }
  doc[F("ProhibitHeating")] = HeatPump.Status.ProhibitHeatingZ1;
  doc[F("ProhibitCooling")] = HeatPump.Status.ProhibitCoolingZ1;
  doc[F("FlowTemp")] = HeatPump.Status.Zone1FlowTemperature;
  doc[F("ReturnTemp")] = HeatPump.Status.Zone1ReturnTemperature;
  doc[F("InputType")] = ThermostatString[HeatPump.Status.ThermostatZ1];
  doc[F("HB_ID")] = Heart_Value;

  serializeJson(doc, Buffer);

  MQTTClient1.publish(MQTT_STATUS_ZONE1.c_str(), Buffer, false);
  MQTTClient2.publish(MQTT_2_STATUS_ZONE1.c_str(), Buffer, false);
}

void Zone2Report(void) {
  JsonDocument doc;
  char Buffer[512];

  doc[F("Temperature")] = HeatPump.Status.Zone2Temperature;
  doc[F("Setpoint")] = HeatPump.Status.Zone2TemperatureSetpoint;
  doc[F("HeatingControlMode")] = HeatingControlModeString[HeatPump.Status.HeatingControlModeZ2];
  doc[F("FSP")] = round2(HeatPump.Status.Zone2FlowTemperatureSetpoint);
  doc[F("TwoZone_Z2Working")] = HeatPump.Status.TwoZone_Z2Working;
  doc[F("ProhibitHeating")] = HeatPump.Status.ProhibitHeatingZ2;
  doc[F("ProhibitCooling")] = HeatPump.Status.ProhibitCoolingZ2;
  doc[F("FlowTemp")] = HeatPump.Status.Zone2FlowTemperature;
  doc[F("ReturnTemp")] = HeatPump.Status.Zone2ReturnTemperature;
  doc[F("InputType")] = ThermostatString[HeatPump.Status.ThermostatZ2];
  doc[F("HB_ID")] = Heart_Value;

  serializeJson(doc, Buffer);
  MQTTClient1.publish(MQTT_STATUS_ZONE2.c_str(), Buffer, false);
  MQTTClient2.publish(MQTT_2_STATUS_ZONE2.c_str(), Buffer, false);
}

void HotWaterReport(void) {
  JsonDocument doc;
  char Buffer[1024];

  doc[F("Temperature")] = HeatPump.Status.HotWaterTemperature;
  doc[F("TempTHW5A")] = HeatPump.Status.HotWaterTemperatureTHW5A;
  doc[F("Setpoint")] = HeatPump.Status.HotWaterSetpoint;
  doc[F("HotWaterBoostActive")] = HeatPump.Status.HotWaterBoostActive;
  doc[F("HotWaterEcoBoostActive")] = NormalHWBoostOperating;
  doc[F("ProhibitDHW")] = HeatPump.Status.ProhibitDHW;
  doc[F("DHWActive")] = HeatPump.Status.DHWActive;
  doc[F("HotWaterControlMode")] = HotWaterControlModeString[HeatPump.Status.HotWaterControlMode];
  doc[F("LegionellaSetpoint")] = HeatPump.Status.LegionellaSetpoint;
  doc[F("HotWaterMaxTDrop")] = HeatPump.Status.HotWaterMaximumTempDrop;
  doc[F("HotWaterPhase")] = DHWPhaseString[HeatPump.Status.DHWHeatSourcePhase];
  doc[F("HB_ID")] = Heart_Value;

  serializeJson(doc, Buffer);
  MQTTClient1.publish(MQTT_STATUS_HOTWATER.c_str(), Buffer, false);
  MQTTClient2.publish(MQTT_2_STATUS_HOTWATER.c_str(), Buffer, false);
}

void SystemReport(void) {
  JsonDocument doc;
  char Buffer[2048];

  double EstInputPower = 0;
  double OutputPower = 0;
  float HeatOutputPower = 0;
  float HeatingOutputPower = 0;
  float DHWOutputPower = 0;
  float CoolOutputPower = 0;
  float EstCoolingInputPower = 0;
  float EstHeatingInputPower = 0;
  float EstDHWInputPower = 0;
  float Min_Input_Power = 0;
  float Max_Input_Power = 0;
  float Outside_Air_Temp = 0;

  bool DHW_Mode = false;
  bool Non_HP_Mode = false;
  float UnitSizeFactor, Instant_CoP;



  // Unit Size Factoring
  if (unitSettings.UnitSize == 4.0) {
    UnitSizeFactor = 0.4;
  } else if (unitSettings.UnitSize == 5.0) {
    UnitSizeFactor = 0.6;
  } else if (unitSettings.UnitSize == 7.5 || unitSettings.UnitSize == 6.0) {
    UnitSizeFactor = 0.95;
  } else if (unitSettings.UnitSize == 8.5 || unitSettings.UnitSize == 11.2) {
    UnitSizeFactor = 1.1;
  } else if (unitSettings.UnitSize == 8.0) {
    UnitSizeFactor = 1.3;
  } else if (unitSettings.UnitSize == 10.0) {
    UnitSizeFactor = 1.5;
  } else if ((unitSettings.UnitSize == 12.0) || (unitSettings.UnitSize == 14.0)) {
    UnitSizeFactor = 1.7;
  } else if (unitSettings.UnitSize == 23.0) {
    UnitSizeFactor = 2.0;
  }

  if (HeatPump.Status.InputPower < 2) {  // To account for FTC's onboard estimation and limit the input power range
    Max_Input_Power = 2;
  } else {
    Min_Input_Power = HeatPump.Status.InputPower;
    Max_Input_Power = HeatPump.Status.InputPower + 1;
  }

  if (HeatPump.Status.ThreeWayValve == 1 || HeatPump.Status.SystemOperationMode == 1 || HeatPump.Status.SystemOperationMode == 6) { DHW_Mode = true; }

  float x = 0.0f;
  if (HeatPump.Status.CompressorFrequency > 0) {
    float baseRunOverhead = 0.15f * UnitSizeFactor;   // Start with a fixed physical overhead (e.g., 150W scaled by unit size)
    if (HeatPump.Status.HeatCool == 0 || DHW_Mode) {  // Dynamic heating calculation
      float dynamicFactor = (((((float)HeatPump.Status.CompressorFrequency * 2) * ((float)HeatPump.Status.HeaterOutputFlowTemperature * 0.8)) / 1000) / 2) * UnitSizeFactor;
      x = baseRunOverhead + dynamicFactor;
    } else if (HeatPump.Status.HeatCool == 1) {  // Dynamic cooling calculation
      float tempDifference = 20.25f - (float)HeatPump.Status.HeaterOutputFlowTemperature;
      if (tempDifference < 1.0f) {
        tempDifference = 1.0f;
      }
      float coolingTempFactor = tempDifference * 4.2f;
      float dynamicFactor = (((((float)HeatPump.Status.CompressorFrequency * 2) * coolingTempFactor) / 1000) / 2) * UnitSizeFactor;
      x = baseRunOverhead + dynamicFactor;
    }
  } else {
    x = 0.015f * UnitSizeFactor;  // Compressor is off. (Note: Standby heater/controller draw is usually ~15W-40W, which you can optionally set here)
  }

  EstInputPower = ((x - Min_Input_Power) * (Max_Input_Power - Min_Input_Power) / (Max_Input_Power - Min_Input_Power) + Min_Input_Power);  // Constrain Input Power to FTC Onboard Reading range
  OutputPower = (((float)HeatPump.Status.PrimaryFlowRate / 60) * (float)HeatPump.Status.HeaterDeltaT * unitSettings.GlycolStrength);      // Approx Heat Capacity of Fluid in Use (Carnot Power then 8% removed for losses)


  if (HeatPump.Status.ImmersionActive == 1 || HeatPump.Status.Booster1Active == 1 || HeatPump.Status.Booster2Active == 1) {  // Account for Immersion or Booster Instead of HP
    Non_HP_Mode = true;
    if (EstInputPower == 0) { EstInputPower = HeatPump.Status.InputPower; }  // Uses Booster/Immersion Size in MRC
    if (OutputPower == 0) { OutputPower = HeatOutputPower = HeatPump.Status.OutputPower; }
  }

  if (HeatPump.Status.SystemOperationMode > 0 || HeatPump.Status.CompressorFrequency > 0) {  // Pump Operating
    if (OutputPower <= 0) {                                                                  // Cooling or Defrosting Mode
      if (HeatPump.Status.Defrost != 0) {                                                    // If Defrosting Mode
        EstHeatingInputPower = EstInputPower;                                                // Input Power attributed to Heating & Cooling
        HeatingOutputPower = HeatOutputPower = OutputPower;                                  // Heating is Negative (Extracting heat to defrost)
        CoolOutputPower = fabsf(OutputPower);                                                // Defrosting is also cooling
      }                                                                                      //
      else if (DHW_Mode) {                                                                   // Not defrosting, hot water mode
        EstDHWInputPower = EstInputPower;                                                    //
        DHWOutputPower = HeatOutputPower = OutputPower;                                      // DHW Output Power is Negative or 0 (could be due to immersion)
      } else {                                                                               // Heating/Cooling Mode
        if (HeatPump.Status.HeatCool == 0) {                                                 // Heating Operating Mode (Should not be triggered)
          EstHeatingInputPower = EstInputPower;                                              // Input Power attribution to Heating
          HeatingOutputPower = HeatOutputPower = OutputPower;                                //
        } else if (HeatPump.Status.HeatCool == 1) {                                          // Cooling Operation Mode
          EstCoolingInputPower = EstInputPower;                                              // Input Power attribution to Cooling
          HeatingOutputPower = HeatOutputPower = 0;                                          // Heating is 0
          CoolOutputPower = fabsf(OutputPower);                                              // Make Cooling Positive Output Power
        }                                                                                    //
      }                                                                                      //
    } else if (OutputPower > 0) {                                                            // Heating by HP
      if (DHW_Mode) {                                                                        // DHW Operation Mode via HP
        EstDHWInputPower = EstInputPower;                                                    //
        DHWOutputPower = HeatOutputPower = OutputPower;                                      //
      } else {                                                                               // Heating Operation Mode via HP
        EstHeatingInputPower = EstInputPower;                                                //
        HeatingOutputPower = HeatOutputPower = OutputPower;                                  //
      }                                                                                      // Heating Modes
    } else if (OutputPower == 0 && Non_HP_Mode) {                                            // Boosters or Immersion
      if (DHW_Mode) {                                                                        // DHW Operation Mode
        EstDHWInputPower = EstInputPower;                                                    //
        DHWOutputPower = OutputPower = HeatOutputPower;                                      //
      } else {                                                                               // Heating Modes
        EstHeatingInputPower = EstInputPower;                                                //
        HeatingOutputPower = OutputPower = HeatOutputPower;                                  //
      }                                                                                      //
    }                                                                                        //
  }


  // Instant CoP measurement from computed estimates
  if (fabsf(OutputPower) > 0 && EstInputPower > 0) {
    Instant_CoP = fabsf(OutputPower) / EstInputPower;
  } else {
    Instant_CoP = 0;
  }

  if (!inDefrostWindow) {
    getOATRunningAverage(HeatPump.Status.OutsideTemperature);
  }
  if (OAT_isFull) {
    Outside_Air_Temp = OAT_average;
  } else {
    Outside_Air_Temp = HeatPump.Status.OutsideTemperature;
  }

  doc[F("HeaterFlow")] = HeatPump.Status.HeaterOutputFlowTemperature;
  doc[F("HeaterReturn")] = HeatPump.Status.HeaterReturnFlowTemperature;
  doc[F("FlowReturnDeltaT")] = HeatPump.Status.HeaterDeltaT;
  doc[F("OutsideTemp")] = round1(Outside_Air_Temp);
  doc[F("Defrost")] = DefrostModeString[HeatPump.Status.Defrost];
  doc[F("InputPower")] = HeatPump.Status.InputPower;
  doc[F("HeaterPower")] = HeatPump.Status.OutputPower;
  doc[F("EstInputPower")] = round2(EstInputPower);
  doc[F("EstCoolingInputPower")] = round2(EstCoolingInputPower);
  doc[F("EstHeatingInputPower")] = round2(EstHeatingInputPower);
  doc[F("EstDHWInputPower")] = round2(EstDHWInputPower);
  doc[F("EstHeatOutputPower")] = round2(HeatOutputPower);
  doc[F("EstHeatingOutputPower")] = round2(HeatingOutputPower);
  doc[F("EstDHWOutputPower")] = round2(DHWOutputPower);
  doc[F("EstCoolOutputPower")] = round2(CoolOutputPower);
  doc[F("Instant_CoP")] = round2(Instant_CoP);
  doc[F("Compressor")] = HeatPump.Status.CompressorFrequency;
  doc[F("SystemPower")] = SystemPowerModeString[HeatPump.Status.SystemPowerMode];
  if (HeatPump.Status.Defrost == 2) {
    doc[F("SystemOperationMode")] = "Defrosting";
  } else {
    doc[F("SystemOperationMode")] = SystemOperationModeString[HeatPump.Status.SystemOperationMode];
  }
  doc[F("HolidayMode")] = HeatPump.Status.HolidayModeActive;
  doc[F("FlowRate")] = HeatPump.Status.PrimaryFlowRate;
  doc[F("PumpPWM")] = HeatPump.Status.PrimaryWaterPumpSpeed;
  doc[F("PumpPwr")] = HeatPump.Status.PumpPower;
  doc[F("RunHours")] = HeatPump.Status.RunHours;
  doc[F("HB_ID")] = Heart_Value;


  // Calculate Consumption Energy Onboard (Left Integral)
  if (EstHeatingInputPower != 0) {
    updateEnergyMeter(round2(EstHeatingInputPower), 0);
  } else if (EstCoolingInputPower != 0) {
    updateEnergyMeter(round2(EstCoolingInputPower), 1);
  } else if (EstDHWInputPower != 0) {
    updateEnergyMeter(round2(EstDHWInputPower), 2);
  }
  if (HeatingOutputPower != 0) {
    updateEnergyMeter(round2(HeatingOutputPower), 3);
  } else if (CoolOutputPower != 0) {
    updateEnergyMeter(round2(CoolOutputPower), 4);
  } else if (DHWOutputPower != 0) {
    updateEnergyMeter(round2(DHWOutputPower), 5);
  }


  serializeJson(doc, Buffer);
  MQTTClient1.publish(MQTT_STATUS_SYSTEM.c_str(), Buffer, false);
  MQTTClient2.publish(MQTT_2_STATUS_SYSTEM.c_str(), Buffer, false);
}

void AdvancedReport(void) {
  JsonDocument doc;
  char Buffer[2048];

  doc[F("FlowTMax")] = HeatPump.Status.FlowTempMax;
  doc[F("FlowTMin")] = HeatPump.Status.FlowTempMin;
  doc[F("BoilerFlow")] = HeatPump.Status.ExternalBoilerFlowTemperature;
  doc[F("BoilerReturn")] = HeatPump.Status.ExternalBoilerReturnTemperature;
  doc[F("MixingTemp")] = HeatPump.Status.MixingTemperature;
  doc[F("MixingStep")] = HeatPump.Status.MixingStep;
  doc[F("Immersion")] = OFF_ON_String[HeatPump.Status.ImmersionActive];
  doc[F("Booster")] = OFF_ON_String[HeatPump.Status.Booster1Active];
  doc[F("Booster2")] = OFF_ON_String[HeatPump.Status.Booster2Active];
  doc[F("Booster2Plus")] = OFF_ON_String[HeatPump.Status.Booster2PlusActive];
  doc[F("ThreeWayValve")] = HeatPump.Status.ThreeWayValve;
  doc[F("PrimaryWaterPump")] = OFF_ON_String[HeatPump.Status.PrimaryWaterPump];
  doc[F("RefrigeTemp")] = HeatPump.Status.RefrigeTemp;
  doc[F("CondensingTemp")] = HeatPump.Status.CondensingTemp;
  doc[F("HeatingActive")] = HeatingRunningBinary[HeatPump.Status.SystemOperationMode];
  doc[F("CoolingActive")] = CoolingRunningBinary[HeatPump.Status.SystemOperationMode];
  doc[F("BrineInletTemp")] = HeatPump.Status.TH32;
  doc[F("BrineOutletTemp")] = HeatPump.Status.TH34;
  doc[F("HB_ID")] = Heart_Value;

  serializeJson(doc, Buffer);
  MQTTClient1.publish(MQTT_STATUS_ADVANCED.c_str(), Buffer, false);
  MQTTClient2.publish(MQTT_2_STATUS_ADVANCED.c_str(), Buffer, false);
}



void EnergyReport(void) {
  JsonDocument doc;
  char Buffer[2048];
  time_t now;
  struct tm timeinfo;
  float heat_cop, cool_cop, dhw_cop, ctotal, dtotal, total_cop, ob_ctotal, ob_dtotal, ob_total_cop;

  // Energy Substitution and Data Checking
  bool DeliveredYesterday = false;
  bool ConsumedYesterday = false;
  // Check if we are in the 5-minute window right after midnight (12:00 AM - 12:05 AM)
  time(&now);
  localtime_r(&now, &timeinfo);


  bool inMidnightWindow = (timeinfo.tm_hour == 0 && timeinfo.tm_min < 5) || (timeinfo.tm_hour == 23 && timeinfo.tm_min > 58);

  if (!inMidnightWindow) {
    // Use exact 24h offset (86400 seconds) for yesterday's date check
    struct tm yesterday = timeinfo;
    yesterday.tm_mday -= 1;
    mktime(&yesterday);  // Auto-normalizes day/month/year boundaries

    if (yesterday.tm_mday == HeatPump.Status.DeliveredDateTimeStamp.tm_mday && yesterday.tm_mon == HeatPump.Status.DeliveredDateTimeStamp.tm_mon && yesterday.tm_year == HeatPump.Status.DeliveredDateTimeStamp.tm_year) {
      DeliveredYesterday = true;
    }

    if (yesterday.tm_mday == HeatPump.Status.ConsumedDateTimeStamp.tm_mday && yesterday.tm_mon == HeatPump.Status.ConsumedDateTimeStamp.tm_mon && yesterday.tm_year == HeatPump.Status.ConsumedDateTimeStamp.tm_year) {
      ConsumedYesterday = true;
    }

    // Only zero out data outside the 5-minute rollover period
    if (!DeliveredYesterday) { HeatPump.Status.DeliveredHeatingEnergy = HeatPump.Status.DeliveredCoolingEnergy = HeatPump.Status.DeliveredHotWaterEnergy = 0; }
    if (!ConsumedYesterday) { HeatPump.Status.ConsumedHeatingEnergy = HeatPump.Status.ConsumedCoolingEnergy = HeatPump.Status.ConsumedHotWaterEnergy = 0; }
  } else {   // Skip publishing during the volatile midnight rollover window
    return;  // Don't output misleading zeroed-out telemetry to MQTT
  }

  // Re-write the onboard data into the memory locations
  if (cumulativeEnergyYesterday[0] > 0 && HeatPump.Status.ConsumedHeatingEnergy == 0) { HeatPump.Status.ConsumedHeatingEnergy = cumulativeEnergyYesterday[0]; }
  if (cumulativeEnergyYesterday[1] > 0 && HeatPump.Status.ConsumedCoolingEnergy == 0) { HeatPump.Status.ConsumedCoolingEnergy = cumulativeEnergyYesterday[1]; }
  if (cumulativeEnergyYesterday[2] > 0 && HeatPump.Status.ConsumedHotWaterEnergy == 0) { HeatPump.Status.ConsumedHotWaterEnergy = cumulativeEnergyYesterday[2]; }
  if (cumulativeEnergyYesterday[3] > 0 && HeatPump.Status.DeliveredHeatingEnergy == 0) { HeatPump.Status.DeliveredHeatingEnergy = cumulativeEnergyYesterday[3]; }
  if (cumulativeEnergyYesterday[4] > 0 && HeatPump.Status.DeliveredCoolingEnergy == 0) { HeatPump.Status.DeliveredCoolingEnergy = cumulativeEnergyYesterday[4]; }
  if (cumulativeEnergyYesterday[5] > 0 && HeatPump.Status.DeliveredHotWaterEnergy == 0) { HeatPump.Status.DeliveredHotWaterEnergy = cumulativeEnergyYesterday[5]; }


  // A check for errors before calculating CoP
  if ((HeatPump.Status.DeliveredHeatingEnergy == 0) && (HeatPump.Status.ConsumedHeatingEnergy > 0)) {
    HeatPump.Status.ConsumedHeatingEnergy = 0;  // Re-write
  }
  if ((HeatPump.Status.DeliveredCoolingEnergy == 0) && (HeatPump.Status.ConsumedCoolingEnergy > 0)) {
    HeatPump.Status.ConsumedCoolingEnergy = 0;  // Re-write
  }
  if ((HeatPump.Status.DeliveredHotWaterEnergy == 0) && (HeatPump.Status.ConsumedHotWaterEnergy > 0)) {
    HeatPump.Status.ConsumedHotWaterEnergy = 0;  // Re-write
  }

  // CoP Calculations to avoid divide by 0 occuring
  if (HeatPump.Status.ConsumedHeatingEnergy > 0) {
    heat_cop = HeatPump.Status.DeliveredHeatingEnergy / HeatPump.Status.ConsumedHeatingEnergy;
  } else {
    heat_cop = 0;
  }
  if (HeatPump.Status.ConsumedCoolingEnergy > 0) {
    cool_cop = HeatPump.Status.DeliveredCoolingEnergy / HeatPump.Status.ConsumedCoolingEnergy;
  } else {
    cool_cop = 0;
  }
  if (HeatPump.Status.ConsumedHotWaterEnergy > 0) {
    dhw_cop = (HeatPump.Status.DeliveredHotWaterEnergy / HeatPump.Status.ConsumedHotWaterEnergy);
  } else {
    dhw_cop = 0;
  }

  // CoP Totals
  ctotal = (HeatPump.Status.ConsumedHeatingEnergy + HeatPump.Status.ConsumedCoolingEnergy + HeatPump.Status.ConsumedHotWaterEnergy);
  dtotal = (HeatPump.Status.DeliveredHeatingEnergy + HeatPump.Status.DeliveredCoolingEnergy + HeatPump.Status.DeliveredHotWaterEnergy);
  ob_ctotal = cumulativeEnergyToday[0] + cumulativeEnergyToday[1] + cumulativeEnergyToday[2];
  ob_dtotal = cumulativeEnergyToday[3] + cumulativeEnergyToday[4] + cumulativeEnergyToday[5];

  if (ctotal != 0) {
    total_cop = dtotal / ctotal;
  } else {
    total_cop = 0;
  }

  if (ob_ctotal != 0) {
    ob_total_cop = ob_dtotal / ob_ctotal;
  } else {
    ob_total_cop = 0;
  }




  // Write into the JSON with 2dp rounding
  doc[F("CHEAT")] = round2(HeatPump.Status.ConsumedHeatingEnergy);
  doc[F("CCOOL")] = round2(HeatPump.Status.ConsumedCoolingEnergy);
  doc[F("CDHW")] = round2(HeatPump.Status.ConsumedHotWaterEnergy);
  doc[F("DHEAT")] = round2(HeatPump.Status.DeliveredHeatingEnergy);
  doc[F("DCOOL")] = round2(HeatPump.Status.DeliveredCoolingEnergy);
  doc[F("DDHW")] = round2(HeatPump.Status.DeliveredHotWaterEnergy);
  doc[F("CTOTAL")] = round2(ctotal);
  doc[F("DTOTAL")] = round2(dtotal);
  doc[F("HEAT_CoP")] = round2(heat_cop);
  doc[F("COOL_CoP")] = round2(cool_cop);
  doc[F("DHW_CoP")] = round2(dhw_cop);
  doc[F("TOTAL_CoP")] = round2(total_cop);
  doc[F("ConsumedTotalInc")] = HeatPump.Status.EnergyConsumedIncreasing;

  doc[F("OB_CHEAT_YDay")] = round2(cumulativeEnergyYesterday[0]);
  doc[F("OB_CCOOL_YDay")] = round2(cumulativeEnergyYesterday[1]);
  doc[F("OB_CDHW_YDay")] = round2(cumulativeEnergyYesterday[2]);
  doc[F("OB_DHEAT_YDay")] = round2(cumulativeEnergyYesterday[3]);
  doc[F("OB_DCOOL_YDay")] = round2(cumulativeEnergyYesterday[4]);
  doc[F("OB_DDHW_YDay")] = round2(cumulativeEnergyYesterday[5]);
  doc[F("OB_CHEAT_TDay")] = round2(cumulativeEnergyToday[0]);
  doc[F("OB_CCOOL_TDay")] = round2(cumulativeEnergyToday[1]);
  doc[F("OB_CDHW_TDay")] = round2(cumulativeEnergyToday[2]);
  doc[F("OB_DHEAT_TDay")] = round2(cumulativeEnergyToday[3]);
  doc[F("OB_DCOOL_TDay")] = round2(cumulativeEnergyToday[4]);
  doc[F("OB_DDHW_TDay")] = round2(cumulativeEnergyToday[5]);
  doc[F("OB_CTOTAL_TDay")] = round2(ob_ctotal);
  doc[F("OB_DTOTAL_TDay")] = round2(ob_dtotal);
  doc[F("OB_TOTAL_CoP_TDay")] = round2(ob_total_cop);


  doc[F("HB_ID")] = Heart_Value;
  serializeJson(doc, Buffer);
  MQTTClient1.publish(MQTT_STATUS_ENERGY.c_str(), Buffer, false);
  MQTTClient2.publish(MQTT_2_STATUS_ENERGY.c_str(), Buffer, false);
}


void AdvancedTwoReport(void) {
  JsonDocument doc;
  char Buffer[1024];

  int ErrorCode = ((String(HeatPump.Status.ErrCode1, HEX)).toInt() * 100) + (String(HeatPump.Status.ErrCode2, HEX)).toInt();

  if (ErrorCode == 8000 || ErrorCode == 0) {
    doc[F("ErrCode")] = String("Normal");
  } else {
    doc[F("ErrCode")] = ErrorCode;
  }

  doc[F("SvrControlMode")] = HeatPump.Status.SvrControlMode;
  doc[F("WaterPump2")] = OFF_ON_String[HeatPump.Status.WaterPump2];
  doc[F("WaterPump4")] = OFF_ON_String[HeatPump.Status.WaterPump4];
  if (!HeatPump.Status.Simple2Zone) {
    doc[F("WaterPump3")] = OFF_ON_String[HeatPump.Status.WaterPump3a];
  } else {
    doc[F("WaterPump3")] = OFF_ON_String[HeatPump.Status.WaterPump3b];
  }
  doc[F("WaterPump13")] = OFF_ON_String[HeatPump.Status.WaterPump13];
  doc[F("ThreeWayValve2")] = HeatPump.Status.ThreeWayValve2;
  doc[F("RefrigeFltCode")] = RefrigeFltCodeString[HeatPump.Status.RefrigeFltCode];


  String FltCodeString = String(FltCodeLetterOne[HeatPump.Status.FltCode1]) + String(FltCodeLetterTwo[HeatPump.Status.FltCode2]);
  if (FltCodeString == "A0") {
    doc[F("FltCode")] = String("Normal");
  } else {
    doc[F("FltCode")] = String(FltCodeString);
  }

  doc[F("Z1TstatDemand")] = OFF_ON_String[HeatPump.Status.Zone1ThermostatDemand];
  doc[F("Z2TstatDemand")] = OFF_ON_String[HeatPump.Status.Zone2ThermostatDemand];
  doc[F("OTstatDemand")] = OFF_ON_String[HeatPump.Status.OutdoorThermostatDemand];
  doc[F("OpMode")] = HPControlModeString[HeatPump.Status.HeatCool];

  if (SvcRequested == HeatPump.Status.LastServiceCodeNumber) {
    SvcReply = HeatPump.Status.ServiceCodeReply;
  }

  doc[F("LastSvc")] = SvcRequested;
  doc[F("LastSvcReply")] = SvcReply;
  doc[F("HB_ID")] = Heart_Value;

  serializeJson(doc, Buffer);
  MQTTClient1.publish(MQTT_STATUS_ADVANCED_TWO.c_str(), Buffer, false);
  MQTTClient2.publish(MQTT_2_STATUS_ADVANCED_TWO.c_str(), Buffer, false);
}

void StatusReport(void) {
  JsonDocument doc;
  char Buffer[2048];
  char TmBuffer[32];
  bool changemade = false;
  String DeviceType = "None";

  doc[F("SSID")] = WiFi.SSID();
  doc[F("RSSI")] = WiFi.RSSI();
#if defined(ESP32) && !defined(ARDUINO_WT32_ETH01)
  doc[F("RoamCount")] = RoamCount;
#endif
  doc[F("Uptime")] = (millis() / 1000 / 60);  // Subject to rollover
#ifdef ARDUINO_WT32_ETH01
  doc[F("IP")] = ETH.localIP().toString();
#else
  doc[F("IP")] = WiFi.localIP().toString();
#endif
  doc[F("Firmware")] = FirmwareVersion + Language;
#ifdef ESP32  // Define the M5Stack LED
  doc[F("CPUTemp")] = round2(temperatureRead());
#endif
#ifdef ESP8266  // Define the M5Stack LED
  doc[F("CPUTemp")] = "None";
#endif
  doc[F("CPULoopTime")] = CPULoopSpeed;
  doc[F("FTCLoopTime")] = FTCLoopSpeed;
  doc[F("FTCReplyTime")] = HeatPump.Lastmsbetweenmsg();
  doc[F("FTCVersion")] = FTCString[HeatPump.Status.FTCVersion];
  doc[F("FTCSoftwareVersion")] = HeatPump.Status.FTCSoftware;
  if (HeatPump.SVCPopulated) { doc[F("OutdoorSoftwareVersion")] = HeatPump.Status.OutdoorFirmware; }
  if (MELCloud_Adapter_Connected) {
    doc[F("MELCloud_Status")] = MELCloudStatusString[MELCloud.Status.MEL_Online];
  } else {
    doc[F("MELCloud_Status")] = "Adapter Disconnected";
  }
  doc[F("MELCloud_Write_Blocking")] = unitSettings.BlockWriteFromMELCloud;
  strftime(TmBuffer, sizeof(TmBuffer), "%FT%T", &HeatPump.Status.DateTimeStamp);
  doc[F("FTCTime")] = TmBuffer;

  // Device Type Connected
  if (HeatPump.PrevConnected) {
    DeviceType = "A2W";
  } else if (AC.PrevConnected) {
    DeviceType = "A2A";
  }
  doc[F("DeviceType")] = DeviceType;


  // Verify Outdoor Unit Size set by selector against outdoor unit Service Code Read and adjust if required
  if (HeatPump.Status.OutdoorUnitCapacity > 0) {
    if (HeatPump.Status.OutdoorUnitCapacity == 9 && (unitSettings.UnitSize < 4.0 || unitSettings.UnitSize > 5.0)) {  // 3.5kW
      unitSettings.UnitSize = 4.0;
      changemade = true;
    } else if (HeatPump.Status.OutdoorUnitCapacity == 10 && (unitSettings.UnitSize < 4.0 || unitSettings.UnitSize > 5.0)) {  // 5kW
      unitSettings.UnitSize = 5.0;
      changemade = true;
    } else if (HeatPump.Status.OutdoorUnitCapacity == 11 && unitSettings.UnitSize != 6.0) {  // 6kW
      unitSettings.UnitSize = 6.0;
      changemade = true;
    } else if (HeatPump.Status.OutdoorUnitCapacity == 14 && (unitSettings.UnitSize < 7.5 || unitSettings.UnitSize > 8.5)) {  // 8.5kW
      unitSettings.UnitSize = 8.5;
      changemade = true;
    } else if (HeatPump.Status.OutdoorUnitCapacity == 20 && (unitSettings.UnitSize < 10 || unitSettings.UnitSize > 11.2)) {  // 10kW
      unitSettings.UnitSize = 10.0;
      changemade = true;
    } else if (HeatPump.Status.OutdoorUnitCapacity == 25 && (unitSettings.UnitSize < 12 || unitSettings.UnitSize > 14)) {  // 12.5kW or 14kW (14kW monobloc shows as 25, 14kW split shows 14)
      unitSettings.UnitSize = 12.0;
      changemade = true;
    } else if (HeatPump.Status.OutdoorUnitCapacity == 28 && (unitSettings.UnitSize < 12 || unitSettings.UnitSize > 14)) {  // 14kW mono
      unitSettings.UnitSize = 14.0;
      changemade = true;
    } else if (HeatPump.Status.OutdoorUnitCapacity >= 40 && unitSettings.UnitSize != 23.0) {  // 17, 20 or 25kW  ( 23kW Split )
      unitSettings.UnitSize = 23.0;
      changemade = true;
    }
    if (changemade) { shouldSaveConfig = true; }
  }
  doc[F("UnitSize")] = String(unitSettings.UnitSize, 1);



  if (round2(unitSettings.GlycolStrength) == 4.18) {
    doc[F("Glycol")] = "0%";
  } else if (round2(unitSettings.GlycolStrength) == 4.12) {
    doc[F("Glycol")] = "10%";
  } else if (round2(unitSettings.GlycolStrength) == 4.10) {
    doc[F("Glycol")] = "15%";
  } else if (round2(unitSettings.GlycolStrength) == 4.07) {
    doc[F("Glycol")] = "20%";
  } else if (round2(unitSettings.GlycolStrength) == 3.98) {
    doc[F("Glycol")] = "25%";
  } else if (round2(unitSettings.GlycolStrength) == 3.9) {
    doc[F("Glycol")] = "30%";
  }
  doc[F("HB_ID")] = Heart_Value;

  serializeJson(doc, Buffer);
  MQTTClient1.publish(MQTT_STATUS_WIFISTATUS.c_str(), Buffer, false);
  MQTTClient2.publish(MQTT_2_STATUS_WIFISTATUS.c_str(), Buffer, false);
  MQTTClient1.publish(MQTT_LWT.c_str(), "online", true);
  MQTTClient2.publish(MQTT_2_LWT.c_str(), "online", true);
}

void UpdateReport(void) {
  JsonDocument doc;
  char Buffer[512];

  doc[F("installed_version")] = FirmwareVersion;
  doc[F("latest_version")] = LatestFirmwareVersion;
  if (update_in_progress) {
    doc[F("in_progress")] = true;
  } else {
    doc[F("in_progress")] = false;
  }
  doc[F("release_summary")] = update_summary;

  serializeJson(doc, Buffer);
  MQTTClient1.publish(MQTT_STATUS_WIFISTATUS_UPDATE.c_str(), Buffer, false);
  MQTTClient2.publish(MQTT_2_STATUS_WIFISTATUS_UPDATE.c_str(), Buffer, false);
}

void ConfigurationReport(void) {
  JsonDocument doc;
  char Buffer[2048];

  doc[F("DipSw1")] = decimalToBinary(HeatPump.Status.DipSwitch1);
  doc[F("DipSw2")] = decimalToBinary(HeatPump.Status.DipSwitch2);
  doc[F("DipSw3")] = decimalToBinary(HeatPump.Status.DipSwitch3);
  doc[F("DipSw4")] = decimalToBinary(HeatPump.Status.DipSwitch4);
  doc[F("DipSw5")] = decimalToBinary(HeatPump.Status.DipSwitch5);
  doc[F("DipSw6")] = decimalToBinary(HeatPump.Status.DipSwitch6);
  doc[F("DipSw7")] = decimalToBinary(HeatPump.Status.DipSwitch7);
  doc[F("HasCooling")] = HeatPump.Status.HasCooling;
  doc[F("Has2Zone")] = HeatPump.Status.Has2Zone;
  doc[F("HasSimple2Zone")] = HeatPump.Status.Simple2Zone;
  doc[F("RefrigerantType")] = HeatPump.Status.RefrigerantType;
  doc[F("ExtUnitSensors")] = HeatPump.Status.OutdoorExtendedSensors;
  doc[F("HasR290DualComp")] = HeatPump.Status.HasR290DualComp;
  // Publish only when available
  if (HeatPump.SVCPopulated || HeatPump.Status.CompOpTimes != 0) { doc[F("CompOpTimes")] = HeatPump.Status.CompOpTimes; }
  if (HeatPump.SVCPopulated || HeatPump.Status.LiquidTemp != 0) { doc[F("LiquidTemp")] = HeatPump.Status.LiquidTemp; }
  if (HeatPump.SVCPopulated || HeatPump.Status.TH4Discharge != 0) { doc[F("TH4Discharge")] = HeatPump.Status.TH4Discharge; }
  if (HeatPump.SVCPopulated || HeatPump.Status.Superheat != 0) { doc[F("Superheat")] = HeatPump.Status.Superheat; }
  if (HeatPump.SVCPopulated || HeatPump.Status.Subcool != 0) { doc[F("Subcool")] = HeatPump.Status.Subcool; }
  if (HeatPump.SVCPopulated || HeatPump.Status.TH8HeatSink != 0) { doc[F("TH8HeatSink")] = HeatPump.Status.TH8HeatSink; }
  if (HeatPump.SVCPopulated || HeatPump.Status.TH6Pipe != 0) { doc[F("TH6Pipe")] = HeatPump.Status.TH6Pipe; }
  if (HeatPump.SVCPopulated || HeatPump.Status.TH32Pipe != 0) { doc[F("TH32Pipe")] = HeatPump.Status.TH32Pipe; }
  if (HeatPump.SVCPopulated || HeatPump.Status.Fan1RPM != 0) { doc[F("Fan1RPM")] = HeatPump.Status.Fan1RPM; }
  if (HeatPump.SVCPopulated || HeatPump.Status.Fan2RPM != 0) { doc[F("Fan2RPM")] = HeatPump.Status.Fan2RPM; }
  if (HeatPump.SVCPopulated || HeatPump.Status.LEVA != 0) { doc[F("LEVA")] = HeatPump.Status.LEVA; }
  if (HeatPump.SVCPopulated || HeatPump.Status.LEVB != 0) { doc[F("LEVB")] = HeatPump.Status.LEVB; }
  if (HeatPump.SVCPopulated || HeatPump.Status.HasR290DualComp) { doc[F("LEVC")] = HeatPump.Status.LEVC; }  // Only Applies to multi-compressor units e.g. R290
  if (HeatPump.SVCPopulated || HeatPump.Status.TH33 != 0) { doc[F("TH33")] = HeatPump.Status.TH33; }

  doc[F("HB_ID")] = Heart_Value;

  serializeJson(doc, Buffer);
  MQTTClient1.publish(MQTT_STATUS_CONFIGURATION.c_str(), Buffer, false);
  MQTTClient2.publish(MQTT_2_STATUS_CONFIGURATION.c_str(), Buffer, false);
}

void CompCurveReport(void) {
  JsonDocument storeddoc;
  deserializeJson(storeddoc, unitSettings.CompCurve);  // Extract Saved to Flash Settings
  char Buffer[2048];

  // Add to saved settings with live
  storeddoc[F("zone1")]["active"] = unitSettings.z1_active;
  storeddoc[F("zone1")]["room_influence_active"] = unitSettings.z1_room_influence_active;
  storeddoc[F("zone1")]["use_local_tsensor"] = unitSettings.z1_use_local_sensor;
  storeddoc[F("zone1")]["room_setpoint"] = unitSettings.z1_room_setpoint;
  storeddoc[F("zone1")]["room_temperature"] = unitSettings.z1_room_temperature;
  storeddoc[F("zone1")]["manual_offset"] = unitSettings.z1_manual_offset;
  storeddoc[F("zone1")]["temp_offset"] = unitSettings.z1_temp_offset;
  storeddoc[F("zone1")]["wind_offset"] = unitSettings.z1_wind_offset;
  storeddoc[F("zone1")]["calculated_FSP"] = Z1_CurveFSP;
  storeddoc[F("zone2")]["active"] = unitSettings.z2_active;
  storeddoc[F("zone2")]["room_influence_active"] = unitSettings.z2_room_influence_active;
  storeddoc[F("zone2")]["use_local_tsensor"] = unitSettings.z2_use_local_sensor;
  storeddoc[F("zone2")]["room_setpoint"] = unitSettings.z2_room_setpoint;
  storeddoc[F("zone2")]["room_temperature"] = unitSettings.z2_room_temperature;
  storeddoc[F("zone2")]["manual_offset"] = unitSettings.z2_manual_offset;
  storeddoc[F("zone2")]["temp_offset"] = unitSettings.z2_temp_offset;
  storeddoc[F("zone2")]["wind_offset"] = unitSettings.z2_wind_offset;
  storeddoc[F("zone2")]["calculated_FSP"] = Z2_CurveFSP;
  storeddoc[F("use_local_outdoor")] = unitSettings.use_local_outdoor;
  storeddoc[F("cloud_outdoor")] = unitSettings.cloud_outdoor;
  storeddoc[F("max_flow_overshoot")] = unitSettings.max_flow_overshoot;

  storeddoc[F("HB_ID")] = Heart_Value;

  serializeJson(storeddoc, Buffer);
  MQTTClient1.publish(MQTT_STATUS_CURVE.c_str(), Buffer, false);
  MQTTClient2.publish(MQTT_2_STATUS_CURVE.c_str(), Buffer, false);
}

void ActiveControlReport(void) {
  JsonDocument doc;
  char Buffer[1024];
  String CycleProtectionStatus = "";

  doc[F("ShortCycleProtectionEnabled")] = unitSettings.shortcycleprotectionenabled ? 1 : 0;

  if (FlowFollowingActive || Flow_Inc_Count > 0) { CycleProtectionStatus = "Anti-Stop Flow Temperature Following Active (" + String(Flow_Inc_Count * 0.5) + "C)"; }
  if (DHWFlowFollowingActive) { CycleProtectionStatus = "DHW Flow Temperature Following Active"; }
  if (ShortCycleProtectionActive) { CycleProtectionStatus = "Short Cycle Lockout Active"; }
  if ((!FlowFollowingActive && Flow_Inc_Count == 0) && !DHWFlowFollowingActive && !ShortCycleProtectionActive) { CycleProtectionStatus = "Inactive"; }

  doc[F("ShortCycleProtectionActive")] = CycleProtectionStatus;
  doc[F("ShortCycleReason")] = ShortCycleReason[ShortCycleCauseNumber];

  if (unitSettings.fixedlockoutduration == 0) {
    doc[F("FixedShortCycleLockoutDuration")] = String("Disabled (Automatic)");
  } else {
    doc[F("FixedShortCycleLockoutDuration")] = unitSettings.fixedlockoutduration;
  }
  doc[F("ShortCycleLockoutDuration")] = lockoutdurationMillis;
  doc[F("LastCompressorPeriods")][0] = CompressorPeriodDurations[0];
  doc[F("LastCompressorPeriods")][1] = CompressorPeriodDurations[1];
  doc[F("FlowTemp_Target")] = FlowTemp_Target;
  doc[F("FlowIncrementCounter")] = Flow_Inc_Count;
  doc[F("HB_ID")] = Heart_Value;

  serializeJson(doc, Buffer);
  MQTTClient1.publish(MQTT_STATUS_ACTV_CTRL.c_str(), Buffer, false);
  MQTTClient2.publish(MQTT_2_STATUS_ACTV_CTRL.c_str(), Buffer, false);
}


void ACReport(void) {
  JsonDocument doc;
  char Buffer[2048];



  int ErrorCode = ((String(AC.Status.ErrCode1, HEX)).toInt() * 100) + (String(AC.Status.ErrCode2, HEX)).toInt();

  if (ErrorCode == 8000 || ErrorCode == 0) {
    doc[F("ErrCode")] = String("Normal");
  } else {
    doc[F("ErrCode")] = ErrorCode;
  }


  String FltCodeString = String(FltCodeLetterOne[HeatPump.Status.FltCode1]) + String(FltCodeLetterTwo[HeatPump.Status.FltCode2]);
  if (FltCodeString == "A0") {
    doc[F("FltCode")] = String("Normal");
  } else {
    doc[F("FltCode")] = String(FltCodeString);
  }

  doc[F("InPwr")] = AC.Status.InputPower;
  doc[F("LPwr")] = AC.Status.LifePower;

  //doc[F("InPwr1")] = AC.Status.InputPower1;
  //doc[F("InPwr2")] = AC.Status.InputPower2;
  doc[F("LPwr1")] = AC.Status.LifePower1;
  doc[F("LPwr2")] = AC.Status.LifePower2;

  doc[F("Status")] = AC.Status.Status;
  doc[F("FAct")] = AC.Status.FanActual;
  doc[F("Auto")] = AC.Status.AutoMode;


  if (AC.Status.RmtempMode) {
    doc[F("RoomTemp")] = AC.lookupByteMapValue(AC.ROOM_TEMP_MAP, AC.ROOM_TEMP, 32, AC.Status.RoomTemp);
  } else {
    doc[F("RoomTemp")] = AC.Status.RoomTempFloat;
  }

  if (!AC.Status.tempMode) {
    doc[F("SetpointTemp")] = AC.lookupByteMapValue(AC.TEMP_MAP, AC.TEMP, 16, AC.Status.Temperature);
  } else {
    doc[F("SetpointTemp")] = AC.Status.Temperature;
  }

  doc[F("RemoteTempOn")] = unitSettings.RemoteTempOn;
  doc[F("RemoteTemp")] = unitSettings.ac_remote_room_temp;

  doc[F("RPhbt")] = AC.Status.remoteProhibit;
  doc[F("OAT")] = AC.Status.OAT;
  doc[F("Rtme")] = AC.Status.Runtime;

  doc[F("fltr")] = (AC.Status.Status == 0x01);
  doc[F("dfrst")] = (AC.Status.Status == 0x02);
  doc[F("prht")] = (AC.Status.Status == 0x04);
  doc[F("sby")] = (AC.Status.Status == 0x08);


  doc[F("Fan")] = AC.lookupByteMapValue(AC.FAN_HA_MAP, AC.FAN, 6, AC.Status.fan);
  doc[F("Vane")] = AC.lookupByteMapValue(AC.VANE_MAP, AC.VANE, 7, AC.Status.vane);
  doc[F("wideVane")] = AC.lookupByteMapValue(AC.WIDEVANE_MAP, AC.WIDEVANE, 7, AC.Status.wideVane & 0x0F);
  doc[F("iSee")] = AC.Status.isee;
  if (AC.Status.SystemPowerMode == 0x00) {  // Powered off - present as the HA climate "off" mode
    doc[F("mode")] = "off";
    doc[F("action")] = "off";
  } else {
    doc[F("mode")] = AC.lookupByteMapValue(AC.MODE_MAP, AC.MODE, 5, AC.Status.isee ? (AC.Status.Buffer04 - 0x08) : AC.Status.Buffer04);
    if (!AC.Status.Operating) {
      doc[F("action")] = "idle";
    } else {
      doc[F("action")] = AC.lookupByteMapValue(AC.MODE_HA_MAP, AC.MODE, 5, AC.Status.isee ? (AC.Status.Buffer04 - 0x08) : AC.Status.Buffer04);
    }
  }
  doc[F("compressorFreq")] = AC.Status.CompressorFrequency;

  doc[F("power")] = AC.lookupByteMapValue(AC.POWER_MAP, AC.POWER, 2, AC.Status.SystemPowerMode);
  doc[F("timermode")] = AC.lookupByteMapValue(AC.TIMER_MODE_MAP, AC.TIMER_MODE, 4, AC.Status.Timermode);
  doc[F("onMinsSet")] = AC.Status.onMinutesSet;
  doc[F("onMinsRemain")] = AC.Status.onMinutesRemaining;
  doc[F("offMinsSet")] = AC.Status.offMinutesSet;
  doc[F("offMinsRemain")] = AC.Status.offMinutesRemaining;
  doc[F("HasHozVane")] = AC.Status.SupportsHozVane;
  doc[F("HB_ID")] = Heart_Value;

  serializeJson(doc, Buffer);
  MQTTClient1.publish(MQTT_STATUS_AC.c_str(), Buffer, false);
  MQTTClient2.publish(MQTT_2_STATUS_AC.c_str(), Buffer, false);
}

void PublishAllReports(void) {
  // Increment the Heatbeat ID Counter
  ++Heart_Value;
  if (Heart_Value > Heartbeat_Range) {
    Heart_Value = 1;
  }

  Zone1Report();
  Zone2Report();
  HotWaterReport();
  SystemReport();
  ConfigurationReport();
  AdvancedReport();
  AdvancedTwoReport();
  EnergyReport();
  StatusReport();
  CompCurveReport();
  ActiveControlReport();
  UpdateReport();

  FlashGreenLED();
  DEBUG_PRINTLN(F("MQTT Published!"));
}


void PublishAllACReports(void) {
  // Increment the Heatbeat ID Counter
  ++Heart_Value;
  if (Heart_Value > Heartbeat_Range) {
    Heart_Value = 1;
  }

  ACReport();
  StatusReport();
  FlashGreenLED();
  DEBUG_PRINTLN(F("MQTT Published!"));
}

void FastPublish(void) {
  if (HeatPump.Status.FTCVersion != 0) {
    SystemReport();
    HotWaterReport();
    AdvancedReport();
    AdvancedTwoReport();
  }  // Don't fast publish until at least whole data set gathering is complete
  else {
    UpdateReport();
  }
}


void FlashGreenLED(void) {
#ifdef ARDUINO_M5STACK_ATOMS3  // Define the M5Stack LED
  myLED.setPixel(0, L_GREEN, 1);
  myLED.brightness(255, 1);
#endif
#ifdef ESP8266                        // Define the Witty ESP8266 Ports
  digitalWrite(Green_RGB_LED, HIGH);  // Flash the Green LED full brightness
#endif
  delay(10);                       // Hold for 10ms then WiFi brightness will return it to 25%
#ifdef ESP8266                     // Define the Witty ESP8266 Ports
  analogWrite(Green_RGB_LED, 30);  // Green LED on, 25% brightness
#endif
#ifdef ARDUINO_M5STACK_ATOMS3  // Define the M5Stack LED
  myLED.brightness(LED_BRIGHT, 1);
#endif
}

void setupTelnet() {
  TelnetServer.onConnect(onTelnetConnect);
  TelnetServer.onConnectionAttempt(onTelnetConnectionAttempt);
  TelnetServer.onReconnect(onTelnetReconnect);
  TelnetServer.onDisconnect(onTelnetDisconnect);
}

void startTelnet() {
  DEBUG_PRINT(F("Telnet: "));
#ifdef ARDUINO_WT32_ETH01
  if (TelnetServer.begin(23, false)) {
#else
  if (TelnetServer.begin()) {
#endif
    DEBUG_PRINTLN(F("Telnet Running"));
  } else {
    DEBUG_PRINTLN(F("Telnet Error"));
  }
}

void stopTelnet() {
  //DEBUG_PRINTLN(F("Stopping Telnet"));
  TelnetServer.stop();
}

void onTelnetConnect(String ip) {
  //DEBUG_PRINT(F("Telnet: "));
  //DEBUG_PRINT(ip);
  //DEBUG_PRINTLN(F(" connected"));
  TelnetServer.println("\nWelcome " + TelnetServer.getIP());
  TelnetServer.println(F("(Use ^] + q  to disconnect.)"));
}

void onTelnetDisconnect(String ip) {
  //DEBUG_PRINT(F("Telnet: "));
  //DEBUG_PRINT(ip);
  //DEBUG_PRINTLN(F(" disconnected"));
}

void onTelnetReconnect(String ip) {
  //DEBUG_PRINT(F("Telnet: "));
  //DEBUG_PRINT(ip);
  //DEBUG_PRINTLN(F(" reconnected"));
}

void onTelnetConnectionAttempt(String ip) {
  //DEBUG_PRINT(F("Telnet: "));
  //DEBUG_PRINT(ip);
  //DEBUG_PRINTLN(F(" tried to connected"));
}

float roundToOneDecimal(float value) {
  return ((round(value * 10.0)) / 10.0);
}

double round0(double value) {
  return (int)(value);
}
double round1(double value) {
  return (int)(value * 10 + 0.5) / 10.0;
}
double round2(double value) {
  return (int)(value * 100 + 0.5) / 100.0;
}

String decimalToBinary(int decimal) {
  String binary = "";

  for (int i = 0; i < 8; i++) {  // 8 bits for a byte
    binary += (decimal >> i) & 1 ? '1' : '0';
  }

  return binary;
}

void write_thermostats() {
  if (HeatPump.Status.Zone1TemperatureSetpoint > 0 && HeatPump.Status.Zone1Temperature > 0) { HeatPump.SetZoneTempSetpoint(HeatPump.Status.Zone1TemperatureSetpoint, HeatPump.Status.HeatingControlModeZ1, ZONE1); }
  if (HeatPump.Status.Has2Zone && HeatPump.Status.Zone2TemperatureSetpoint > 0 && HeatPump.Status.Zone2Temperature > 0) { HeatPump.SetZoneTempSetpoint(HeatPump.Status.Zone2TemperatureSetpoint, HeatPump.Status.HeatingControlModeZ2, ZONE2); }
}

void dhw_flow_follower() {
  if (HeatPump.Status.DHWActive == 1 && HeatPump.Status.HeatingControlModeZ1 == 1 && unitSettings.shortcycleprotectionenabled && (unitSettings.z1_active || unitSettings.z2_active)) {
    HeatPump.SetFlowSetpoint(HeatPump.Status.HeaterOutputFlowTemperature, HEATING_CONTROL_MODE_FLOW_TEMP, ZONE1);  // In Hot Water mode, keep FSP following Actual
    write_thermostats();
    DHWFlowFollowingActive = true;
  } else {
    DHWFlowFollowingActive = false;
  }
}


void CalculateCompCurve(void) {
  DEBUG_PRINTLN("Performing Compensation Curve Calculation");
  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, unitSettings.CompCurve);
  if (error) {
    DEBUG_PRINT("Failed to read: ");
    DEBUG_PRINTLN(error.c_str());
  } else {
    // Read the Active Status First
    unitSettings.z1_active = doc["zone1"]["active"];  // Transfer JSON to Struct Bool
    unitSettings.z2_active = doc["zone2"]["active"];
    //if (!unitSettings.z1_active && !unitSettings.z2_active) { return; }  // Only calculates (saves time, if mode enabled)
    //else{
    {
      // Continue to unpack the JSON document into unitSettings for the other saved parameters from the save file
      unitSettings.z1_manual_offset = doc["zone1"]["manual_offset"];
      unitSettings.z1_wind_offset = doc["zone1"]["wind_offset"];
      unitSettings.z1_temp_offset = doc["zone1"]["temp_offset"];
      unitSettings.z2_manual_offset = doc["zone2"]["manual_offset"];
      unitSettings.z2_wind_offset = doc["zone2"]["wind_offset"];
      unitSettings.z2_temp_offset = doc["zone2"]["temp_offset"];
      unitSettings.use_local_outdoor = doc["use_local_outdoor"];
      unitSettings.max_flow_overshoot = doc["max_flow_overshoot"];
      unitSettings.fixedlockoutduration = doc["fixedlockoutduration"];


      float OutsideAirTemperature = 0;

      if (!unitSettings.use_local_outdoor && (MQTTClient1.connected() || MQTTClient2.connected())) {  // Determine Outdoor Temperature Input
        OutsideAirTemperature = unitSettings.cloud_outdoor;
      } else {
        if (inDefrostWindow) {  // To allow sensor to stabilise after influence from the defrost
          DEBUG_PRINTLN("Skipping due to Defrost...");
          return;  // If currently defrosting or less than 6 minutes post-defrost skip re-calculation
        }
        if (OAT_isFull) {
          OutsideAirTemperature = OAT_average;
        } else {
          OutsideAirTemperature = HeatPump.Status.OutsideTemperature;  // Set the OAT as the local heat pump figure
        }
      }

      int z1_points = doc["base"]["zone1"]["curve"].size() - 1;                            // How many points are there specified on the curve
      for (int i = 0; i <= z1_points; i++) {                                               // Iterate through the points
        float tmp_o_1 = doc["base"]["zone1"]["curve"][i]["outside"];                       // Outside Temperature for this point
        if ((i == 0) && (OutsideAirTemperature <= tmp_o_1)) {                              // On the first point, this determines the Maximum Flow Temp
          Z1_CurveFSP = doc["base"]["zone1"]["curve"][i]["flow"];                          // Set to Max Flow Temp
        } else if ((i == z1_points) && (OutsideAirTemperature >= tmp_o_1)) {               // The last point determines the Minimum Flow Temp
          Z1_CurveFSP = doc["base"]["zone1"]["curve"][i]["flow"];                          // Set to Min Flow Temp
        } else {                                                                           // Intermediate Flow Points are calculated
          float tmp_o_2 = doc["base"]["zone1"]["curve"][i + 1]["outside"];                 // Outside Temperature of the next point (warmer)
          if ((OutsideAirTemperature >= tmp_o_1) && (OutsideAirTemperature <= tmp_o_2)) {  // Validate the current outside temp value is in the correct range between points
            float y1 = doc["base"]["zone1"]["curve"][i + 1]["flow"];                       // Calculate the slope using the formula: m = (y2 - y1) / (x2 - x1)
            float y2 = doc["base"]["zone1"]["curve"][i]["flow"];                           //
            float z1_delta_y = y2 - y1;                                                    // y2-y1
            float z1_delta_x = tmp_o_1 - tmp_o_2;                                          // x2-x1
            float z1_m = 0;                                                                //
            if (z1_delta_x != 0) { z1_m = z1_delta_y / z1_delta_x; }                       // Prevent Div by 0          m = y2-y1 / x2-x1
            float z1_c = y2 - (z1_m * tmp_o_1);                                            // c = y-mx at point
            Z1_CurveFSP = (z1_m * OutsideAirTemperature) + z1_c;                           // y = mx+c
          }
        }
      }

      int z2_points = doc["base"]["zone2"]["curve"].size() - 1;  // How many points are there specified on the curve
      for (int i = 0; i <= z2_points; i++) {
        float tmp_o_1 = doc["base"]["zone2"]["curve"][i]["outside"];
        if ((i == 0) && (OutsideAirTemperature <= tmp_o_1)) {  // Max Flow Temp
          Z2_CurveFSP = doc["base"]["zone2"]["curve"][i]["flow"];
        } else if ((i == z2_points) && (OutsideAirTemperature >= tmp_o_1)) {  // Min Flow Temp
          Z2_CurveFSP = doc["base"]["zone2"]["curve"][i]["flow"];
        } else {
          float tmp_o_2 = doc["base"]["zone2"]["curve"][i + 1]["outside"];
          if ((OutsideAirTemperature >= tmp_o_1) && (OutsideAirTemperature <= tmp_o_2)) {
            float y1 = doc["base"]["zone2"]["curve"][i + 1]["flow"];  // Calculate the slope using the formula: m = (y2 - y1) / (x2 - x1)
            float y2 = doc["base"]["zone2"]["curve"][i]["flow"];
            float z2_delta_y = y2 - y1;
            float z2_delta_x = tmp_o_1 - tmp_o_2;
            float z2_m = 0;                                           //
            if (z2_delta_x != 0) { z2_m = z2_delta_y / z2_delta_x; }  // Prevent Div by 0          m = y2-y1 / x2-x1
            float z2_c = y2 - (z2_m * tmp_o_1);                       // c = y-mx
            Z2_CurveFSP = (z2_m * OutsideAirTemperature) + z2_c;      // y = mx+c
          }
        }
      }
    }

    // Apply Room Influence
    float Z1_Room_Offset = 0;
    float Z2_Room_Offset = 0;

    if (unitSettings.z1_room_influence_active) {
      if (unitSettings.z1_use_local_sensor) {
        unitSettings.z1_room_temperature = HeatPump.Status.Zone1Temperature;
        unitSettings.z1_room_setpoint = HeatPump.Status.Zone1TemperatureSetpoint;
      }
      Z1_Room_Offset = calculateRoomInfluence(unitSettings.z1_room_temperature, unitSettings.z1_room_setpoint, 1.5);
    }
    if (unitSettings.z2_room_influence_active && unitSettings.z2_active && HeatPump.Status.Has2Zone && !HeatPump.Status.Simple2Zone) {
      if (unitSettings.z2_use_local_sensor) {
        unitSettings.z2_room_temperature = HeatPump.Status.Zone2Temperature;
        unitSettings.z2_room_setpoint = HeatPump.Status.Zone2TemperatureSetpoint;
      }
      Z2_Room_Offset = calculateRoomInfluence(unitSettings.z2_room_temperature, unitSettings.z2_room_setpoint, 1.5);
    }

    // Apply Post Calculation Offsets to Calculated Curve Flow Setpoint
    Z1_CurveFSP = roundToOneDecimal(Z1_CurveFSP + Z1_Room_Offset + unitSettings.z1_wind_offset + unitSettings.z1_temp_offset + unitSettings.z1_manual_offset);
    Z2_CurveFSP = roundToOneDecimal(Z2_CurveFSP + Z2_Room_Offset + unitSettings.z2_wind_offset + unitSettings.z2_temp_offset + unitSettings.z2_manual_offset);

    // Apply Clamping based on FTC Settings For Min/Max Flow Temperature
    if (Z1_CurveFSP > HeatPump.Status.FlowTempMax) { Z1_CurveFSP = HeatPump.Status.FlowTempMax; }  // Protect UFH from high temp
    //if (Z1_CurveFSP < HeatPump.Status.FlowTempMin) { Z1_CurveFSP = HeatPump.Status.FlowTempMin; }   // Removed due to Cooling

    // Write the Flow Setpoints to Heat Pump
    if (unitSettings.z1_active && Flow_Inc_Count == 0 && HeatPump.Status.DHWActive != 1 && Z1_CurveFSP != HeatPump.Status.Zone1FlowTemperatureSetpoint) {
      HeatPump.SetFlowSetpoint(Z1_CurveFSP, HeatPump.Status.HeatingControlModeZ1, ZONE1);
      write_thermostats();
      HeatPump.Status.Zone1FlowTemperatureSetpoint = Z1_CurveFSP;
    }
    if (unitSettings.z2_active && HeatPump.Status.Has2Zone && !HeatPump.Status.Simple2Zone && Z2_CurveFSP != HeatPump.Status.Zone2FlowTemperatureSetpoint) {  // User must have Complex 2 zone to set different flow temp in different zones
      HeatPump.SetFlowSetpoint(Z2_CurveFSP, HeatPump.Status.HeatingControlModeZ2, ZONE2);
      write_thermostats();
      HeatPump.Status.Zone2FlowTemperatureSetpoint = Z2_CurveFSP;
    }
    if (HeatPump.PrevConnected) { CompCurveReport(); }  // Publish only for A2W
  }
}

float calculateRoomInfluence(float actual, float setpoint, float gain) {
  float error = setpoint - actual;
  return error * gain;
}

void ModifyCompCurveState(int Zone, bool Active, int ModType, float Value) {
  // Mod Types: 1 = Activate, 2 = manual_offset, 3 = temp_offset, 4 = wind_offset, 5 = use_local_outdoor, 6 = max_flow_overshoot, 7 = fixed lockout duration
  JsonDocument local_stored_doc;                                                           // Variable for the locally decoded JSON
  DeserializationError error = deserializeJson(local_stored_doc, unitSettings.CompCurve);  // Unpack the local stored JSON document
  if (error) {
    DEBUG_PRINT("Failed to read: ");
    DEBUG_PRINTLN(error.c_str());
  } else {
    String target_zone;
    if (Zone == 1) {
      target_zone = "zone1";
    } else if (Zone == 2) {
      target_zone = "zone2";
    }

    if (ModType == 1) {
      local_stored_doc[target_zone]["active"] = Active;
    } else if (ModType == 2) {
      local_stored_doc[target_zone]["manual_offset"] = Value;
    } else if (ModType == 3) {
      local_stored_doc[target_zone]["temp_offset"] = Value;
    } else if (ModType == 4) {
      local_stored_doc[target_zone]["wind_offset"] = Value;
    } else if (ModType == 5) {
      local_stored_doc["use_local_outdoor"] = Active;
    } else if (ModType == 6) {
      local_stored_doc["max_flow_overshoot"] = Value;
    } else if (ModType == 7) {
      local_stored_doc["fixedlockoutduration"] = Value;
    }
  }
  local_stored_doc.shrinkToFit();
  serializeJson(local_stored_doc, unitSettings.CompCurve);  // Repack the JSON
  shouldSaveConfig = true;                                  // Write the data to onboard JSON file so if device reboots it is saved
}

void syncCurrentTime() {
  // Update the ESP clock from the FTC
  time_t epochTime = mktime(&HeatPump.Status.DateTimeStamp);  // Convert to epoch

  if (epochTime != (time_t)(-1)) {
    struct timeval tv;
    tv.tv_sec = epochTime;
    tv.tv_usec = 0;
    if (settimeofday(&tv, nullptr) == 0) {
      DEBUG_PRINTLN("Time set successfully from FTC");
    } else {
      DEBUG_PRINTLN("Error setting time from FTC");
    }
  } else {
    DEBUG_PRINTLN("Error converting time from");
  }

  HeatPump.Status.SyncTime = false;
  return;
}

void printCurrentTime() {
  time_t now;
  struct tm timeinfo;
  char TimeBuffer[32];

  time(&now);
  localtime_r(&now, &timeinfo);

  strftime(TimeBuffer, sizeof(TimeBuffer), "%F %T -> ", &timeinfo);
  DEBUG_PRINT(TimeBuffer);
}

void MQTTWriteReceived(String message, int MsgNumber) {
  DEBUG_PRINTLN(message);
  WriteInProgress = true;  // Wait For OK
}


bool getOATRunningAverage(float newOAT) {
  OAT_total -= OAT_readings[OAT_readIndex];
  OAT_readings[OAT_readIndex] = newOAT;
  OAT_total += newOAT;
  OAT_readIndex++;

  if (OAT_readIndex >= OAT_Window_Size) {
    OAT_readIndex = 0;
    OAT_isFull = true;
  }

  if (OAT_isFull) {
    OAT_average = (float)OAT_total / OAT_Window_Size;
    return true;
  }

  return false;
}



void updateEnergyMeter(double currentPowerKW, int mode) {
  unsigned long* lastTimestamp;

  if (mode >= 0 && mode <= 2) {
    lastTimestamp = &lastConsumedEnergyTimestamp;
  } else if (mode >= 3 && mode <= 5) {
    lastTimestamp = &lastDeliveredEnergyTimestamp;
  } else {
    return;
  }

  unsigned long currentTime = millis();
  unsigned long durationMs = currentTime - *lastTimestamp;

  if (*lastTimestamp > 0 && durationMs > 0) {
    // (1000ms * 60s * 60m) = 3,600,000
    double durationHours = (double)durationMs / 3600000.0;
    cumulativeEnergyToday[mode] += (currentPowerKW * durationHours);
  }

  *lastTimestamp = currentTime;
}

#ifdef ESP32  // Define the M5Stack AtomS3

void CheckForOTAUpdates(void) {
  printCurrentTime();
  DEBUG_PRINT(F("Checking for Firmware Updates..."));

  if (http.begin(F("https://witty.house/ecodanbridge/update.json"), ISGR_root_ca)) {  //HTTPS
    int httpCode = http.GET();

    if (httpCode == HTTP_CODE_OK) {
      DEBUG_PRINTLN(F(" OK"));  // HTTP header has been sent and Server response header has been handled
      String payload = http.getString();

      JsonDocument doc;
      deserializeJson(doc, payload);
      String tv = doc["version"];
      LatestFirmwareVersion = tv;
    } else {  // httpCode will be negative on error
      DEBUG_PRINT(F(" Failed - Error: "));
      DEBUG_PRINT(httpCode);
      DEBUG_PRINTLN(http.errorToString(httpCode));
    }

    http.end();
  } else {
    // http.begin() failing here often points to DNS or CA validation issues.
    DEBUG_PRINTLN("FAILURE (http.begin() returned null or false).");
    DEBUG_PRINTLN("Possible causes: Incorrect CA, DNS error, or WiFi issue.");
  }
}

void InstallOTAUpdates(void) {
  DEBUG_PRINT(F("Starting Update - Downloading from "));                                                                                    // Publish the update in progress status
  update_in_progress = true;                                                                                                                // Set the flag for discovery again
  UpdateReport();                                                                                                                           // Publish that an update has started
  String TargetURL = "https://witty.house/ecodanbridge/ECODAN_Bridge_" + OTADeviceType + "_v" + LatestFirmwareVersion + Language + ".bin";  // Form the Target URL
  DEBUG_PRINTLN(TargetURL);                                                                                                                 // Print Target Download URL
  HttpsOTA.begin(TargetURL.c_str(), ISGR_root_ca);                                                                                          // Begin the update
}


void HttpEvent(HttpEvent_t* event) {
  switch (event->event_id) {
    case HTTP_EVENT_ERROR: DEBUG_PRINTLN("Http Event Error"); break;
    case HTTP_EVENT_ON_CONNECTED: DEBUG_PRINTLN("Http Event On Connected"); break;
    case HTTP_EVENT_HEADER_SENT: DEBUG_PRINTLN("Http Event Header Sent"); break;
    case HTTP_EVENT_ON_HEADER:
      DEBUG_PRINT("Http Event On Header, key=");
      DEBUG_PRINT(event->header_key);
      DEBUG_PRINT(" value=");
      DEBUG_PRINTLN(event->header_value);
      break;
    case HTTP_EVENT_ON_DATA: break;
    case HTTP_EVENT_ON_FINISH: DEBUG_PRINTLN("Http Event On Finish"); break;
    case HTTP_EVENT_DISCONNECTED: DEBUG_PRINTLN("Http Event Disconnected"); break;
    case HTTP_EVENT_REDIRECT: DEBUG_PRINTLN("Http Event Redirect"); break;
  }
}
#endif


#if defined(ESP32) && !defined(ARDUINO_WT32_ETH01)
void WiFiRoamHandler(bool JustConnected) {
  if (JustConnected) {
    RoamLastCheck = millis() - ROAM_CHECK_INTERVAL + ROAM_FIRST_CHECK;
    RoamScanRunning = false;
  }
  if (!RoamScanRunning) {
    if (millis() - RoamLastCheck < ROAM_CHECK_INTERVAL) { return; }
    RoamLastCheck = millis();
    if (WiFi.RSSI() > ROAM_WEAK_RSSI) { return; }
    if (WiFi.scanNetworks(true, false) == WIFI_SCAN_FAILED) { return; }  // Scan asynchrone : la boucle CN105 continue
    RoamScanRunning = true;
    return;
  }
  int16_t n = WiFi.scanComplete();
  if (n == WIFI_SCAN_RUNNING) { return; }
  RoamScanRunning = false;
  if (n <= 0) {
    WiFi.scanDelete();
    return;
  }
  String CurrentSSID = WiFi.SSID();
  int32_t CurrentRSSI = WiFi.RSSI();
  uint8_t CurrentBSSID[6];
  memcpy(CurrentBSSID, WiFi.BSSID(), 6);
  int Best = -1;
  int32_t BestRSSI = -127;
  for (int i = 0; i < n; i++) {
    if (WiFi.SSID(i) == CurrentSSID && WiFi.RSSI(i) > BestRSSI) {
      Best = i;
      BestRSSI = WiFi.RSSI(i);
    }
  }
  if (Best >= 0 && BestRSSI >= CurrentRSSI + ROAM_MIN_GAIN && memcmp(WiFi.BSSID(Best), CurrentBSSID, 6) != 0) {
    uint8_t TargetBSSID[6];
    memcpy(TargetBSSID, WiFi.BSSID(Best), 6);
    int32_t TargetChannel = WiFi.channel(Best);
    RoamSSID = CurrentSSID;
    RoamPSK = WiFi.psk();
    WiFi.scanDelete();
    DEBUG_PRINT(F("WiFi roam: "));
    DEBUG_PRINT(CurrentRSSI);
    DEBUG_PRINT(F(" dBm -> "));
    DEBUG_PRINT(BestRSSI);
    DEBUG_PRINTLN(F(" dBm"));
    WiFi.persistent(false);  // Le choix de borne reste en RAM : au redémarrage, connexion standard
    RoamCount++;
    WiFi.begin(RoamSSID.c_str(), RoamPSK.c_str(), TargetChannel, TargetBSSID);
    WiFi.persistent(true);
    RoamBssidLocked = true;
    return;
  }
  WiFi.scanDelete();
}

void WiFiRoamUnlock(unsigned long DisconnectedFor) {
  if (RoamBssidLocked && DisconnectedFor >= ROAM_UNLOCK_AFTER) {
    RoamBssidLocked = false;
    DEBUG_PRINTLN(F("WiFi roam: borne perdue, reconnexion sans verrouillage"));
    WiFi.persistent(false);
    WiFi.disconnect(false, false);
    RoamCount++;
    WiFi.begin(RoamSSID.c_str(), RoamPSK.c_str());
    WiFi.persistent(true);
  }
}
#endif


#ifdef ARDUINO_WT32_ETH01
// WARNING: onEvent is called from a separate FreeRTOS task (thread)!
void onEvent(arduino_event_id_t event) {
  switch (event) {
    case ARDUINO_EVENT_ETH_START:
      //DEBUG_PRINTLN(F("ETH Started"));
      // The hostname must be set after the interface is started, but needs
      // to be set before DHCP, so set it from the event handler thread.
      ETH.setHostname("Ecodan-Bridge");
      break;
    case ARDUINO_EVENT_ETH_CONNECTED:
      DEBUG_PRINTLN(F("ETH Connected"));
      break;
    case ARDUINO_EVENT_ETH_GOT_IP:
      //DEBUG_PRINTLN(F("ETH Got IP"));
      //DEBUG_PRINTLN(ETH);
      eth_connected = true;
      break;
    case ARDUINO_EVENT_ETH_LOST_IP:
      //DEBUG_PRINTLN(F("ETH Lost IP"));
      eth_connected = false;
      break;
    case ARDUINO_EVENT_ETH_DISCONNECTED:
      //DEBUG_PRINTLN(F("ETH Disconnected"));
      eth_connected = false;
      break;
    case ARDUINO_EVENT_ETH_STOP:
      //DEBUG_PRINTLN(F("ETH Stopped"));
      eth_connected = false;
      break;
    default: break;
  }
}
#endif