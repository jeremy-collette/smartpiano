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

#ifndef SMARTPIANO_SMARTPIANO_H_
#define SMARTPIANO_SMARTPIANO_H_

#include "SmartPianoInterface.h"

#include "DelayerInterface.h"
#include "LoggerInterface.h"
#include "LedCommandInputInterface.h"
#include "LedDisplayInterface.h"

namespace SmartPiano
{

class SmartPiano : public SmartPianoInterface
{
 public:
    SmartPiano(
        LedCommandInputInterface& led_command_input
        , LedDisplayInterface& note_display
        , DelayerInterface& delayer
        , LoggerInterface& logger);

    virtual void Run();

 private:
    LedCommandInputInterface& led_command_input_;
    LedDisplayInterface& led_display_;
    DelayerInterface& delayer_;
    LoggerInterface& logger_;
};

}

#endif  // SMARTPIANO_SMARTPIANO_H_