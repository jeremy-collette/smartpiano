#ifndef SMARTPIANO_LEDCOMMAND_H_
#define SMARTPIANO_LEDCOMMAND_H_

namespace SmartPiano
{

struct LedCommand
{
    unsigned long tick;
    bool on;
    unsigned char channel;
    unsigned char key;
    unsigned int volume;
};

}

#endif  // SMARTPIANO_LEDCOMMAND_H_