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

#include "Serial.h"

#include <Arduino.h>

namespace SmartPiano
{

Serial::Serial(unsigned long baud)
    : baud_{baud}
{
}

int Serial::AvailableBytes()
{
    return ::Serial.available();
}

bool Serial::Initialize()
{
    ::Serial.begin(baud_);
    ::Serial.println("Serial initialized!");
    return true;
}

int Serial::WriteData(const char* data)
{
    return ::Serial.println(data);
}

int Serial::WriteByte(char data)
{
    // TODO(@jeremy): consider just using write here
    return ::Serial.println(data);
}

int Serial::ReadByte()
{
    return ::Serial.read();
}

int Serial::PeekByte()
{
    return ::Serial.peek();
}

}