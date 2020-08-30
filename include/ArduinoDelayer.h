#ifndef SMARTPIANO_ARDUINODELAYER_H_
#define SMARTPIANO_ARDUINODELAYER_H_

#include "DelayerInterface.h"

namespace SmartPiano
{

class ArduinoDelayer : public DelayerInterface
{
 public:
    virtual void Delay(int milliseconds);
};

}

#endif  // SMARTPIANO_ARDUINODELAYER_H_