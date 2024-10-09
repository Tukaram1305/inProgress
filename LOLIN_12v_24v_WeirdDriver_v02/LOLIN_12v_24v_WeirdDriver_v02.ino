
#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#elif defined(ESP32)
  #include <WiFi.h>
  #include <AsyncTCP.h>
#endif

#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include <FastLED.h>

const char* ssid = "RagNet";
const char* password =  "azgard666";
// spobuje ustawic statyczne IP
IPAddress local_IP(192, 168, 1, 152);
IPAddress gateway(192, 168, 1 ,1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8); 
IPAddress secondaryDNS(8, 8, 4, 4);

AsyncWebServer server(80);

/*
typedef struct cRGB
{
  int r,g,b;
} cRGB;

cRGB crgb;

void intToRGB(int col, cRGB &cCol)
{
    cCol.r = col>>16;
    cCol.g = (col&0xFF00)>>8;
    cCol.b = (col&0xFF);
}
*/
// LEDS ----------------------------------------
#include "MLEDS.h"
#define NUM_LEDS 159
#define DATA_PIN 5
#define BUILDINLED 22
MYLEDS led{&FastLED, 159};
//#define CLOCK_PIN -1

// Define the array of leds
//CRGB leds[NUM_LEDS];

void connWIFI()
{
  pinMode(BUILDINLED,OUTPUT);
  digitalWrite(BUILDINLED,LOW);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    digitalWrite(BUILDINLED,!digitalRead(BUILDINLED));
  }
  if (WiFi.status() == WL_CONNECTED)
  {
    if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {Serial.println("Nie udalo sie skonfigurowac WiFi STA");}
    else {Serial.println("WiFi Config OK!"); }
  }
  digitalWrite(BUILDINLED,LOW);
  
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() { 
  
  Serial.begin(115200);
  connWIFI();
  
  #include "aws.h"

  AsyncElegantOTA.begin(&server);    // Start AsyncElegantOTA
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  server.begin();
  Serial.println("HTTP server started");
  
  Serial.println("WITTY LEDS");
  //FastLED.addLeds<WS2812B,DATA_PIN,GRB>(leds,NUM_LEDS);
  //FastLED.setBrightness(180);
  led.setMode(MYLEDS::MODES::pixel);
  led.clear();
}

//void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(250); } }

/*
void rainbow()
{
static uint8_t hue = 0;
  Serial.print("x");
  // First slide the led in one direction
  for(int i = 0; i < NUM_LEDS; i++) {
    // Set the i'th led to red 
    leds[i] = CHSV(hue++, 255, 255);
    // Show the leds
    FastLED.show(); 
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeall();
    // Wait a little bit before we loop around and do it again
    delay(10);
  }
  Serial.print("x");

  // Now go in the other direction.  
  for(int i = (NUM_LEDS)-1; i >= 0; i--) {
    // Set the i'th led to red 
    leds[i] = CHSV(hue++, 255, 255);
    // Show the leds
    FastLED.show();
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeall();
    // Wait a little bit before we loop around and do it again
    delay(30);
  }
}
*/

// VARS
uint8_t HUE{0};

void loop() { 
  
  //led.justRun(50);
  led.handler(); // glowna metoda wrappera
}
