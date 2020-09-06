#include "FastLedDisplay.h"

#include <FastLED.h>

namespace SmartPiano
{

FastLedDisplay::FastLedDisplay(
    unsigned char num_leds,
    LoggerInterface& logger)
        : num_leds_{num_leds}
        , logger_{logger}
{
    leds_ = new CRGB[num_leds];
}

FastLedDisplay::~FastLedDisplay()
{
    delete[] leds_;
}

bool FastLedDisplay::Initialize()
{
    logger_.Log(INFO, "Initializing FastLED...");
    FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds_, num_leds_);
    for (auto i = 0U; i < num_leds_; ++i)
    {
        leds_[i] = CRGB::Black;
    }
    FastLED.show();
    return true;
}

void FastLedDisplay::ExecuteLedCommand(const LedCommand& led_command)
{
    if (led_command.index < 0 || led_command.index >= num_leds_)
    {
        return;
    }

    char buf[128];
    if (IsLedCommandOn(led_command))
    {
        sprintf(buf, "Setting LED %u to color (%u, %u, %u, %u).", led_command.index, led_command.red
            , led_command.green, led_command.blue, led_command.white);
    }
    else
    {
        sprintf(buf, "Turning off LED %u.", led_command.index);
    }
    logger_.Log(DEBUG, buf);

    auto color = CRGB{ led_command.red, led_command.green, led_command.blue };
    // TODO(@jeremy): fix
    leds_[(led_command.index - 30) * 2] = color;
    leds_[(led_command.index - 30) * 2 + 1] = color;
    FastLED.show();
}


bool FastLedDisplay::IsLedCommandOn(const LedCommand& note) const
{
    return note.red | note.green | note.blue | note.white;
}

}