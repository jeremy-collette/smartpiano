#include <Arduino.h>

#include "Delayer.h"
#include "FastLedDisplay.h"
#include "Serial.h"
#include "SerialBinaryLedCommandInput.h"
#include "SerialLogger.h"
#include "SmartPiano.h"

auto baud = 115200U;
SmartPiano::Serial serial { baud };

auto buffer_size = 256U;
unsigned char level_mask =
  SmartPiano::TEST
  | SmartPiano::WARNING
  | SmartPiano::ERROR
  | SmartPiano::INFO
  | SmartPiano::DEBUG;
  //| SmartPiano::NOISY;

  //SmartPiano::DEBUG | SmartPiano::INFO | SmartPiano::WARNING | SmartPiano::ERROR /*| SmartPiano::NOISY*/ | SmartPiano::TEST;
SmartPiano::SerialLogger logger { serial, buffer_size, level_mask };

SmartPiano::SerialBinaryLedCommandInput led_command_input { serial, logger };

unsigned char num_leds = 144U;
SmartPiano::FastLedDisplay led_display { num_leds, logger, serial };

SmartPiano::Delayer delayer;

SmartPiano::SmartPiano smart_piano { led_command_input, led_display, delayer, logger };

void setup()
{
  serial.Initialize();
  logger.Initialize();
  led_display.Initialize();
  serial.PrintLine("Ready!");
}

void loop()
{
  smart_piano.Run();
}