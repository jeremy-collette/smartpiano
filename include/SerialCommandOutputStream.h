#ifndef SMARTPIANO_SERIALCOMMANDOUTPUTSTREAM_H_
#define SMARTPIANO_SERIALCOMMANDOUTPUTSTREAM_H_

#include "OutputStreamInterface.h"

#include "SerialInterface.h"

namespace SmartPiano
{

class SerialCommandOutputStream : public OutputStreamInterface
{
 public:
  SerialCommandOutputStream(SerialInterface& serial);

  unsigned int WriteData(const char* data);

 private:
   SerialInterface& serial_;
};

}

#endif  // SMARTPIANO_SERIALCOMMANDOUTPUTSTREAM_H_