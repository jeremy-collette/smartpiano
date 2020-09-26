/*
 * smartpiano
 * Copyright (C) 2020 Jeremy Collette.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

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
  logger.Log(SmartPiano::INFO, "smartpiano Arduino Server %s", SMARTPIANO_VERSION_STRING);
  led_display.Initialize();
}

void loop()
{
  smart_piano.Run();
}