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

#ifndef SMARTPIANO_SERIAL_H_
#define SMARTPIANO_SERIAL_H_

#include "SerialInterface.h"

namespace SmartPiano
{

class Serial : public SerialInterface
{
 public:
    Serial(unsigned long baud);

    virtual int AvailableBytes();
    virtual bool Initialize();
    virtual int WriteData(const char* data);
    virtual int WriteByte(char byte);
    virtual int ReadByte();
    virtual int PeekByte();

 private:
    unsigned long baud_;
};

}

#endif  // SMARTPIANO_SERIAL_H_