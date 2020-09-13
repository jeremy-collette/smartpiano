#ifndef SMARTPIANO_SERIALJSONLEDCOMMANDINPUT_H_
#define SMARTPIANO_SERIALJSONLEDCOMMANDINPUT_H_

#include "LedCommandInputInterface.h"

#include <ArduinoJson.h>

#include "LoggerInterface.h"

namespace SmartPiano
{

class SerialJsonLedCommandInput : public LedCommandInputInterface
{
 public:
   SerialJsonLedCommandInput(LoggerInterface& logger);

   virtual bool Initialize();

   virtual bool TryGetNextCommand(LedCommand* note_out);
   virtual void Tick(int delta);
   virtual bool IsEof();

 private:
   LoggerInterface& logger_;
   StaticJsonDocument<128> json_doc_;
};

}

#endif  // SMARTPIANO_SERIALJSONLEDCOMMANDINPUT_H_