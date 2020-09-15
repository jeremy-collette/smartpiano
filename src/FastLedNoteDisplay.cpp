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

    auto startingIndex = 0;
    uint8_t brightness = 255;
    CRGBPalette16 currentPalette = RainbowColors_p;
    TBlendType    currentBlending = LINEARBLEND;

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
    if (led_command.index < 0 || led_command.index >= num_leds_)
    {
        return;
    }

// TODO(@jeremy): restore
/*
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
*/

    auto color = CRGB{ led_command.red, led_command.green, led_command.blue };
    // TODO(@jeremy): fix
    auto index = (led_command.index - 30) * 2;
    if (index < 0 || index + 1 >= num_leds_ - 1)
    {
        return;
    }
    /*
    char buf[128];
    sprintf(buf, "Setting LED %u and %u to color (%u, %u, %u, %u).", index, index+1,
        led_command.red, led_command.green, led_command.blue, led_command.white);
    Serial.println(buf);
    */
    leds_[index] = color;
    leds_[index + 1] = color;
}

void FastLedDisplay::Tick(int delta)
{
    Serial.println("Show!");
    FastLED.show();
}

bool FastLedDisplay::IsLedCommandOn(const LedCommand& note) const
{
    return note.red | note.green | note.blue | note.white;
}

}