// TODO: don't include
#include <Arduino.h>

#include "SmartPiano.h"

namespace SmartPiano
{

SmartPiano::SmartPiano(
    MidiInputInterface& midi_input
    , NoteDisplayInterface& note_display
    , DelayerInterface& delayer
    , LoggerInterface& logger)
        : midi_input_{midi_input}
        , note_display_{note_display}
        , delayer_{delayer}
        , logger_{logger}
{
}

void SmartPiano::Run()
{
    logger_.Log(INFO, "Started running");
    while (!midi_input_.IsEof())
    {
        logger_.Log(NOISY, "Tick");
        MidiNote midi_note;
        while (midi_input_.TryGetNextNote(&midi_note))
        {
            char buf[256];
            sprintf(buf, "Got note. Key = %u, On = %u", midi_note.key, midi_note.on);
            logger_.Log(INFO, buf);
            note_display_.DisplayNote(midi_note);
        }

        auto delta = 100;
        delayer_.Delay(delta);
        midi_input_.Tick(delta);
    }
}

}