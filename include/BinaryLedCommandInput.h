#ifndef SMARTPIANO_BINARYLEDCOMMANDINPUT_H_
#define SMARTPIANO_BINARYLEDCOMMANDINPUT_H_

#include "LedCommandInputInterface.h"

#include "InputStreamInterface.h"
#include "LoggerInterface.h"

namespace SmartPiano
{

class BinaryLedCommandInput : public LedCommandInputInterface
{
 public:
   BinaryLedCommandInput(
     InputStreamInterface& input_stream
     , LoggerInterface& logger);

   virtual bool Initialize();

   virtual bool TryGetNextCommand(LedCommand* command_out);
   virtual void Tick(int delta);
   virtual bool IsEof();

 private:
  static const int COLOR_COMMAND_HEADER = 0x32;
  static const int UPDATE_COMMAND_HEADER = 0x93;

  InputStreamInterface& input_stream_;
  LoggerInterface& logger_;

  bool HandleColorCommand(LedCommand* command_out);
  bool HandleUpdateCommand(LedCommand* command_out);
  bool IsValidHeaderByte(int byte);
};

}

#endif  // SMARTPIANO_BINARYLEDCOMMANDINPUT_H_