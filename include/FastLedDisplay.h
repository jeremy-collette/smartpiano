#ifndef SMARTPIANO_FASTLEDDISPLAY_H_
#define SMARTPIANO_FASTLEDDISPLAY_H_

#include "LedDisplayInterface.h"

#include <FastLED.h>

#include "LoggerInterface.h"

namespace SmartPiano
{

class FastLedDisplay : public LedDisplayInterface
{
 public:
    const static int DATA_PIN = 8;

    FastLedDisplay(
        unsigned char num_leds,
        LoggerInterface& logger);
    virtual ~FastLedDisplay();

    virtual bool Initialize();
    virtual void ExecuteLedCommand(const LedCommand& note);

 private:
    CRGB* leds_;
    unsigned char num_leds_;
    unsigned char data_pin_;
    LoggerInterface& logger_;

    bool IsLedCommandOn(const LedCommand& note) const;
};

}

#endif  // SMARTPIANO_FASTLEDNOTEDISPLAY_H_