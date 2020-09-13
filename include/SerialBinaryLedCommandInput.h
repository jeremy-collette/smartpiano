#ifndef SMARTPIANO_SERIALBINARYLEDCOMMANDINPUT_H_
#define SMARTPIANO_SERIALBINARYLEDCOMMANDINPUT_H_

#include "LedCommandInputInterface.h"

#include "LoggerInterface.h"

namespace SmartPiano
{

class SerialBinaryLedCommandInput : public LedCommandInputInterface
{
 public:
   SerialBinaryLedCommandInput(LoggerInterface& logger);

   virtual bool Initialize();

   virtual bool TryGetNextCommand(LedCommand* note_out);
   virtual void Tick(int delta);
   virtual bool IsEof();

 private:
   LoggerInterface& logger_;
};

}

#endif  // SMARTPIANO_SERIALBINARYLEDCOMMANDINPUT_H_