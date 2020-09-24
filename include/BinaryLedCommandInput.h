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

   virtual bool TryGetNextCommand(LedCommand* note_out);
   virtual void Tick(int delta);
   virtual bool IsEof();

 private:
   InputStreamInterface& input_stream_;
   LoggerInterface& logger_;
};

}

#endif  // SMARTPIANO_BINARYLEDCOMMANDINPUT_H_