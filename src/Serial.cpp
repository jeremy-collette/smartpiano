#include "Serial.h"

#include <Arduino.h>

namespace SmartPiano
{

Serial::Serial(unsigned long baud)
    : baud_{baud}
{
}

int Serial::Available()
{
    return ::Serial.available();
}

bool Serial::Initialize()
{
    ::Serial.begin(baud_);
    ::Serial.println("Serial initialized!");
    return true;
}

unsigned int Serial::PrintLine(const char* data)
{
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