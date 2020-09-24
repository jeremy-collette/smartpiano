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