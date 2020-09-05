#ifndef SMARTPIANO_MOCKLEDCOMMANDINPUT_H_
#define SMARTPIANO_MOCKLEDCOMMANDINPUT_H_

#include "LedCommandInputInterface.h"

#include "LoggerInterface.h"

namespace SmartPiano
{

class MockLedCommandInput : public LedCommandInputInterface
{
 public:
    MockLedCommandInput(LoggerInterface& logger);

    virtual bool TryGetNextCommand(LedCommand* note_out);
    virtual void Tick(int delta);
    virtual bool IsEof();
 private:
    unsigned int tick_;
    LoggerInterface& logger_;
    unsigned int index_;
};

}

#endif  // SMARTPIANO_MOCKLEDCOMMANDINPUT_H_