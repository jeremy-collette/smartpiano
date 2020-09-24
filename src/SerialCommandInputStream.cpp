#include "SerialCommandInputStream.h"

namespace SmartPiano
{

SerialCommandInputStream::SerialCommandInputStream(
    SerialInterface& serial)
        : serial_{serial}
{
}

int SerialCommandInputStream::AvailableBytes()
{
    return serial_.Available();
}

int SerialCommandInputStream::ReadByte()
{
    return serial_.ReadByte();
}

int SerialCommandInputStream::PeekByte()
{
    return serial_.PeekByte();
}

}