#include "SerialBinaryLedCommandInput.h"

namespace SmartPiano
{

SerialBinaryLedCommandInput::SerialBinaryLedCommandInput(
    SerialInterface& serial
    , LoggerInterface& logger)
        : serial_{serial}
        , logger_{logger}
{

}

bool SerialBinaryLedCommandInput::Initialize()
{
    return true;
}

bool SerialBinaryLedCommandInput::TryGetNextCommand(LedCommand* command_out)
{
    // TODO(jeremy): move this logic to tick?
    auto available_bytes = serial_.Available();
    if (available_bytes < 4)
    {
        return false;
    }
    logger_.Log(SmartPiano::NOISY, "Available bytes: %d", available_bytes);

    char check_byte = serial_.ReadByte();
    if (check_byte != 0x32)
    {
        logger_.Log(SmartPiano::WARNING, "Got invalid check byte: %d", check_byte);
        return false;
    }

    int key = serial_.ReadByte();
    int on = serial_.ReadByte();
    int track = serial_.ReadByte();
    logger_.Log(SmartPiano::TEST, "Got command: note=%d, on=%s, track=%d", key, on ? "True" : "False", track);

    command_out->index = key;
    if (!on)
    {
        command_out->red = 0;
        command_out->green = 0;
        command_out->blue = 0;
        command_out->white = 0;
        return true;
    }

    if (track % 2 == 0)
    {
        command_out->red = 255;
        command_out->green = 0;
        command_out->blue = 0;
        command_out->white = 0;
    }
    else
    {
        command_out->red = 0;
        command_out->green = 0;
        command_out->blue = 255;
        command_out->white = 0;
    }
    return true;
}

void SerialBinaryLedCommandInput::Tick(int delta)
{
    // Do nothing
}

bool SerialBinaryLedCommandInput::IsEof()
{
    return false;
}

}