#ifndef SMARTPIANO_DELAYER_H_
#define SMARTPIANO_DELAYER_H_

#include "DelayerInterface.h"

namespace SmartPiano
{

class Delayer : public DelayerInterface
{
 public:
    virtual void Delay(int milliseconds);
};

}

#endif  // SMARTPIANO_DELAYER_H_