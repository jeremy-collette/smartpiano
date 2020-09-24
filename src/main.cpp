#include <Arduino.h>

#include "BinaryLedCommandInput.h"
#include "BinaryUpdateCommandInput.h"
#include "Delayer.h"
#include "FastLedDisplay.h"
#include "Logger.h"
#include "Serial.h"
#include "SerialCommandInputStream.h"
#include "SerialCommandOutputStream.h"
#include "SerialLogOutputStream.h"
#include "SmartPiano.h"


auto baud = 115200U;
SmartPiano::Serial serial { baud };

auto buffer_size = 256U;
auto highest_level = SmartPiano::TEST;
auto logger_output_stream = SmartPiano::SerialLogOutputStream { serial };
SmartPiano::Logger logger { logger_output_stream, buffer_size, highest_level };

SmartPiano::SerialCommandInputStream command_input_stream { serial };

SmartPiano::BinaryLedCommandInput led_command_input { command_input_stream, logger };

SmartPiano::BinaryUpdateCommandInput update_command_input { command_input_stream, logger };

SmartPiano::SerialCommandOutputStream command_output_stream { serial };

unsigned char num_leds = 144U;
SmartPiano::FastLedDisplay led_display { num_leds, logger, command_output_stream };

SmartPiano::Delayer delayer;

SmartPiano::SmartPiano smart_piano { led_command_input, led_display, delayer, logger, update_command_input };

void setup()
{
  serial.Initialize();
  logger.Initialize();
  led_display.Initialize();
}

void loop()
{
  smart_piano.Run();
}