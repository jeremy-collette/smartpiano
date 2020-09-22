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
        , waiting_to_show_{false}
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
    auto index1 = (led_command.index - 30) * 2;
    auto index2 = index1 + 1;
    if (index1 < 0 || index2 >= num_leds_ - 1)
    {
        return;
    }

    auto color = CRGB{ led_command.red, led_command.green, led_command.blue };
    if (IsLedCommandOn(led_command))
    {
        logger_.Log(DEBUG, "Setting LEDs %u and %u to color (%u, %u, %u, %u)."
            , index1
            , index2
            , led_command.red
            , led_command.green
            , led_command.blue
            , led_command.white);
    }
    else
    {
        logger_.Log(DEBUG, "Turning off LED %u and %u."
            , index1
            , index2);
    }

    leds_[index1] = color;
    leds_[index2] = color;
}

void FastLedDisplay::Tick(int delta)
{
    tick_ += delta;
    if (tick_ % 50 == 0 && waiting_to_show_)
    {
        while (serial_.Available() && serial_.Available() % 4 != 0)
        {
            auto extra_byte = serial_.ReadByte();
            logger_.Log(WARNING, "Cleared out extra byte %d", extra_byte);
        }
    }

    if (tick_ % 100 == 0 || waiting_to_show_)
    {
        serial_.PrintLine("STOP");
        waiting_to_show_ = true;
        logger_.Log(DEBUG, "Waiting to call FastLED.Show(). %d bytes remaining in buffer.", serial_.Available());
        tick_ = 0;
    }

    // If we've told the PC to stop & we've read all the data then we
    // can show :-)
    if (waiting_to_show_ && serial_.Available() == 0)
    {
        logger_.Log(DEBUG, "Calling FastLED.show()!");
        FastLED.show();
        waiting_to_show_ = false;

        // TODO(@jez): move
        serial_.PrintLine("START");
    }
}

bool FastLedDisplay::IsLedCommandOn(const LedCommand& note) const
{
    return note.red | note.green | note.blue | note.white;
}

}