#include "SerialLogger.h"

#include <Arduino.h>

namespace SmartPiano
{

SerialLogger::SerialLogger(
    unsigned long baud
    , size_t buffer_size
    , unsigned char level_mask)
        : baud_{baud}
        , buffer_size_{buffer_size}
        , level_mask_{level_mask}
{
    buffer_ = new char[buffer_size_];
}

SerialLogger::~SerialLogger()
{
    delete[] buffer_;
}

void SerialLogger::Initialize()
{
    Serial.begin(baud_);
    Serial.println("Logger initialized!");
}

void SerialLogger::Log(LogLevel level, const char* format, ...)
{
    // TODO(jeremy): use format strings
    if (level & level_mask_)
    {
        snprintf(buffer_, buffer_size_, "[%u]: %s", level, format);
        Serial.println(buffer_);
    }
}

}