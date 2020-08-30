#ifndef SMARTPIANO_DELAYERINTERFACE_H_
#define SMARTPIANO_DELAYERINTERFACE_H_

namespace SmartPiano
{

class DelayerInterface
{
 public:
    virtual void Delay(int milliseconds) = 0;
};

}

#endif  // SMARTPIANO_DELAYERINTERFACE_H_