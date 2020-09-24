#ifndef SMARTPIANO_UPDATECOMMANDINPUTINTERFACE_H_
#define SMARTPIANO_UPDATECOMMANDINPUTINTERFACE_H_

#include "UpdateCommand.h"

namespace SmartPiano
{

class UpdateCommandInputInterface
{
 public:
    virtual bool TryGetNextCommand(UpdateCommand* command_out) = 0;
    virtual void Tick(int delta) = 0;
    virtual bool IsEof() = 0;
};

}

#endif  // SMARTPIANO_UPDATECOMMANDINPUTINTERFACE_H_