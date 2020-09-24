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
    return serial_.PrintLine(data);

    //serial_.PrintLine("\x2");
    //return serial_.PrintLine(data) + 1;
}

}