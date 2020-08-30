#include "FastLedNoteDisplay.h"

#include <FastLED.h>

namespace SmartPiano
{

FastLedNoteDisplay::FastLedNoteDisplay(
    unsigned char num_leds,
    LoggerInterface& logger)
        : num_leds_{num_leds}
        , logger_{logger}
{
    leds_ = new CRGB[num_leds];
}

FastLedNoteDisplay::~FastLedNoteDisplay()
{
    delete[] leds_;
}

bool FastLedNoteDisplay::Initialize()
{
    logger_.Log(INFO, "Initializing FastLED...");
    FastLED.addLeds<WS2811, DATA_PIN, GRB>(leds_, num_leds_);
    for (auto i = 0U; i < num_leds_; ++i)
    {
        leds_[i] = CRGB::Black;
    }
    FastLED.show();
    return true;
}

void FastLedNoteDisplay::DisplayNote(MidiNote midi_note)
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
        leds_[midi_note.key] = CRGB::Red;
        FastLED.show();
    }
    else
    {
        char buf[256];
        sprintf(buf, "Turning LED %u off!", midi_note.key);
        logger_.Log(DEBUG, buf);
        leds_[midi_note.key] = CRGB::Black;
        FastLED.show();
    }
}

}