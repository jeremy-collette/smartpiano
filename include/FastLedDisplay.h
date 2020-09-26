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

#ifndef SMARTPIANO_FASTLEDDISPLAY_H_
#define SMARTPIANO_FASTLEDDISPLAY_H_

#include "LedDisplayInterface.h"

#include <FastLED.h>

#include "LoggerInterface.h"
#include "OutputStreamInterface.h"

namespace SmartPiano
{

class FastLedDisplay : public LedDisplayInterface
{
 public:
    const static int DATA_PIN = 8;

    FastLedDisplay(
        unsigned char num_leds
        , LoggerInterface& logger
        , OutputStreamInterface& command_output);
    virtual ~FastLedDisplay();

    virtual bool Initialize();
    virtual void ExecuteLedCommand(const LedCommand& command);
    virtual void Tick(int delta);

 private:
    const static char READY_MESSAGE = 0x42;
    const static char UPDATE_COMPLETE_MESSAGE = 0x64;

    CRGB* leds_;
    unsigned char num_leds_;
    unsigned char data_pin_;
    LoggerInterface& logger_;
    OutputStreamInterface& command_output_;
    // TODO: change data type
    int tick_;

    bool IsLedCommandOn(const LedCommand& command) const;
    void ExecuteUpdateCommand(const LedCommand& command);
    void ExecuteColorCommand(const LedCommand& command);
};

}

#endif  // SMARTPIANO_FASTLEDNOTEDISPLAY_H_