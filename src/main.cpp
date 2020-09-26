#include "BinaryLedCommandInput.h"
#include "Delayer.h"
#include "FastLedDisplay.h"
#include "Logger.h"
#include "Serial.h"
#include "SmartPiano.h"
#include "Version.h"

auto baud = 115200U;
SmartPiano::Serial serial { baud };

auto buffer_size = 256U;
auto highest_level = SmartPiano::INFO;
SmartPiano::Logger logger { serial, buffer_size, highest_level };

SmartPiano::BinaryLedCommandInput led_command_input { serial, logger };

unsigned char num_leds = 144U;
SmartPiano::FastLedDisplay led_display { num_leds, logger, serial };

SmartPiano::Delayer delayer;

SmartPiano::SmartPiano smart_piano { led_command_input, led_display, delayer, logger };

void setup()
{
  serial.Initialize();
  logger.Initialize();
  logger.Log(SmartPiano::INFO, "SmartPiano Arduino server %s", SMARTPIANO_VERSION_STRING);
  led_display.Initialize();
}

void loop()
{
  smart_piano.Run();
}