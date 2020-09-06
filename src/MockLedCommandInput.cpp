#include "MockLedCommandInput.h"

#include <Arduino.h>

#include <limits.h>

namespace SmartPiano
{

struct MidiNote
{
    unsigned long tick;
    bool on;
    unsigned char channel;
    unsigned char key;
    unsigned int volume;
};

const int NUM_NOTES = 20;
MidiNote midi_song[NUM_NOTES]
{
    /*tick on chan key vol*/
    { 0, 1, 0, 64, 52 },
    { 1000, 0, 0, 64, 64 },
    { 1000, 1, 0, 62, 59 },
    { 2000, 1, 0, 52, 71 },
    { 2000, 1, 0, 45, 77 },
    { 2000, 1, 0, 57, 82 },
    { 2000, 0, 0, 62, 64 },
    { 2000, 1, 0, 60, 64 },
    { 4500, 0, 0, 60, 64 },
    { 4500, 0, 0, 62, 59 },
    { 4500, 0, 0, 64, 64 },
    { 4500, 0, 0, 45, 60 },
    { 4500, 0, 0, 52, 45 },
    { 4500, 0, 0, 57, 45 },
    { ULONG_MAX, 0, 0, 0, 0 }
};

MockLedCommandInput::MockLedCommandInput(LoggerInterface& logger)
    : tick_{0}
    , logger_{logger}
    , index_{0}
{

}

bool MockLedCommandInput::IsEof()
{
    return false;
}

void MockLedCommandInput::Tick(int delta)
{
    tick_ += delta;
}

bool MockLedCommandInput::TryGetNextCommand(LedCommand* command_out)
{
    if (index_ < 0 || index_ >= NUM_NOTES-1
        || midi_song[index_].tick == ULONG_MAX)
    {
        tick_ = 0;
        index_ = 0;
        return false;
    }

    auto next_note = midi_song[index_];
    if (tick_ < next_note.tick)
    {
        return false;
    }
    ++index_;

    command_out->index = next_note.key;

    if (!next_note.on)
    {
        command_out->red = 0;
        command_out->green = 0;
        command_out->blue = 0;
        command_out->white = 0;
        return true;
    }

    if (next_note.key >= 60)
    {
        command_out->red = 255;
        command_out->green = 0;
        command_out->blue = 0;
        command_out->white = 0;
    }
    else
    {
        command_out->red = 0;
        command_out->green = 0;
        command_out->blue = 255;
        command_out->white = 0;
    }
    return true;
}

}