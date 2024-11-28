#ifndef LAMP_H
#define LAMP_H

#include <Arduino.h>

#include "FastLED.h"


#define DATA_PIN    48          // TODO: MOVE to "config.h"
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    1
#define BRIGHTNESS  255

#define ON_TIME_MS  30000UL


class WarnLamp
{
    private:
    uint32_t _turnOnTime = 0UL;
    uint32_t _turnOffTime = 0UL;
    bool _isOn = false;

    public:
    WarnLamp(void);
    void Init(void);
    void TurnOn(void);
    void TurnOff(void);
    void LampCheck(void);
    bool IsOn(void);
};


#endif
