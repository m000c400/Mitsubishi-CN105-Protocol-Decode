//-- MQTT Home Assistant Auto Discovery --//

const int discovery_topics PROGMEM = 127;

// Build the sensor JSON structure
const char MQTT_DISCOVERY_OBJ_ID[][3] PROGMEM = { "aa", "ab", "ac", "ad", "ae", "af", "ag", "ai", "aj", "ak", "al", "am", "an", "ao", "ap", "aq", "ar", "as", "au", "av", "aw", "ax", "ay", "az", "ba", "bb", "bc", "bd", "be", "bf", "bg", "bh", "bi", "bj", "bk", "bl", "bm", "bn", "bo", "bp", "bq", "br", "bs", "bt", "bu", "bv", "bw", "bx", "by", "bz", "ca", "cb", "cc", "cd", "cu", "cv", "cw", "cx", "cz", "da", "db", "dc", "de", "df", "dg", "dh", "di", "dj", "dk", "dl", "dm", "dn", "do", "dp", "dq", "ds", "dt", "dx", "dz", "ea", "eb", "ec", "ed", "ee", "ef", "eg", "eh", "ei", "ej", "ek", "el", "em", "en", "eo", "ep", "eq", "er", "et", "eu", "ev", "ew", "ex", "ey", "ez", "ce", "cf", "cg", "dw", "du", "ch", "ci", "cj", "ck", "cl", "cm", "cn", "co", "cp", "dr", "es", "cs", "fa", "ct", "dv", "dx", "dy", "es" };

const char MQTT_SENSOR_UNIQUE_ID[][32] PROGMEM = {
  "ashp_bridge_lwt_",
  "ashp_bridge_firmware_",
  "ashp_bridge_rssi_",
  "ashp_ftc_",
  "ashp_op_mode_",
  "ashp_heater_return_",  //5
  "ashp_heater_flow_",
  "ashp_outside_air_temp_",
  "ashp_defrost_status_",
  "ashp_pump_power_",  //10
  "ashp_compressor_freq_",
  "ashp_flow_rate_",
  "ashp_run_hours_",
  "ashp_max_flow_temp_",
  "ashp_min_flow_temp_",  //15
  "ashp_boiler_flow_temp_",
  "ashp_boiler_return_temp_",
  "ashp_mixing_tank_temp_",
  "ashp_refrige_temp_",  //20
  "ashp_immersion_active_",
  "ashp_booster_active_",
  "ashp_primary_water_pump_active_",
  "ashp_water_pump_2_active_",
  "ashp_3WayValve_1_active_",  //25
  "ashp_3WayValve_2_active_",
  "ashp_dhw_temp_",
  "ashp_dhw_temp_thw5a_",
  "ashp_dhw_prohibit_",
  "ashp_dhw_active_",  //30
  "ashp_dhw_mode_",
  "ashp_legionella_setpoint_",
  "ashp_dhw_max_tempdrop_",
  "ashp_dhw_phase_",
  "ashp_z1_flow_temp_",  //35
  "ashp_z1_return_temp_",
  "ashp_z2_flow_temp_",
  "ashp_z2_return_temp_",
  "ashp_twozone_z1_working_",
  "ashp_twozone_z2_working_",  //40
  "ashp_consumed_heat_",
  "ashp_delivered_heat_",
  "ashp_consumed_cool_",
  "ashp_delivered_cool_",
  "ashp_consumed_dhw_",  //45
  "ashp_delivered_dhw_",
  "ashp_total_consumed_",
  "ashp_total_delivered_",
  "ashp_heat_cop_",
  "ashp_cool_cop_",  //50
  "ashp_dhw_cop_",
  "ashp_total_cop_",
  "ashp_refrige_flt_code_",
  "ashp_err_code_",
  "ashp_flt_code_",  //55
  "ashp_delta_t_",
  "ashp_est_heat_pwr_out_",
  "ashp_est_cool_pwr_out_",
  "ashp_heat_active_",
  "ashp_cool_active_",  //60
  "ashp_z1h_prohibit_",
  "ashp_z1c_prohibit_",
  "ashp_z2h_prohibit_",
  "ashp_z2c_prohibit_",
  "ashp_z1_fsp",  //65
  "ashp_z2_fsp",
  "ashp_z1_tstat_demand",
  "ashp_z2_tstat_demand",
  "ashp_ext_tstat_demand",
  "ashp_water_pump_4_active",
  "ashp_water_pump_3_active",
  "ashp_water_pump_13_active",
  "ashp_input_power_",
  "ashp_est_pwr_in_",
  "ashp_ftc_sw_v_",
  "ashp_dhw_eco_boost_",
  "ashp_mix_valve_pos_",
  "ashp_bridge_cpu_",
  "ashp_booster2_active_",
  "ashp_instant_cop_",
  "ashp_liquid_temp_",
  "ashp_comp_op_times",   //eb
  "ashp_th4_discharge_",  //ec
  "ashp_subcool_",        //ed
  "ashp_th8_",            //ee
  "ashp_th6_",            //ef
  "ashp_fan1_rpm_",       //eg
  "ashp_fan2_rpm_",       //eh
  "ashp_LEVA_",           //ei
  "ashp_LEVB_",
  "ashp_th32_",
  "ashp_est_dhw_pwr_out_",  //el
  "ashp_est_dhw_pwr_in_",
  "ashp_est_heating_pwr_out_",
  "ashp_est_heating_pwr_in_",
  "ashp_est_cooling_pwr_in_",
  "ashp_superheat_",
  "ashp_actv_ctrl_cycl_prtc_",
  "ashp_outdoor_sw_v_",
  "ashp_mel_status_",
  "ashp_dip_sw_conf_",
  "ashp_pri_pump_pwm_",
  "gshp_brine_in_",
  "gshp_brine_out_",
  "ashp_est_cop_today",

  "ashp_dhw_climate_",  //65
  "ashp_Zone1_climate_",
  "ashp_Zone2_climate_",  //67
  "ashp_Zone1_flow_climate_",
  "ashp_Zone2_flow_climate_",  //67

  "ashp_dhw_boost_",  //68
  "ashp_systempower_",
  "ashp_holidaymode_",
  "ashp_svr_control_mode_",
  "ashp_svrctrol_dhw_",
  "ashp_svrctrol_z1h_",  //73
  "ashp_svrctrol_z1c_",
  "ashp_svrctrol_z2h_",
  "ashp_svrctrol_z2c_",
  "ashp_svrctrol_norm_dhw_",
  "ashp_actv_ctrl_cycl_",
  "ashp_melcloud_readonly_",

  "ashp_dhw_mode",  //79
  "ashp_heat_cool_mode",
  "ashp_heat_cool_mode_z2",
  "ashp_unit_size_",
  "ashp_glycol_",
  "ashp_bridge_fmwre_upd_"
};


const char MQTT_MDI_ICONS_AC[][30] PROGMEM = {
  "mdi:cloud-check-variant",
  "mdi:alpha-v-box",
  "mdi:signal-variant",
  "mdi:sine-wave",  
  "mdi:rotate-3d",
  "mdi:timer-cog-outline",
  "mdi:timer-cog-outline",
  "mdi:timer-cog-outline",
  "mdi:timer-cog-outline",
  "mdi:timer-cog-outline",
  "mdi:home-thermometer",
  "mdi:home-alert",
  "mdi:home-alert",
  "mdi:transmission-tower-import",
  "mdi:transmission-tower-import",
  "mdi:fan",
  "mdi:auto-mode",
  "mdi:cancel",
  "mdi:sun-thermometer-outline",
  "mdi:clock-outline",
  "mdi:air-filter",
  "mdi:car-defrost-front",
  "mdi:heat-wave",
  "mdi:power-standby"
};

const char MQTT_MDI_ICONS[][30] PROGMEM = {
  "mdi:cloud-check-variant",
  "mdi:alpha-v-box",
  "mdi:signal-variant",
  "mdi:alpha-v-circle",
  "mdi:auto-mode",
  "mdi:keyboard-return",  //5
  "mdi:waves-arrow-right",
  "mdi:sun-thermometer-outline",
  "mdi:car-defrost-front",
  "mdi:heat-pump",
  "mdi:sine-wave",  //10
  "mdi:waves-arrow-right",
  "mdi:clock-digital",
  "mdi:thermometer-chevron-up",
  "mdi:thermometer-chevron-down",
  "mdi:water-boiler",  //15
  "mdi:water-boiler",
  "mdi:storage-tank",
  "mdi:coolant-temperature",
  "mdi:water-pump",
  "mdi:thermometer-plus",  //20
  "mdi:heat-pump-outline",
  "mdi:heat-pump-outline",
  "mdi:valve",
  "mdi:valve",
  "mdi:hand-water",  //25
  "mdi:hand-water",
  "mdi:cancel",
  "mdi:water-thermometer",
  "mdi:auto-mode",
  "mdi:thermometer-auto",  //30
  "mdi:thermometer-auto",
  "mdi:auto-mode",
  "mdi:heating-coil",
  "mdi:heating-coil",
  "mdi:heating-coil",  //35
  "mdi:heating-coil",
  "mdi:heating-coil",
  "mdi:heating-coil",
  "mdi:transmission-tower-import",
  "mdi:radiator",  //40
  "mdi:transmission-tower-import",
  "mdi:radiator",
  "mdi:transmission-tower-import",
  "mdi:radiator",
  "mdi:transmission-tower-import",  //45
  "mdi:radiator",
  "mdi:calculator",
  "mdi:calculator",
  "mdi:calculator",
  "mdi:calculator",  //50
  "mdi:fridge-industrial-alert",
  "mdi:home-alert",
  "mdi:home-alert",
  "mdi:delta",
  "mdi:export",  //55
  "mdi:export",
  "mdi:radiator",
  "mdi:snowflake",
  "mdi:radiator-off",
  "mdi:snowflake-off",  //60
  "mdi:radiator-off",
  "mdi:snowflake-off",
  "mdi:waves-arrow-right",
  "mdi:waves-arrow-right",
  "mdi:thermostat",  //65
  "mdi:thermostat",
  "mdi:thermostat",
  "mdi:heat-pump-outline",
  "mdi:heat-pump-outline",
  "mdi:heat-pump-outline",  //70
  "mdi:transmission-tower-import",
  "mdi:transmission-tower-import",
  "mdi:alpha-v-circle-outline",
  "mdi:hand-water",
  "mdi:valve",  //75
  "mdi:chip",
  "mdi:thermometer-plus",
  "mdi:calculator",
  "mdi:water-thermometer",
  "mdi:heat-pump-outline",
  "mdi:water-thermometer",
  "mdi:water-thermometer",
  "mdi:water-thermometer",
  "mdi:water-thermometer",
  "mdi:fan",
  "mdi:fan",
  "mdi:valve",
  "mdi:valve",
  "mdi:water-thermometer",
  "mdi:export",
  "mdi:transmission-tower-import",
  "mdi:export",
  "mdi:transmission-tower-import",
  "mdi:transmission-tower-import",
  "mdi:water-thermometer",
  "mdi:fan-alert",
  "mdi:alpha-v-box-outline",
  "mdi:cloud-question",
  "mdi:dip-switch",
  "mdi:pump",
  "mdi:heating-coil",
  "mdi:heating-coil",
  "mdi:poll",

  "mdi:thermostat",
  "mdi:thermostat",  //80
  "mdi:thermostat",
  "mdi:thermostat",
  "mdi:thermostat",

  "mdi:thermometer-plus",
  "mdi:power",  //85
  "mdi:bag-suitcase",
  "mdi:server-network-outline",
  "mdi:cancel",
  "mdi:cancel",
  "mdi:cancel",  //90
  "mdi:cancel",
  "mdi:cancel",
  "mdi:thermometer-plus",
  "mdi:fan-alert",
  "mdi:read",

  "mdi:auto-mode",
  "mdi:sun-snowflake-variant",
  "mdi:sun-snowflake-variant",
  "mdi:resize",
  "mdi:water-opacity"  //100
};

#ifdef LANG_DE
const char MQTT_SENSOR_NAME[][65] PROGMEM = {
  "Bridge-Status",                             // Bridge Status
  "Firmware-Version",                          // Firmware Version
  "Bridge WLAN-Signal",                        // Bridge WiFi Signal
  "FTC-Version",                               // FTC Version
  "System-Betriebsart",                        // System Operation Mode
  "Heizung Rücklauftemperatur",                // Heater Return Temperature //5
  "Heizung Vorlauftemperatur",                 // Heater Flow Temperature
  "Außentemperatur",                           // Outside Temperature
  "Abtauung",                                  // Defrost
  "Wärmepumpen-Abgabeleistung",                // Heat Pump Output Power
  "Kompressorfrequenz",                        // Compressor Frequency // 10
  "Durchflussrate",                            // Flow Rate
  "Betriebsstunden",                           // Run Hours
  "Max. Vorlauftemperatur",                    // Max Flow Temperature
  "Min. Vorlauftemperatur",                    // Min Flow Temperature
  "Kessel Vorlauftemperatur",                  // Boiler Flow Temperature //15
  "Kessel Rücklauftemperatur",                 // Boiler Return Temperature
  "Mischbehälter-Temperatur",                  // Mixing Tank Temperature
  "Kältemitteltemperatur",                     // Refrigerant Temperature
  "Eintauchheizkörper (WW)",                   // Immersion Heater
  "Zusatzheizung 1",                           // Booster Heater 1 //20
  "Wasserpumpe 1",                             // Water Pump 1
  "Wasserpumpe 2",                             // Water Pump 2
  "Drei-Wege-Ventil 1",                        // Three Way Valve 1
  "Drei-Wege-Ventil 2",                        // Three Way Valve 2
  "Warmwassertemperatur",                      // DHW Temperature //25
  "Warmwassertemperatur oben",                 // DHW Temperature Upper
  "Warmwasser sperren",                        // Prohibit DHW
  "Warmwasserbereitung läuft",                 // DHW Running
  "Warmwasser-Regelungsart",                   // DHW Control Mode
  "Legionellen-Sollwert",                      // Legionella Setpoint //30
  "WW Max. Temperaturabfall",                  // DHW Max Temperature Drop
  "Warmwasser-Heizphase",                      // DHW Heating Phase
  "Zone 1 Vorlauftemperatur",                  // Zone 1 Flow Temperature
  "Zone 1 Rücklauftemperatur",                 // Zone 1 Return Temperature
  "Zone 2 Vorlauftemperatur",                  // Zone 2 Flow Temperature //35
  "Zone 2 Rücklauftemperatur",                 // Zone 2 Return Temperature
  "Zone 1 aktiv",                              // Zone 1 Working
  "Zone 2 aktiv",                              // Zone 2 Working
  "Heizungsverbrauch gestern",                 // Consumed Heating Yesterday
  "Heizungserzeugung gestern",                 // Delivered Heating Yesterday //40
  "Kühlverbrauch gestern",                     // Consumed Cooling Yesterday
  "Kühlerzeugung gestern",                     // Delivered Cooling Yesterday
  "Warmwasserverbrauch gestern",               // Consumed DHW Yesterday
  "Warmwassererzeugung gestern",               // Delivered DHW Yesterday
  "Gesamtenergieverbrauch gestern",            // Total Consumed Energy Yesterday //45
  "Gesamtenergieerzeugung gestern",            // Total Delivered Energy Yesterday
  "Heizung CoP gestern",                       // Heating CoP Yesterday
  "Kühlung CoP gestern",                       // Cooling CoP Yesterday
  "Warmwasser CoP gestern",                    // DHW CoP Yesterday
  "Gesamt-CoP gestern",                        // Total CoP Yesterday //50
  "Kältemittel-Fehlercode",                    // Refrigerant Fault Code
  "Fehlercode",                                // Error Code
  "Störungscode",                              // Fault Code
  "Spreizung Vor-/Rücklauf (DeltaT)",          // Flow Return DeltaT
  "Berechnete Heiz-Abgabeleistung",            // Computed Heat Output Power //55
  "Berechnete Kühl-Abgabeleistung",            // Computed Cool Output Power
  "Heizbetrieb läuft",                         // Heating Running
  "Kühlbetrieb läuft",                         // Cooling Running
  "Zone 1 Heizsperre",                         // Zone 1 Heating Prohibit
  "Zone 1 Kühlsperre",                         // Zone 1 Cooling Prohibit //60
  "Zone 2 Heizsperre",                         // Zone 2 Heating Prohibit
  "Zone 2 Kühlsperre",                         // Zone 2 Cooling Prohibit
  "Zone 1 Vorlauf-Sollwert",                   // Zone 1 Flow Setpoint
  "Zone 2 Vorlauf-Sollwert",                   // Zone 2 Flow Setpoint
  "Zone 1 Ext. Thermostatanforderung",         // Zone 1 Ext Thermostat Demand //65
  "Zone 2 Ext. Thermostatanforderung",         // Zone 2 Ext Thermostat Demand
  "Außen Ext. Thermostatanforderung",          // Outside Ext Thermostat Demand
  "Wasserpumpe 4",                             // Water Pump 4
  "Wasserpumpe 3",                             // Water Pump 3
  "Wasserpumpe 13",                            // Water Pump 13 // 70
  "Wärmepumpen-Aufnahmeleistung",              // Heat Pump Input Power
  "Berechnete Aufnahmeleistung",               // Computed Input Power
  "FTC-Softwareversion",                       // FTC Software Version
  "Warmwasser-Boost",                          // DHW Boost
  "Mischventil-Stufe",                         // Mixing Valve Step //75
  "Bridge CPU-Temperatur",                     // Bridge CPU Temperature
  "Zusatzheizung 2",                           // Booster Heater 2
  "Aktueller CoP",                             // Instant CoP
  "Flüssigkältemittel-Temperatur TH3",         // Refrigerant Liquid Temperature TH3
  "Kompressor Startanzahl",                    // Compressor Start Quantity
  "Heißgastemperatur TH4",                     // Discharge Temperature TH4
  "Unterkühlungstemperatur",                   // Subcool Temperature
  "Kühlkörpertemperatur TH8",                  // Heatsink Temperature TH8
  "Plattenwärmetauscher Flüssigtemp. TH6",     // Plate Hex Liquid Temperature TH6
  "Lüfter 1 Drehzahl",                         // Fan 1 Speed
  "Lüfter 2 Drehzahl",                         // Fan 2 Speed
  "Ventil LEV A",                              // Valve LEV A
  "Ventil LEV B",                              // Valve LEV B
  "Wassereinlasstemperatur TH32",              // Water Inlet Temperature TH32
  "Berechnete WW-Abgabeleistung",              // Computed DHW Output Power
  "Berechnete WW-Aufnahmeleistung",            // Computed DHW Input Power
  "Berechnete Heiz-Abgabeleistung",            // Computed Heating Output Power
  "Berechnete Heiz-Aufnahmeleistung",          // Computed Heating Input Power
  "Berechnete Kühl-Aufnahmeleistung",          // Computed Cooling Input Power
  "Überhitzungstemperatur",                    // Superheat Temperature
  "Taktungsschutz-Status",                     // Short Cycle Protection State
  "Außengerät-Softwareversion",                // Outdoor Unit Software Version
  "MELCloud-Adapterstatus",                    // MELCloud Adapter Status
  "DIP-Schalter-Konfiguration (1-1 bis 7-8)",  // Dip Switch Configuration
  "Wasserpumpe 1 PWM-Drehzahl",                // Water Pump 1 PWM Speed
  "Sole-Einlasstemperatur",                    // Brine Inlet Temperature
  "Sole-Auslasstemperatur",                    // Brine Outlet Temperature
  "Gesamt-CoP heute",                          // Total CoP Today

  "Warmwasserthermostat",      // DHW Thermostat
  "Zone 1 Thermostat",         // Zone 1 Thermostat //80
  "Zone 2 Thermostat",         // Zone 2 Thermostat
  "Zone 1 Vorlaufthermostat",  // Zone 1 Flow Thermostat
  "Zone 2 Vorlaufthermostat",  // Zone 2 Flow Thermostat

  "Schneller WW-Boost",      // Fast DHW Boost
  "Systemleistung",          // System Power //85
  "Urlaubsmodus",            // Holiday Mode
  "Server-Steuerungsmodus",  // Server Control Mode
  "Warmwasser sperren",      // Prohibit DHW
  "Zone 1 Heizsperre",       // Prohibit Zone 1 Heating
  "Zone 1 Kühlsperre",       // Prohibit Zone 1 Cooling //90
  "Zone 2 Heizsperre",       // Prohibit Zone 2 Heating
  "Zone 2 Kühlsperre",       // Prohibit Zone 2 Cooling
  "Warmwasser-Boost",        // DHW Boost
  "Taktungsschutz",          // Short Cycle Protection
  "MELCloud Nur Lesen",      // MELCloud Read Only

  "Warmwassermodus",               // DHW Mode
  "Heiz-/Kühlbetriebsart Zone 1",  // Heating/Cooling Operation Mode Zone 1 //95
  "Heiz-/Kühlbetriebsart Zone 2",  // Heating/Cooling Operation Mode Zone 2
  "Leistung Außengerät (kW)",      // Outdoor Unit Size (kW)
  "Glykolkonzentration",           // Glycol Strength
  "Firmware-Update"                // Firmware Update
};

const char MQTT_AC_SENSOR_NAME[][45] PROGMEM = {
  "Bridge-Status",
  "Firmware-Version",
  "Bridge WLAN-Signal",
  "Kompressorfrequenz",  // 10
  "iSee",
  "Timer-Modus",
  "Einschaltzeit Min (Soll)",
  "Einschaltzeit Min (Rest)",
  "Ausschaltzeit Min (Soll)",
  "Ausschaltzeit Min (Rest)",
  "Raumtemperatur",
  "Fehlercode",
  "Störungscode",
  "Eingangsleistung",
  "Gesamtleistung",
  "Ist-Lüfterdrehzahl",
  "Automatikmodus",
  "Fernbedienung Sperre",
  "Außentemperatur",
  "Laufzeit",
  "Filter wechseln",
  "Abtauen",
  "Vorheizen",
  "Standby",

  "Raumthermostat",
  "Systemleistung",
  "Firmware-Update"
  "Externe Temperatur",
  "Externen Sensor nutzen"
};


// Finnish
#elif defined(LANG_FI)
const char MQTT_SENSOR_NAME[][65] PROGMEM = {
  "Sillan tila",                             // Bridge Status
  "Laiteohjelmiston versio",                 // Firmware Version
  "Sillan WiFi-signaali",                    // Bridge WiFi Signal
  "FTC-versio",                              // FTC Version
  "Järjestelmän toimintatila",               // System Operation Mode
  "Lämmityksen paluulämpötila",              // Heater Return Temperature //5
  "Lämmityksen menolämpötila",               // Heater Flow Temperature
  "Ulkolämpötila",                           // Outside Temperature
  "Sulatustoiminto",                         // Defrost
  "Lämpöpumpun antoteho",                    // Heat Pump Output Power
  "Kompressorin taajuus",                    // Compressor Frequency // 10
  "Virtausnopeus",                           // Flow Rate
  "Käyttötunnit",                            // Run Hours
  "Maksimi menolämpötila",                   // Max Flow Temperature
  "Minimi menolämpötila",                    // Min Flow Temperature
  "Kattilan menolämpötila",                  // Boiler Flow Temperature //15
  "Kattilan paluulämpötila",                 // Boiler Return Temperature
  "Varaajan lämpötila",                      // Mixing Tank Temperature
  "Kylmäaineen lämpötila",                   // Refrigerant Temperature
  "Sähkövastus (LKV)",                       // Immersion Heater
  "Lisälämmitin 1",                          // Booster Heater 1 //20
  "Vesipumppu 1",                            // Water Pump 1
  "Vesipumppu 2",                            // Water Pump 2
  "Kolmitieventtiili 1",                     // Three Way Valve 1
  "Kolmitieventtiili 2",                     // Three Way Valve 2
  "LKV-lämpötila",                           // DHW Temperature //25
  "LKV-lämpötila yläosa",                    // DHW Temperature Upper
  "Estä LKV",                                // Prohibit DHW
  "LKV-lämmitys käynnissä",                  // DHW Running
  "LKV-ohjaustila",                          // DHW Control Mode
  "Legionellatoiminnon asetusarvo",          // Legionella Setpoint //30
  "LKV suurin lämpötilan pudotus",           // DHW Max Temperature Drop
  "LKV-lämmitysvaihe",                       // DHW Heating Phase
  "Vyöhyke 1 menolämpötila",                 // Zone 1 Flow Temperature
  "Vyöhyke 1 paluulämpötila",                // Zone 1 Return Temperature
  "Vyöhyke 2 menolämpötila",                 // Zone 2 Flow Temperature //35
  "Vyöhyke 2 paluulämpötila",                // Zone 2 Return Temperature
  "Vyöhyke 1 käytössä",                      // Zone 1 Working
  "Vyöhyke 2 käytössä",                      // Zone 2 Working
  "Kulutettu lämmitys eilen",                // Consumed Heating Yesterday
  "Tuotettu lämmitys eilen",                 // Delivered Heating Yesterday //40
  "Kulutettu jäähdytys eilen",               // Consumed Cooling Yesterday
  "Tuotettu jäähdytys eilen",                // Delivered Cooling Yesterday
  "Kulutettu LKV eilen",                     // Consumed DHW Yesterday
  "Tuotettu LKV eilen",                      // Delivered DHW Yesterday
  "Kokonaisenergiankulutus eilen",           // Total Consumed Energy Yesterday //45
  "Kokonaisenergiantuotto eilen",            // Total Delivered Energy Yesterday
  "Lämmityksen CoP eilen",                   // Heating CoP Yesterday
  "Jäähdytyksen CoP eilen",                  // Cooling CoP Yesterday
  "LKV CoP eilen",                           // DHW CoP Yesterday
  "Kokonais-CoP eilen",                      // Total CoP Yesterday //50
  "Kylmäainepiirin vikakoodi",               // Refrigerant Fault Code
  "Virhekoodi",                              // Error Code
  "Vikakoodi",                               // Fault Code
  "Meno- ja paluun erotus (DeltaT)",         // Flow Return DeltaT
  "Laskettu lämmityksen antoteho",           // Computed Heat Output Power //55
  "Laskettu jäähdytyksen antoteho",          // Computed Cool Output Power
  "Lämmitys käynnissä",                      // Heating Running
  "Jäähdytys käynnissä",                     // Cooling Running
  "Vyöhyke 1 lämmityksen esto",              // Zone 1 Heating Prohibit
  "Vyöhyke 1 jäähdytyksen esto",             // Zone 1 Cooling Prohibit //60
  "Vyöhyke 2 lämmityksen esto",              // Zone 2 Heating Prohibit
  "Vyöhyke 2 jäähdytyksen esto",             // Zone 2 Cooling Prohibit
  "Vyöhyke 1 menoveden asetusarvo",          // Zone 1 Flow Setpoint
  "Vyöhyke 2 menoveden asetusarvo",          // Zone 2 Flow Setpoint
  "Vyöhyke 1 ulkoisen term. pyyntö",         // Zone 1 Ext Thermostat Demand //65
  "Vyöhyke 2 ulkoisen term. pyyntö",         // Zone 2 Ext Thermostat Demand
  "Ulkoisen termostaatin pyyntö",            // Outside Ext Thermostat Demand
  "Vesipumppu 4",                            // Water Pump 4
  "Vesipumppu 3",                            // Water Pump 3
  "Vesipumppu 13",                           // Water Pump 13 // 70
  "Lämpöpumpun ottoteho",                    // Heat Pump Input Power
  "Laskettu ottoteho",                       // Computed Input Power
  "FTC-ohjelmistoversio",                    // FTC Software Version
  "LKV-tehostus",                            // DHW Boost
  "Sekoitusventtiilin asento",               // Mixing Valve Step //75
  "Sillan CPU-lämpötila",                    // Bridge CPU Temperature
  "Lisälämmitin 2",                          // Booster Heater 2
  "Hetkellinen CoP",                         // Instant CoP
  "Nestemäisen kylmäaineen lämpötila TH3",   // Refrigerant Liquid Temperature TH3
  "Kompressorin käynnistykset",              // Compressor Start Quantity
  "Kuumakaasun lämpötila TH4",               // Discharge Temperature TH4
  "Alijäähtymislämpötila",                   // Subcool Temperature
  "Jäähdytysprofiilin lämpötila TH8",        // Heatsink Temperature TH8
  "Levylämmönsiirtimen nestelämpötila TH6",  // Plate Hex Liquid Temperature TH6
  "Puhaltimen 1 nopeus",                     // Fan 1 Speed
  "Puhaltimen 2 nopeus",                     // Fan 2 Speed
  "Venttiili LEV A",                         // Valve LEV A
  "Venttiili LEV B",                         // Valve LEV B
  "Tuloveden lämpötila TH32",                // Water Inlet Temperature TH32
  "Laskettu LKV-antoteho",                   // Computed DHW Output Power
  "Laskettu LKV-ottoteho",                   // Computed DHW Input Power
  "Laskettu lämmityksen antoteho",           // Computed Heating Output Power
  "Laskettu lämmityksen ottoteho",           // Computed Heating Input Power
  "Laskettu jäähdytyksen ottoteho",          // Computed Cooling Input Power
  "Tulistuslämpötila",                       // Superheat Temperature
  "Lyhyen kierron suojatila",                // Short Cycle Protection State
  "Ulkoyksikön ohjelmistoversio",            // Outdoor Unit Software Version
  "MELCloud-sovittimen tila",                // MELCloud Adapter Status
  "DIP-kytkinten asetukset (1-1 - 7-8)",     // Dip Switch Configuration (Switch 1-1 to 7-8)
  "Vesipumpun 1 PWM-nopeus",                 // Water Pump 1 PWM Speed
  "Keruupiirin tulolämpötila",               // Brine Inlet Temperature
  "Keruupiirin lähtölämpötila",              // Brine Outlet Temperature
  "Kokonais-CoP tänään",                     // Total CoP Today

  "LKV-termostaatti",                  // DHW Thermostat
  "Vyöhykkeen 1 termostaatti",         // Zone 1 Thermostat //80
  "Vyöhykkeen 2 termostaatti",         // Zone 2 Thermostat
  "Vyöhykkeen 1 virtaustermostaatti",  // Zone 1 Flow Thermostat
  "Vyöhykkeen 2 virtaustermostaatti",  // Zone 2 Flow Thermostat

  "Nopea LKV-tehostus",           // Fast DHW Boost
  "Järjestelmän virta",           // System Power //85
  "Lomatila",                     // Holiday Mode
  "Palvelimen ohjaustila",        // Server Control Mode
  "Estä LKV",                     // Prohibit DHW
  "Estä vyöhykkeen 1 lämmitys",   // Prohibit Zone 1 Heating
  "Estä vyöhykkeen 1 jäähdytys",  // Prohibit Zone 1 Cooling //90
  "Estä vyöhykkeen 2 lämmitys",   // Prohibit Zone 2 Heating
  "Estä vyöhykkeen 2 jäähdytys",  // Prohibit Zone 2 Cooling
  "LKV-tehostus",                 // DHW Boost
  "Lyhyen kierron suojaus",       // Short Cycle Protection
  "MELCloud Vain luku",           // MELCloud Read Only

  "LKV-tila",                           // DHW Mode
  "Lämmitys-/jäähdytystila Vyöhyke 1",  // Heating/Cooling Operation Mode Zone 1 //95
  "Lämmitys-/jäähdytystila Vyöhyke 2",  // Heating/Cooling Operation Mode Zone 2
  "Ulkoyksikön koko (kW)",              // Outdoor Unit Size (kW)
  "Glykolipitoisuus",                   // Glycol Strength
  "Laiteohjelmiston päivitys"           // Firmware Update
};

const char MQTT_AC_SENSOR_NAME[][45] PROGMEM = {
  "Sillan tila",
  "Laiteohjelmiston versio",
  "Sillan Wi-Fi-signaali",
  "Kompressorin taajuus",  // 10
  "iSee",
  "Ajastintila",
  "Asetetut minuutit (Päällä)",
  "Jäljellä olevat minuutit (Päällä)",
  "Asetetut minuutit (Pois)",
  "Jäljellä olevat minuutit (Pois)",
  "Huonelämpötila",
  "Virhekoodi",
  "Vikaloodi",
  "Ottoteho",
  "Kokonaiskulutus",
  "Tuulettimen todellinen nopeus",
  "Automaattitila",
  "Kaukosäätimen esto",
  "Ulkolämpötila",
  "Käyntiaika",
  "Suodattimen vaihto",
  "Sulatus",
  "Esilämmitys",
  "Valmiustila",

  "Huonetermostaatti",
  "Järjestelmän teho",
  "Laiteohjelmiston päivitys",
  "Ulkoinen lämpötila",
  "Käytä etäanturia"
};

// Swedish
#elif defined(LANG_SE)
const char MQTT_SENSOR_NAME[][65] PROGMEM = {
  "Bryggstatus",                              // Bridge Status
  "Firmware-version",                        // Firmware Version
  "Bryggans WiFi-signal",                    // Bridge WiFi Signal
  "FTC-version",                             // FTC Version
  "Systemets driftläge",                     // System Operation Mode
  "Returledningstemperatur värme",           // Heater Return Temperature //5
  "Framledningstemperatur värme",            // Heater Flow Temperature
  "Utomhustemperatur",                       // Outside Temperature
  "Avfrostning",                             // Defrost
  "Värmepumpens avgivna effekt",             // Heat Pump Output Power
  "Kompressorfrekvens",                      // Compressor Frequency // 10
  "Flödeshastighet",                         // Flow Rate
  "Drifttimmar",                             // Run Hours
  "Max framledningstemperatur",              // Max Flow Temperature
  "Min framledningstemperatur",              // Min Flow Temperature
  "Pannans framledningstemperatur",          // Boiler Flow Temperature //15
  "Pannans returledningstemperatur",         // Boiler Return Temperature
  "Arbetstanktemperatur",                    // Mixing Tank Temperature
  "Köldmedietemperatur",                     // Refrigerant Temperature
  "Elpatron (VV)",                           // Immersion Heater
  "Tillsatsvärmare 1",                       // Booster Heater 1 //20
  "Vattenpump 1",                            // Water Pump 1
  "Vattenpump 2",                            // Water Pump 2
  "Trevägsventil 1",                         // Three Way Valve 1
  "Trevägsventil 2",                         // Three Way Valve 2
  "VV-temperatur",                           // DHW Temperature //25
  "VV-temperatur övre del",                  // DHW Temperature Upper
  "Spärra VV",                               // Prohibit DHW
  "VV-laddning pågår",                       // DHW Running
  "VV-styrläge",                             // DHW Control Mode
  "Börvärde legionellafunktion",             // Legionella Setpoint //30
  "VV max temperaturfall",                   // DHW Max Temperature Drop
  "VV-uppvärmningsfas",                      // DHW Heating Phase
  "Zon 1 framledningstemperatur",            // Zone 1 Flow Temperature
  "Zon 1 returledningstemperatur",           // Zone 1 Return Temperature
  "Zon 2 framledningstemperatur",            // Zone 2 Flow Temperature //35
  "Zon 2 returledningstemperatur",           // Zone 2 Return Temperature
  "Zon 1 i drift",                           // Zone 1 Working
  "Zon 2 i drift",                           // Zone 2 Working
  "Förbrukad värme igår",                    // Consumed Heating Yesterday
  "Avgiven värme igår",                      // Delivered Heating Yesterday //40
  "Förbrukad kyla igår",                     // Consumed Cooling Yesterday
  "Avgiven kyla igår",                       // Delivered Cooling Yesterday
  "Förbrukad VV igår",                       // Consumed DHW Yesterday
  "Avgiven VV igår",                         // Delivered DHW Yesterday
  "Total energiförbrukning igår",            // Total Consumed Energy Yesterday //45
  "Total avgiven energi igår",               // Total Delivered Energy Yesterday
  "COP värme igår",                          // Heating CoP Yesterday
  "COP kyla igår",                           // Cooling CoP Yesterday
  "COP VV igår",                             // DHW CoP Yesterday
  "Total-COP igår",                          // Total CoP Yesterday //50
  "Felkod köldmediekrets",                   // Refrigerant Fault Code
  "Felkod (Error)",                          // Error Code
  "Felkod (Fault)",                          // Fault Code
  "Differens fram-/returledning (DeltaT)",   // Flow Return DeltaT
  "Beräknad avgiven värmeeffekt",            // Computed Heat Output Power //55
  "Beräknad avgiven kyleffekt",              // Computed Cool Output Power
  "Värme pågår",                             // Heating Running
  "Kyla pågår",                              // Cooling Running
  "Zon 1 värmespärr",                        // Zone 1 Heating Prohibit
  "Zon 1 kylspärr",                          // Zone 1 Cooling Prohibit //60
  "Zon 2 värmespärr",                        // Zone 2 Heating Prohibit
  "Zon 2 kylspärr",                          // Zone 2 Cooling Prohibit
  "Zon 1 börvärde framledning",              // Zone 1 Flow Setpoint
  "Zon 2 börvärde framledning",              // Zone 2 Flow Setpoint
  "Zon 1 begäran extern termostat",          // Zone 1 Ext Thermostat Demand //65
  "Zon 2 begäran extern termostat",          // Zone 2 Ext Thermostat Demand
  "Begäran extern utetermostat",             // Outside Ext Thermostat Demand
  "Vattenpump 4",                            // Water Pump 4
  "Vattenpump 3",                            // Water Pump 3
  "Vattenpump 13",                           // Water Pump 13 // 70
  "Värmepumpens tillförda effekt",           // Heat Pump Input Power
  "Beräknad tillförd effekt",                // Computed Input Power
  "FTC-programvaruversion",                  // FTC Software Version
  "VV-boost",                                // DHW Boost
  "Blandningsventilens position",            // Mixing Valve Step //75
  "Bryggans CPU-temperatur",                 // Bridge CPU Temperature
  "Tillsatsvärmare 2",                       // Booster Heater 2
  "Momentant COP",                           // Instant CoP
  "Vätskeformig köldmedietemp TH3",          // Refrigerant Liquid Temperature TH3
  "Kompressorstarter",                       // Compressor Start Quantity
  "Högtrycksgastemperatur TH4",              // Discharge Temperature TH4
  "Underkylningstemperatur",                 // Subcool Temperature
  "Kylflänstemperatur TH8",                  // Heatsink Temperature TH8
  "Plattvärmeväxlare vätsketemp TH6",        // Plate Hex Liquid Temperature TH6
  "Fläkthastighet 1",                        // Fan 1 Speed
  "Fläkthastighet 2",                        // Fan 2 Speed
  "Ventil LEV A",                            // Valve LEV A
  "Ventil LEV B",                            // Valve LEV B
  "Inloppsvattentemperatur TH32",            // Water Inlet Temperature TH32
  "Beräknad avgiven VV-effekt",              // Computed DHW Output Power
  "Beräknad tillförd VV-effekt",             // Computed DHW Input Power
  "Beräknad avgiven värmeeffekt",            // Computed Heating Output Power
  "Beräknad tillförd värmeeffekt",           // Computed Heating Input Power
  "Beräknad tillförd kyleffekt",             // Computed Cooling Input Power
  "Överhettningstemperatur",                 // Superheat Temperature
  "Kortcyklingsskydd status",                // Short Cycle Protection State
  "Utomhusenhet programvaruversion",         // Outdoor Unit Software Version
  "MELCloud-adapterstatus",                  // MELCloud Adapter Status
  "DIP-brytarinställningar (1-1 till 7-8)",  // Dip Switch Configuration (Switch 1-1 to 7-8)
  "Vattenpump 1 PWM-hastighet",              // Water Pump 1 PWM Speed
  "Brine-inloppstemperatur",                 // Brine Inlet Temperature
  "Brine-utloppstemperatur",                 // Brine Outlet Temperature
  "Total-COP idag",                          // Total CoP Today

  "VV-termostat",                            // DHW Thermostat
  "Zon 1 termostat",                         // Zone 1 Thermostat //80
  "Zon 2 termostat",                         // Zone 2 Thermostat
  "Zon 1 flödestermostat",                   // Zone 1 Flow Thermostat
  "Zon 2 flödestermostat",                   // Zone 2 Flow Thermostat

  "Snabb VV-boost",                          // Fast DHW Boost
  "Systemström",                             // System Power //85
  "Semesterläge",                            // Holiday Mode
  "Serverstyrläge",                          // Server Control Mode
  "Spärra VV",                               // Prohibit DHW
  "Spärra värme Zon 1",                      // Prohibit Zone 1 Heating
  "Spärra kyla Zon 1",                       // Prohibit Zone 1 Cooling //90
  "Spärra värme Zon 2",                      // Prohibit Zone 2 Heating
  "Spärra kyla Zon 2",                       // Prohibit Zone 2 Cooling
  "VV-boost",                                // DHW Boost
  "Kortcyklingsskydd",                       // Short Cycle Protection
  "MELCloud Skrivskyddad",                   // MELCloud Read Only

  "VV-läge",                                 // DHW Mode
  "Driftläge Värme/Kyla Zon 1",              // Heating/Cooling Operation Mode Zone 1 //95
  "Driftläge Värme/Kyla Zon 2",              // Heating/Cooling Operation Mode Zone 2
  "Utomhusenhet storlek (kW)",               // Outdoor Unit Size (kW)
  "Glykolhalt",                              // Glycol Strength
  "Firmware-uppdatering"                     // Firmware Update
};

const char MQTT_AC_SENSOR_NAME[][45] PROGMEM = {
  "Bryggstatus",
  "Firmware-version",
  "Bryggans Wi-Fi-signal",
  "Kompressorfrekvens",                      // 10
  "iSee",
  "Timerläge",
  "Inställda minuter (På)",
  "Återstående minuter (På)",
  "Inställda minuter (Av)",
  "Återstående minuter (Av)",
  "Rumstemperatur",
  "Felkod (Error)",
  "Felkod (Fault)",
  "Tillförd effekt",
  "Total förbrukning",
  "Faktisk fläktthastighet",
  "Autoläge",
  "Spärra fjärrkontroll",
  "Utomhustemperatur",
  "Drifttid",
  "Filterbyte",
  "Avfrostning",
  "Förvärmning",
  "Standbyläge",

  "Rumstermostat",
  "Systemeffekt",
  "Firmware-uppdatering",
  "Extern rumstemperatur",
  "Använd extern givare"
};

// Italian
#elif defined(LANG_IT)
const char MQTT_SENSOR_NAME[][45] PROGMEM = {
  "Stato Bridge",
  "Versione Firmware",
  "Segnale WiFi Bridge",
  "Versione FTC",
  "Modo Operativo Sistema",
  "Temp. Ritorno Riscaldatore",  //5
  "Temp. Mandata Riscaldatore",
  "Temperatura Esterna",
  "Sbrinamento",
  "Potenza Uscita Pompa Calore",
  "Frequenza Compressore",  // 10
  "Portata",
  "Ore Funzionamento",
  "Temp. Massima Mandata",
  "Temp. Minima Mandata",
  "Temp. Mandata Caldaia",  //15
  "Temp. Ritorno Caldaia",
  "Temp. Serbatoio Miscela",
  "Temperatura Refrigerante",
  "Riscaldatore Immersione",
  "Riscaldatore Integrativo 1",  //20
  "Pompa Acqua 1",
  "Pompa Acqua 2",
  "Valvola a Tre Vie 1",
  "Valvola a Tre Vie 2",
  "Temperatura ACS",  //25
  "Temp. ACS Superiore",
  "Inibizione ACS",
  "ACS in Funzione",
  "Modo Controllo ACS",
  "Setpoint Legionella",  //30
  "Caduta Temp. Max ACS",
  "Fase Riscaldamento ACS",
  "Temp. Mandata Zona 1",
  "Temp. Ritorno Zona 1",
  "Temp. Mandata Zona 2",  //35
  "Temp. Ritorno Zona 2",
  "Zona 1 in Funzione",
  "Zona 2 in Funzione",
  "Riscald. Consumato Ieri",
  "Riscald. Prodotto Ieri",  //40
  "Raffredd. Consumato Ieri",
  "Raffredd. Prodotto Ieri",
  "ACS Consumato Ieri",
  "ACS Prodotto Ieri",
  "Energia Tot. Consumata Ieri",  //45
  "Energia Tot. Prodotta Ieri",
  "CoP Riscaldamento Ieri",
  "CoP Raffreddamento Ieri",
  "CoP ACS Ieri",
  "CoP Totale Ieri",  //50
  "Codice Errore Refrigerante",
  "Codice Errore",
  "Codice Guasto",
  "DeltaT Mandata Ritorno",
  "Potenza Riscald. Calcolata",  //55
  "Potenza Raffredd. Calcolata",
  "Riscaldamento in Corso",
  "Raffreddamento in Corso",
  "Inibizione Riscald. Zona 1",
  "Inibizione Raffredd. Zona 1",  //60
  "Inibizione Riscald. Zona 2",
  "Inibizione Raffredd. Zona 2",
  "Setpoint Mandata Zona 1",
  "Setpoint Mandata Zona 2",
  "Consenso Termostato Est. Z1",  //65
  "Consenso Termostato Est. Z2",
  "Consenso Termostato Esterno",
  "Pompa Acqua 4",
  "Pompa Acqua 3",
  "Pompa Acqua 13",  // 70
  "Potenza Assorbita PdC",
  "Potenza Assorbita Calcolata",
  "Versione Software FTC",
  "Boost ACS",
  "Step Valvola Miscelatrice",  //75
  "Temperatura CPU Bridge",
  "Riscaldatore Integrativo 2",
  "CoP Istantaneo",
  "Temp. Liquido Refrig. TH3",
  "Numero Avvii Compressore",
  "Temperatura Scarico TH4",
  "Temperatura Sottoraffredd.",
  "Temperatura Dissipatore TH8",
  "Temp. Liq. Scambiatore TH6",
  "Velocità Ventola 1",
  "Velocità Ventola 2",
  "Valvola LEV A",
  "Valvola LEV B",
  "Temp. Ingresso Acqua TH32",
  "Potenza ACS Prod. Calcolata",
  "Potenza ACS Ass. Calcolata",
  "Potenza Riscald. Prod. Calc.",
  "Potenza Riscald. Ass. Calc.",
  "Potenza Raffredd. Ass. Calc.",
  "Temperatura Surriscald.",
  "Stato Protez. Ciclo Breve",
  "Versione SW Unità Esterna",
  "Stato Adattatore MELCloud",
  "Config. Dip Switch (1-1 a 7-8)",
  "Velocità PWM Pompa Acqua 1",
  "Temp. Ingresso Salamoia",
  "Temp. Uscita Salamoia",
  "CoP Totale Oggi",

  "Termostato ACS",
  "Termostato Zona 1",  //80
  "Termostato Zona 2",
  "Termostato Mandata Zona 1",
  "Termostato Mandata Zona 2",

  "Boost ACS Rapido",
  "Alimentazione Sistema",  //85
  "Modo Vacanza",
  "Modo Controllo Server",
  "Inibizione ACS",
  "Inibizione Riscald. Zona 1",
  "Inibizione Raffredd. Zona 1",  //90
  "Inibizione Riscald. Zona 2",
  "Inibizione Raffredd. Zona 2",
  "Boost ACS",
  "Protezione Ciclo Breve",
  "MELCloud Sola Lettura",

  "Modo ACS",
  "Modo Riscald/Raffredd Zona 1",  //95
  "Modo Riscald/Raffredd Zona 2",
  "Taglia Unità Esterna (kW)",
  "Percentuale Glicole",
  "Aggiornamento Firmware"
};

const char MQTT_AC_SENSOR_NAME[][45] PROGMEM = {
  "Stato Bridge",
  "Versione Firmware",
  "Segnale WiFi Bridge",
  "Frequenza Compressore",  // 10
  "iSee",
  "Modalità Timer",
  "Minuti Accensione Impostati",
  "Minuti Accensione Rimanenti",
  "Minuti Spegnimento Impostati",
  "Minuti Spegnimento Rimanenti",
  "Temperatura Ambiente",
  "Codice Errore",
  "Codice Guasto",
  "Potenza Assorbita",
  "Energia Totale",
  "Velocità Effettiva Ventola",
  "Modalità Auto",
  "Inibisci Telecomando",
  "Temperatura Esterna",
  "Tempo di Funzionamento",
  "Cambio Filtro",
  "Sbrinamento",
  "Preriscaldamento",
  "Standby",

  "Termostato Ambiente",
  "Potenza di Sistema",
  "Aggiornamento Firmware",
  "Temperatura remota",
  "Usa sensore remoto"
};

// Spanish
#elif defined(LANG_ES)
const char MQTT_SENSOR_NAME[][45] PROGMEM = {
  "Estado del Bridge",
  "Versión del Firmware",
  "Señal WiFi del Bridge",
  "Versión FTC",
  "Modo de Operación del Sistema",
  "Temp. Retorno Calefactor",  //5
  "Temp. Impulsión Calefactor",
  "Temperatura Exterior",
  "Desescarche",
  "Potencia de Salida Bomba Calor",
  "Frecuencia del Compresor",  // 10
  "Caudal",
  "Horas de Funcionamiento",
  "Temp. Máx de Impulsión",
  "Temp. Mín de Impulsión",
  "Temp. Impulsión Caldera",  //15
  "Temp. Retorno Caldera",
  "Temp. Tanque de Mezcla",
  "Temperatura Refrigerante",
  "Calentador de Inmersión",
  "Calentador de Apoyo 1",  //20
  "Bomba de Agua 1",
  "Bomba de Agua 2",
  "Válvula de Tres Vías 1",
  "Válvula de Tres Vías 2",
  "Temperatura ACS",  //25
  "Temp. ACS Superior",
  "Prohibir ACS",
  "ACS en Funcionamiento",
  "Modo Control ACS",
  "Consigna Legionela",  //30
  "Caída Máx Temp. ACS",
  "Fase Calentamiento ACS",
  "Temp. Impulsión Zona 1",
  "Temp. Retorno Zona 1",
  "Temp. Impulsión Zona 2",  //35
  "Temp. Retorno Zona 2",
  "Zona 1 Activa",
  "Zona 2 Activa",
  "Calefacción Consumida Ayer",
  "Calefacción Entregada Ayer",  //40
  "Refrigeración Consumida Ayer",
  "Refrigeración Entregada Ayer",
  "ACS Consumido Ayer",
  "ACS Entregado Ayer",
  "Energía Total Consumida Ayer",  //45
  "Energía Total Entregada Ayer",
  "COP Calefacción Ayer",
  "COP Refrigeración Ayer",
  "COP ACS Ayer",
  "COP Total Ayer",  //50
  "Cód. Fallo Refrigerante",
  "Código de Error",
  "Código de Fallo",
  "DeltaT Impulsión/Retorno",
  "Potencia Calor Computada",  //55
  "Potencia Frío Computada",
  "Calefacción en Marcha",
  "Refrigeración en Marcha",
  "Prohibir Calefacción Zona 1",
  "Prohibir Refrigeración Zona 1",  //60
  "Prohibir Calefacción Zona 2",
  "Prohibir Refrigeración Zona 2",
  "Consigna Impulsión Zona 1",
  "Consigna Impulsión Zona 2",
  "Demanda Termostato Ext. Zona 1",  //65
  "Demanda Termostato Ext. Zona 2",
  "Demanda Termostato Ext. Exterior",
  "Bomba de Agua 4",
  "Bomba de Agua 3",
  "Bomba de Agua 13",  // 70
  "Potencia Entrada Bomba Calor",
  "Potencia Entrada Computada",
  "Versión Software FTC",
  "Refuerzo ACS",
  "Paso Válvula Mezcladora",  //75
  "Temp. CPU del Bridge",
  "Calentador de Apoyo 2",
  "COP Instantáneo",
  "Temp. Líquido Refrigerante TH3",
  "Cantidad Arranques Compresor",
  "Temp. de Descarga TH4",
  "Temp. de Subenfriamiento",
  "Temp. del Disipador TH8",
  "Temp. Líquido Intercambiador TH6",
  "Velocidad Ventilador 1",
  "Velocidad Ventilador 2",
  "Válvula LEV A",
  "Válvula LEV B",
  "Temp. Entrada de Agua TH32",
  "Potencia ACS Entregada Comp.",
  "Potencia ACS Consumida Comp.",
  "Potencia Calor Entregada Comp.",
  "Potencia Calor Consumida Comp.",
  "Potencia Frío Consumida Comp.",
  "Temp. de Recalentamiento",
  "Estado Protección Ciclo Corto",
  "Versión Software Unidad Ext.",
  "Estado Adaptador MELCloud",
  "Config. Dip Switch (1-1 a 7-8)",
  "Velocidad PWM Bomba Agua 1",
  "Temp. Entrada Salmuera",
  "Temp. Salida Salmuera",
  "COP Total Hoy",

  "Termostato ACS",
  "Termostato Zona 1",  //80
  "Termostato Zona 2",
  "Termostato Impulsión Zona 1",
  "Termostato Impulsión Zona 2",

  "Refuerzo ACS Rápido",
  "Encendido del Sistema",  //85
  "Modo Vacaciones",
  "Modo Control Servidor",
  "Prohibir ACS",
  "Prohibir Calefacción Zona 1",
  "Prohibir Refrigeración Zona 1",  //90
  "Prohibir Calefacción Zona 2",
  "Prohibir Refrigeración Zona 2",
  "Refuerzo ACS",
  "Protección Ciclo Corto",
  "MELCloud Solo Lectura",

  "Modo ACS",
  "Modo Frío/Calor Zona 1",  //95
  "Modo Frío/Calor Zona 2",
  "Potencia Unidad Ext. (kW)",
  "Concentración Glicol",
  "Actualización de Firmware"
};

const char MQTT_AC_SENSOR_NAME[][45] PROGMEM = {
  "Estado del Bridge",
  "Versión de Firmware",
  "Señal WiFi del Bridge",
  "Frecuencia del Compresor",  // 10
  "iSee",
  "Modo Temporizador",
  "Minutos Encendido Prog.",
  "Minutos Encendido Rest.",
  "Minutos Apagado Prog.",
  "Minutos Apagado Rest.",
  "Temperatura Ambiente",
  "Código de Errore",
  "Código de Fallo",
  "Potencia de Entrada",
  "Energía Total",
  "Velocidad Real Ventilador",
  "Modo Automático",
  "Bloqueo de Mando",
  "Temperatura Exterior",
  "Tiempo de Funcionamiento",
  "Cambio de Filtro",
  "Desescarche",
  "Precalentamiento",
  "Standby",

  "Termostato Ambiente",
  "Potencia del Sistema",
  "Actualización de Firmware",
  "Temperatura remota",
  "Usar sensor remoto"
};


// English
#elif defined(LANG_EN)
const char MQTT_SENSOR_NAME[][45] PROGMEM = {
  "Bridge Status",
  "Firmware Version",
  "Bridge WiFi Signal",
  "FTC Version",
  "System Operation Mode",
  "Heater Return Temperature",  //5
  "Heater Flow Temperature",
  "Outside Temperature",
  "Defrost",
  "Heat Pump Output Power",
  "Compressor Frequency",  // 10
  "Flow Rate",
  "Run Hours",
  "Max Flow Temperature",
  "Min Flow Temperature",
  "Boiler Flow Temperature",  //15
  "Boiler Return Temperature",
  "Mixing Tank Temperature",
  "Refrigerant Temperature",
  "Immersion Heater",
  "Booster Heater 1",  //20
  "Water Pump 1",
  "Water Pump 2",
  "Three Way Valve 1",
  "Three Way Valve 2",
  "DHW Temperature",  //25
  "DHW Temperature Upper",
  "Prohibit DHW",
  "DHW Running",
  "DHW Control Mode",
  "Legionella Setpoint",  //30
  "DHW Max Temperature Drop",
  "DHW Heating Phase",
  "Zone 1 Flow Temperature",
  "Zone 1 Return Temperature",
  "Zone 2 Flow Temperature",  //35
  "Zone 2 Return Temperature",
  "Zone 1 Working",
  "Zone 2 Working",
  "Consumed Heating Yesterday",
  "Delivered Heating Yesterday",  //40
  "Consumed Cooling Yesterday",
  "Delivered Cooling Yesterday",
  "Consumed DHW Yesterday",
  "Delivered DHW Yesterday",
  "Total Consumed Energy Yesterday",  //45
  "Total Delivered Energy Yesterday",
  "Heating CoP Yesterday",
  "Cooling CoP Yesterday",
  "DHW CoP Yesterday",
  "Total CoP Yesterday",  //50
  "Refrigerant Fault Code",
  "Error Code",
  "Fault Code",
  "Flow Return DeltaT",
  "Computed Heat Output Power",  //55
  "Computed Cool Output Power",
  "Heating Running",
  "Cooling Running",
  "Zone 1 Heating Prohibit",
  "Zone 1 Cooling Prohibit",  //60
  "Zone 2 Heating Prohibit",
  "Zone 2 Cooling Prohibit",
  "Zone 1 Flow Setpoint",
  "Zone 2 Flow Setpoint",
  "Zone 1 Ext Thermostat Demand",  //65
  "Zone 2 Ext Thermostat Demand",
  "Outside Ext Thermostat Demand",
  "Water Pump 4",
  "Water Pump 3",
  "Water Pump 13",  // 70
  "Heat Pump Input Power",
  "Computed Input Power",
  "FTC Software Version",
  "DHW Boost",
  "Mixing Valve Step",  //75
  "Bridge CPU Temperature",
  "Booster Heater 2",
  "Instant CoP",
  "Refrigerant Liquid Temperature TH3",
  "Compressor Start Quantity",
  "Discharge Temperature TH4",
  "Subcool Temperature",
  "Heatsink Temperature TH8",
  "Plate Hex Liquid Temperature TH6",
  "Fan 1 Speed",
  "Fan 2 Speed",
  "Valve LEV A",
  "Valve LEV B",
  "Water Inlet Temperature TH32",
  "Computed DHW Output Power",
  "Computed DHW Input Power",
  "Computed Heating Output Power",
  "Computed Heating Input Power",
  "Computed Cooling Input Power",
  "Superheat Temperature",
  "Short Cycle Protection State",
  "Outdoor Unit Software Version",
  "MELCloud Adapter Status",
  "Dip Switch Configuration (Switch 1-1 to 7-8)",
  "Water Pump 1 PWM Speed",
  "Brine Inlet Temperature",
  "Brine Outlet Temperature",
  "Total CoP Today",

  "DHW Thermostat",
  "Zone 1 Thermostat",  //80
  "Zone 2 Thermostat",
  "Zone 1 Flow Thermostat",
  "Zone 2 Flow Thermostat",

  "Fast DHW Boost",
  "System Power",  //85
  "Holiday Mode",
  "Server Control Mode",
  "Prohibit DHW",
  "Prohibit Zone 1 Heating",
  "Prohibit Zone 1 Cooling",  //90
  "Prohibit Zone 2 Heating",
  "Prohibit Zone 2 Cooling",
  "DHW Boost",
  "Short Cycle Protection",
  "MELCloud Read Only",

  "DHW Mode",
  "Heating/Cooling Operation Mode Zone 1",  //95
  "Heating/Cooling Operation Mode Zone 2",
  "Outdoor Unit Size (kW)",
  "Glycol Strength",
  "Firmware Update"
};


const char MQTT_AC_SENSOR_NAME[][45] PROGMEM = {
  "Bridge Status",
  "Firmware Version",
  "Bridge WiFi Signal",
  "Compressor Frequency",  // 10
  "iSee",
  "Timer Mode",
  "On Minutes Set",
  "On Minutes Remaining",
  "Off MinutesSet",
  "Off Minutes Remaining",
  "Room Temperature",
  "Error Code",
  "Fault Code",
  "Input Power",
  "Lifetime Power",
  "Fan Actual Speed",
  "Auto Mode",
  "Remote Prohibit",
  "Outside Air Temperature",
  "Runtime",
  "Filter Change",
  "Defrost",
  "Preheat",
  "Standby",


  "Room Thermostat",
  "System Power",
  "Firmware Update",
  "Remote Room Temperature",
  "Use Remote Temperature"
};

// Polish
#elif defined(LANG_PL)
const char MQTT_SENSOR_NAME[][60] PROGMEM = { // Recommended to increase [45] to [60]
  "Status mostka",
  "Wersja oprogramowania",
  "Sygnal WiFi mostka",
  "Wersja FTC",
  "Tryb pracy systemu",
  "Temp. powrotu ogrzewania",  //5
  "Temp. zasilania ogrzewania",
  "Temperatura zewnetrzna",
  "Odszranianie",
  "Moc wyjsciowa pompy ciepla",
  "Czestotliwosc sprezarki",  // 10
  "Przepływ",
  "Czas pracy (godziny)",
  "Maks. temp. zasilania",
  "Min. temp. zasilania",
  "Temp. zasilania kotla",  //15
  "Temp. powrotu kotla",
  "Temperatura zbiornika buforowego",
  "Temperatura czynnika chlodniczego",
  "Grzalka zanurzeniowa",
  "Grzalka wspomagajaca 1",  //20
  "Pompa wody 1",
  "Pompa wody 2",
  "Zawor trojdrozny 1",
  "Zawor trojdrozny 2",
  "Temperatura CWU",  //25
  "Gorna temperatura CWU",
  "Blokada CWU",
  "Praca CWU",
  "Tryb sterowania CWU",
  "Nastawa dezynfekcji Legionelli",  //30
  "Maks. spadek temperatury CWU",
  "Faza grzania CWU",
  "Temp. zasilania Strefa 1",
  "Temp. powrotu Strefa 1",
  "Temp. zasilania Strefa 2",  //35
  "Temp. powrotu Strefa 2",
  "Praca Strefy 1",
  "Praca Strefy 2",
  "Zuzycie energii ogrzewanie wczoraj",
  "Dostarczone cieplo wczoraj",  //40
  "Zuzycie energii chlodzenie wczoraj",
  "Dostarczone chlodzenie wczoraj",
  "Zuzycie energii CWU wczoraj",
  "Dostarczone cieplo CWU wczoraj",
  "Calkowite zuzycie energii wczoraj",  //45
  "Calkowita dostarczona energia wczoraj",
  "COP ogrzewania wczoraj",
  "COP chlodzenia wczoraj",
  "COP CWU wczoraj",
  "Calkowity COP wczoraj",  //50
  "Kod bledu czynnika chlodniczego",
  "Kod bledu",
  "Kod usterki",
  "DeltaT zasilanie powrot",
  "Obliczona moc grzewcza wyjsciowa",  //55
  "Obliczona moc chlodnicza wyjsciowa",
  "Praca ogrzewania",
  "Praca chlodzenia",
  "Blokada ogrzewania Strefa 1",
  "Blokada chlodzenia Strefa 1",  //60
  "Blokada ogrzewania Strefa 2",
  "Blokada chlodzenia Strefa 2",
  "Nastawa zasilania Strefa 1",
  "Nastawa zasilania Strefa 2",
  "Zadanie termostatu zewn. Strefa 1",  //65
  "Zadanie termostatu zewn. Strefa 2",
  "Zadanie zewnetrznego termostatu",
  "Pompa wody 4",
  "Pompa wody 3",
  "Pompa wody 13",  // 70
  "Moc wejsciowa pompy ciepla",
  "Obliczona moc pobierana",
  "Wersja oprogramowania FTC",
  "Szybkie grzanie CWU",
  "Krok zaworu mieszajacego",  //75
  "Temperatura CPU mostka",
  "Grzalka wspomagajaca 2",
  "Chwilowy COP",
  "Temp. cieczy czynnika TH3",
  "Liczba uruchomien sprezarki",
  "Temperatura tloczenia TH4",
  "Temperatura dochlodzenia",
  "Temperatura radiatora TH8",
  "Temp. cieczy wymiennika płyt. TH6",
  "Predkosc wentylatora 1",
  "Predkosc wentylatora 2",
  "Zawor LEV A",
  "Zawor LEV B",
  "Temperatura wlotu wody TH32",
  "Obliczona moc grzewcza CWU",
  "Obliczony pobor mocy CWU",
  "Obliczona moc ogrzewania",
  "Obliczony pobor mocy ogrzewania",
  "Obliczony pobor mocy chlodzenia",
  "Temperatura przegrzania",
  "Stan ochrony przed krotkim cyklem",
  "Wersja oprogramowania jedn. zewn.",
  "Status adaptera MELCloud",
  "Konfiguracja Dip Switch (1-1 do 7-8)",
  "Predkosc PWM pompy wody 1",
  "Temperatura wlotu solanki",
  "Temperatura wylotu solanki",
  "Calkowity COP dzisiaj",

  "Termostat CWU",
  "Termostat Strefa 1",  //80
  "Termostat Strefa 2",
  "Termostat zasilania Strefa 1",
  "Termostat zasilania Strefa 2",

  "Szybkie wspomaganie CWU",
  "Zasilanie systemu",  //85
  "Tryb wakacyjny",
  "Tryb sterowania serwerem",
  "Blokada CWU",
  "Blokada ogrzewania Strefa 1",
  "Blokada chlodzenia Strefa 1",  //90
  "Blokada ogrzewania Strefa 2",
  "Blokada chlodzenia Strefa 2",
  "Wymuszenie CWU",
  "Ochrona przed krotkim cyklem",
  "MELCloud tylko do odczytu",

  "Tryb CWU",
  "Tryb pracy grzanie/chlodzenie Strefa 1",  //95
  "Tryb pracy grzanie/chlodzenie Strefa 2",
  "Moc jednostki zewnetrznej (kW)",
  "Stezenie glikolu",
  "Aktualizacja oprogramowania"
};


const char MQTT_AC_SENSOR_NAME[][60] PROGMEM = { // Recommended to increase [45] to [60]
  "Status mostka",
  "Wersja oprogramowania",
  "Sygnal WiFi mostka",
  "Czestotliwosc sprezarki",  // 10
  "Czujnik iSee",
  "Tryb timera",
  "Ustawiony czas wl. (minuty)",
  "Pozostaly czas wl. (minuty)",
  "Ustawiony czas wyl. (minuty)",
  "Pozostaly czas wyl. (minuty)",
  "Temperatura pokojowa",
  "Kod bledu",
  "Kod usterki",
  "Moc wejsciowa",
  "Laczne zuzycie energii",
  "Rzeczywista predkosc wentylatora",
  "Tryb Auto",
  "Blokada sterowania zdalnego",
  "Temperatura powietrza zewn.",
  "Czas pracy",
  "Wymiana filtra",
  "Odszranianie",
  "Podgrzewanie wstepne",
  "Tryb czuwania",


  "Termostat pokojowy",
  "Zasilanie systemu",
  "Aktualizacja oprogramowania",
  "Zdalna temperatura pokojowa",
  "Uzyj zdalnego czujnika temperatury"
};

// French
#elif defined(LANG_FR)
const char MQTT_SENSOR_NAME[][45] PROGMEM = {
  "Statut de la passerelle",
  "Version du firmware",
  "Signal WiFi de la passerelle",
  "Version FTC",
  "Mode de fonctionnement système",
  "Température retour chauffage",  //5
  "Température départ chauffage",
  "Température extérieure",
  "Dégivrage",
  "Puissance restituée PAC",
  "Fréquence du compresseur",  // 10
  "Débit",
  "Heures de fonctionnement",
  "Température départ max",
  "Température départ min",
  "Température départ chaudière",  //15
  "Température retour chaudière",
  "Température ballon de mélange",
  "Température du réfrigérant",
  "Thermoplongeur",
  "Réchauffeur de boucle 1",  //20
  "Pompe à eau 1",
  "Pompe à eau 2",
  "Vanne trois voies 1",
  "Vanne trois voies 2",
  "Température ECS",  //25
  "Température haute ECS",
  "Interdiction ECS",
  "ECS en cours",
  "Mode de régulation ECS",
  "Consigne anti-légionellose",  //30
  "Chute de temp maximale ECS",
  "Phase de chauffe ECS",
  "Température départ Zone 1",
  "Température retour Zone 1",
  "Température départ Zone 2",  //35
  "Température retour Zone 2",
  "Zone 1 active",
  "Zone 2 active",
  "Énergie chauffage consommée hier",
  "Énergie chauffage restituée hier",  //40
  "Énergie refroidissement conso hier",
  "Énergie refroidissement rest hier",
  "Énergie ECS consommée hier",
  "Énergie ECS restituée hier",
  "Énergie totale consommée hier",  //45
  "Énergie totale restituée hier",
  "COP chauffage hier",
  "COP refroidissement hier",
  "COP ECS hier",
  "COP total hier",  //50
  "Code défaut réfrigérant",
  "Code d'erreur",
  "Code de défaut",
  "DeltaT départ retour",
  "Puis. restituée calculée chaud",  //55
  "Puis. restituée calculée froid",
  "Chauffage en cours",
  "Refroidissement en cours",
  "Interdiction chauffage Zone 1",
  "Interdiction froid Zone 1",  //60
  "Interdiction chauffage Zone 2",
  "Interdiction froid Zone 2",
  "Consigne de départ Zone 1",
  "Consigne de départ Zone 2",
  "Demande thermostat ext Zone 1",  //65
  "Demande thermostat ext Zone 2",
  "Demande thermostat ext extér",
  "Pompe à eau 4",
  "Pompe à eau 3",
  "Pompe à eau 13",  // 70
  "Puissance absorbée PAC",
  "Puissance absorbée calculée",
  "Version logiciel FTC",
  "Boost ECS",
  "Pas de la vanne mélangeuse",  //75
  "Température CPU passerelle",
  "Réchauffeur de boucle 2",
  "COP instantané",
  "Temp liquide réfrigérant TH3",
  "Nombre de démarrages compresseur",
  "Température de refoulement TH4",
  "Température de sous-refroidis.",
  "Température dissipateur TH8",
  "Temp liquide échangeur plaques TH6",
  "Vitesse ventilateur 1",
  "Vitesse ventilateur 2",
  "Vanne LEV A",
  "Vanne LEV B",
  "Température entrée d'eau TH32",
  "Puis. restituée calculée ECS",
  "Puissance absorbée calculée ECS",
  "Puis. calculée restituée chaud",
  "Puis. calculée absorbée chaud",
  "Puis. calculée absorbée froid",
  "Température de surchauffe",
  "État protect. cycle court",
  "Version logiciel unité ext",
  "Statut adaptateur MELCloud",
  "Config Dip Switch (1-1 à 7-8)",
  "Vitesse PWM pompe à eau 1",
  "Température entrée eau glycolée",
  "Température sortie eau glycolée",
  "COP total aujourd'hui",

  "Thermostat ECS",
  "Thermostat Zone 1",  //80
  "Thermostat Zone 2",
  "Thermostat de départ Zone 1",
  "Thermostat de départ Zone 2",

  "Boost ECS rapide",
  "Alimentation système",  //85
  "Mode vacances",
  "Mode contrôle serveur",
  "Interdire ECS",
  "Interdire chauffage Zone 1",
  "Interdire refroidissement Zone 1",  //90
  "Interdire chauffage Zone 2",
  "Interdire refroidissement Zone 2",
  "Boost ECS active",
  "Protection cycle court",
  "MELCloud lecture seule",

  "Mode ECS",
  "Mode fonct. chaud/froid Zone 1",  //95
  "Mode fonct. chaud/froid Zone 2",
  "Puissance unité ext (kW)",
  "Taux de glycol",
  "Mise à jour du firmware"
};

const char MQTT_AC_SENSOR_NAME[][45] PROGMEM = {
  "État du Bridge",
  "Version du Firmware",
  "Signal WiFi du Bridge",
  "Fréquence Compresseur",  // 10
  "iSee",
  "Mode Minuterie",
  "Minutes Marche Définies",
  "Minutes Marche Restantes",
  "Minutes Arrêt Définies",
  "Minutes Arrêt Restantes",
  "Température Ambiante",
  "Code Erreur",
  "Code Défaut",
  "Puissance Absorbée",
  "Énergie Totale",
  "Vitesse Réelle Ventilo",
  "Mode Automatique",
  "Verrouillage Télécommande",
  "Température Extérieure",
  "Temps de Fonctionnement",
  "Changement Filtre",
  "Dégivrage",
  "Préchauffage",
  "Standby",

  "Thermostat Ambiant",
  "Puissance Système",
  "Mise à Jour Firmware",
  "Température capteur distant",
  "Utiliser le capteur distant"
};


// Dutch
#elif defined(LANG_NL)
const char MQTT_SENSOR_NAME[][45] PROGMEM = {
  "Bridge Status",
  "Firmware Versie",
  "Bridge WiFi Signaal",
  "FTC Versie",
  "Systeem Bedrijfsmodus",
  "Retourtemperatuur Verwarming",  //5
  "Aanvoertemperatuur Verwarming",
  "Buitentemperatuur",
  "Ontdooien",
  "Warmtepomp Vermogen",
  "Compressor Frequentie",  // 10
  "Debiet",
  "Bedrijfsuren",
  "Max Aanvoertemperatuur",
  "Min Aanvoertemperatuur",
  "Aanvoertemperatuur Ketel",  //15
  "Retourtemperatuur Ketel",
  "Mengtank Temperatuur",
  "Koudemiddel Temperatuur",
  "Elektrisch Element",
  "Bijverwarming 1",  //20
  "Waterpomp 1",
  "Waterpomp 2",
  "Driewegklep 1",
  "Driewegklep 2",
  "SWW Temperatuur",  //25
  "SWW Temperatuur Boven",
  "SWW Blokkeren",
  "SWW Actief",
  "SWW Regelmodus",
  "Legionella Instelwaarde",  //30
  "SWW Max Temperatuurdal",
  "SWW Verwarmingsfase",
  "Zone 1 Aanvoertemperatuur",
  "Zone 1 Retourtemperatuur",
  "Zone 2 Aanvoertemperatuur",  //35
  "Zone 2 Retourtemperatuur",
  "Zone 1 Actief",
  "Zone 2 Actief",
  "Verbruikt Verwarmen Gisteren",
  "Geleverd Verwarmen Gisteren",  //40
  "Verbruikt Koelen Gisteren",
  "Geleverd Koelen Gisteren",
  "Verbruikt SWW Gisteren",
  "Geleverd SWW Gisteren",
  "Totaal Verbruikt Gisteren",  //45
  "Totaal Geleverd Gisteren",
  "CoP Verwarmen Gisteren",
  "CoP Koelen Gisteren",
  "CoP SWW Gisteren",
  "Totaal CoP Gisteren",  //50
  "Koudemiddel Foutcode",
  "Foutcode",
  "Storingscode",
  "DeltaT Aanvoer Retour",
  "Berekend Verwarmingsvermogen",  //55
  "Berekend Koelvermogen",
  "Verwarmen Actief",
  "Koelen Actief",
  "Zone 1 Verwarmen Blokkeren",
  "Zone 1 Koelen Blokkeren",  //60
  "Zone 2 Verwarmen Blokkeren",
  "Zone 2 Koelen Blokkeren",
  "Zone 1 Aanvoer Instelwaarde",
  "Zone 2 Aanvoer Instelwaarde",
  "Zone 1 Ext Thermostaat Vraag",  //65
  "Zone 2 Ext Thermostaat Vraag",
  "Buiten Ext Thermostaat Vraag",
  "Waterpomp 4",
  "Waterpomp 3",
  "Waterpomp 13",  // 70
  "Warmtepomp Opgenomen Vermogen",
  "Berekend Opgenomen Vermogen",
  "FTC Software Versie",
  "SWW Boost",
  "Mengklep Stap",  //75
  "Bridge CPU Temperatuur",
  "Bijverwarming 2",
  "Actuele CoP",
  "Vloeibaar Koudemiddel Temp TH3",
  "Aantal Compressor Starts",
  "Persgastemperatuur TH4",
  "Subcooling Temperatuur",
  "Koellichaam Temperatuur TH8",
  "Platenwisselaar Vloeistof TH6",
  "Ventilator 1 Snelheid",
  "Ventilator 2 Snelheid",
  "Klep LEV A",
  "Klep LEV B",
  "Waterinlaattemperatuur TH32",
  "Berekend SWW Vermogen",
  "Berekend Opgenomen SWW Vermgen",
  "Berekend Verwarming Vermogen",
  "Berekend Opgen Verw Vermogen",
  "Berekend Opgen Koel Vermogen",
  "Oververhitting Temperatuur",
  "Korte Cyclus Bescherming",
  "Buitenunit Software Versie",
  "MELCloud Adapter Status",
  "Dip Switch Config (1-1 tot 7-8)",
  "Waterpomp 1 PWM Snelheid",
  "Brine Inlaattemperatuur",
  "Brine Uitlaattemperatuur",
  "Totaal CoP Vandaag",

  "SWW Thermostaat",
  "Zone 1 Thermostaat",  //80
  "Zone 2 Thermostaat",
  "Zone 1 Aanvoer Thermostaat",
  "Zone 2 Aanvoer Thermostaat",

  "Snelle SWW Boost",
  "Systeem Ingeschakeld",  //85
  "Vakantiemodus",
  "Server Regelmodus",
  "SWW Blokkeren",
  "Zone 1 Verwarmen Blokkeren",
  "Zone 1 Koelen Blokkeren",  //90
  "Zone 2 Verwarmen Blokkeren",
  "Zone 2 Koelen Blokkeren",
  "SWW Boost",
  "Korte Cyclus Bescherming",
  "MELCloud Alleen Lezen",

  "SWW Modus",
  "Bedrijfsmodus Verw/Koel Zone 1",  //95
  "Bedrijfsmodus Verw/Koel Zone 2",
  "Buitenunit Vermogen (kW)",
  "Glycol Concentratie",
  "Firmware Update"
};

const char MQTT_AC_SENSOR_NAME[][45] PROGMEM = {
  "Bridge-status",
  "Firmware-versie",
  "Bridge wifi-signaal",
  "Compressorfrequentie",  // 10
  "iSee",
  "Timer-modus",
  "Inschakeltijd ingesteld",
  "Inschakeltijd resterend",
  "Uitschakeltijd ingesteld",
  "Uitschakeltijd resterend",
  "Kamertemperatuur",
  "Foutcode",
  "Storingscode",
  "Ingangsvermogen",
  "Totale energie",
  "Actuele ventilator-snelh.",
  "Automatische modus",
  "Afstandsbediening blokk.",
  "Buitentemperatuur",
  "Bedrijfstijd",
  "Filter vervangen",
  "Ontdooien",
  "Voorverwarmen",
  "Standby",

  "Ruimtethermostaat",
  "Systeemvermogen",
  "Firmware-update",
  "Externe temperatuur",
  "Externe sensor gebruiken"
};

#endif



const char MQTT_TOPIC[][34] PROGMEM = {
  "/LWT",                               //0
  "/Status/WiFiStatus",                 //1
  "/Status/System",                     //2
  "/Status/Advanced",                   //3
  "/Status/HotWater",                   //4
  "/Status/Zone1",                      //5
  "/Status/Zone2",                      //6
  "/Status/Energy",                     //7
  "/Status/AdvancedTwo",                //8
  "/Status/Configuration",              //9
  "/Status/ActiveControl",              //10
  "/Command/System/HeatingMode",        //11
  "/Command/HotWater/Setpoint",         //12
  "/Command/Zone1/ThermostatSetpoint",  //13
  "/Command/Zone2/ThermostatSetpoint",  //14
  "/Command/HotWater/Boost",            //15
  "/Command/System/Power",              //16
  "/Command/System/HolidayMode",        //17
  "/Command/System/SvrControlMode",     //18
  "/Command/HotWater/Prohibit",         //19
  "/Command/Zone1/ProhibitHeating",     //20
  "/Command/Zone1/ProhibitCooling",     //21
  "/Command/Zone2/ProhibitHeating",     //22
  "/Command/Zone2/ProhibitCooling",     //23
  "/Command/HotWater/NormalBoost",      //24
  "/Command/System/ActiveControl",      //25
  "/Command/Zone1/FlowSetpoint",        //26
  "/Command/Zone2/FlowSetpoint",        //27
  "/Command/HotWater/Mode",             //28
  "/Command/Zone1/HeatingMode",         //29
  "/Command/Zone2/HeatingMode",         //30
  "/Command/System/UnitSize",           //31
  "/Command/System/Glycol",             //32
  "/Command/System/Svc",                //33
  "/Status/WiFiStatus/Update",          //34
};


int MQTT_SWITCH_STATE_POS[] PROGMEM = {
  4,
  2,
  2,
  8,
  4,
  5,
  5,
  6,
  6,
  4,
  10,
  1
};

int MQTT_TOPIC_POS[] PROGMEM = {
  0,
  1,
  1,
  1,
  2,
  2,  //5
  2,
  2,
  2,
  2,  //10
  2,
  2,
  2,
  3,
  3,  //15
  3,
  3,
  3,
  3,  //20
  3,
  3,
  3,
  8,
  3,  //25
  8,
  4,
  4,
  4,
  4,  //30
  4,
  4,
  4,
  4,
  5,  //35
  5,
  6,
  6,
  5,
  6,  //40
  7,
  7,
  7,
  7,
  7,  //45
  7,
  7,
  7,
  7,
  7,  //50
  7,
  7,
  8,
  8,
  8,  //55
  2,
  2,
  2,
  3,
  3,  //60
  5,
  5,
  6,
  6,
  5,  //65
  6,
  8,
  8,
  8,
  8,
  8,
  8,
  2,
  2,
  1,
  4,
  3,
  1,
  3,
  2,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  2,
  2,
  2,
  2,
  2,
  9,
  10,
  1,
  1,
  9,
  2,
  3,
  3,
  7
};

int MQTT_UNITS_POS[] PROGMEM = {
  0,
  0,
  1,
  0,
  0,
  2,  //5
  2,
  2,
  0,
  3,  //10
  4,
  5,
  6,
  2,
  2,  //15
  2,
  2,
  2,
  2,  //20
  0,
  0,
  0,
  0,
  0,  //25
  0,
  2,
  2,
  0,
  0,  //30
  0,
  2,
  2,
  0,
  2,  //35
  2,
  2,
  2,
  0,
  0,  //40
  7,
  7,
  7,
  7,
  7,  //45
  7,
  7,
  7,
  8,
  8,  //50
  8,
  8,
  0,
  0,
  0,  //55
  2,
  3,
  3,
  0,
  0,  //60
  0,
  0,
  0,
  0,
  2,  //65
  2,
  0,
  0,
  0,
  0,
  0,
  0,
  3,
  3,
  0,
  0,
  0,
  2,
  0,
  8,
  2,
  12,
  2,
  2,
  2,
  2,
  10,
  10,
  11,
  11,
  2,
  3,
  3,
  3,
  3,
  3,
  2,
  0,
  0,
  0,
  0,
  0,
  2,
  2,
  8
};


const char MQTT_OBJECT_ID[][19] PROGMEM = {
  "dhw_climate",
  "zone1_climate",
  "zone2_climate",
  "zone1_flow_climate",
  "zone2_flow_climate"
};


int MQTT_CLIMATE_MAX[] PROGMEM = {
  60,
  30,
  30,
  60,
  60,
  65,
  70
};

int MQTT_CLIMATE_MIN[] PROGMEM = {
  0,
  10,
  10,
  5,
  5
};

float MQTT_CLIMATE_TEMP_STEP[] PROGMEM = {
  0.5,
  0.5,
  0.5,
  0.1,
  0.1
};

float MQTT_CLIMATE_PRECISION[] PROGMEM = {
  0.5,
  0.5,
  0.5,
  0.1,
  0.1
};

int MQTT_CLIMATE_INITAL[] PROGMEM = {
  50,
  10,
  10,
  30,
  30
};

const char MQTT_CLIMATE_MODE[][120] PROGMEM = {
  "{%set values = {'heat':'Heating Temperature','cool':'Cooling Temperature'}%}{{values[value] if value in values.keys()}}"
};

const char MQTT_CLIMATE_STATE_TOPIC[][375] PROGMEM = {
  "{{'heat' if states('sensor.ecodan_ashp_prohibit_dhw')=='0' or states('sensor.ecodan_ashp_dhw_heating_phase')!='Off' else 'off'}}",
  "{{'heat' if (value_json.OpMode=='Heat' and states('sensor.ecodan_ashp_zone_1_heating_prohibit')=='0') else 'cool' if (value_json.OpMode=='Cool' and states('sensor.ecodan_ashp_zone_1_cooling_prohibit')=='0') else 'off'}}",
  "{{'heat' if (value_json.OpMode=='Heat' and state_attr('climate.zone2_climate','current_temperature')!=0 and states('sensor.ecodan_ashp_zone_2_heating_prohibit')=='0') else 'cool' if (value_json.OpMode=='Cool' and state_attr('climate.zone2_climate','current_temperature')|default(0)!=0 and states('sensor.ecodan_ashp_zone_2_cooling_prohibit')|default(0)=='0') else 'off'}}",
  "{{'heat' if (value_json.OpMode=='Heat' and states('sensor.ecodan_ashp_zone_1_heating_prohibit')=='0') else 'cool' if (value_json.OpMode=='Cool' and states('sensor.ecodan_ashp_zone_1_cooling_prohibit')=='0') else 'off'}}",
  "{{'heat' if (value_json.OpMode=='Heat' and state_attr('climate.zone2_climate','current_temperature')!=0 and states('sensor.ecodan_ashp_zone_2_heating_prohibit')=='0') else 'cool' if (value_json.OpMode=='Cool' and state_attr('climate.zone2_climate','current_temperature')|default(0)!=0 and states('sensor.ecodan_ashp_zone_2_cooling_prohibit')|default(0)=='0') else 'off'}}"
};

const char MQTT_CLIMATE_MODE_STATE_TEMPLATE[][455] PROGMEM = {
  "{{'heating' if value_json.SystemOperationMode in ['Hot Water','Legionella'] else 'defrosting' if value_json.SystemOperationMode in ['Defrosting','Frost Protect'] else 'idle' if states('sensor.ecodan_ashp_prohibit_dhw')!='1' else 'off'}}",
  "{%set mode=value_json.SystemOperationMode|lower%}{%set h_prhbt=not(states('sensor.ecodan_ashp_zone_1_heating_prohibit')|bool(false))%}{%set c_prhbt=not(states('sensor.ecodan_ashp_zone_1_cooling_prohibit')|bool(false))%}{%set wrkg=states('sensor.ecodan_ashp_zone_1_working')|bool(false)%}{%if mode in ['defrosting','frost protect']%}defrosting{%elif ((h_prhbt or c_prhbt) and not(wrkg)) or mode in ['hot water','legionella']%}idle{%else%}{{mode}}{%endif%}",
  "{%set mode=value_json.SystemOperationMode|lower%}{%set h_prhbt=not(states('sensor.ecodan_ashp_zone_2_heating_prohibit')|bool(false))%}{%set c_prhbt=not(states('sensor.ecodan_ashp_zone_2_cooling_prohibit')|bool(false))%}{%set wrkg=states('sensor.ecodan_ashp_zone_2_working')|bool(false)%}{%if mode in ['defrosting','frost protect']%}defrosting{%elif ((h_prhbt or c_prhbt) and not(wrkg)) or mode in ['hot water','legionella']%}idle{%else%}{{mode}}{%endif%}",
  "{%set mode=value_json.SystemOperationMode|lower%}{%set h_prhbt=not(states('sensor.ecodan_ashp_zone_1_heating_prohibit')|bool(false))%}{%set c_prhbt=not(states('sensor.ecodan_ashp_zone_1_cooling_prohibit')|bool(false))%}{%set wrkg=states('sensor.ecodan_ashp_zone_1_working')|bool(false)%}{%if mode in ['defrosting','frost protect']%}defrosting{%elif ((h_prhbt or c_prhbt) and not(wrkg)) or mode in ['hot water','legionella']%}idle{%else%}{{mode}}{%endif%}",
  "{%set mode=value_json.SystemOperationMode|lower%}{%set h_prhbt=not(states('sensor.ecodan_ashp_zone_2_heating_prohibit')|bool(false))%}{%set c_prhbt=not(states('sensor.ecodan_ashp_zone_2_cooling_prohibit')|bool(false))%}{%set wrkg=states('sensor.ecodan_ashp_zone_2_working')|bool(false)%}{%if mode in ['defrosting','frost protect']%}defrosting{%elif ((h_prhbt or c_prhbt) and not(wrkg)) or mode in ['hot water','legionella']%}idle{%else%}{{mode}}{%endif%}",
};

const char MQTT_SELECT_VALUE_TEMPLATE[][480] PROGMEM = {
  "{{'Normal' if value_json.HotWaterControlMode=='Normal' else 'Eco' if value_json.HotWaterControlMode=='Eco'}}",
  "{{'Heating Temperature' if value_json.HeatingControlMode=='Temp' else 'Heating Flow' if value_json.HeatingControlMode=='Flow' else 'Heating Compensation' if value_json.HeatingControlMode=='Compensation' else 'Cooling Temperature' if value_json.HeatingControlMode=='Cool' else 'Cooling Flow' if value_json.HeatingControlMode=='Cool Flow' else 'Dry Up' if value_json.HeatingControlMode=='Dry Up' else 'Cool Compensation' if value_json.HeatingControlMode=='Cool Compensation'}}",
  "{{'Heating Temperature' if value_json.HeatingControlMode=='Temp' else 'Heating Flow' if value_json.HeatingControlMode=='Flow' else 'Heating Compensation' if value_json.HeatingControlMode=='Compensation' else 'Cooling Temperature' if value_json.HeatingControlMode=='Cool' else 'Cooling Flow' if value_json.HeatingControlMode=='Cool Flow' else 'Dry Up' if value_json.HeatingControlMode=='Dry Up' else 'Cool Compensation' if value_json.HeatingControlMode=='Cool Compensation'}}",
  "{{value_json.UnitSize}}",
  "{{value_json.Glycol}}"
};

const char MQTT_SENSOR_UNITS[][7] PROGMEM = {
  "",
  "dBm",
  "°C",
  "kW",
  "Hz",
  "L/min",
  "h",
  "kWh",
  "CoP",
  "C",  //Unused
  "rpm",
  "Pulses",
  "Times"
};

const char MQTT_NUMBER_AVAIL_TEMPLATE[][98] PROGMEM = {
  "{{'online' if value_json.HeatingControlMode in ['Flow','Cool Flow'] else 'offline'}}",
  "{{'online' if value_json.Has2Zone is true and value_json.HasSimple2Zone is false else 'offline'}}",
  "{{'online' if value_json.MELCloud_Status in ['Online','Offline'] else 'offline'}}"
};

const char MQTT_SENSOR_VALUE_TEMPLATE[][154] PROGMEM = {
  "{{ value if value is defined else 'Unknown' }}",
  "{{ value_json.Firmware }}",
  "{{ value_json.RSSI }}",
  "{{ value_json.FTCVersion }}",
  "{{ value_json.SystemOperationMode }}",
  "{{ value_json.HeaterReturn|round(1) }}",  //5
  "{{ value_json.HeaterFlow|round(1) }}",
  "{{ value_json.OutsideTemp }}",
  "{{ value_json.Defrost }}",
  "{{ value_json.HeaterPower }}",
  "{{ value_json.Compressor }}",  //10
  "{{ value_json.FlowRate }}",
  "{{ value_json.RunHours }}",
  "{{ value_json.FlowTMax }}",
  "{{ value_json.FlowTMin }}",
  "{{ value_json.BoilerFlow }}",  //15
  "{{ value_json.BoilerReturn }}",
  "{{ value_json.MixingTemp }}",
  "{{ value_json.RefrigeTemp }}",
  "{{ value_json.Immersion }}",
  "{{ value_json.Booster }}",  //20
  "{{ value_json.PrimaryWaterPump }}",
  "{{ value_json.WaterPump2 }}",
  "{{ value_json.ThreeWayValve }}",
  "{{ value_json.ThreeWayValve2 }}",
  "{{ value_json.Temperature|round(1) }}",  //25
  "{{ value_json.TempTHW5A|round(1) }}",
  "{{ value_json.ProhibitDHW }}",
  "{{ value_json.DHWActive }}",
  "{{ value_json.HotWaterControlMode }}",
  "{{ value_json.LegionellaSetpoint }}",  //30
  "{{ value_json.HotWaterMaxTDrop }}",
  "{{ value_json.HotWaterPhase }}",
  "{{ value_json.FlowTemp }}",
  "{{ value_json.ReturnTemp }}",
  "{{ value_json.FlowTemp }}",  //35
  "{{ value_json.ReturnTemp }}",
  "{{ value_json.TwoZone_Z1Working }}",
  "{{ value_json.TwoZone_Z2Working }}",
  "{{ value_json.CHEAT|round(2) }}",
  "{{ value_json.DHEAT|round(2) }}",  //40
  "{{ value_json.CCOOL|round(2) }}",
  "{{ value_json.DCOOL|round(2) }}",
  "{{ value_json.CDHW|round(2) }}",
  "{{ value_json.DDHW|round(2) }}",
  "{{ value_json.CTOTAL|round(2) }}",  //45
  "{{ value_json.DTOTAL|round(2) }}",
  "{{ value_json.HEAT_CoP|round(2) }}",
  "{{ value_json.COOL_CoP|round(2) }}",
  "{{ value_json.DHW_CoP|round(2) }}",
  "{{ value_json.TOTAL_CoP|round(2) }}",  //50
  "{{ value_json.RefrigeFltCode }}",
  "{{ value_json.ErrCode }}",
  "{{ value_json.FltCode }}",
  "{{ value_json.FlowReturnDeltaT }}",
  "{{ value_json.EstHeatOutputPower }}",  //55
  "{{ value_json.EstCoolOutputPower }}",
  "{{ value_json.HeatingActive }}",
  "{{ value_json.CoolingActive }}",
  "{{ value_json.ProhibitHeating }}",
  "{{ value_json.ProhibitCooling }}",  //60
  "{{ value_json.ProhibitHeating }}",
  "{{ value_json.ProhibitCooling }}",
  "{{ value_json.FSP }}",
  "{{ value_json.FSP }}",
  "{{ value_json.Z1TstatDemand }}",  //65
  "{{ value_json.Z2TstatDemand }}",
  "{{ value_json.OTstatDemand }}",
  "{{ value_json.WaterPump4 }}",
  "{{ value_json.WaterPump3 }}",
  "{{ value_json.WaterPump13 }}",  //70
  "{{ value_json.InputPower }}",
  "{{ value_json.EstInputPower }}",
  "{{ value_json.FTCSoftwareVersion }}",
  "{{ value_json.HotWaterEcoBoostActive }}",
  "{{ value_json.MixingStep }}",  //75
  "{{ value_json.CPUTemp }}",
  "{{ value_json.Booster2 }}",
  "{{ value_json.Instant_CoP }}",
  "{{ value_json.LiquidTemp }}",
  "{{ value_json.CompOpTimes|int *100 }}",
  "{{ value_json.TH4Discharge }}",
  "{{ value_json.Subcool }}",
  "{{ value_json.TH8HeatSink }}",
  "{{ value_json.TH6Pipe }}",
  "{{ value_json.Fan1RPM }}",
  "{{ value_json.Fan2RPM }}",
  "{{ value_json.LEVA }}",
  "{{ value_json.LEVB }}",
  "{{ value_json.TH32Pipe }}",
  "{{ value_json.EstDHWOutputPower }}",
  "{{ value_json.EstDHWInputPower }}",
  "{{ value_json.EstHeatingOutputPower }}",
  "{{ value_json.EstHeatingInputPower }}",
  "{{ value_json.EstCoolingInputPower }}",
  "{{ value_json.Superheat }}",
  "{{ value_json.ShortCycleProtectionActive }}",
  "{{ value_json.OutdoorSoftwareVersion }}",
  "{{ value_json.MELCloud_Status }}",
  "{{value_json.DipSw1~' '~value_json.DipSw2~' '~value_json.DipSw3~' '~value_json.DipSw4~' '~value_json.DipSw5~' '~value_json.DipSw6~' '~value_json.DipSw7}}",
  "{{ value_json.PumpPWM }}",
  "{{ value_json.BrineInletTemp }}",
  "{{ value_json.BrineOutletTemp }}",
  "{{ value_json.OB_TOTAL_CoP_TDay }}",
  "{{ value_json }}",
  "{{ value_json.Setpoint }}",  //80
  "{{ value_json.FSP }}",
  "{{ value_json.HotWaterBoostActive }}",
  "{{ value_json.SystemPower }}",
  "{{ value_json.HolidayMode }}",
  "{{ value_json.SvrControlMode }}",  //85
  "{{ value_json.ProhibitDHW }}",
  "{{ value_json.ProhibitHeating }}",
  "{{ value_json.ProhibitCooling }}",
  "{{ value_json.ProhibitHeating }}",
  "{{ value_json.ProhibitCooling }}",  //90
  "{{ value_json.HotWaterEcoBoostActive }}",
  "{{ value_json.ShortCycleProtectionEnabled }}",
  "{{ value_json.MELCloud_Write_Blocking }}",
  "{{ value_json.HeatingControlMode }}",
  "{{ value_json.latest_version }}"
};


const char MQTT_AC_SENSOR_VALUE_TEMPLATE[][154] PROGMEM = {
  "{{ value if value is defined else 'Unknown' }}",
  "{{ value_json.Firmware }}",
  "{{ value_json.RSSI }}",

  "{{ value_json.compressorFreq }}",
  "{{ value_json.iSee }}",
  "{{ value_json.timermode }}",
  "{{ value_json.onMinsSet }}",
  "{{ value_json.onMinsRemain }}",
  "{{ value_json.offMinsSet }}",
  "{{ value_json.offMinsRemain }}",
  "{{ value_json.RoomTemp }}",

  "{{ value_json.ErrCode }}",
  "{{ value_json.FltCode }}",
  "{{ value_json.InPwr }}",
  "{{ value_json.LPwr }}",
  "{{ value_json.FAct }}",
  "{{ value_json.Auto }}",
  "{{ value_json.RPhbt }}",
  "{{ value_json.OAT }}",
  "{{ value_json.Rtme }}",
  "{{ value_json.fltr }}",
  "{{ value_json.dfrst }}",
  "{{ value_json.prht }}",
  "{{ value_json.sby }}",

  "{{ value_json.latest_version }}"
};

const char MQTT_DISCOVERY_TOPICS[][23] PROGMEM = {
  "homeassistant/sensor/",
  "homeassistant/climate/",
  "homeassistant/switch/",
  "homeassistant/climate/",
  "homeassistant/select/",
  "/config",
  "homeassistant/update/",
  "homeassistant/number/"
};

const char MQTT_DEVICE_CLASS[][17] PROGMEM = {  // Uses same structure as Units - but blank when no match
  "",
  "signal_strength",
  "temperature",
  "power",
  "frequency",
  "volume_flow_rate",
  "duration",
  "energy",
  "firmware"
};