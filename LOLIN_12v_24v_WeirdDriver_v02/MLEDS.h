#ifndef MLEDS_H
#define MLEDS_H
#define DATAPIN 5
class MYLEDS
{
  public:
  MYLEDS(CFastLED *FLED, uint16_t numLeds);

  ~MYLEDS();
  
  enum class MODES {pixel, softrun, rainbow};
  
  void setMode(MODES userMode) { cmode={userMode}; }
  void handler()
  {
    switch(cmode)
    {
      case MODES::pixel:
      {
        // generealnie nic, tylko ustaw pixel przez AWS
        break;
      }
      case MODES::softrun:
      {
        this->justRun(SPD);
        break;
      }
      default: break;
    }
  }

  void waterfallHandler()
  {
    if (0) {}
    if (1) {}
  }
  void setSpeed(uint16_t spd)
  {
    this->SPD = spd;
  }
  void fade(uint16_t S, uint16_t E)
  {
    if (E>N_LEDS) E=N_LEDS;
    for(int i = S; i < E; i++) { leds[i].nscale8(250); }
    fled->show();
  }
  void clear()
  {
    for(int i = 0; i < N_LEDS; i++) { leds[i]=CHSV(0,0,0); }
    fled->show();
  }
  
  void writeRGB(uint16_t NUM, uint8_t R, uint8_t G, uint8_t B)
  {
    leds[NUM] = CRGB(R,G,B);
    fled->show();
  }
  
  void justRun(byte DEL)
  {
    for(int i = 0; i < N_LEDS; i++) 
    {
      leds[i] = CHSV(HUE++, 255, 255);
      leds[N_LEDS-i-1] = CHSV(HUE++, 255, 255);
      fled->show();
      delay(DEL);
    }
  }
  
  private:
  CFastLED* fled {nullptr};
  CRGB *leds;
  uint16_t N_LEDS;
  uint8_t HUE{0};
  MODES cmode{MODES::pixel};
  uint16_t SPD{50};
};
#endif
