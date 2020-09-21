#include "SerialLogger.h"

#include <Arduino.h>
#include <stdarg.h>

namespace SmartPiano
{

SerialLogger::SerialLogger(
    SerialInterface& serial
    , size_t buffer_size
    , unsigned char level_mask)
        : serial_{serial}
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
    Log(LogLevel::INFO, "Logger initialized!");
}

void SerialLogger::Log(LogLevel level, const char* format, ...)
{
    va_list arglist;
    va_start (arglist, format);
    Log(level, format, arglist);
    va_end (arglist);
}

void SerialLogger::Log(LogLevel level, const char* format, va_list arglist)
{
    if (level & level_mask_)
    {
        // Add LogLevel to buffer
        auto written = snprintf(buffer_, buffer_size_, "[%u]: ", level);

        // Add text after LogLevel
        vsnprintf(buffer_ + written, buffer_size_ - written, format, arglist);
        serial_.PrintLine(buffer_);
    }
}

}