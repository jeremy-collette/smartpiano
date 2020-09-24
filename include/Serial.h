#ifndef SMARTPIANO_SERIAL_H_
#define SMARTPIANO_SERIAL_H_

#include "SerialInterface.h"

namespace SmartPiano
{

class Serial : public SerialInterface
{
 public:
    Serial(unsigned long baud);

    virtual int Available();
    virtual bool Initialize();
    virtual unsigned int PrintLine(const char* data);
    virtual int ReadByte();
    virtual int PeekByte();

 private:
    unsigned long baud_;
};

}

#endif  // SMARTPIANO_SERIAL_H_