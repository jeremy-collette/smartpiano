#ifndef SMARTPIANO_SERIALLOGGER_H_
#define SMARTPIANO_SERIALLOGGER_H_

#include <Arduino.h>

#include "LoggerInterface.h"

namespace SmartPiano
{

class SerialLogger : public LoggerInterface
{
 public:
    SerialLogger(
        unsigned long baud
        , size_t buffer_size
        , unsigned char level_mask);
    ~SerialLogger();

    virtual void Initialize();
    virtual void Log(LogLevel level, const char* format, ...);

 private:
    unsigned long baud_;
    size_t buffer_size_;
    char* buffer_;
    unsigned char level_mask_;
};

}

#endif  // SMARTPIANO_SERIALLOGGER_H_