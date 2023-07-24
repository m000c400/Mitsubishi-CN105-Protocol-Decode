
#define MQTT_BASETOPIC "Ecodan/ASHP"
#define MQTT_LWT MQTT_BASETOPIC "/LWT"

#define MQTT_STATUS MQTT_BASETOPIC "/Status"
#define MQTT_COMMAND MQTT_BASETOPIC "/Command"

#define MQTT_STATUS_ZONE1 MQTT_STATUS "/Zone1"
#define MQTT_STATUS_ZONE2 MQTT_STATUS "/Zone2"
#define MQTT_STATUS_HOTWATER MQTT_STATUS "/HotWater"
#define MQTT_STATUS_SYSTEM MQTT_STATUS "/System"
#define MQTT_STATUS_TEST MQTT_STATUS "/Test"
#define MQTT_STATUS_WIFISTATUS MQTT_STATUS "/WiFiStatus"

#define MQTT_COMMAND_ZONE1 MQTT_COMMAND "/Zone1"
#define MQTT_COMMAND_ZONE2 MQTT_COMMAND "/Zone2"
#define MQTT_COMMAND_HOTWATER MQTT_COMMAND "/HotWater"
#define MQTT_COMMAND_SYSTEM MQTT_COMMAND "/System"

#define MQTT_COMMAND_ZONE1_TEMP_SETPOINT MQTT_COMMAND_ZONE1 "/TempSetpoint"
#define MQTT_COMMAND_ZONE1_FLOW_SETPOINT MQTT_COMMAND_ZONE1 "/FlowSetpoint"
#define MQTT_COMMAND_ZONE1_CURVE_SETPOINT MQTT_COMMAND_ZONE1 "/CurveSetpoint"

#define MQTT_COMMAND_ZONE2_TEMP_SETPOINT MQTT_COMMAND_ZONE2 "/TempSetpoint"
#define MQTT_COMMAND_ZONE2_FLOW_SETPOINT MQTT_COMMAND_ZONE2 "/FlowSetpoint"
#define MQTT_COMMAND_ZONE2_CURVE_SETPOINT MQTT_COMMAND_ZONE2 "/CurveSetpoint"

#define MQTT_COMMAND_SYSTEM_HEATINGMODE MQTT_COMMAND_SYSTEM "/HeatingMode"
#define MQTT_COMMAND_HOTWATER_SETPOINT MQTT_COMMAND_HOTWATER "/Setpoint"
#define MQTT_COMMAND_HOTWATER_BOOST MQTT_COMMAND_HOTWATER "/Boost"
#define MQTT_COMMAND_SYSTEM_POWER MQTT_COMMAND_SYSTEM "/Power"
#define MQTT_COMMAND_SYSTEM_TEMP MQTT_COMMAND_SYSTEM "/Temp"


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

// save config to file
bool shouldSaveConfig = false;
String HostName;

// Here you can pre-set the settings for the MQTT connection. The settings can later be changed via Wifi Manager.
struct MqttSettings {
  char clientId[20] = "Pre-PopulatedClientName";
  char hostname[40] = "Pre-PopulatedIP";
  char port[6] = "1883";
  char user[20] = "Pre-PopulatedUsername";
  char password[30] = "Pre-PopulatedPassword";              // 30 Char Max
  char wm_mqtt_client_id_identifier[15] = "mqtt_client_id";
  char wm_mqtt_hostname_identifier[14] = "mqtt_hostname";
  char wm_mqtt_port_identifier[10] = "mqtt_port";
  char wm_mqtt_user_identifier[10] = "mqtt_user";
  char wm_mqtt_password_identifier[14] = "mqtt_password";
};

MqttSettings mqttSettings;



void readSettingsFromConfig() {
  //clean FS for testing
  //SPIFFS.format();

  //read configuration from FS json
  Serial.println("mounting FS...");

  if (SPIFFS.begin()) {
    Serial.println("mounted file system");
    if (SPIFFS.exists("/config.json")) {
      //file exists, reading and loading
      Serial.println("reading config file");
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {
        Serial.println("opened config file");
        Serial.print(configFile);
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);
        // Use arduinojson.org/v6/assistant to compute the capacity.
        StaticJsonDocument<1024> doc;
        DeserializationError error = deserializeJson(doc, configFile);
        if (error) {
          Serial.println(F("Failed to read file, using default configuration"));
        } else {
          Serial.println("\nparsed json");

          strcpy(mqttSettings.clientId, doc[mqttSettings.wm_mqtt_client_id_identifier]);
          strcpy(mqttSettings.hostname, doc[mqttSettings.wm_mqtt_hostname_identifier]);
          strcpy(mqttSettings.port, doc[mqttSettings.wm_mqtt_port_identifier]);
          strcpy(mqttSettings.user, doc[mqttSettings.wm_mqtt_user_identifier]);
          strcpy(mqttSettings.password, doc[mqttSettings.wm_mqtt_password_identifier]);
        }
      }
    }
  } else {
    Serial.println("failed to mount FS");
  }
}

//callback notifying us of the need to save config
void saveConfigCallback() {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}

void initializeWifiManager() {
  // The extra parameters to be configured (can be either global or just in the setup)
  // After connecting, parameter.getValue() will get you the configured value
  // id/name placeholder/prompt default length
  WiFiManagerParameter custom_mqtt_client_id("client_id", "MQTT Client ID", mqttSettings.clientId, 40);
  WiFiManagerParameter custom_mqtt_server("server", "MQTT Server", mqttSettings.hostname, 40);
  WiFiManagerParameter custom_mqtt_port("port", "MQTT Server Port", mqttSettings.port, 6);
  WiFiManagerParameter custom_mqtt_user("user", "MQTT Username", mqttSettings.user, 20);
  WiFiManagerParameter custom_mqtt_pass("pass", "MQTT Password", mqttSettings.password, 30);

  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;

  // Reset Wifi settings for testing
  //wifiManager.resetSettings();

  //set config save notify callback
  wifiManager.setSaveConfigCallback(saveConfigCallback);

  //add all your parameters here
  wifiManager.addParameter(&custom_mqtt_client_id);
  wifiManager.addParameter(&custom_mqtt_server);
  wifiManager.addParameter(&custom_mqtt_port);
  wifiManager.addParameter(&custom_mqtt_user);
  wifiManager.addParameter(&custom_mqtt_pass);

  //reset settings - for testing
  //wifiManager.resetSettings();

  //set minimum quality of signal so it ignores AP's under that quality
  //defaults to 8%
  //wifiManager.setMinimumSignalQuality();


  HostName = "EcodanBridge-";
  HostName += String(ESP.getChipId(), HEX);
  WiFi.hostname(HostName);

  wifiManager.setConfigPortalTimeout(180);  // Timeout before launching the config portal
  wifiManager.setConnectTimeout(180);       // Retry
  if (wifiManager.getWiFiIsSaved()) { wifiManager.setEnableConfigPortal(false); }
  if (!wifiManager.autoConnect("Ecodan Bridge AP")) {
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    ESP.reset();
    delay(5000);
  }

  //if you get here you have connected to the WiFi
  Serial.println("Connected...yay! :)");


  //read updated parameters
  strcpy(mqttSettings.clientId, custom_mqtt_client_id.getValue());
  strcpy(mqttSettings.hostname, custom_mqtt_server.getValue());
  strcpy(mqttSettings.port, custom_mqtt_port.getValue());
  strcpy(mqttSettings.user, custom_mqtt_user.getValue());
  strcpy(mqttSettings.password, custom_mqtt_pass.getValue());
}

void saveConfig() {
  Serial.println("saving config");
  StaticJsonDocument<1024> doc;
  doc[mqttSettings.wm_mqtt_client_id_identifier] = mqttSettings.clientId;
  doc[mqttSettings.wm_mqtt_hostname_identifier] = mqttSettings.hostname;
  doc[mqttSettings.wm_mqtt_port_identifier] = mqttSettings.port;
  doc[mqttSettings.wm_mqtt_user_identifier] = mqttSettings.user;
  doc[mqttSettings.wm_mqtt_password_identifier] = mqttSettings.password;

  File configFile = SPIFFS.open("/config.json", "w");
  if (!configFile) {
    Serial.println("failed to open config file for writing");
  }

  configFile.close();
}

void initializeMqttClient() {
  Serial.println("local ip");
  Serial.println(WiFi.localIP());
  MQTTClient.setServer(mqttSettings.hostname, atoi(mqttSettings.port));
}


void MQTTonConnect(void) {
  DEBUG_PRINTLN("MQTT ON CONNECT");
  MQTTClient.publish(MQTT_LWT, "online");
  delay(10);

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


uint8_t MQTTReconnect() {
  if (MQTTClient.connected()) {
    return 1;
  }

  DEBUG_PRINTLN("Attempting MQTT connection...");
  if (MQTTClient.connect(HostName.c_str(), mqttSettings.user, mqttSettings.password, MQTT_LWT, 0, true, "offline")) {
    DEBUG_PRINTLN("MQTT Connected");
    MQTTonConnect();
    DEBUG_PRINTLN("Connected to MQTT");
    digitalWrite(Red_RGB_LED, LOW);     // Turn off the Red LED
    digitalWrite(Green_RGB_LED, HIGH);  // Flash the Green LED
    delay(10);
    digitalWrite(Green_RGB_LED, LOW);
    return 1;
  } else {
    switch (MQTTClient.state()) {
      case -4:
        DEBUG_PRINTLN("MQTT_CONNECTION_TIMEOUT");
        break;
      case -3:
        DEBUG_PRINTLN("MQTT_CONNECTION_LOST");
        break;
      case -2:
        DEBUG_PRINTLN("MQTT_CONNECT_FAILED");
        break;
      case -1:
        DEBUG_PRINTLN("MQTT_DISCONNECTED");
        break;
      case 0:
        DEBUG_PRINTLN("MQTT_CONNECTED");
        break;
      case 1:
        DEBUG_PRINTLN("MQTT_CONNECT_BAD_PROTOCOL");
        break;
      case 2:
        DEBUG_PRINTLN("MQTT_CONNECT_BAD_CLIENT_ID");
        break;
      case 3:
        DEBUG_PRINTLN("MQTT_CONNECT_UNAVAILABLE");
        break;
      case 4:
        DEBUG_PRINTLN("MQTT_CONNECT_BAD_CREDENTIALS");
        break;
      case 5:
        DEBUG_PRINTLN("MQTT_CONNECT_UNAUTHORIZED");
        break;
    }
    return 0;
  }
  return 0;
}


void handleMqttState() {
  if (!MQTTClient.connected()) {
    MQTTReconnect();
  }
  MQTTClient.loop();
}