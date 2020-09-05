#ifndef SMARTPIANO_SERIALLEDCOMMANDINPUT_H_
#define SMARTPIANO_SERIALLEDCOMMANDINPUT_H_

#include "LedCommandInputInterface.h"

#include "LoggerInterface.h"

namespace SmartPiano
{

class SerialLedCommandInput : public LedCommandInputInterface
{
 public:
   SerialLedCommandInput(LoggerInterface& logger);

   virtual bool Initialize();

   virtual bool TryGetNextCommand(LedCommand* note_out);
   virtual void Tick(int delta);
   virtual bool IsEof();

 private:
   LoggerInterface& logger_;
};

}

#endif  // SMARTPIANO_SERIALLEDCOMMANDINPUT_H_