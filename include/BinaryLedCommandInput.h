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

#ifndef SMARTPIANO_BINARYLEDCOMMANDINPUT_H_
#define SMARTPIANO_BINARYLEDCOMMANDINPUT_H_

#include "LedCommandInputInterface.h"

#include "InputStreamInterface.h"
#include "LoggerInterface.h"

namespace SmartPiano
{

class BinaryLedCommandInput : public LedCommandInputInterface
{
 public:
   BinaryLedCommandInput(
     InputStreamInterface& input_stream
     , LoggerInterface& logger);

   virtual bool Initialize();

   virtual bool TryGetNextCommand(LedCommand* command_out);
   virtual void Tick(int delta);
   virtual bool IsEof();

 private:
  static const int COLOR_COMMAND_HEADER = 0x32;
  static const int UPDATE_COMMAND_HEADER = 0x93;

  InputStreamInterface& input_stream_;
  LoggerInterface& logger_;

  bool HandleColorCommand(LedCommand* command_out);
  bool HandleUpdateCommand(LedCommand* command_out);
  bool IsValidHeaderByte(int byte);
};

}

#endif  // SMARTPIANO_BINARYLEDCOMMANDINPUT_H_