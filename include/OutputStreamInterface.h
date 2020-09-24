#ifndef SMARTPIANO_OUTPUTSTREAMINTERFACE_H_
#define SMARTPIANO_OUTPUTSTREAMINTERFACE_H_

namespace SmartPiano
{

class OutputStreamInterface
{
 public:
    virtual int WriteData(const char* data) = 0;
    virtual int WriteByte(char byte) = 0;
};

}

#endif  // SMARTPIANO_OUTPUTSTREAMINTERFACE_H_