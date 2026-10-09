String MQTT_BASETOPIC = "ASHP";

String MQTT_LWT = MQTT_BASETOPIC + "/LWT";
String MQTT_STATUS = MQTT_BASETOPIC + "/Status";
String MQTT_COMMAND = MQTT_BASETOPIC + "/Command";

String MQTT_STATUS_ZONE1 = MQTT_STATUS + "/Zone1";
String MQTT_STATUS_ZONE2 = MQTT_STATUS + "/Zone2";
String MQTT_STATUS_HOTWATER = MQTT_STATUS + "/HotWater";
String MQTT_STATUS_SYSTEM = MQTT_STATUS + "/System";
String MQTT_STATUS_CONFIGURATION = MQTT_STATUS + "/Configuration";
String MQTT_STATUS_ADVANCED = MQTT_STATUS + "/Advanced";
String MQTT_STATUS_ADVANCED_TWO = MQTT_STATUS + "/AdvancedTwo";
String MQTT_STATUS_ENERGY = MQTT_STATUS + "/Energy";
String MQTT_STATUS_WIFISTATUS = MQTT_STATUS + "/WiFiStatus";
String MQTT_STATUS_CURVE = MQTT_STATUS + "/CompCurve";
String MQTT_STATUS_ACTV_CTRL = MQTT_STATUS + "/ActiveControl";
String MQTT_STATUS_AC = MQTT_STATUS + "/AC";

String MQTT_STATUS_WIFISTATUS_UPDATE = MQTT_STATUS_WIFISTATUS + "/Update";

String MQTT_COMMAND_ZONE1 = MQTT_COMMAND + "/Zone1";
String MQTT_COMMAND_ZONE2 = MQTT_COMMAND + "/Zone2";
String MQTT_COMMAND_HOTWATER = MQTT_COMMAND + "/HotWater";
String MQTT_COMMAND_SYSTEM = MQTT_COMMAND + "/System";
String MQTT_COMMAND_AC = MQTT_COMMAND + "/AC";

String MQTT_COMMAND_ZONE1_FLOW_SETPOINT = MQTT_COMMAND_ZONE1 + "/FlowSetpoint";
String MQTT_COMMAND_ZONE1_NOMODE_SETPOINT = MQTT_COMMAND_ZONE1 + "/ThermostatSetpoint";
String MQTT_COMMAND_ZONE1_HEAT_PROHIBIT = MQTT_COMMAND_ZONE1 + "/ProhibitHeating";
String MQTT_COMMAND_ZONE1_COOL_PROHIBIT = MQTT_COMMAND_ZONE1 + "/ProhibitCooling";
String MQTT_COMMAND_ZONE1_HEATINGMODE = MQTT_COMMAND_ZONE1 + "/HeatingMode";

String MQTT_COMMAND_ZONE2_FLOW_SETPOINT = MQTT_COMMAND_ZONE2 + "/FlowSetpoint";
String MQTT_COMMAND_ZONE2_NOMODE_SETPOINT = MQTT_COMMAND_ZONE2 + "/ThermostatSetpoint";
String MQTT_COMMAND_ZONE2_HEAT_PROHIBIT = MQTT_COMMAND_ZONE2 + "/ProhibitHeating";
String MQTT_COMMAND_ZONE2_COOL_PROHIBIT = MQTT_COMMAND_ZONE2 + "/ProhibitCooling";
String MQTT_COMMAND_ZONE2_HEATINGMODE = MQTT_COMMAND_ZONE2 + "/HeatingMode";

String MQTT_COMMAND_HOTWATER_MODE = MQTT_COMMAND_HOTWATER + "/Mode";
String MQTT_COMMAND_HOTWATER_SETPOINT = MQTT_COMMAND_HOTWATER + "/Setpoint";
String MQTT_COMMAND_HOTWATER_BOOST = MQTT_COMMAND_HOTWATER + "/Boost";
String MQTT_COMMAND_HOTWATER_NORM_BOOST = MQTT_COMMAND_HOTWATER + "/NormalBoost";
String MQTT_COMMAND_HOTWATER_PROHIBIT = MQTT_COMMAND_HOTWATER + "/Prohibit";

String MQTT_COMMAND_SYSTEM_HOLIDAYMODE = MQTT_COMMAND_SYSTEM + "/HolidayMode";
String MQTT_COMMAND_SYSTEM_SVRMODE = MQTT_COMMAND_SYSTEM + "/SvrControlMode";
String MQTT_COMMAND_SYSTEM_POWER = MQTT_COMMAND_SYSTEM + "/Power";
String MQTT_COMMAND_SYSTEM_UNITSIZE = MQTT_COMMAND_SYSTEM + "/UnitSize";
String MQTT_COMMAND_SYSTEM_GLYCOL = MQTT_COMMAND_SYSTEM + "/Glycol";
String MQTT_COMMAND_SYSTEM_SERVICE = MQTT_COMMAND_SYSTEM + "/Svc";
String MQTT_COMMAND_SYSTEM_COMPCURVE = MQTT_COMMAND_SYSTEM + "/CompCurve";
String MQTT_COMMAND_SYSTEM_ACTV_CTRL = MQTT_COMMAND_SYSTEM + "/ActiveControl";

String MQTTCommandZone1FlowSetpoint = MQTT_COMMAND_ZONE1_FLOW_SETPOINT;
String MQTTCommandZone1NoModeSetpoint = MQTT_COMMAND_ZONE1_NOMODE_SETPOINT;
String MQTTCommandZone1ProhibitHeating = MQTT_COMMAND_ZONE1_HEAT_PROHIBIT;
String MQTTCommandZone1ProhibitCooling = MQTT_COMMAND_ZONE1_COOL_PROHIBIT;
String MQTTCommandZone1HeatingMode = MQTT_COMMAND_ZONE1_HEATINGMODE;

String MQTTCommandZone2FlowSetpoint = MQTT_COMMAND_ZONE2_FLOW_SETPOINT;
String MQTTCommandZone2NoModeSetpoint = MQTT_COMMAND_ZONE2_NOMODE_SETPOINT;
String MQTTCommandZone2ProhibitHeating = MQTT_COMMAND_ZONE2_HEAT_PROHIBIT;
String MQTTCommandZone2ProhibitCooling = MQTT_COMMAND_ZONE2_COOL_PROHIBIT;
String MQTTCommandZone2HeatingMode = MQTT_COMMAND_ZONE2_HEATINGMODE;

String MQTTCommandHotwaterMode = MQTT_COMMAND_HOTWATER_MODE;
String MQTTCommandHotwaterSetpoint = MQTT_COMMAND_HOTWATER_SETPOINT;
String MQTTCommandHotwaterBoost = MQTT_COMMAND_HOTWATER_BOOST;
String MQTTCommandHotwaterNormalBoost = MQTT_COMMAND_HOTWATER_NORM_BOOST;
String MQTTCommandHotwaterProhibit = MQTT_COMMAND_HOTWATER_PROHIBIT;

String MQTTCommandSystemHolidayMode = MQTT_COMMAND_SYSTEM_HOLIDAYMODE;
String MQTTCommandSystemSvrMode = MQTT_COMMAND_SYSTEM_SVRMODE;
String MQTTCommandSystemPower = MQTT_COMMAND_SYSTEM_POWER;
String MQTTCommandSystemUnitSize = MQTT_COMMAND_SYSTEM_UNITSIZE;
String MQTTCommandSystemGlycol = MQTT_COMMAND_SYSTEM_GLYCOL;
String MQTTCommandSystemService = MQTT_COMMAND_SYSTEM_SERVICE;
String MQTTCommandSystemCompCurve = MQTT_COMMAND_SYSTEM_COMPCURVE;
String MQTTCommandSystemActvCtrl = MQTT_COMMAND_SYSTEM_ACTV_CTRL;
String MQTTCommandAC = MQTT_COMMAND_AC;


String MQTT_2_BASETOPIC = "00000";

String MQTT_2_LWT = MQTT_2_BASETOPIC + "/LWT";
String MQTT_2_STATUS = MQTT_2_BASETOPIC + "/Status";
String MQTT_2_COMMAND = MQTT_2_BASETOPIC + "/Command";

String MQTT_2_STATUS_ZONE1 = MQTT_2_STATUS + "/Zone1";
String MQTT_2_STATUS_ZONE2 = MQTT_2_STATUS + "/Zone2";
String MQTT_2_STATUS_HOTWATER = MQTT_2_STATUS + "/HotWater";
String MQTT_2_STATUS_SYSTEM = MQTT_2_STATUS + "/System";
String MQTT_2_STATUS_CONFIGURATION = MQTT_2_STATUS + "/Configuration";
String MQTT_2_STATUS_ADVANCED = MQTT_2_STATUS + "/Advanced";
String MQTT_2_STATUS_ADVANCED_TWO = MQTT_2_STATUS + "/AdvancedTwo";
String MQTT_2_STATUS_ENERGY = MQTT_2_STATUS + "/Energy";
String MQTT_2_STATUS_WIFISTATUS = MQTT_2_STATUS + "/WiFiStatus";
String MQTT_2_STATUS_CURVE = MQTT_2_STATUS + "/CompCurve";
String MQTT_2_STATUS_ACTV_CTRL = MQTT_2_STATUS + "/ActiveControl";
String MQTT_2_STATUS_AC = MQTT_2_STATUS + "/AC";

String MQTT_2_STATUS_WIFISTATUS_UPDATE = MQTT_2_STATUS_WIFISTATUS + "/Update";

String MQTT_2_COMMAND_ZONE1 = MQTT_2_COMMAND + "/Zone1";
String MQTT_2_COMMAND_ZONE2 = MQTT_2_COMMAND + "/Zone2";
String MQTT_2_COMMAND_HOTWATER = MQTT_2_COMMAND + "/HotWater";
String MQTT_2_COMMAND_SYSTEM = MQTT_2_COMMAND + "/System";
String MQTT_2_COMMAND_AC = MQTT_2_COMMAND + "/AC";

String MQTT_2_COMMAND_ZONE1_FLOW_SETPOINT = MQTT_2_COMMAND_ZONE1 + "/FlowSetpoint";
String MQTT_2_COMMAND_ZONE1_NOMODE_SETPOINT = MQTT_2_COMMAND_ZONE1 + "/ThermostatSetpoint";
String MQTT_2_COMMAND_ZONE1_HEAT_PROHIBIT = MQTT_2_COMMAND_ZONE1 + "/ProhibitHeating";
String MQTT_2_COMMAND_ZONE1_COOL_PROHIBIT = MQTT_2_COMMAND_ZONE1 + "/ProhibitCooling";
String MQTT_2_COMMAND_ZONE1_HEATINGMODE = MQTT_2_COMMAND_ZONE1 + "/HeatingMode";

String MQTT_2_COMMAND_ZONE2_FLOW_SETPOINT = MQTT_2_COMMAND_ZONE2 + "/FlowSetpoint";
String MQTT_2_COMMAND_ZONE2_NOMODE_SETPOINT = MQTT_2_COMMAND_ZONE2 + "/ThermostatSetpoint";
String MQTT_2_COMMAND_ZONE2_HEAT_PROHIBIT = MQTT_2_COMMAND_ZONE2 + "/ProhibitHeating";
String MQTT_2_COMMAND_ZONE2_COOL_PROHIBIT = MQTT_2_COMMAND_ZONE2 + "/ProhibitCooling";
String MQTT_2_COMMAND_ZONE2_HEATINGMODE = MQTT_2_COMMAND_ZONE2 + "/HeatingMode";

String MQTT_2_COMMAND_HOTWATER_MODE = MQTT_2_COMMAND_HOTWATER + "/Mode";
String MQTT_2_COMMAND_HOTWATER_SETPOINT = MQTT_2_COMMAND_HOTWATER + "/Setpoint";
String MQTT_2_COMMAND_HOTWATER_BOOST = MQTT_2_COMMAND_HOTWATER + "/Boost";
String MQTT_2_COMMAND_HOTWATER_NORM_BOOST = MQTT_2_COMMAND_HOTWATER + "/NormalBoost";
String MQTT_2_COMMAND_HOTWATER_PROHIBIT = MQTT_2_COMMAND_HOTWATER + "/Prohibit";

String MQTT_2_COMMAND_SYSTEM_HOLIDAYMODE = MQTT_2_COMMAND_SYSTEM + "/HolidayMode";
String MQTT_2_COMMAND_SYSTEM_SVRMODE = MQTT_2_COMMAND_SYSTEM + "/SvrControlMode";
String MQTT_2_COMMAND_SYSTEM_POWER = MQTT_2_COMMAND_SYSTEM + "/Power";
String MQTT_2_COMMAND_SYSTEM_UNITSIZE = MQTT_2_COMMAND_SYSTEM + "/UnitSize";
String MQTT_2_COMMAND_SYSTEM_GLYCOL = MQTT_2_COMMAND_SYSTEM + "/Glycol";
String MQTT_2_COMMAND_SYSTEM_SERVICE = MQTT_2_COMMAND_SYSTEM + "/Svc";
String MQTT_2_COMMAND_SYSTEM_COMPCURVE = MQTT_2_COMMAND_SYSTEM + "/CompCurve";
String MQTT_2_COMMAND_SYSTEM_ACTV_CTRL = MQTT_2_COMMAND_SYSTEM + "/ActiveControl";

String MQTTCommand2Zone1FlowSetpoint = MQTT_2_COMMAND_ZONE1_FLOW_SETPOINT;
String MQTTCommand2Zone1NoModeSetpoint = MQTT_2_COMMAND_ZONE1_NOMODE_SETPOINT;
String MQTTCommand2Zone1ProhibitHeating = MQTT_2_COMMAND_ZONE1_HEAT_PROHIBIT;
String MQTTCommand2Zone1ProhibitCooling = MQTT_2_COMMAND_ZONE1_COOL_PROHIBIT;
String MQTTCommand2Zone1HeatingMode = MQTT_2_COMMAND_ZONE1_HEATINGMODE;

String MQTTCommand2Zone2FlowSetpoint = MQTT_2_COMMAND_ZONE2_FLOW_SETPOINT;
String MQTTCommand2Zone2NoModeSetpoint = MQTT_2_COMMAND_ZONE2_NOMODE_SETPOINT;
String MQTTCommand2Zone2ProhibitHeating = MQTT_2_COMMAND_ZONE2_HEAT_PROHIBIT;
String MQTTCommand2Zone2ProhibitCooling = MQTT_2_COMMAND_ZONE2_COOL_PROHIBIT;
String MQTTCommand2Zone2HeatingMode = MQTT_2_COMMAND_ZONE2_HEATINGMODE;

String MQTTCommand2HotwaterMode = MQTT_2_COMMAND_HOTWATER_MODE;
String MQTTCommand2HotwaterSetpoint = MQTT_2_COMMAND_HOTWATER_SETPOINT;
String MQTTCommand2HotwaterBoost = MQTT_2_COMMAND_HOTWATER_BOOST;
String MQTTCommand2HotwaterNormalBoost = MQTT_2_COMMAND_HOTWATER_NORM_BOOST;
String MQTTCommand2HotwaterProhibit = MQTT_2_COMMAND_HOTWATER_PROHIBIT;

String MQTTCommand2SystemHolidayMode = MQTT_2_COMMAND_SYSTEM_HOLIDAYMODE;
String MQTTCommand2SystemSvrMode = MQTT_2_COMMAND_SYSTEM_SVRMODE;
String MQTTCommand2SystemPower = MQTT_2_COMMAND_SYSTEM_POWER;
String MQTTCommand2SystemUnitSize = MQTT_2_COMMAND_SYSTEM_UNITSIZE;
String MQTTCommand2SystemGlycol = MQTT_2_COMMAND_SYSTEM_GLYCOL;
String MQTTCommand2SystemService = MQTT_2_COMMAND_SYSTEM_SERVICE;
String MQTTCommand2SystemCompCurve = MQTT_2_COMMAND_SYSTEM_COMPCURVE;
String MQTTCommand2SystemActvCtrl = MQTT_2_COMMAND_SYSTEM_ACTV_CTRL;
String MQTTCommand2AC = MQTT_2_COMMAND_AC;



char snprintbuffer[41] = "";
char DeviceID[15] = "";
const char ClientPrefixA2W[14] = "EcodanBridge-";  // Keep Static for A2W users updating from < v7 to prevent new device creation
const char ClientPrefixA2A[14] = "MitsiBridge-";   // Add new for A2A
char WiFiHostname[40] = "";
char MQTTIDs[40] = "";



// Programs

#if defined(ESP8266) || defined(ESP32)  // ESP32 or ESP8266 Compatiability
void readSettingsFromConfig() {
  // Clean LittleFS for testing
  //LittleFS.format();

  // Read configuration from LittleFS JSON
  DEBUG_PRINTLN(F("Mounting File System..."));
#ifdef ESP8266
  if (LittleFS.begin()) {
#endif
#ifdef ESP32
    if (LittleFS.begin("/storage")) {
#endif
      DEBUG_PRINTLN(F("Mounted File System"));
      if (LittleFS.exists("/config.json")) {
        //file exists, reading and loading
        DEBUG_PRINTLN(F("Reading config file"));
        File configFile = LittleFS.open("/config.json", "r");
        if (configFile) {
          DEBUG_PRINTLN(F("Opened config file"));
          JsonDocument doc;
          DeserializationError error = deserializeJson(doc, configFile);
          if (error) {
            DEBUG_PRINT(F("Failed to read file: "));
            DEBUG_PRINTLN(error.c_str());
          } else {
            DEBUG_PRINTLN(F("Parsed JSON: "));
            serializeJson(doc, DEBUGPORT);
            DEBUG_PRINTLN();

            // Build in safety check, otherwise ESP will crash out and you can't get back in
            if (doc.containsKey(mqttSettings.wm_device_id_identifier)) {
              if ((strlen(doc[mqttSettings.wm_device_id_identifier]) > 0) && ((strlen(doc[mqttSettings.wm_device_id_identifier]) + 1) <= deviceId_max_length)) {
                strcpy(mqttSettings.deviceId, doc[mqttSettings.wm_device_id_identifier]);
              }
            } else {  // For upgrading from <5.3.1, create the entry
#ifdef ESP8266
              snprintf(snprintbuffer, deviceId_max_length, (String(ESP.getChipId(), HEX)).c_str());
#endif
#ifdef ESP32
              snprintf(snprintbuffer, deviceId_max_length, (String(ESP.getEfuseMac(), HEX)).c_str());
#endif
              strcpy(mqttSettings.deviceId, snprintbuffer);
              shouldSaveConfig = true;  // Save config after exit to update the file
            }
            if (doc.containsKey(mqttSettings.wm_mqtt_hostname_identifier)) {
              if ((strlen(doc[mqttSettings.wm_mqtt_hostname_identifier]) > 0) && ((strlen(doc[mqttSettings.wm_mqtt_hostname_identifier]) + 1) <= hostname_max_length)) {
                strcpy(mqttSettings.hostname, doc[mqttSettings.wm_mqtt_hostname_identifier]);
              }
            }
            if (doc.containsKey(mqttSettings.wm_mqtt_port_identifier)) {
              if ((strlen(doc[mqttSettings.wm_mqtt_port_identifier]) > 0) && ((strlen(doc[mqttSettings.wm_mqtt_port_identifier]) + 1) <= port_max_length)) {
                strcpy(mqttSettings.port, doc[mqttSettings.wm_mqtt_port_identifier]);
              }
            }
            if (doc.containsKey(mqttSettings.wm_mqtt_user_identifier)) {
              if ((strlen(doc[mqttSettings.wm_mqtt_user_identifier]) > 0) && ((strlen(doc[mqttSettings.wm_mqtt_user_identifier]) + 1) <= user_max_length)) {
                strcpy(mqttSettings.user, doc[mqttSettings.wm_mqtt_user_identifier]);
              }
            }
            if (doc.containsKey(mqttSettings.wm_mqtt_password_identifier)) {
              if ((strlen(doc[mqttSettings.wm_mqtt_password_identifier]) > 0) && ((strlen(doc[mqttSettings.wm_mqtt_password_identifier]) + 1) <= password_max_length)) {
                strcpy(mqttSettings.password, doc[mqttSettings.wm_mqtt_password_identifier]);
              }
            }
            if (doc.containsKey(mqttSettings.wm_mqtt_basetopic_identifier)) {
              if ((strlen(doc[mqttSettings.wm_mqtt_basetopic_identifier]) > 0) && ((strlen(doc[mqttSettings.wm_mqtt_basetopic_identifier]) + 1) <= basetopic_max_length)) {
                strcpy(mqttSettings.baseTopic, doc[mqttSettings.wm_mqtt_basetopic_identifier]);
                MQTT_BASETOPIC = mqttSettings.baseTopic;
              }
            } else {  // For upgrading from <6.0.0, create the entry
              strcpy(mqttSettings.baseTopic, mqttSettings.deviceId);
              MQTT_BASETOPIC = mqttSettings.baseTopic;
              shouldSaveConfig = true;  // Save config after exit to update the file
            }

            // MQTT Stream 2
            if (doc.containsKey(mqttSettings.wm_mqtt2_hostname_identifier)) {
              if ((strlen(doc[mqttSettings.wm_mqtt2_hostname_identifier]) > 0) && ((strlen(doc[mqttSettings.wm_mqtt2_hostname_identifier]) + 1) <= hostname_max_length)) {
                strcpy(mqttSettings.hostname2, doc[mqttSettings.wm_mqtt2_hostname_identifier]);
              }
            } else {  // For upgrading from <6.0.0, create the entry
              snprintf(snprintbuffer, hostname_max_length, mqttSettings.hostname2);
              strcpy(mqttSettings.hostname2, snprintbuffer);
              shouldSaveConfig = true;  // Save config after exit to update the file
            }
            if (doc.containsKey(mqttSettings.wm_mqtt2_port_identifier)) {
              if ((strlen(doc[mqttSettings.wm_mqtt2_port_identifier]) > 0) && ((strlen(doc[mqttSettings.wm_mqtt2_port_identifier]) + 1) <= port_max_length)) {
                strcpy(mqttSettings.port2, doc[mqttSettings.wm_mqtt2_port_identifier]);
              }
            } else {  // For upgrading from <6.0.0, create the entry
              snprintf(snprintbuffer, port_max_length, mqttSettings.port2);
              strcpy(mqttSettings.port2, snprintbuffer);
              shouldSaveConfig = true;  // Save config after exit to update the file
            }
            if (doc.containsKey(mqttSettings.wm_mqtt2_user_identifier)) {
              if ((strlen(doc[mqttSettings.wm_mqtt2_user_identifier]) > 0) && ((strlen(doc[mqttSettings.wm_mqtt2_user_identifier]) + 1) <= user_max_length)) {
                strcpy(mqttSettings.user2, doc[mqttSettings.wm_mqtt2_user_identifier]);
              }
            } else {  // For upgrading from <6.0.0, create the entry
              snprintf(snprintbuffer, user_max_length, mqttSettings.user2);
              strcpy(mqttSettings.user2, snprintbuffer);
              shouldSaveConfig = true;  // Save config after exit to update the file
            }
            if (doc.containsKey(mqttSettings.wm_mqtt2_password_identifier)) {
              if ((strlen(doc[mqttSettings.wm_mqtt2_password_identifier]) > 0) && ((strlen(doc[mqttSettings.wm_mqtt2_password_identifier]) + 1) <= password_max_length)) {
                strcpy(mqttSettings.password2, doc[mqttSettings.wm_mqtt2_password_identifier]);
              }
            } else {  // For upgrading from <6.0.0, create the entry
              snprintf(snprintbuffer, password_max_length, mqttSettings.password2);
              strcpy(mqttSettings.password2, snprintbuffer);
              shouldSaveConfig = true;  // Save config after exit to update the file
            }
            if (doc.containsKey(mqttSettings.wm_mqtt2_basetopic_identifier)) {
              if ((strlen(doc[mqttSettings.wm_mqtt2_basetopic_identifier]) > 0) && ((strlen(doc[mqttSettings.wm_mqtt2_basetopic_identifier]) + 1) <= basetopic_max_length)) {
                strcpy(mqttSettings.baseTopic2, doc[mqttSettings.wm_mqtt2_basetopic_identifier]);
                MQTT_2_BASETOPIC = mqttSettings.baseTopic2;
              }
            } else {  // For upgrading from <6.0.0, create the entry
              strcpy(mqttSettings.baseTopic2, mqttSettings.deviceId);
              MQTT_2_BASETOPIC = mqttSettings.baseTopic2;
              shouldSaveConfig = true;  // Save config after exit to update the file
            }
            // Unit Size
            if (doc.containsKey(unitSettings.unitsize_identifier)) {
              if (doc[unitSettings.unitsize_identifier] > 0) {
                unitSettings.UnitSize = doc[unitSettings.unitsize_identifier];
              }
            } else {                    // For upgrading from <6.1.1, create the entry
              shouldSaveConfig = true;  // Save config after exit to update the file
            }
            // Glycol Strength
            if (doc.containsKey(unitSettings.glycol_identifier)) {
              if (doc[unitSettings.glycol_identifier] > 0) {
                unitSettings.GlycolStrength = doc[unitSettings.glycol_identifier];
              }
            } else {                    // For upgrading from <6.1.1, create the entry
              shouldSaveConfig = true;  // Save config after exit to update the file
            }
            // Compensation Curve
            if (doc.containsKey(unitSettings.compcurve_identifier)) {
              if (strlen(doc[unitSettings.compcurve_identifier]) > 0) {
                unitSettings.CompCurve = doc[unitSettings.compcurve_identifier].as<String>();
              }
            } else {                    // For upgrading from <6.3.0, create the entry
              shouldSaveConfig = true;  // Save config after exit to update the file
            }
            // Short Cycle Protection
            if (doc.containsKey(unitSettings.act_ctrl_sc_identifier)) {
              unitSettings.shortcycleprotectionenabled = doc[unitSettings.act_ctrl_sc_identifier].as<bool>();
            } else {                    // For upgrading from <6.4.0, create the entry
              shouldSaveConfig = true;  // Save config after exit to update the file
            }
            // MELCloud Read Only
            if (doc.containsKey(unitSettings.mel_block_identifier)) {
              unitSettings.BlockWriteFromMELCloud = doc[unitSettings.mel_block_identifier].as<bool>();
            } else {                    // For upgrading from <6.5.6, create the entry
              shouldSaveConfig = true;  // Save config after exit to update the file
            }
            // AC Remote Temp
            if (doc.containsKey(unitSettings.remote_ac_identifier)) {
              unitSettings.RemoteTempOn = doc[unitSettings.remote_ac_identifier].as<bool>();
            } else {                    // For upgrading from <6.5.6, create the entry
              shouldSaveConfig = true;  // Save config after exit to update the file
            }
          }
        }
        configFile.close();
      } else {
        DEBUG_PRINTLN(F("No config file exists, using placeholder values"));
        // Populate the Dynamic Variables (Device ID)
#ifdef ESP8266
        snprintf(DeviceID, deviceId_max_length, (String(ESP.getChipId(), HEX)).c_str());
#endif
#ifdef ESP32
        snprintf(DeviceID, deviceId_max_length, (String(ESP.getEfuseMac(), HEX)).c_str());
#endif
        strcpy(mqttSettings.deviceId, DeviceID);
        strcpy(mqttSettings.baseTopic, "ASHP/");
        strcat(mqttSettings.baseTopic, DeviceID);
        strcpy(mqttSettings.baseTopic2, DeviceID);  // Base topic 2 defaults to deviceID

        MQTT_BASETOPIC = mqttSettings.baseTopic;
        MQTT_2_BASETOPIC = mqttSettings.baseTopic2;
        shouldSaveConfig = true;  // Save config after exit to update the file
      }
    } else {
      DEBUG_PRINTLN(F("Failed to mount File System"));
    }
  }



  void RecalculateMQTTTopics() {
    // The base topic may change via WiFi Manager
    MQTT_LWT = MQTT_BASETOPIC + "/LWT";
    MQTT_STATUS = MQTT_BASETOPIC + "/Status";
    MQTT_COMMAND = MQTT_BASETOPIC + "/Command";

    MQTT_STATUS_ZONE1 = MQTT_STATUS + "/Zone1";
    MQTT_STATUS_ZONE2 = MQTT_STATUS + "/Zone2";
    MQTT_STATUS_HOTWATER = MQTT_STATUS + "/HotWater";
    MQTT_STATUS_SYSTEM = MQTT_STATUS + "/System";
    MQTT_STATUS_CONFIGURATION = MQTT_STATUS + "/Configuration";
    MQTT_STATUS_ADVANCED = MQTT_STATUS + "/Advanced";
    MQTT_STATUS_ADVANCED_TWO = MQTT_STATUS + "/AdvancedTwo";
    MQTT_STATUS_ENERGY = MQTT_STATUS + "/Energy";
    MQTT_STATUS_WIFISTATUS = MQTT_STATUS + "/WiFiStatus";
    MQTT_STATUS_CURVE = MQTT_STATUS + "/CompCurve";
    MQTT_STATUS_ACTV_CTRL = MQTT_STATUS + "/ActiveControl";
    MQTT_STATUS_AC = MQTT_STATUS + "/AC";
    MQTT_STATUS_WIFISTATUS_UPDATE = MQTT_STATUS_WIFISTATUS + "/Update";

    MQTT_COMMAND_ZONE1 = MQTT_COMMAND + "/Zone1";
    MQTT_COMMAND_ZONE2 = MQTT_COMMAND + "/Zone2";
    MQTT_COMMAND_HOTWATER = MQTT_COMMAND + "/HotWater";
    MQTT_COMMAND_SYSTEM = MQTT_COMMAND + "/System";
    MQTT_COMMAND_AC = MQTT_COMMAND + "/AC";

    MQTT_COMMAND_ZONE1_FLOW_SETPOINT = MQTT_COMMAND_ZONE1 + "/FlowSetpoint";
    MQTT_COMMAND_ZONE1_NOMODE_SETPOINT = MQTT_COMMAND_ZONE1 + "/ThermostatSetpoint";
    MQTT_COMMAND_ZONE1_HEAT_PROHIBIT = MQTT_COMMAND_ZONE1 + "/ProhibitHeating";
    MQTT_COMMAND_ZONE1_COOL_PROHIBIT = MQTT_COMMAND_ZONE1 + "/ProhibitCooling";
    MQTT_COMMAND_ZONE1_HEATINGMODE = MQTT_COMMAND_ZONE1 + "/HeatingMode";

    MQTT_COMMAND_ZONE2_FLOW_SETPOINT = MQTT_COMMAND_ZONE2 + "/FlowSetpoint";
    MQTT_COMMAND_ZONE2_NOMODE_SETPOINT = MQTT_COMMAND_ZONE2 + "/ThermostatSetpoint";
    MQTT_COMMAND_ZONE2_HEAT_PROHIBIT = MQTT_COMMAND_ZONE2 + "/ProhibitHeating";
    MQTT_COMMAND_ZONE2_COOL_PROHIBIT = MQTT_COMMAND_ZONE2 + "/ProhibitCooling";
    MQTT_COMMAND_ZONE2_HEATINGMODE = MQTT_COMMAND_ZONE2 + "/HeatingMode";

    MQTT_COMMAND_HOTWATER_MODE = MQTT_COMMAND_HOTWATER + "/Mode";
    MQTT_COMMAND_HOTWATER_SETPOINT = MQTT_COMMAND_HOTWATER + "/Setpoint";
    MQTT_COMMAND_HOTWATER_BOOST = MQTT_COMMAND_HOTWATER + "/Boost";
    MQTT_COMMAND_HOTWATER_NORM_BOOST = MQTT_COMMAND_HOTWATER + "/NormalBoost";
    MQTT_COMMAND_HOTWATER_PROHIBIT = MQTT_COMMAND_HOTWATER + "/Prohibit";

    MQTT_COMMAND_SYSTEM_HOLIDAYMODE = MQTT_COMMAND_SYSTEM + "/HolidayMode";
    MQTT_COMMAND_SYSTEM_SVRMODE = MQTT_COMMAND_SYSTEM + "/SvrControlMode";
    MQTT_COMMAND_SYSTEM_POWER = MQTT_COMMAND_SYSTEM + "/Power";
    MQTT_COMMAND_SYSTEM_UNITSIZE = MQTT_COMMAND_SYSTEM + "/UnitSize";
    MQTT_COMMAND_SYSTEM_GLYCOL = MQTT_COMMAND_SYSTEM + "/Glycol";
    MQTT_COMMAND_SYSTEM_SERVICE = MQTT_COMMAND_SYSTEM + "/Svc";
    MQTT_COMMAND_SYSTEM_COMPCURVE = MQTT_COMMAND_SYSTEM + "/CompCurve";
    MQTT_COMMAND_SYSTEM_ACTV_CTRL = MQTT_COMMAND_SYSTEM + "/ActiveControl";

    MQTTCommandZone1FlowSetpoint = MQTT_COMMAND_ZONE1_FLOW_SETPOINT;
    MQTTCommandZone1NoModeSetpoint = MQTT_COMMAND_ZONE1_NOMODE_SETPOINT;
    MQTTCommandZone1ProhibitHeating = MQTT_COMMAND_ZONE1_HEAT_PROHIBIT;
    MQTTCommandZone1ProhibitCooling = MQTT_COMMAND_ZONE1_COOL_PROHIBIT;
    MQTTCommandZone1HeatingMode = MQTT_COMMAND_ZONE1_HEATINGMODE;

    MQTTCommandZone2FlowSetpoint = MQTT_COMMAND_ZONE2_FLOW_SETPOINT;
    MQTTCommandZone2NoModeSetpoint = MQTT_COMMAND_ZONE2_NOMODE_SETPOINT;
    MQTTCommandZone2ProhibitHeating = MQTT_COMMAND_ZONE2_HEAT_PROHIBIT;
    MQTTCommandZone2ProhibitCooling = MQTT_COMMAND_ZONE2_COOL_PROHIBIT;
    MQTTCommandZone2HeatingMode = MQTT_COMMAND_ZONE2_HEATINGMODE;

    MQTTCommandHotwaterMode = MQTT_COMMAND_HOTWATER_MODE;
    MQTTCommandHotwaterSetpoint = MQTT_COMMAND_HOTWATER_SETPOINT;
    MQTTCommandHotwaterBoost = MQTT_COMMAND_HOTWATER_BOOST;
    MQTTCommandHotwaterNormalBoost = MQTT_COMMAND_HOTWATER_NORM_BOOST;
    MQTTCommandHotwaterProhibit = MQTT_COMMAND_HOTWATER_PROHIBIT;

    MQTTCommandSystemHolidayMode = MQTT_COMMAND_SYSTEM_HOLIDAYMODE;
    MQTTCommandSystemSvrMode = MQTT_COMMAND_SYSTEM_SVRMODE;
    MQTTCommandSystemPower = MQTT_COMMAND_SYSTEM_POWER;
    MQTTCommandSystemUnitSize = MQTT_COMMAND_SYSTEM_UNITSIZE;
    MQTTCommandSystemGlycol = MQTT_COMMAND_SYSTEM_GLYCOL;
    MQTTCommandSystemService = MQTT_COMMAND_SYSTEM_SERVICE;
    MQTTCommandSystemCompCurve = MQTT_COMMAND_SYSTEM_COMPCURVE;
    MQTTCommandSystemActvCtrl = MQTT_COMMAND_SYSTEM_ACTV_CTRL;
    MQTTCommandAC = MQTT_COMMAND_AC;
  }


  void saveConfig() {
    // Read MQTT Portal Values for save to file system
    DEBUG_PRINTLN(F("Copying Portal Values..."));
    strcpy(mqttSettings.deviceId, custom_device_id.getValue());
    strcpy(mqttSettings.hostname, custom_mqtt_server.getValue());
    strcpy(mqttSettings.port, custom_mqtt_port.getValue());
    strcpy(mqttSettings.user, custom_mqtt_user.getValue());
    strcpy(mqttSettings.password, custom_mqtt_pass.getValue());
    strcpy(mqttSettings.baseTopic, custom_mqtt_basetopic.getValue());
    strcpy(mqttSettings.hostname2, custom_mqtt2_server.getValue());
    strcpy(mqttSettings.port2, custom_mqtt2_port.getValue());
    strcpy(mqttSettings.user2, custom_mqtt2_user.getValue());
    strcpy(mqttSettings.password2, custom_mqtt2_pass.getValue());
    strcpy(mqttSettings.baseTopic2, custom_mqtt2_basetopic.getValue());

    DEBUG_PRINT(F("Saving config... "));
    File configFile = LittleFS.open("/config.json", "w");
    if (!configFile) {
      DEBUG_PRINTLN(F("[FAILED] Unable to open config file for writing"));
    } else {
      JsonDocument doc;
      doc[mqttSettings.wm_device_id_identifier] = mqttSettings.deviceId;
      doc[mqttSettings.wm_mqtt_hostname_identifier] = mqttSettings.hostname;
      doc[mqttSettings.wm_mqtt_port_identifier] = mqttSettings.port;
      doc[mqttSettings.wm_mqtt_user_identifier] = mqttSettings.user;
      doc[mqttSettings.wm_mqtt_password_identifier] = mqttSettings.password;
      doc[mqttSettings.wm_mqtt_basetopic_identifier] = mqttSettings.baseTopic;
      doc[mqttSettings.wm_mqtt2_hostname_identifier] = mqttSettings.hostname2;
      doc[mqttSettings.wm_mqtt2_port_identifier] = mqttSettings.port2;
      doc[mqttSettings.wm_mqtt2_user_identifier] = mqttSettings.user2;
      doc[mqttSettings.wm_mqtt2_password_identifier] = mqttSettings.password2;
      doc[mqttSettings.wm_mqtt2_basetopic_identifier] = mqttSettings.baseTopic2;
      doc[unitSettings.unitsize_identifier] = unitSettings.UnitSize;
      doc[unitSettings.glycol_identifier] = unitSettings.GlycolStrength;
      doc[unitSettings.compcurve_identifier] = unitSettings.CompCurve;
      doc[unitSettings.act_ctrl_sc_identifier] = unitSettings.shortcycleprotectionenabled;
      doc[unitSettings.mel_block_identifier] = unitSettings.BlockWriteFromMELCloud;
      doc[unitSettings.remote_ac_identifier] = unitSettings.RemoteTempOn;

      if (serializeJson(doc, configFile) == 0) {
        DEBUG_PRINTLN(F("[FAILED]"));
      } else {
        DEBUG_PRINTLN(F("[DONE]"));
        serializeJson(doc, DEBUGPORT);
        DEBUG_PRINTLN();
#ifndef ARDUINO_WT32_ETH01
        if (WiFi.status() == WL_CONNECTED) {
          DEBUG_PRINTLN(F("Restarting Web Server..."));  // Restart the web server now it's on WiFi
          wifiManager.stopWebPortal();
          wifiManager.startWebPortal();
          MDNS.end();
          MDNS.begin("heatpump");
          MDNS.addService("http", "tcp", 80);
        }
#endif
      }
    }
    configFile.close();
    shouldSaveConfig = false;
  }

  // Callback notifying us of the need to save config
  void saveConfigCallback() {
    saveConfig();
  }

  // Handle Webhook Callbacks
  void handleRoute() {
    if (wifiManager.server->hasArg("z1temp")) {  // Pull Argument room1
      String input = wifiManager.server->arg("z1temp");
      unitSettings.z1_room_temperature = input.toFloat();
      wifiManager.server->send(200, "text/plain", "success");
    } else if (wifiManager.server->hasArg("z1setpoint")) {
      String input = wifiManager.server->arg("z1setpoint");
      unitSettings.z1_room_setpoint = input.toFloat();
      wifiManager.server->send(200, "text/plain", "success");
    } else if (wifiManager.server->hasArg("z2temp")) {
      String input = wifiManager.server->arg("z2temp");
      unitSettings.z2_room_temperature = input.toFloat();
      wifiManager.server->send(200, "text/plain", "success");
    } else if (wifiManager.server->hasArg("z2setpoint")) {
      String input = wifiManager.server->arg("z2setpoint");
      unitSettings.z2_room_setpoint = input.toFloat();
      wifiManager.server->send(200, "text/plain", "success");
    } else if (wifiManager.server->hasArg("actemp")) {
      String input = wifiManager.server->arg("actemp");
      if (unitSettings.ac_remote_room_temp != input.toFloat()) {
        unitSettings.ac_remote_val_change = true;
        unitSettings.ac_remote_room_temp = input.toFloat();
      }
      wifiManager.server->send(200, "text/plain", "success");
    } else {
      wifiManager.server->send(400, "text/plain", "failed");
    }
  }

  // Callback for webhooks
  void bindServerCallback() {
    wifiManager.server->on("/webhook", handleRoute);
  }

  void initializeWifiManager() {
    DEBUG_PRINTLN(F("Starting WiFi Manager"));
    // Reset Wifi settings for testing
    //wifiManager.resetSettings();
    //wifiManager.setDebugOutput(true);
    wifiManager.setTitle("Mitsibushi Bridge");

    // Set or Update the values
    custom_device_id.setValue(mqttSettings.deviceId, deviceId_max_length);
    custom_mqtt_server.setValue(mqttSettings.hostname, hostname_max_length);
    custom_mqtt_port.setValue(mqttSettings.port, port_max_length);
    custom_mqtt_user.setValue(mqttSettings.user, user_max_length);
    custom_mqtt_pass.setValue(mqttSettings.password, password_max_length);
    custom_mqtt_basetopic.setValue(mqttSettings.baseTopic, basetopic_max_length);
    custom_mqtt2_server.setValue(mqttSettings.hostname2, hostname_max_length);
    custom_mqtt2_port.setValue(mqttSettings.port2, port_max_length);
    custom_mqtt2_user.setValue(mqttSettings.user2, user_max_length);
    custom_mqtt2_pass.setValue(mqttSettings.password2, password_max_length);
    custom_mqtt2_basetopic.setValue(mqttSettings.baseTopic2, basetopic_max_length);

    // Add the custom MQTT parameters here
    wifiManager.addParameter(&custom_mqtt_server);
    wifiManager.addParameter(&custom_mqtt_user);
    wifiManager.addParameter(&custom_mqtt_pass);
    wifiManager.addParameter(&custom_mqtt_port);
    wifiManager.addParameter(&custom_mqtt_basetopic);
    wifiManager.addParameter(&custom_mqtt2_server);
    wifiManager.addParameter(&custom_mqtt2_user);
    wifiManager.addParameter(&custom_mqtt2_pass);
    wifiManager.addParameter(&custom_mqtt2_port);
    wifiManager.addParameter(&custom_mqtt2_basetopic);
    wifiManager.addParameter(&custom_device_id);

    //set minimum quality of signal so it ignores AP's under that quality
    //defaults to 8%
    //wifiManager.setMinimumSignalQuality(50);

    snprintf(WiFiHostname, 40, "%s%s", ClientPrefixA2A, mqttSettings.deviceId);
    WiFi.hostname(WiFiHostname);
#ifdef ESP8266                         // Define the Witty ESP8266 Ports
    digitalWrite(Blue_RGB_LED, HIGH);  // Turn the Blue LED On
#endif
    wifiManager.setConfigPortalBlocking(false);             // Non-Blocking portal
    wifiManager.setBreakAfterConfig(true);                  // Saves settings, even if WiFi Fails
    wifiManager.setSaveConfigCallback(saveConfigCallback);  // Set config save callback
    wifiManager.setAPClientCheck(true);                     // Avoid timeout if client connected to softap
    wifiManager.setWebServerCallback(bindServerCallback);   // Callback for the webhook route
    wifiManager.setConnectTimeout(15);                      // Set WiFi Connection Timeout

#ifndef ARDUINO_WT32_ETH01
    wifiManager.setConfigPortalTimeout(600);  // Timeout before launching the config portal (WiFi Only)
    if (!wifiManager.autoConnect("Mitsibushi Bridge AP")) {
      DEBUG_PRINTLN(F("Failed to connect and hit timeout"));
    } else {
      DEBUG_PRINTLN(F("WiFi Connected!"));
    }
#else
  //WiFi.mode(WIFI_OFF);  // Disable WiFi on Ethernet Module (unsupported)
#endif
  }



  void PublishDiscoveryTopics(uint8_t MQTTStream, String BASETOPIC) {

    // Compile Name
    snprintf(MQTTIDs, 40, "%s%s", ClientPrefixA2W, mqttSettings.deviceId);

    // Compile Topics
    String MQTT_DISCOVERY_TOPIC, Buffer_Topic;
    int j;

// -- Entities Configuration JSON -- //
#ifdef ESP8266
    String ChipModel = "ESP8266";
#endif
#ifdef ESP32
    String ChipModel = ESP.getChipModel();
#endif

    String ChipID = mqttSettings.deviceId;

    // JSON Formation
    JsonDocument Config;

    // Publish all the discovery topics
    for (int i = 0; i < discovery_topics; i++) {

      if (i == 0) {  // If the first topic
        Config["device"]["ids"] = MQTTIDs;
        Config["device"]["mf"] = "F1p";
        Config["device"]["model"] = ChipModel;
        Config["device"]["sn"] = ChipID;
        Config["device"]["name"] = "Ecodan ASHP";
#ifdef ARDUINO_WT32_ETH01
        Config["device"]["cu"] = "http://" + ETH.localIP().toString() + ":80";
#else
      Config["device"]["cu"] = "http://" + WiFi.localIP().toString() + ":80";
#endif
        Config["device"]["sw_version"] = FirmwareVersion;
      } else {  // Otherwise post just identifier
        Config["device"]["ids"] = MQTTIDs;
      }

      // Every one has a unique_id and name
      Config["uniq_id"] = String(MQTT_SENSOR_UNIQUE_ID[i]) + ChipID;
      Config["name"] = String(MQTT_SENSOR_NAME[i]);


      // Sensors
      if (i >= 0 && i < 105) {
        Config["stat_t"] = BASETOPIC + String(MQTT_TOPIC[MQTT_TOPIC_POS[i]]);                               // Needs a positioner
        if (MQTT_UNITS_POS[i] > 0) {                                                                        // If there is a unit
          Config["unit_of_meas"] = String(MQTT_SENSOR_UNITS[MQTT_UNITS_POS[i]]);                            // Publish Units
          if (MQTT_UNITS_POS[i] < 8) { Config["dev_cla"] = String(MQTT_DEVICE_CLASS[MQTT_UNITS_POS[i]]); }  // Device classes only exist for some units
          if (MQTT_UNITS_POS[i] != 7) { Config["stat_cla"] = "measurement"; }                               // Only some can be measurement
        }
        Config["val_tpl"] = String(MQTT_SENSOR_VALUE_TEMPLATE[i]);
        Config["icon"] = String(MQTT_MDI_ICONS[i]);

        MQTT_DISCOVERY_TOPIC = String(MQTT_DISCOVERY_TOPICS[0]);
      }

      // Climate
      if (i >= 105 && i < 110) {
        Config["default_entity_id"] = String(MQTT_OBJECT_ID[i - 105]);
        if (i >= 105 && i < 108) {
          Config["curr_temp_t"] = BASETOPIC + String(MQTT_TOPIC[i - 101]);
          Config["curr_temp_tpl"] = String(MQTT_SENSOR_VALUE_TEMPLATE[25]);
          Config["temp_cmd_t"] = BASETOPIC + String(MQTT_TOPIC[i - 93]);
          Config["temp_stat_t"] = BASETOPIC + String(MQTT_TOPIC[i - 101]);
          Config["temp_stat_tpl"] = String(MQTT_SENSOR_VALUE_TEMPLATE[106]);
        } else if (i >= 108 && i < 110) {
          Config["curr_temp_t"] = BASETOPIC + String(MQTT_TOPIC[2]);
          Config["curr_temp_tpl"] = String(MQTT_SENSOR_VALUE_TEMPLATE[6]);
          Config["temp_cmd_t"] = BASETOPIC + String(MQTT_TOPIC[i - 82]);
          Config["temp_stat_t"] = BASETOPIC + String(MQTT_TOPIC[i - 103]);
          Config["temp_stat_tpl"] = String(MQTT_SENSOR_VALUE_TEMPLATE[107]);
        }
        Config["temp_unit"] = String(MQTT_SENSOR_UNITS[9]);
        if (HeatPump.Status.RefrigerantType == 2 && i == 105) {  // If R290 then DHW Max can be 70C
          Config["max_temp"] = MQTT_CLIMATE_MAX[6];
        } else {
          Config["max_temp"] = MQTT_CLIMATE_MAX[i - 105];
        }

        Config["min_temp"] = MQTT_CLIMATE_MIN[i - 105];
        Config["temp_step"] = MQTT_CLIMATE_TEMP_STEP[i - 105];
        Config["precision"] = MQTT_CLIMATE_PRECISION[i - 105];
        Config["init"] = MQTT_CLIMATE_INITAL[i - 105];
        Config["act_t"] = BASETOPIC + String(MQTT_TOPIC[2]);
        Config["act_tpl"] = String(MQTT_CLIMATE_MODE_STATE_TEMPLATE[i - 105]);
        Config["mode_stat_t"] = BASETOPIC + String(MQTT_TOPIC[8]);
        Config["mode_stat_tpl"] = String(MQTT_CLIMATE_STATE_TOPIC[i - 105]);
        if (i == 105) {
          Config["modes"][0] = "heat";
          Config["modes"][1] = "off";
        } else {
          Config["modes"][0] = "heat";
          Config["modes"][1] = "cool";
          Config["modes"][2] = "off";
          Config["mode_cmd_tpl"] = String(MQTT_CLIMATE_MODE[0]);
          Config["mode_cmd_t"] = BASETOPIC + String(MQTT_TOPIC[9]);
        }

        MQTT_DISCOVERY_TOPIC = String(MQTT_DISCOVERY_TOPICS[1]);
      }

      // Switches
      if (i >= 110 && i < 122) {
        Config["stat_t"] = BASETOPIC + String(MQTT_TOPIC[MQTT_SWITCH_STATE_POS[i - 110]]);
        Config["val_tpl"] = String(MQTT_SENSOR_VALUE_TEMPLATE[i - 2]);
        if (i == 121) {
          Config["cmd_t"] = BASETOPIC + String(MQTT_TOPIC[33]);
        } else {
          Config["cmd_t"] = BASETOPIC + String(MQTT_TOPIC[i - 95]);
        }

        if (i == 111) {
          Config["state_on"] = "On";
          Config["state_off"] = "Standby";
          Config["payload_on"] = "On";
          Config["payload_off"] = "Standby";
        } else if (i == 121) {
          Config["state_on"] = true;
          Config["state_off"] = false;
          Config["payload_on"] = "997";
          Config["payload_off"] = "996";
        } else {
          Config["state_on"] = ITEM_ON;
          Config["state_off"] = ITEM_OFF;
          Config["payload_on"] = ITEM_ON;
          Config["payload_off"] = ITEM_OFF;
        }
        Config["icon"] = String(MQTT_MDI_ICONS[i]);

        MQTT_DISCOVERY_TOPIC = String(MQTT_DISCOVERY_TOPICS[2]);
      }


      // Selects
      if (i >= 122 && i < 127) {
        Config["cmd_t"] = BASETOPIC + String(MQTT_TOPIC[i - 94]);
        Config["stat_t"] = BASETOPIC + String(MQTT_TOPIC[i - 118]);
        Config["val_tpl"] = String(MQTT_SELECT_VALUE_TEMPLATE[i - 122]);
        if (i == 122) {  // DHW Modes
          Config["options"][0] = HotWaterControlModeString[0];
          Config["options"][1] = HotWaterControlModeString[1];
        } else if (i == 125) {  // Unit Sizes - for some reason it doesn't like doing this from PROGMEM in a loop on the 8266
          Config["stat_t"] = BASETOPIC + String(MQTT_TOPIC[1]);
          Config["options"][0] = "4.0";
          Config["options"][1] = "5.0";
          Config["options"][2] = "6.0";
          Config["options"][3] = "7.5";
          Config["options"][4] = "8.0";
          Config["options"][5] = "8.5";
          Config["options"][6] = "10.0";
          Config["options"][7] = "11.2";
          Config["options"][8] = "12.0";
          Config["options"][9] = "14.0";
          Config["options"][10] = "23.0";
        } else if (i == 126) {  // Glycol Strengths
          Config["stat_t"] = BASETOPIC + String(MQTT_TOPIC[1]);
          Config["options"][0] = "0%";
          Config["options"][1] = "10%";
          Config["options"][2] = "15%";
          Config["options"][3] = "20%";
          Config["options"][4] = "25%";
          Config["options"][5] = "30%";
        } else {  // Zone Options
          Config["options"][0] = "Heating Temperature";
          Config["options"][1] = "Heating Flow";
          Config["options"][2] = "Heating Compensation";
          Config["options"][3] = "Cooling Temperature";
          Config["options"][4] = "Cooling Flow";
          Config["options"][5] = "Dry Up";
          Config["options"][6] = "Cooling Compensation";
        }
        MQTT_DISCOVERY_TOPIC = String(MQTT_DISCOVERY_TOPICS[4]);
      }

#ifdef ESP32
      // Update only on ESP32
      if (i == 127) {
        Config["stat_t"] = BASETOPIC + String(MQTT_TOPIC[34]);
        Config["dev_cla"] = String(MQTT_DEVICE_CLASS[8]);
        Config["l_ver_t"] = "{{ value_json.latest_version }}";
        Config["cmd_t"] = BASETOPIC + String(MQTT_TOPIC[33]);
        Config["pl_inst"] = "995";
        Config["rel_u"] = "https://github.com/F1p/Mitsubishi-CN105-Protocol-Decode/releases/latest";
        MQTT_DISCOVERY_TOPIC = String(MQTT_DISCOVERY_TOPICS[6]);
      }
#endif

      // Add Availability Topics
      if (i >= 106) {
        if (i >= 114 && i < 119) {  // Server Control Mode Interlocks
          Config["avty"]["t"] = BASETOPIC + String(MQTT_TOPIC[8]);
          Config["avty"]["val_tpl"] = String(MQTT_SENSOR_VALUE_TEMPLATE[111]);
          Config["avty"]["pl_avail"] = ITEM_ON;
          Config["avty"]["pl_not_avail"] = ITEM_OFF;
        } else if (i >= 108 && i < 110) {  // Flow Op Mode Interlocks on Climate & Number
          Config["avty"]["t"] = BASETOPIC + String(MQTT_TOPIC[i - 103]);
          Config["avty"]["val_tpl"] = String(MQTT_NUMBER_AVAIL_TEMPLATE[0]);
        } else if (i == 121) {  // Interlock MELCloud Read Only with Adapter Status Not Disconnected
          Config["avty"]["t"] = BASETOPIC + String(MQTT_TOPIC[1]);
          Config["avty"]["val_tpl"] = String(MQTT_NUMBER_AVAIL_TEMPLATE[2]);
        } else if (i == 124) {  // Interlock Zone2 Mode with Complex 2 Zone only
          Config["avty"]["t"] = BASETOPIC + String(MQTT_TOPIC[9]);
          Config["avty"]["val_tpl"] = String(MQTT_NUMBER_AVAIL_TEMPLATE[1]);
        } else {  // Everything else LWT
          Config["avty"]["t"] = BASETOPIC + String(MQTT_TOPIC[0]);
        }
      }

      char Buffer_Payload[2048];
      size_t buf_size = serializeJson(Config, Buffer_Payload);
      Buffer_Topic = MQTT_DISCOVERY_TOPIC + ChipID + String(MQTT_DISCOVERY_OBJ_ID[i]) + String(MQTT_DISCOVERY_TOPICS[5]);

      if (MQTTStream == 1) {
        MQTTClient1.publish(Buffer_Topic.c_str(), (uint8_t*)&Buffer_Payload, buf_size, true);
      } else if (MQTTStream == 2) {
        MQTTClient2.publish(Buffer_Topic.c_str(), (uint8_t*)&Buffer_Payload, buf_size, true);
      }

      MQTT_DISCOVERY_TOPIC = "";  // Clear everything ready for next loop to save RAM
      Buffer_Topic = "";
      Config.clear();
    }

    // Generate Publish Message
    DEBUG_PRINTLN("A2W Discovery Published!");
  }


  void PublishA2ADiscoveryTopics(uint8_t MQTTStream, String BASETOPIC) {

    snprintf(MQTTIDs, 40, "%s%s", ClientPrefixA2A, mqttSettings.deviceId);

    // Compile Topics
    String MQTT_DISCOVERY_TOPIC, Buffer_Topic;
    int j;

// -- Entities Configuration JSON -- //
#ifdef ESP8266
    String ChipModel = "ESP8266";
#endif
#ifdef ESP32
    String ChipModel = ESP.getChipModel();
#endif

    String ChipID = mqttSettings.deviceId;

    // JSON Formation
    JsonDocument Config;

    // Publish all the discovery topics
    for (int i = 0; i < 29; i++) {

      if (i == 0) {  // If the first topic
        Config["dev"]["ids"] = MQTTIDs;
        Config["dev"]["mf"] = "F1p";
        Config["dev"]["model"] = ChipModel;
        Config["dev"]["sn"] = ChipID;
        Config["dev"]["name"] = "Mitsibushi A2A ASHP";
#ifdef ARDUINO_WT32_ETH01
        Config["dev"]["cu"] = "http://" + ETH.localIP().toString() + ":80";
#else
      Config["dev"]["cu"] = "http://" + WiFi.localIP().toString() + ":80";
#endif
        Config["dev"]["sw_version"] = FirmwareVersion;
      } else {  // Otherwise post just identifier
        Config["dev"]["ids"] = MQTTIDs;
      }

      // Every one has a unique_id and name
      Config["uniq_id"] = String(MQTT_DISCOVERY_OBJ_ID[i]) + ChipID;
      Config["name"] = String(MQTT_AC_SENSOR_NAME[i]);


      // Sensors (Generic)
      if (i >= 0 && i < 3) {
        // Status, Firmware Update, WiFi Signal

        Config["stat_t"] = BASETOPIC + String(MQTT_TOPIC[MQTT_TOPIC_POS[i]]);                               // Needs a positioner
        if (MQTT_UNITS_POS[i] > 0) {                                                                        // If there is a unit
          Config["unit_of_meas"] = String(MQTT_SENSOR_UNITS[MQTT_UNITS_POS[i]]);                            // Publish Units
          if (MQTT_UNITS_POS[i] < 8) { Config["dev_cla"] = String(MQTT_DEVICE_CLASS[MQTT_UNITS_POS[i]]); }  // Device classes only exist for some units
          if (MQTT_UNITS_POS[i] != 7) { Config["stat_cla"] = "measurement"; }                               // Only some can be measurement
        }
        Config["val_tpl"] = String(MQTT_AC_SENSOR_VALUE_TEMPLATE[i]);
        Config["icon"] = String(MQTT_MDI_ICONS_AC[i]);

        MQTT_DISCOVERY_TOPIC = String(MQTT_DISCOVERY_TOPICS[0]);
      }
      if (i >= 3 && i < 24) {
        // Compressor Freq, isee, Timermode, onMinutesSet, onMinutesRemaining, offMinutesSet, offMinutesRemaining, Room Temperature

        Config["stat_t"] = BASETOPIC + String("/Status/AC");      // Needs a positioner
        if (i == 3) {                                             // If there is a unit
          Config["unit_of_meas"] = String(MQTT_SENSOR_UNITS[4]);  // Publish Units
        } else if (i == 10 || i == 18) {
          Config["unit_of_meas"] = String(MQTT_SENSOR_UNITS[2]);  // Publish Units
        } else if (i == 13) {
          Config["unit_of_meas"] = String(MQTT_SENSOR_UNITS[3]);  // Publish Units
        } else if (i == 14) {
          Config["unit_of_meas"] = String(MQTT_SENSOR_UNITS[7]);  // Publish Units
        }

        Config["val_tpl"] = String(MQTT_AC_SENSOR_VALUE_TEMPLATE[i]);
        Config["icon"] = String(MQTT_MDI_ICONS_AC[i]);


        MQTT_DISCOVERY_TOPIC = String(MQTT_DISCOVERY_TOPICS[0]);
      }


      // Main Climate
      if (i == 24) {
        Config["default_entity_id"] = String(MQTT_OBJECT_ID[1]);
        Config["curr_temp_t"] = BASETOPIC + String("/Status/AC");  // Shortened from curr_temp_topic
        Config["curr_temp_tpl"] = "{{ value_json.RoomTemp }}";

        Config["temp_cmd_t"] = BASETOPIC + String("/Command/AC");  // Shortened from temperature_command_topic
        Config["temp_cmd_tpl"] = "{\"SetTempSetpoint\": {{ value }}}";
        Config["temp_stat_t"] = BASETOPIC + String("/Status/AC");  // Shortened from temperature_state_topic
        Config["temp_stat_tpl"] = "{% if (value_json is defined and value_json.SetpointTemp is defined) %}{% if (value_json.SetpointTemp|int >= 16 and value_json.SetpointTemp|int <= 31) %}{{ value_json.SetpointTemp }}{% else %}22{% endif %}{% else %}22{% endif %}";

        Config["temp_unit"] = String(MQTT_SENSOR_UNITS[9]);
        Config["max_temp"] = 31;
        Config["min_temp"] = 16;
        Config["temp_step"] = 1;
        Config["precision"] = 1;
        Config["init"] = 16;

        Config["act_t"] = BASETOPIC + String("/Status/AC");  // Shortened from action_topic
        Config["act_tpl"] = String("{{ value_json.action }}");

        Config["modes"][0] = "auto";
        Config["modes"][1] = "cool";
        Config["modes"][2] = "dry";
        Config["modes"][3] = "heat";
        Config["modes"][4] = "fan_only";
        Config["modes"][5] = "off";
        Config["mode_cmd_t"] = BASETOPIC + String("/Command/AC");  // Shortened from mode_command_topic
        Config["mode_cmd_tpl"] = "{\"SetMode\": \"{{ value }}\"}";
        Config["mode_stat_t"] = BASETOPIC + String("/Status/AC");  // Shortened from mode_state_topic
        Config["mode_stat_tpl"] = String("{{ value_json.mode }}");

        Config["swing_modes"][0] = "AUTO";
        Config["swing_modes"][1] = "1";
        Config["swing_modes"][2] = "2";
        Config["swing_modes"][3] = "3";
        Config["swing_modes"][4] = "4";
        Config["swing_modes"][5] = "5";
        Config["swing_modes"][6] = "SWING";
        Config["swing_mode_cmd_t"] = BASETOPIC + String("/Command/AC");  // Shortened from swing_mode_command_topic
        Config["swing_mode_cmd_tpl"] = "{\"SetVane\": \"{{ value }}\"}";
        Config["swing_mode_stat_t"] = BASETOPIC + String("/Status/AC");  // Shortened from swing_mode_state_topic
        Config["swing_mode_stat_tpl"] = String("{{ value_json.Vane }}");

        if (AC.Status.SupportsHozVane) {  // Optional Support
          Config["swing_h_modes"][0] = "<<";
          Config["swing_h_modes"][1] = "<";
          Config["swing_h_modes"][2] = "|";
          Config["swing_h_modes"][3] = ">";
          Config["swing_h_modes"][4] = ">>";
          Config["swing_h_modes"][5] = "<>";
          Config["swing_h_modes"][6] = "SWING";
          Config["swing_h_mode_cmd_t"] = BASETOPIC + String("/Command/AC");  // Shortened from swing_mode_command_topic
          Config["swing_h_mode_cmd_tpl"] = "{\"SetWideVane\": \"{{ value }}\"}";
          Config["swing_h_mode_stat_t"] = BASETOPIC + String("/Status/AC");  // Shortened from swing_mode_state_topic
          Config["swing_h_mode_stat_tpl"] = String("{{ value_json.wideVane }}");
        }

        Config["fan_modes"][0] = "AUTO";
        Config["fan_modes"][1] = "QUIET";
        Config["fan_modes"][2] = "1";
        Config["fan_modes"][3] = "2";
        Config["fan_modes"][4] = "3";
        Config["fan_modes"][5] = "4";
        Config["fan_mode_cmd_t"] = BASETOPIC + String("/Command/AC");  // Shortened from fan_mode_command_topic
        Config["fan_mode_cmd_tpl"] = "{\"SetFanSpeed\": \"{{ value }}\"}";
        Config["fan_mode_stat_t"] = BASETOPIC + String("/Status/AC");  // Shortened from fan_mode_state_topic
        Config["fan_mode_stat_tpl"] = String("{{ value_json.Fan if (value_json is defined and value_json.Fan is defined and value_json.Fan|length) else 'AUTO' }}");

        MQTT_DISCOVERY_TOPIC = String(MQTT_DISCOVERY_TOPICS[1]);
      }

      // Switches
      if (i == 25 || i == 27) {

        if (i == 25) {  // Power
          Config["stat_t"] = BASETOPIC + String("/Status/AC");
          Config["val_tpl"] = String("{{ value_json.power }}");
          Config["cmd_t"] = BASETOPIC + String("/Command/AC");
          Config["cmd_tpl"] = "{\"systempower\":{{ value|lower }}}";
          Config["state_on"] = "ON";
          Config["state_off"] = "OFF";
          Config["payload_on"] = true;
          Config["payload_off"] = false;
          Config["icon"] = String(MQTT_MDI_ICONS_AC[23]);
        }
        // Remote Temperature
        if (i == 27) {
          Config["stat_t"] = BASETOPIC + String("/Status/AC");
          Config["val_tpl"] = String("{{ value_json.RemoteTempOn }}");
          Config["cmd_t"] = BASETOPIC + String("/Command/AC");
          Config["cmd_tpl"] = "{\"RemoteTempOn\":{{ value|lower }}}";
          Config["state_on"] = true;
          Config["state_off"] = false;
          Config["payload_on"] = true;
          Config["payload_off"] = false;
          Config["icon"] = String(MQTT_MDI_ICONS_AC[10]);
        }

        MQTT_DISCOVERY_TOPIC = String(MQTT_DISCOVERY_TOPICS[2]);
      }

      // Number (Remote Temp Input)
      if (i == 28) {
        Config["min"] = 0;
        Config["max"] = 50;
        Config["mode"] = "box";
        Config["platform"] = "number";
        Config["step"] = 0.1;
        Config["unit_of_measurement"] = "°C";
        Config["cmd_t"] = BASETOPIC + String("/Command/AC");  // Shortened from temperature_command_topic
        Config["cmd_tpl"] = "{\"SetRemoteTemp\": {{ value }}}";
        Config["stat_t"] = BASETOPIC + String("/Status/AC");
        Config["val_tpl"] = String("{{ value_json.RemoteTemp }}");

        Config["icon"] = String(MQTT_MDI_ICONS[i]);
        MQTT_DISCOVERY_TOPIC = String(MQTT_DISCOVERY_TOPICS[7]);
      }


#ifdef ESP32
      // Update
      if (i == 26) {
        Config["stat_t"] = BASETOPIC + String(MQTT_TOPIC[34]);
        Config["dev_cla"] = String(MQTT_DEVICE_CLASS[8]);
        Config["l_ver_t"] = "{{ value_json.latest_version }}";
        Config["cmd_t"] = BASETOPIC + String(MQTT_TOPIC[33]);
        Config["pl_inst"] = "995";
        Config["rel_u"] = "https://github.com/F1p/Mitsubishi-CN105-Protocol-Decode/releases/latest";
        MQTT_DISCOVERY_TOPIC = String(MQTT_DISCOVERY_TOPICS[6]);
      }
#endif

      // Number Input


      // Add Availability Topics
      if (i >= 24) {
        if (i == 28) {  // Custom linked with Remote Thermostat Interlock
          Config["avty"]["t"] = BASETOPIC + String("/Status/AC");
          Config["avty"]["val_tpl"] = String("{{ value_json.RemoteTempOn }}");
          Config["avty"]["pl_avail"] = true;
          Config["avty"]["pl_not_avail"] = false;
        } else {
          Config["avty"]["t"] = BASETOPIC + String(MQTT_TOPIC[0]);
        }
      }

      char Buffer_Payload[4096];
      size_t buf_size = serializeJson(Config, Buffer_Payload);
      Buffer_Topic = MQTT_DISCOVERY_TOPIC + ChipID + String(MQTT_DISCOVERY_OBJ_ID[i]) + String(MQTT_DISCOVERY_TOPICS[5]);

      if (MQTTStream == 1) {
        MQTTClient1.publish(Buffer_Topic.c_str(), (uint8_t*)&Buffer_Payload, buf_size, true);
      } else if (MQTTStream == 2) {
        MQTTClient2.publish(Buffer_Topic.c_str(), (uint8_t*)&Buffer_Payload, buf_size, true);
      }

      MQTT_DISCOVERY_TOPIC = "";  // Clear everything ready for next loop to save RAM
      Buffer_Topic = "";
      Config.clear();
    }

    // Generate Publish Message
    DEBUG_PRINTLN("A2A Discovery Published!");
  }

  void initializeMQTTClient1() {
    DEBUG_PRINT(F("Attempting MQTT 1 connection to: "));
    DEBUG_PRINT(mqttSettings.hostname);
    DEBUG_PRINT(F(":"));
    DEBUG_PRINTLN(mqttSettings.port);
    MQTTClient1.setServer(mqttSettings.hostname, atoi(mqttSettings.port));
  }

  void MQTTonConnect(void) {
    DEBUG_PRINTLN(F("MQTT ON CONNECT"));
    MQTTClient1.publish(MQTT_LWT.c_str(), "online");
    delay(10);

    MQTTClient1.subscribe(MQTTCommandZone1FlowSetpoint.c_str());
    MQTTClient1.subscribe(MQTTCommandZone1NoModeSetpoint.c_str());
    MQTTClient1.subscribe(MQTTCommandZone1ProhibitHeating.c_str());
    MQTTClient1.subscribe(MQTTCommandZone1ProhibitCooling.c_str());
    MQTTClient1.subscribe(MQTTCommandZone1HeatingMode.c_str());
    MQTTClient1.subscribe(MQTTCommandZone2FlowSetpoint.c_str());
    MQTTClient1.subscribe(MQTTCommandZone2NoModeSetpoint.c_str());
    MQTTClient1.subscribe(MQTTCommandZone2ProhibitHeating.c_str());
    MQTTClient1.subscribe(MQTTCommandZone2ProhibitCooling.c_str());
    MQTTClient1.subscribe(MQTTCommandZone2HeatingMode.c_str());
    MQTTClient1.subscribe(MQTTCommandHotwaterMode.c_str());
    MQTTClient1.subscribe(MQTTCommandHotwaterSetpoint.c_str());
    MQTTClient1.subscribe(MQTTCommandHotwaterBoost.c_str());
    MQTTClient1.subscribe(MQTTCommandHotwaterNormalBoost.c_str());
    MQTTClient1.subscribe(MQTTCommandHotwaterProhibit.c_str());
    MQTTClient1.subscribe(MQTTCommandSystemHolidayMode.c_str());
    MQTTClient1.subscribe(MQTTCommandSystemPower.c_str());
    MQTTClient1.subscribe(MQTTCommandSystemSvrMode.c_str());
    MQTTClient1.subscribe(MQTTCommandSystemUnitSize.c_str());
    MQTTClient1.subscribe(MQTTCommandSystemGlycol.c_str());
    MQTTClient1.subscribe(MQTTCommandSystemService.c_str());
    MQTTClient1.subscribe(MQTTCommandSystemCompCurve.c_str());
    MQTTClient1.subscribe(MQTTCommandSystemActvCtrl.c_str());
    MQTTClient1.subscribe(MQTTCommandAC.c_str());

    delay(10);
    if (HeatPump.PrevConnected) {
      PublishDiscoveryTopics(1, MQTT_BASETOPIC);
    } else if (AC.PrevConnected) {
      PublishA2ADiscoveryTopics(1, MQTT_BASETOPIC);
    }


#ifdef ESP8266                       // Define the Witty ESP8266 Ports
    analogWrite(Green_RGB_LED, 30);  // Green LED on, 25% brightness
    digitalWrite(Red_RGB_LED, LOW);  // Turn the Red LED Off
#endif
#ifdef ARDUINO_M5STACK_ATOMS3       // Define the M5Stack LED
    myLED.setPixel(0, L_GREEN, 1);  // set the LED colour and show it
    myLED.brightness(LED_BRIGHT, 1);
#endif
  }


  uint8_t MQTTReconnect() {
    if (MQTTClient1.connected()) {
      return 1;
    }
#ifdef ARDUINO_WT32_ETH01
    else if (strcmp(mqttSettings.hostname, "IPorDNS") != 0 && strcmp(mqttSettings.hostname, "") != 0) {  // Do not block MQTT attempt on Ethernet
#else
  else if (strcmp(mqttSettings.hostname, "IPorDNS") != 0 && strcmp(mqttSettings.hostname, "") != 0 && WiFi.status() == WL_CONNECTED) {  // WiFi should be active to attempt connections (as MQTT connect is blocking)
#endif
      initializeMQTTClient1();
      //DEBUG_PRINT(F("With Client ID: "));
      //DEBUG_PRINT(mqttSettings.deviceId);
      //DEBUG_PRINT(F(", Username: "));
      //DEBUG_PRINT(mqttSettings.user);
      //DEBUG_PRINT(F(" and Password: "));
      //DEBUG_PRINTLN(mqttSettings.password);

      if (MQTTClient1.connect(mqttSettings.deviceId, mqttSettings.user, mqttSettings.password, MQTT_LWT.c_str(), 0, true, "offline")) {
        DEBUG_PRINTLN(F("MQTT Server Connected"));
        MQTTonConnect();
#ifdef ESP8266                              // Define the Witty ESP8266 Ports
        digitalWrite(Red_RGB_LED, LOW);     // Turn off the Red LED
        digitalWrite(Green_RGB_LED, HIGH);  // Flash the Green LED
        delay(10);
        analogWrite(Green_RGB_LED, 30);  // Green LED on, 25% brightness
#endif
        return 1;
      } else {
#ifdef ARDUINO_M5STACK_ATOMS3                        // Define the M5Stack LED
        if (!wifiManager.getConfigPortalActive()) {  // Not got config portal open, change to orange:
          myLED.setPixel(0, L_ORANGE, 1);            // set the LED colour and show it
        }
#endif
        switch (MQTTClient1.state()) {
          case -4:
            DEBUG_PRINTLN(F("MQTT_CONNECTION_TIMEOUT"));
            break;
          case -3:
            DEBUG_PRINTLN(F("MQTT_CONNECTION_LOST"));
            break;
          case -2:
            DEBUG_PRINTLN(F("MQTT_CONNECT_FAILED"));
            break;
          case -1:
            DEBUG_PRINTLN(F("MQTT_DISCONNECTED"));
            break;
          case 0:
            DEBUG_PRINTLN(F("MQTT_CONNECTED"));
            break;
          case 1:
            DEBUG_PRINTLN(F("MQTT_CONNECT_BAD_PROTOCOL"));
            break;
          case 2:
            DEBUG_PRINTLN(F("MQTT_CONNECT_BAD_CLIENT_ID"));
            break;
          case 3:
            DEBUG_PRINTLN(F("MQTT_CONNECT_UNAVAILABLE"));
            break;
          case 4:
            DEBUG_PRINTLN(F("MQTT_CONNECT_BAD_CREDENTIALS"));
            break;
          case 5:
            DEBUG_PRINTLN(F("MQTT_CONNECT_UNAUTHORIZED"));
            break;
        }
        return 0;
      }
      return 0;
    } else {
      DEBUG_PRINTLN(F("Primary MQTT Not Set or WiFi not connected"));
      return 0;
    }
  }


  void handleMQTTState() {
    if (!MQTTClient1.connected()) {
#ifdef ARDUINO_M5STACK_ATOMS3                      // Define the M5Stack LED
      if (!wifiManager.getConfigPortalActive()) {  // Not got config portal open, change to orange:
        myLED.setPixel(0, L_ORANGE, 1);            // set the LED colour and show it
      }
#endif
#ifdef ESP8266                          // Define the Witty ESP8266 Ports
      analogWrite(Green_RGB_LED, 30);   // Green LED on, 25% brightness
      digitalWrite(Red_RGB_LED, HIGH);  // Add the Red LED to the Green LED = Orange
#endif
      MQTTReconnect();
      delay(10);
    }
  }


  void RecalculateMQTT2Topics() {
    // The base topic may change via WiFi Manager
    MQTT_2_LWT = MQTT_2_BASETOPIC + "/LWT";
    MQTT_2_STATUS = MQTT_2_BASETOPIC + "/Status";
    MQTT_2_COMMAND = MQTT_2_BASETOPIC + "/Command";

    MQTT_2_STATUS_ZONE1 = MQTT_2_STATUS + "/Zone1";
    MQTT_2_STATUS_ZONE2 = MQTT_2_STATUS + "/Zone2";
    MQTT_2_STATUS_HOTWATER = MQTT_2_STATUS + "/HotWater";
    MQTT_2_STATUS_SYSTEM = MQTT_2_STATUS + "/System";
    MQTT_2_STATUS_CONFIGURATION = MQTT_2_STATUS + "/Configuration";
    MQTT_2_STATUS_ADVANCED = MQTT_2_STATUS + "/Advanced";
    MQTT_2_STATUS_ADVANCED_TWO = MQTT_2_STATUS + "/AdvancedTwo";
    MQTT_2_STATUS_ENERGY = MQTT_2_STATUS + "/Energy";
    MQTT_2_STATUS_WIFISTATUS = MQTT_2_STATUS + "/WiFiStatus";
    MQTT_2_STATUS_CURVE = MQTT_2_STATUS + "/CompCurve";
    MQTT_2_STATUS_ACTV_CTRL = MQTT_2_STATUS + "/ActiveControl";
    MQTT_2_STATUS_AC = MQTT_2_STATUS + "/AC";
    MQTT_2_STATUS_WIFISTATUS_UPDATE = MQTT_2_STATUS_WIFISTATUS + "/Update";

    MQTT_2_COMMAND_ZONE1 = MQTT_2_COMMAND + "/Zone1";
    MQTT_2_COMMAND_ZONE2 = MQTT_2_COMMAND + "/Zone2";
    MQTT_2_COMMAND_HOTWATER = MQTT_2_COMMAND + "/HotWater";
    MQTT_2_COMMAND_SYSTEM = MQTT_2_COMMAND + "/System";
    MQTT_2_COMMAND_AC = MQTT_2_COMMAND + "/AC";

    MQTT_2_COMMAND_ZONE1_FLOW_SETPOINT = MQTT_2_COMMAND_ZONE1 + "/FlowSetpoint";
    MQTT_2_COMMAND_ZONE1_NOMODE_SETPOINT = MQTT_2_COMMAND_ZONE1 + "/ThermostatSetpoint";
    MQTT_2_COMMAND_ZONE1_HEAT_PROHIBIT = MQTT_2_COMMAND_ZONE1 + "/ProhibitHeating";
    MQTT_2_COMMAND_ZONE1_COOL_PROHIBIT = MQTT_2_COMMAND_ZONE1 + "/ProhibitCooling";
    MQTT_2_COMMAND_ZONE1_HEATINGMODE = MQTT_2_COMMAND_ZONE1 + "/HeatingMode";

    MQTT_2_COMMAND_ZONE2_FLOW_SETPOINT = MQTT_2_COMMAND_ZONE2 + "/FlowSetpoint";
    MQTT_2_COMMAND_ZONE2_NOMODE_SETPOINT = MQTT_2_COMMAND_ZONE2 + "/ThermostatSetpoint";
    MQTT_2_COMMAND_ZONE2_HEAT_PROHIBIT = MQTT_2_COMMAND_ZONE2 + "/ProhibitHeating";
    MQTT_2_COMMAND_ZONE2_COOL_PROHIBIT = MQTT_2_COMMAND_ZONE2 + "/ProhibitCooling";
    MQTT_2_COMMAND_ZONE2_HEATINGMODE = MQTT_2_COMMAND_ZONE2 + "/HeatingMode";

    MQTT_2_COMMAND_HOTWATER_MODE = MQTT_2_COMMAND_HOTWATER + "/Mode";
    MQTT_2_COMMAND_HOTWATER_SETPOINT = MQTT_2_COMMAND_HOTWATER + "/Setpoint";
    MQTT_2_COMMAND_HOTWATER_BOOST = MQTT_2_COMMAND_HOTWATER + "/Boost";
    MQTT_2_COMMAND_HOTWATER_NORM_BOOST = MQTT_2_COMMAND_HOTWATER + "/NormalBoost";
    MQTT_2_COMMAND_HOTWATER_PROHIBIT = MQTT_2_COMMAND_HOTWATER + "/Prohibit";

    MQTT_2_COMMAND_SYSTEM_HOLIDAYMODE = MQTT_2_COMMAND_SYSTEM + "/HolidayMode";
    MQTT_2_COMMAND_SYSTEM_SVRMODE = MQTT_2_COMMAND_SYSTEM + "/SvrControlMode";
    MQTT_2_COMMAND_SYSTEM_POWER = MQTT_2_COMMAND_SYSTEM + "/Power";
    MQTT_2_COMMAND_SYSTEM_UNITSIZE = MQTT_2_COMMAND_SYSTEM + "/UnitSize";
    MQTT_2_COMMAND_SYSTEM_GLYCOL = MQTT_2_COMMAND_SYSTEM + "/Glycol";
    MQTT_2_COMMAND_SYSTEM_SERVICE = MQTT_2_COMMAND_SYSTEM + "/Svc";
    MQTT_2_COMMAND_SYSTEM_COMPCURVE = MQTT_2_COMMAND_SYSTEM + "/CompCurve";
    MQTT_2_COMMAND_SYSTEM_ACTV_CTRL = MQTT_2_COMMAND_SYSTEM + "/ActiveControl";

    MQTTCommand2Zone1FlowSetpoint = MQTT_2_COMMAND_ZONE1_FLOW_SETPOINT;
    MQTTCommand2Zone1NoModeSetpoint = MQTT_2_COMMAND_ZONE1_NOMODE_SETPOINT;
    MQTTCommand2Zone1ProhibitHeating = MQTT_2_COMMAND_ZONE1_HEAT_PROHIBIT;
    MQTTCommand2Zone1ProhibitCooling = MQTT_2_COMMAND_ZONE1_COOL_PROHIBIT;
    MQTTCommand2Zone1HeatingMode = MQTT_2_COMMAND_ZONE1_HEATINGMODE;

    MQTTCommand2Zone2FlowSetpoint = MQTT_2_COMMAND_ZONE2_FLOW_SETPOINT;
    MQTTCommand2Zone2NoModeSetpoint = MQTT_2_COMMAND_ZONE2_NOMODE_SETPOINT;
    MQTTCommand2Zone2ProhibitHeating = MQTT_2_COMMAND_ZONE2_HEAT_PROHIBIT;
    MQTTCommand2Zone2ProhibitCooling = MQTT_2_COMMAND_ZONE2_COOL_PROHIBIT;
    MQTTCommand2Zone2HeatingMode = MQTT_2_COMMAND_ZONE2_HEATINGMODE;

    MQTTCommand2HotwaterMode = MQTT_2_COMMAND_HOTWATER_MODE;
    MQTTCommand2HotwaterSetpoint = MQTT_2_COMMAND_HOTWATER_SETPOINT;
    MQTTCommand2HotwaterBoost = MQTT_2_COMMAND_HOTWATER_BOOST;
    MQTTCommand2HotwaterNormalBoost = MQTT_2_COMMAND_HOTWATER_NORM_BOOST;
    MQTTCommand2HotwaterProhibit = MQTT_2_COMMAND_HOTWATER_PROHIBIT;

    MQTTCommand2SystemHolidayMode = MQTT_2_COMMAND_SYSTEM_HOLIDAYMODE;
    MQTTCommand2SystemSvrMode = MQTT_2_COMMAND_SYSTEM_SVRMODE;
    MQTTCommand2SystemPower = MQTT_2_COMMAND_SYSTEM_POWER;
    MQTTCommand2SystemUnitSize = MQTT_2_COMMAND_SYSTEM_UNITSIZE;
    MQTTCommand2SystemGlycol = MQTT_2_COMMAND_SYSTEM_GLYCOL;
    MQTTCommand2SystemService = MQTT_2_COMMAND_SYSTEM_SERVICE;
    MQTTCommand2SystemCompCurve = MQTT_2_COMMAND_SYSTEM_COMPCURVE;
    MQTTCommand2SystemActvCtrl = MQTT_2_COMMAND_SYSTEM_ACTV_CTRL;
    MQTTCommand2AC = MQTT_2_COMMAND_AC;
  }





  void initializeMQTTClient2() {
    DEBUG_PRINT(F("Attempting MQTT 2 connection to: "));
    DEBUG_PRINT(mqttSettings.hostname2);
    DEBUG_PRINT(F(":"));
    DEBUG_PRINTLN(mqttSettings.port2);
    MQTTClient2.setServer(mqttSettings.hostname2, atoi(mqttSettings.port2));
  }



  void MQTT2onConnect(void) {
    DEBUG_PRINTLN(F("MQTT 2 ON CONNECT"));
    MQTTClient2.publish(MQTT_2_LWT.c_str(), "online");
    delay(10);

    MQTTClient2.subscribe(MQTTCommand2Zone1FlowSetpoint.c_str());
    MQTTClient2.subscribe(MQTTCommand2Zone1NoModeSetpoint.c_str());
    MQTTClient2.subscribe(MQTTCommand2Zone1ProhibitHeating.c_str());
    MQTTClient2.subscribe(MQTTCommand2Zone1ProhibitCooling.c_str());
    MQTTClient2.subscribe(MQTTCommand2Zone1HeatingMode.c_str());
    MQTTClient2.subscribe(MQTTCommand2Zone2FlowSetpoint.c_str());
    MQTTClient2.subscribe(MQTTCommand2Zone2NoModeSetpoint.c_str());
    MQTTClient2.subscribe(MQTTCommand2Zone2ProhibitHeating.c_str());
    MQTTClient2.subscribe(MQTTCommand2Zone2ProhibitCooling.c_str());
    MQTTClient2.subscribe(MQTTCommand2Zone2HeatingMode.c_str());
    MQTTClient2.subscribe(MQTTCommand2SystemHolidayMode.c_str());
    MQTTClient2.subscribe(MQTTCommand2HotwaterMode.c_str());
    MQTTClient2.subscribe(MQTTCommand2HotwaterSetpoint.c_str());
    MQTTClient2.subscribe(MQTTCommand2HotwaterBoost.c_str());
    MQTTClient2.subscribe(MQTTCommand2HotwaterNormalBoost.c_str());
    MQTTClient2.subscribe(MQTTCommand2HotwaterProhibit.c_str());
    MQTTClient2.subscribe(MQTTCommand2SystemPower.c_str());
    MQTTClient2.subscribe(MQTTCommand2SystemSvrMode.c_str());
    MQTTClient2.subscribe(MQTTCommand2SystemUnitSize.c_str());
    MQTTClient2.subscribe(MQTTCommand2SystemGlycol.c_str());
    MQTTClient2.subscribe(MQTTCommand2SystemService.c_str());
    MQTTClient2.subscribe(MQTTCommand2SystemCompCurve.c_str());
    MQTTClient2.subscribe(MQTTCommand2SystemActvCtrl.c_str());
    MQTTClient2.subscribe(MQTTCommand2AC.c_str());
    delay(10);

    if (HeatPump.PrevConnected) {
      PublishDiscoveryTopics(2, MQTT_2_BASETOPIC);
    } else if (AC.PrevConnected) {
      PublishA2ADiscoveryTopics(2, MQTT_2_BASETOPIC);
    }
  }


  uint8_t MQTT2Reconnect() {
    if (MQTTClient2.connected()) {
      return 1;
    } else if (strcmp(mqttSettings.hostname2, "IPorDNS") != 0 && strcmp(mqttSettings.hostname2, "") != 0) {
      initializeMQTTClient2();
      //DEBUG_PRINT(F("With Client ID: "));
      //DEBUG_PRINT(mqttSettings.deviceId);
      //DEBUG_PRINT(F(", Username: "));
      //DEBUG_PRINT(mqttSettings.user2);
      //DEBUG_PRINT(F(" and Password: "));
      //DEBUG_PRINTLN(mqttSettings.password2);

      if (MQTTClient2.connect(mqttSettings.deviceId, mqttSettings.user2, mqttSettings.password2, MQTT_2_LWT.c_str(), 0, true, "offline")) {
        DEBUG_PRINTLN(F("MQTT Server 2 Connected"));
        MQTT2onConnect();
        return 1;
      } else {
        switch (MQTTClient2.state()) {
          case -4:
            DEBUG_PRINTLN(F("MQTT_2_CONNECTION_TIMEOUT"));
            break;
          case -3:
            DEBUG_PRINTLN(F("MQTT_2_CONNECTION_LOST"));
            break;
          case -2:
            DEBUG_PRINTLN(F("MQTT_2_CONNECT_FAILED"));
            break;
          case -1:
            DEBUG_PRINTLN(F("MQTT_2_DISCONNECTED"));
            break;
          case 0:
            DEBUG_PRINTLN(F("MQTT_2_CONNECTED"));
            break;
          case 1:
            DEBUG_PRINTLN(F("MQTT_2_CONNECT_BAD_PROTOCOL"));
            break;
          case 2:
            DEBUG_PRINTLN(F("MQTT_2_CONNECT_BAD_CLIENT_ID"));
            break;
          case 3:
            DEBUG_PRINTLN(F("MQTT_2_CONNECT_UNAVAILABLE"));
            break;
          case 4:
            DEBUG_PRINTLN(F("MQTT_2_CONNECT_BAD_CREDENTIALS"));
            break;
          case 5:
            DEBUG_PRINTLN(F("MQTT_2_CONNECT_UNAUTHORIZED"));
            break;
        }
        return 0;
      }
      return 0;
    } else {
      DEBUG_PRINTLN(F("Secondary MQTT Not Set"));
      return 0;
    }
  }


  void handleMQTT2State() {
    if (!MQTTClient2.connected()) {
      MQTT2Reconnect();
    }
    MQTTClient2.loop();
  }

#endif