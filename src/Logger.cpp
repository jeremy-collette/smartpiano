/*
 * smartpiano Arduino Server
 * Copyright (C) 2020 Jeremy Collette.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

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