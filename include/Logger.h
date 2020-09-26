/*
 * smartpiano
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