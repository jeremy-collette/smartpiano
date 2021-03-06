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

#ifndef SMARTPIANO_LEDCOMMANDINPUTINTERFACE_H_
#define SMARTPIANO_LEDCOMMANDINPUTINTERFACE_H_

#include "LedCommand.h"

namespace SmartPiano
{

class LedCommandInputInterface
{
 public:
    virtual bool TryGetNextCommand(LedCommand* note_out) = 0;
    virtual void Tick(int delta) = 0;
    virtual bool IsEof() = 0;
};

}

#endif  // SMARTPIANO_LEDCOMMANDINPUTINTERFACE_H_