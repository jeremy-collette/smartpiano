#include "Logger.h"

#include <Arduino.h>
#include <stdarg.h>

namespace SmartPiano
{

Logger::Logger(
    OutputStreamInterface& output_stream
    , size_t buffer_size
    , LogLevel highest_level)
        : output_stream_{output_stream}
        , buffer_size_{buffer_size}
        , highest_level_{highest_level}
{
    buffer_ = new char[buffer_size_];
}

Logger::~Logger()
{
    delete[] buffer_;
}

void Logger::Initialize()
{
    Log(LogLevel::INFO, "Logger initialized!");
}

void Logger::Log(LogLevel level, const char* format, ...)
{
    va_list arglist;
    va_start (arglist, format);
    Log(level, format, arglist);
    va_end (arglist);
}

void Logger::Log(LogLevel level, const char* format, va_list arglist)
{
    if (level <= highest_level_)
    {
        // Add LogLevel to buffer
        auto written = snprintf(buffer_, buffer_size_, "[%u]: ", level);

        // Add text after LogLevel
        vsnprintf(buffer_ + written, buffer_size_ - written, format, arglist);
        output_stream_.WriteData(buffer_);
    }
}

}