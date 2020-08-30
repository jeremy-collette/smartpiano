#ifndef SMARTPIANO_NOTEDISPLAYINTERFACE_H_
#define SMARTPIANO_NOTEDISPLAYINTERFACE_H_

#include "MidiNote.h"

namespace SmartPiano
{

class NoteDisplayInterface
{
 public:
    virtual bool Initialize() = 0;
    virtual void DisplayNote(MidiNote note) = 0;
};

}

#endif  // SMARTPIANO_NOTEDISPLAYINTERFACE_H_