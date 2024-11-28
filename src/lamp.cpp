#include "lamp.h"

//#include "fx/1d/pride2015.hpp"


WarnLamp::WarnLamp(void){};


void WarnLamp::Init(void) 
{

  CRGB leds[NUM_LEDS] = 
    {
        {0, 0, 0xFF}
    };    // BLUE

  delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS)
    .setCorrection(TypicalLEDStrip)
    .setTemperature(leds[0])
    .setDither(BRIGHTNESS < 255);

    // set master brightness control
    //FastLED.setBrightness(BRIGHTNESS);
}


void WarnLamp::TurnOn(void)
{
    if (_isOn)
    {
        return;
    }
    _turnOnTime = millis();
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.show();  
    _isOn = true;
}


void WarnLamp::TurnOff()
{
    _turnOffTime = millis();
    FastLED.setBrightness(0);
    FastLED.show(); 
    _isOn = false;
}


void WarnLamp::LampCheck(void)
{
    if (_isOn)
    {
        const uint32_t timeOn = millis() - _turnOnTime;

        if (ON_TIME_MS < timeOn)
        {
            TurnOff();
        }
    }
}


bool WarnLamp::IsOn(void)
{
    return(_isOn);
}

