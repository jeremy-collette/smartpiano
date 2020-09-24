#ifndef SMARTPIANO_SERIALINTERFACE_H_
#define SMARTPIANO_SERIALINTERFACE_H_

#include "InputStreamInterface.h"
#include "OutputStreamInterface.h"

namespace SmartPiano
{

class SerialInterface : public InputStreamInterface, public OutputStreamInterface
{
 public:
    virtual int AvailableBytes() = 0;
    virtual bool Initialize() = 0;
    virtual int WriteData(const char* data) = 0;
    virtual int WriteByte(char byte) = 0;
    virtual int ReadByte() = 0;
    virtual int PeekByte() = 0;
};

}

#endif  // SMARTPIANO_SERIALINTERFACE_H_