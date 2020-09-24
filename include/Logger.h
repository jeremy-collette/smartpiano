#ifndef SMARTPIANO_SERIALLOGGER_H_
#define SMARTPIANO_SERIALLOGGER_H_

#include "LoggerInterface.h"

#include <Arduino.h>
#include <stdarg.h>

#include "OutputStreamInterface.h"

namespace SmartPiano
{

class Logger : public LoggerInterface
{
 public:
    Logger(
        OutputStreamInterface& output_stream
        , size_t buffer_size
        , LogLevel highest_level);
    ~Logger();

    virtual void Initialize();
    virtual void Log(LogLevel level, const char* format, ...);

 private:
    OutputStreamInterface& output_stream_;
    size_t buffer_size_;
    char* buffer_;
    LogLevel highest_level_;

    virtual void Log(LogLevel level, const char* format, va_list arglist);
};

}

#endif  // SMARTPIANO_SERIALLOGGER_H_