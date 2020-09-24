#ifndef SMARTPIANO_FASTLEDDISPLAY_H_
#define SMARTPIANO_FASTLEDDISPLAY_H_

#include "LedDisplayInterface.h"

#include <FastLED.h>

#include "LoggerInterface.h"
#include "SerialInterface.h"

namespace SmartPiano
{

class FastLedDisplay : public LedDisplayInterface
{
 public:
    const static int DATA_PIN = 8;

    FastLedDisplay(
        unsigned char num_leds
        , LoggerInterface& logger
        , SerialInterface& serial);
    virtual ~FastLedDisplay();

    virtual bool Initialize();
    virtual void ExecuteLedCommand(const LedCommand& note);
    virtual void ExecuteUpdateCommand(const UpdateCommand& update_command);
    virtual void Tick(int delta);

 private:
    CRGB* leds_;
    unsigned char num_leds_;
    unsigned char data_pin_;
    LoggerInterface& logger_;
    SerialInterface& serial_;
    // TODO: change data type
    int tick_;

    bool IsLedCommandOn(const LedCommand& note) const;
};

}

#endif  // SMARTPIANO_FASTLEDNOTEDISPLAY_H_