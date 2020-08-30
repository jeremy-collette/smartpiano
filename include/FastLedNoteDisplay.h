#ifndef SMARTPIANO_FASTLEDNOTEDISPLAY_H_
#define SMARTPIANO_FASTLEDNOTEDISPLAY_H_

#include "NoteDisplayInterface.h"

#include <FastLED.h>

#include "LoggerInterface.h"

namespace SmartPiano
{

class FastLedNoteDisplay : public NoteDisplayInterface
{
 public:
    const static int DATA_PIN = 8;

    FastLedNoteDisplay(
        unsigned char num_leds,
        LoggerInterface& logger);
    virtual ~FastLedNoteDisplay();

    virtual bool Initialize();
    virtual void DisplayNote(MidiNote note);

 private:
    CRGB* leds_;
    unsigned char num_leds_;
    unsigned char data_pin_;
    LoggerInterface& logger_;
};

}

#endif  // SMARTPIANO_FASTLEDNOTEDISPLAY_H_