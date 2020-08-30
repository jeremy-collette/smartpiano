#include "MockMidiInput.h"

#include <Arduino.h>

namespace SmartPiano
{

const int NUM_NOTES = 6;
MidiNote midi_song[NUM_NOTES];

void add_midi_note(int index, unsigned long tick, unsigned char key, bool on)
{
    midi_song[index].tick = tick;
    midi_song[index].on = on;
    midi_song[index].key = key;
}

void setup_midi_song()
{
    add_midi_note(0, 0, 0, 1);
    add_midi_note(1, 500, 1, 1);
    add_midi_note(2, 1000, 0, 0);
    add_midi_note(3, 1000, 2, 1);
    add_midi_note(4, 1500, 1, 0);
    add_midi_note(5, 2000, 2, 0);
}

MockMidiInput::MockMidiInput(LoggerInterface& logger)
    : tick_{0}
    , logger_{logger}
    , index_{0}
{
    setup_midi_song();
}

bool MockMidiInput::IsEof()
{
    return false;
}

void MockMidiInput::Tick(int delta)
{
    tick_ += delta;

    if (tick_ == 5000)
    {
        logger_.Log(DEBUG, "Reset song");
        tick_ = 0;
        index_ = 0;
    }
}

bool MockMidiInput::TryGetNextNote(MidiNote* note_out)
{
    if (index_ < 0 || index_ >= NUM_NOTES)
    {
        return false;
    }

    auto next_note = midi_song[index_];
    if (tick_ < next_note.tick)
    {
        return false;
    }
    ++index_;

    note_out->on = next_note.on;
    note_out->channel = next_note.channel;
    note_out->key = next_note.key;
    note_out->volume = next_note.volume;
    return true;
}

}