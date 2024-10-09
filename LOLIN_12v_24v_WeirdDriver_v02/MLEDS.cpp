#include <FastLED.h>
#include "MLEDS.h"

  MYLEDS::MYLEDS(CFastLED *FLED, uint16_t numLeds) : fled{FLED}, N_LEDS{numLeds}
  { 
    leds = new CRGB[numLeds];
    fled->addLeds<WS2812B,DATAPIN,GRB>(leds,numLeds);
    fled->setBrightness(150);
  };

   MYLEDS::~MYLEDS(){ delete [] leds; delete fled; fled=nullptr; };
