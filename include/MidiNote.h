#ifndef SMARTPIANO_MIDINOTE_H_
#define SMARTPIANO_MIDINOTE_H_

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

}

#endif  // SMARTPIANO_MIDINOTE_H_