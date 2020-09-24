#include "SerialLogOutputStream.h"

namespace SmartPiano
{

SerialLogOutputStream::SerialLogOutputStream(
    SerialInterface& serial)
        : serial_{serial}
{
}

unsigned int SerialLogOutputStream::WriteData(
    const char* data)
{
    serial_.PrintLine("\x1");
    return serial_.PrintLine(data) + 1;
}

}