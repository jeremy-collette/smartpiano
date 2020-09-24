#ifndef SMARTPIANO_SERIALCOMMANDINPUTSTREAM_H_
#define SMARTPIANO_SERIALCOMMANDINPUTSTREAM_H_

#include "InputStreamInterface.h"

#include "SerialInterface.h"

namespace SmartPiano
{

class SerialCommandInputStream : public InputStreamInterface
{
 public:
   SerialCommandInputStream(SerialInterface& serial);
   int AvailableBytes();
   int ReadByte();
   int PeekByte();

 private:
   SerialInterface& serial_;
};

}

#endif  // SMARTPIANO_SERIALCOMMANDINPUTSTREAM_H_