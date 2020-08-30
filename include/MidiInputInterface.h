#ifndef SMARTPIANO_MIDIINPUTINTERFACE_H_
#define SMARTPIANO_MIDIINPUTINTERFACE_H_

#include "MidiNote.h"

namespace SmartPiano
{

class MidiInputInterface
{
 public:
    virtual bool TryGetNextNote(MidiNote* note_out) = 0;
    virtual void Tick(int delta) = 0;
    virtual bool IsEof() = 0;
};

}

#endif  // SMARTPIANO_MIDIINPUTINTERFACE_H_