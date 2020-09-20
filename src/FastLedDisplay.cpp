#include "FastLedDisplay.h"

#include <FastLED.h>

namespace SmartPiano
{

FastLedDisplay::FastLedDisplay(
    unsigned char num_leds,
    LoggerInterface& logger)
        : num_leds_{num_leds}
        , logger_{logger}
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

    return true;
}

void FastLedDisplay::ExecuteLedCommand(const LedCommand& led_command)
{
    auto index1 = (led_command.index - 30) * 2;
    auto index2 = index1 + 1;
    if (index1 < 0 || index2 >= num_leds_ - 1)
    {
        return;
    }

    auto color = CRGB{ led_command.red, led_command.green, led_command.blue };
    char buf[128];
    if (IsLedCommandOn(led_command))
    {
        sprintf(buf, "Setting LEDs %u and %u to color (%u, %u, %u, %u)."
            , index1
            , index2
            , led_command.red
            , led_command.green
            , led_command.blue
            , led_command.white);
    }
    else
    {
        sprintf(buf, "Turning off LED %u and %u."
            , index1
            , index2);
    }
    logger_.Log(DEBUG, buf);

    leds_[index1] = color;
    leds_[index2] = color;
}

void FastLedDisplay::Tick(int delta)
{
    tick_ += delta;
    if (tick_ % 100 == 0)
    {
        tick_ = 0;
        // TODO(@jez): move
        Serial.println("STOP send");
        FastLED.show();
        // TODO(@jez): move
        Serial.println("OK send");
    }
}

bool FastLedDisplay::IsLedCommandOn(const LedCommand& note) const
{
    return note.red | note.green | note.blue | note.white;
}

}