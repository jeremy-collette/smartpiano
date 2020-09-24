#include "FastLedDisplay.h"

#include <FastLED.h>

namespace SmartPiano
{

FastLedDisplay::FastLedDisplay(
    unsigned char num_leds,
    LoggerInterface& logger,
    SerialInterface& serial)
        : num_leds_{num_leds}
        , logger_{logger}
        , serial_{serial}
        , tick_{0}
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

    auto startingIndex = 0;
    uint8_t brightness = 255;
    CRGBPalette16 currentPalette = RainbowColors_p;
    TBlendType currentBlending = LINEARBLEND;

    // TODO(@jeremy): can we do this on steady-state (before note is received?)
    for (auto j = 0U; j < 500; ++j)
    {
        auto colorIndex = startingIndex++;
        for (auto i = 0U; i < num_leds_; ++i)
        {
            leds_[i] = ColorFromPalette(currentPalette, colorIndex, brightness, currentBlending);
            colorIndex += 1;
        }
        FastLED.show();
        FastLED.delay(1);
    }

    for (auto i = 0U; i < num_leds_; ++i)
    {
        leds_[i] = CRGB::Black;
    }
    FastLED.show();
    FastLED.delay(50);

    serial_.PrintLine("START");
    return true;
}

void FastLedDisplay::ExecuteLedCommand(const LedCommand& led_command)
{
    if (led_command.index < 0 || led_command.index >= num_leds_ - 1)
    {
        return;
    }

    auto color = CRGB{ led_command.red, led_command.green, led_command.blue };
    if (IsLedCommandOn(led_command))
    {
        logger_.Log(DEBUG, "Setting LEDs %u to color (%u, %u, %u, %u)."
            , led_command.index
            , led_command.red
            , led_command.green
            , led_command.blue
            , led_command.white);
    }
    else
    {
        logger_.Log(DEBUG, "Turning off LED %u."
            , led_command.index);
    }

    leds_[led_command.index] = color;
}

void FastLedDisplay::Tick(int delta)
{
    // Do nothing
}

void FastLedDisplay::ExecuteUpdateCommand(const UpdateCommand& update_command)
{
    logger_.Log(TEST, "Calling FastLED.show()!");
    FastLED.show();
    // TODO(@jeremy): inject command output stream
    serial_.PrintLine("OK");
}

bool FastLedDisplay::IsLedCommandOn(const LedCommand& note) const
{
    return note.red | note.green | note.blue | note.white;
}

}