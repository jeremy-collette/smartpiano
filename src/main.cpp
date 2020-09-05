#include <Arduino.h>

#include "Delayer.h"
#include "FastLedDisplay.h"
//#include "MockLedCommandInput.h"
#include "SerialLedCommandInput.h"
#include "SerialLogger.h"
#include "SmartPiano.h"

void setup() {

}

void loop() {
  auto baud = 115200U;
  auto buffer_size = 256U;
  unsigned char level_mask = //SmartPiano::TEST | SmartPiano::WARNING | SmartPiano::ERROR;
    SmartPiano::DEBUG | SmartPiano::INFO | SmartPiano::WARNING | SmartPiano::ERROR /*| SmartPiano::NOISY*/ | SmartPiano::TEST;
  SmartPiano::SerialLogger logger { baud, buffer_size, level_mask };
  logger.Initialize();

   //SmartPiano::MockLedCommandInput led_command_input { logger };
  SmartPiano::SerialLedCommandInput led_command_input { logger };

  auto num_leds = 144U;
  SmartPiano::FastLedDisplay led_display { num_leds, logger };
  led_display.Initialize();

  SmartPiano::Delayer delayer;

  while (true)
  {
    SmartPiano::SmartPiano smart_piano { led_command_input, led_display, delayer, logger };
    smart_piano.Run();
  }
}