#ifndef SMARTPIANO_INPUTSTREAMINTERFACE_H_
#define SMARTPIANO_INPUTSTREAMINTERFACE_H_

namespace SmartPiano
{

class InputStreamInterface
{
 public:
    virtual int AvailableBytes() = 0;
    virtual int ReadByte() = 0;
    virtual int PeekByte() = 0;

};

}

#endif  // SMARTPIANO_INPUTSTREAMINTERFACE_H_