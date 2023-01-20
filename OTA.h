void OTASetup(const char *HostName)
{
  ArduinoOTA.onStart([]()
  {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
    {
      type = "sketch";
    }
    else     // U_SPIFFS
    {
      type = "filesystem";
    }

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating ");
  });

  ArduinoOTA.onEnd([]()
  {
    Serial.println("End");
  });



  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
  {
    
    Serial.println( progress );
  });



  ArduinoOTA.onError([](ota_error_t error)
  {
    Serial.print  ("Error ");
    Serial.println(error);
    
    if (error == OTA_AUTH_ERROR)
    {
      Serial.println("Auth Failed");
    }
    else if (error == OTA_BEGIN_ERROR)
    {
      Serial.println("Begin Failed");
    }
    else if (error == OTA_CONNECT_ERROR)
    {
      Serial.println("Connect Failed");
    }
    else if (error == OTA_RECEIVE_ERROR)
    {
      Serial.println("Receive Failed");
    }
    else if (error == OTA_END_ERROR)
    {
      Serial.println("End Failed");
    }
  });

  ArduinoOTA.setHostname(HostName);
  ArduinoOTA.begin();
}
