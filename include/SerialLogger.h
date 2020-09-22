#ifndef SMARTPIANO_SERIALLOGGER_H_
#define SMARTPIANO_SERIALLOGGER_H_

#include "LoggerInterface.h"

#include <Arduino.h>
#include <stdarg.h>

#include "SerialInterface.h"

namespace SmartPiano
{

class SerialLogger : public LoggerInterface
{
 public:
    SerialLogger(
        SerialInterface& serial
        , size_t buffer_size
        , LogLevel highest_level);
    ~SerialLogger();

    virtual void Initialize();
    virtual void Log(LogLevel level, const char* format, ...);

 private:
    SerialInterface& serial_;
    size_t buffer_size_;
    char* buffer_;
    LogLevel highest_level_;

    virtual void Log(LogLevel level, const char* format, va_list arglist);
};

}

#endif  // SMARTPIANO_SERIALLOGGER_H_