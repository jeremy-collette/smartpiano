#include "ArduinoSerialLogger.h"

#include <Arduino.h>

namespace SmartPiano
{

ArduinoSerialLogger::ArduinoSerialLogger(
    unsigned long baud
    , size_t buffer_size
    , unsigned char level_mask)
        : baud_{baud}
        , buffer_size_{buffer_size}
        , level_mask_{level_mask}
{
    buffer_ = new char[buffer_size_];
}

ArduinoSerialLogger::~ArduinoSerialLogger()
{
    delete[] buffer_;
}

void ArduinoSerialLogger::Initialize()
{
    Serial.begin(baud_);
    Serial.println("Logger initialized!");
}

void ArduinoSerialLogger::Log(LogLevel level, char* message)
{
    if (level & level_mask_)
    {
        snprintf(buffer_, buffer_size_, "[%u]: %s", level, message);
        Serial.println(buffer_);
    }
}

}