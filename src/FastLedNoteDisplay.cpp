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

void FastLedDisplay::ExecuteLedCommand(LedCommand midi_note)
{
    if (midi_note.key < 0 || midi_note.key >= num_leds_)
    {
        return;
    }

    if (midi_note.on)
    {
        char buf[256];
        sprintf(buf, "Turning LED %u on!", midi_note.key);
        logger_.Log(DEBUG, buf);
        auto color = midi_note.key >= 60 ? CRGB::Red : CRGB::Blue;
        leds_[num_leds_ - 1 - (midi_note.key - 30) * 2] = color;
        leds_[num_leds_ - 1 - (midi_note.key - 30) * 2 - 1] = color;
        FastLED.show();
    }
    else
    {
        char buf[256];
        sprintf(buf, "Turning LED %u off!", midi_note.key);
        logger_.Log(DEBUG, buf);
        leds_[num_leds_ - 1 - (midi_note.key - 30) * 2] = CRGB::Black;
        leds_[num_leds_ - 1 - (midi_note.key - 30) * 2 - 1] = CRGB::Black;
        FastLED.show();
    }
}

}