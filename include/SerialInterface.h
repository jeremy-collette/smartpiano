#ifndef SMARTPIANO_SERIALINTERFACE_H_
#define SMARTPIANO_SERIALINTERFACE_H_

namespace SmartPiano
{

class SerialInterface
{
 public:
    virtual int Available() = 0;
    virtual bool Initialize() = 0;
    virtual void PrintLine(const char* data) = 0;
    virtual int ReadByte() = 0;
};

}

#endif  // SMARTPIANO_SERIALINTERFACE_H_