#ifndef SMARTPIANO_SERIALLOGOUTPUTSTREAM_H_
#define SMARTPIANO_SERIALLOGOUTPUTSTREAM_H_

#include "OutputStreamInterface.h"

#include "SerialInterface.h"

namespace SmartPiano
{

class SerialLogOutputStream : public OutputStreamInterface
{
 public:
    SerialLogOutputStream(SerialInterface& serial);

    unsigned int WriteData(const char* data);

 private:
    SerialInterface& serial_;
};

}

#endif  // SMARTPIANO_SERIALLOGOUTPUTSTREAM_H_