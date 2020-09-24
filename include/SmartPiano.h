#ifndef SMARTPIANO_SMARTPIANO_H_
#define SMARTPIANO_SMARTPIANO_H_

#include "SmartPianoInterface.h"

#include "DelayerInterface.h"
#include "LoggerInterface.h"
#include "LedCommandInputInterface.h"
#include "LedDisplayInterface.h"

namespace SmartPiano
{

class SmartPiano : public SmartPianoInterface
{
 public:
    SmartPiano(
        LedCommandInputInterface& led_command_input
        , LedDisplayInterface& note_display
        , DelayerInterface& delayer
        , LoggerInterface& logger);

    virtual void Run();

 private:
    LedCommandInputInterface& led_command_input_;
    LedDisplayInterface& led_display_;
    DelayerInterface& delayer_;
    LoggerInterface& logger_;
};

}

#endif  // SMARTPIANO_SMARTPIANO_H_