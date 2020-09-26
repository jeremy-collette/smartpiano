/*
 * smartpiano Arduino Server
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

#include "SmartPiano.h"

namespace SmartPiano
{

SmartPiano::SmartPiano(
    LedCommandInputInterface& led_command_input
    , LedDisplayInterface& led_display
    , DelayerInterface& delayer
    , LoggerInterface& logger)
        : led_command_input_{led_command_input}
        , led_display_{led_display}
        , delayer_{delayer}
        , logger_{logger}
{
}

void SmartPiano::Run()
{
    auto delta = 0;
    logger_.Log(INFO, "Started running");
    while (!led_command_input_.IsEof())
    {
        logger_.Log(NOISY, "Tick");

        LedCommand led_command;
        while (led_command_input_.TryGetNextCommand(&led_command))
        {
            logger_.Log(INFO, "Got LED command. Index = %u, Red = %u, Green = %u, Blue = %u, White = %u"
                , led_command.index
                , led_command.red
                , led_command.green
                , led_command.blue
                , led_command.white);

            led_display_.ExecuteLedCommand(led_command);
        }

        led_display_.Tick(delta);
        led_command_input_.Tick(delta);
        delta = 100;
        delayer_.Delay(delta);
    }
}

}