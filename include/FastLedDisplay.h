#ifndef SMARTPIANO_FASTLEDDISPLAY_H_
#define SMARTPIANO_FASTLEDDISPLAY_H_

#include "LedDisplayInterface.h"

#include <FastLED.h>

#include "LoggerInterface.h"
#include "OutputStreamInterface.h"

namespace SmartPiano
{

class FastLedDisplay : public LedDisplayInterface
{
 public:
    const static int DATA_PIN = 8;

    FastLedDisplay(
        unsigned char num_leds
        , LoggerInterface& logger
        , OutputStreamInterface& command_output);
    virtual ~FastLedDisplay();

    virtual bool Initialize();
    virtual void ExecuteLedCommand(const LedCommand& command);
    virtual void Tick(int delta);

 private:
    CRGB* leds_;
    unsigned char num_leds_;
    unsigned char data_pin_;
    LoggerInterface& logger_;
    OutputStreamInterface& command_output_;
    // TODO: change data type
    int tick_;

    bool IsLedCommandOn(const LedCommand& command) const;
    void ExecuteUpdateCommand(const LedCommand& command);
    void ExecuteColorCommand(const LedCommand& command);
};

}

#endif  // SMARTPIANO_FASTLEDNOTEDISPLAY_H_