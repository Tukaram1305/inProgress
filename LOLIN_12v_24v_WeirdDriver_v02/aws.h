#ifndef AWS_H
#define AWS_H



server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Tutaj LOLIN AWS!");
  });

server.on("/pixel", HTTP_GET, [] (AsyncWebServerRequest *request) {
    int NR, VAL;
    String inputMessage;
    if (request->hasParam("nr"))
    {
      inputMessage = request->getParam("nr")->value();
      NR = inputMessage.toInt();

      if (request->hasParam("val"))
      {
        inputMessage = request->getParam("val")->value();
        VAL = inputMessage.toInt();

        int ccR = VAL>>16;
        int ccG = (VAL&0xFF00)>>8;
        int ccB = (VAL&0xFF);
        //intToRGB(VAL, crgb);
          //leds[NR] = CRGB(crgb.r, crgb.g, crgb.b);
          led.writeRGB(NR, static_cast<uint8_t>(ccR), static_cast<uint8_t>(ccG), static_cast<uint8_t>(ccB));
          //FastLED.show();
          String mes = "UFL n. "+String(NR)+" : "+String(ccR)+"/"+String(ccG)+"/"+String(ccB);
          request->send(200, "text/plain", mes.c_str());
      }
    }

    else 
    {
      request->send(200, "application/json", "OK!, bez paramu");
      Serial.println("\nSET LED OK, ale nic nie dostalem");
    }
  });


    server.on("/setmode", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    if (request->hasParam("m"))
    {
      inputMessage = request->getParam("m")->value();
      if (inputMessage=="0")
      {
          led.setMode(MYLEDS::MODES::pixel);
      }
      else if (inputMessage=="1")
      {
          led.setMode(MYLEDS::MODES::softrun);
      }
      else 
      {
        request->send(200, "application/json", "Bez paramu!");
      }
    }
    else 
    {
      request->send(200, "application/json", "OK, bez paramu");
      Serial.println("\nbez paramu");
    }
  });

    server.on("/setspeed", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    if (request->hasParam("speed"))
    {
      inputMessage = request->getParam("speed")->value();
      uint16_t NR = inputMessage.toInt();
      led.setSpeed(NR);
    }
    else 
    {
      request->send(200, "application/json", "OK, bez paramu");
      Serial.println("\nbez paramu");
    }
  });
  
    server.on("/clear", HTTP_GET, [] (AsyncWebServerRequest *request) {
      led.clear();
      request->send(200, "application/json", "Czyszcze!");
      Serial.println("\nbez paramu");
  });
#endif
