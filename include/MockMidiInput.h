#ifndef SMARTPIANO_MOCKMIDIINPUT_H_
#define SMARTPIANO_MOCKMIDIINPUT_H_

#include "MidiInputInterface.h"

#include "LoggerInterface.h"

namespace SmartPiano
{

class MockMidiInput : public MidiInputInterface
{
 public:
    MockMidiInput(LoggerInterface& logger);

    virtual bool TryGetNextNote(MidiNote* note_out);
    virtual void Tick(int delta);
    virtual bool IsEof();
 private:
    unsigned int tick_;
    LoggerInterface& logger_;
    unsigned int index_;
};

}

#endif  // SMARTPIANO_MOCKMIDIINPUT_H_