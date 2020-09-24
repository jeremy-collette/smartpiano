#ifndef SMARTPIANO_BINARYUPDATECOMMANDINPUT_H_
#define SMARTPIANO_BINARYUPDATECOMMANDINPUT_H_

#include "UpdateCommandInputInterface.h"

#include "InputStreamInterface.h"
#include "LoggerInterface.h"

namespace SmartPiano
{

class BinaryUpdateCommandInput : public UpdateCommandInputInterface
{
 public:
   BinaryUpdateCommandInput(
     InputStreamInterface& input_stream
     , LoggerInterface& logger);

   virtual bool Initialize();

   virtual bool TryGetNextCommand(UpdateCommand* command_out);
   virtual void Tick(int delta);
   virtual bool IsEof();

 private:
   InputStreamInterface& input_stream_;
   LoggerInterface& logger_;
};

}

#endif  // SMARTPIANO_BINARYUPDATECOMMANDINPUT_H_