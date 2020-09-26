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

#include "FastLedDisplay.h"

#include <FastLED.h>

namespace SmartPiano
{

FastLedDisplay::FastLedDisplay(
    unsigned char num_leds,
    LoggerInterface& logger,
    OutputStreamInterface& command_output)
        : num_leds_{num_leds}
        , logger_{logger}
        , command_output_{command_output}
        , tick_{0}
{
    leds_ = new CRGB[num_leds];
}

FastLedDisplay::~FastLedDisplay()
{
    delete[] leds_;
}

bool FastLedDisplay::Initialize()
{
    logger_.Log(INFO, "Initializing FastLED...");
    FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds_, num_leds_);

    auto startingIndex = 0;
    uint8_t brightness = 255;
    CRGBPalette16 currentPalette = RainbowColors_p;
    TBlendType currentBlending = LINEARBLEND;

    // TODO(@jeremy): can we do this on steady-state (before note is received?)
    for (auto j = 0U; j < 500; ++j)
    {
        auto colorIndex = startingIndex++;
        for (auto i = 0U; i < num_leds_; ++i)
        {
            leds_[i] = ColorFromPalette(currentPalette, colorIndex, brightness, currentBlending);
            colorIndex += 1;
        }
        FastLED.show();
        FastLED.delay(1);
    }

    for (auto i = 0U; i < num_leds_; ++i)
    {
        leds_[i] = CRGB::Black;
    }
    FastLED.show();
    FastLED.delay(50);

    // TODO(@jeremy): consider moving
    command_output_.WriteByte(READY_MESSAGE);
    return true;
}

void FastLedDisplay::ExecuteLedCommand(const LedCommand& command)
{
    if (command.update)
    {
        ExecuteUpdateCommand(command);
    }
    else
    {
        ExecuteColorCommand(command);
    }

}

void FastLedDisplay::Tick(int delta)
{
    // Do nothing
}

bool FastLedDisplay::IsLedCommandOn(const LedCommand& note) const
{
    return note.red | note.green | note.blue | note.white;
}

void FastLedDisplay::ExecuteUpdateCommand(const LedCommand& command)
{
    logger_.Log(TEST, "Calling FastLED.show()!");
    FastLED.show();

    command_output_.WriteByte(UPDATE_COMPLETE_MESSAGE);
}

void FastLedDisplay::ExecuteColorCommand(const LedCommand& command)
{
    if (command.index < 0 || command.index >= num_leds_ - 1)
    {
        return;
    }

    auto color = CRGB{ command.red, command.green, command.blue };
    if (IsLedCommandOn(command))
    {
        logger_.Log(DEBUG, "Setting LEDs %u to color (%u, %u, %u, %u)."
            , command.index
            , command.red
            , command.green
            , command.blue
            , command.white);
    }
    else
    {
        logger_.Log(DEBUG, "Turning off LED %u."
            , command.index);
    }

    leds_[command.index] = color;
}

}