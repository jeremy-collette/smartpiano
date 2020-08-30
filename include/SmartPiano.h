#ifndef SMARTPIANO_SMARTPIANO_H_
#define SMARTPIANO_SMARTPIANO_H_

#include "SmartPianoInterface.h"

#include "DelayerInterface.h"
#include "LoggerInterface.h"
#include "MidiInputInterface.h"
#include "NoteDisplayInterface.h"

namespace SmartPiano
{

class SmartPiano : public SmartPianoInterface
{
 public:
    SmartPiano(
        MidiInputInterface& midi_input,
        NoteDisplayInterface& note_display,
        DelayerInterface& delayer,
        LoggerInterface& logger);

    virtual void Run();

 private:
    MidiInputInterface& midi_input_;
    NoteDisplayInterface& note_display_;
    DelayerInterface& delayer_;
    LoggerInterface& logger_;
};

}

#endif  // SMARTPIANO_SMARTPIANO_H_