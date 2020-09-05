#ifndef SMARTPIANO_LEDCOMMANDINPUTINTERFACE_H_
#define SMARTPIANO_LEDCOMMANDINPUTINTERFACE_H_

#include "LedCommand.h"

namespace SmartPiano
{

class LedCommandInputInterface
{
 public:
    virtual bool TryGetNextCommand(LedCommand* note_out) = 0;
    virtual void Tick(int delta) = 0;
    virtual bool IsEof() = 0;
};

}

#endif  // SMARTPIANO_LEDCOMMANDINPUTINTERFACE_H_