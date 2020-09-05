#ifndef SMARTPIANO_LEDDISPLAYINTERFACE_H_
#define SMARTPIANO_LEDDISPLAYINTERFACE_H_

#include "LedCommand.h"

namespace SmartPiano
{

class LedDisplayInterface
{
 public:
    virtual bool Initialize() = 0;
    virtual void ExecuteLedCommand(const LedCommand& note) = 0;
};

}

#endif  // SMARTPIANO_NOTEDISPLAYINTERFACE_H_