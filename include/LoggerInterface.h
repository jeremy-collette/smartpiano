#ifndef SMARTPIANO_LOGGERINTERFACE_H_
#define SMARTPIANO_LOGGERINTERFACE_H_

#include "LogLevel.h"

namespace SmartPiano
{

class LoggerInterface
{
 public:
    virtual void Initialize() = 0;
    virtual void Log(LogLevel level, char* message) = 0;
};

}

#endif  // SMARTPIANO_LOGGERINTERFACE_H_