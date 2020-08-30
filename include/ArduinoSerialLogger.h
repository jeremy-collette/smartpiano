#ifndef SMARTPIANO_ARDUINOSERIALLOGGER_H_
#define SMARTPIANO_ARDUINOSERIALLOGGER_H_

#include <Arduino.h>

#include "LoggerInterface.h"

namespace SmartPiano
{

class ArduinoSerialLogger : public LoggerInterface
{
 public:
    ArduinoSerialLogger(
        unsigned long baud
        , size_t buffer_size
        , unsigned char level_mask);
    ~ArduinoSerialLogger();

    virtual void Initialize();
    virtual void Log(LogLevel level, char* message);

 private:
    unsigned long baud_;
    size_t buffer_size_;
    char* buffer_;
    unsigned char level_mask_;
};

}

#endif  // SMARTPIANO_ARDUINOSERIALLOGGER_H_