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

#include "BinaryLedCommandInput.h"

namespace SmartPiano
{

BinaryLedCommandInput::BinaryLedCommandInput(
    InputStreamInterface& input_stream
    , LoggerInterface& logger)
        : input_stream_{input_stream}
        , logger_{logger}
{

}

bool BinaryLedCommandInput::Initialize()
{
    return true;
}

bool BinaryLedCommandInput::TryGetNextCommand(LedCommand* command_out)
{
    while (input_stream_.AvailableBytes() && !IsValidHeaderByte(input_stream_.PeekByte()))
    {
        auto invalid_byte = input_stream_.ReadByte();
        logger_.Log(SmartPiano::WARNING, "Got invalid header byte: %d", invalid_byte);
    }

    if (!input_stream_.AvailableBytes())
    {
        return false;
    }

    auto check_byte = input_stream_.PeekByte();
    switch (check_byte)
    {
        case UPDATE_COMMAND_HEADER:
            return HandleUpdateCommand(command_out);
        case COLOR_COMMAND_HEADER:
            return HandleColorCommand(command_out);
        default:
            return false;
    }


}

void BinaryLedCommandInput::Tick(int delta)
{
    // Do nothing
}

bool BinaryLedCommandInput::IsEof()
{
    return false;
}

bool BinaryLedCommandInput::HandleColorCommand(LedCommand* command_out)
{
    auto available_bytes = input_stream_.AvailableBytes();
    if (available_bytes < 6)
    {
        logger_.Log(SmartPiano::DEBUG, "Expected 6 bytes but found: %d", available_bytes);
        return false;
    }

    auto header_byte = input_stream_.ReadByte();
    if (header_byte != COLOR_COMMAND_HEADER)
    {
        logger_.Log(SmartPiano::DEBUG, "Expected ColorCommand header byte %d but found: %d", COLOR_COMMAND_HEADER, header_byte);
        return false;
    }

    // Not an update command
    command_out->update = false;

    command_out->index = input_stream_.ReadByte();
    command_out->red = input_stream_.ReadByte();
    command_out->green = input_stream_.ReadByte();
    command_out->blue = input_stream_.ReadByte();
    command_out->white = input_stream_.ReadByte();

    logger_.Log(SmartPiano::DEBUG, "Got LED command: index=%d, on=%s"
        , command_out->index
        , command_out->red | command_out->green | command_out->blue | command_out->white ? "True" : "False");

    return true;
}

bool BinaryLedCommandInput::HandleUpdateCommand(LedCommand* command_out)
{
    auto header_byte = input_stream_.ReadByte();
    if (header_byte != UPDATE_COMMAND_HEADER)
    {
        logger_.Log(SmartPiano::DEBUG, "Expected UpdateCommand header byte %d but found: %d", UPDATE_COMMAND_HEADER, header_byte);
        return false;
    }

    // This is an update command
    command_out->update = true;

    return true;
}

bool BinaryLedCommandInput::IsValidHeaderByte(int byte)
{
    return byte == UPDATE_COMMAND_HEADER
        || byte == COLOR_COMMAND_HEADER;
}

}