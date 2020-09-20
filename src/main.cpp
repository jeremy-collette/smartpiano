#include <Arduino.h>

#include "Delayer.h"
#include "FastLedDisplay.h"
#include "SerialBinaryLedCommandInput.h"
#include "SerialLogger.h"
#include "SmartPiano.h"

auto baud = 115200U;
auto buffer_size = 256U;
unsigned char level_mask = SmartPiano::TEST | SmartPiano::WARNING | SmartPiano::ERROR;
  //SmartPiano::DEBUG | SmartPiano::INFO | SmartPiano::WARNING | SmartPiano::ERROR /*| SmartPiano::NOISY*/ | SmartPiano::TEST;
SmartPiano::SerialLogger logger { baud, buffer_size, level_mask };

SmartPiano::SerialBinaryLedCommandInput led_command_input { logger };

auto num_leds = 144U;
SmartPiano::FastLedDisplay led_display { num_leds, logger };

SmartPiano::Delayer delayer;

SmartPiano::SmartPiano smart_piano { led_command_input, led_display, delayer, logger };

void setup()
{
  logger.Initialize();
  led_display.Initialize();
  Serial.println("Ready!");
  Serial.println("OK send");
}

void loop()
{
  smart_piano.Run();
}