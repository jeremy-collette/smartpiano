#include "SerialCommandOutputStream.h"

namespace SmartPiano
{

SerialCommandOutputStream::SerialCommandOutputStream(
    SerialInterface& serial)
        : serial_{serial}
{
}

unsigned int SerialCommandOutputStream::WriteData(
    const char* data)
{
    return serial_.PrintLine(data);

    //serial_.PrintLine("\x1");
    //return serial_.PrintLine(data) + 1;
}

}