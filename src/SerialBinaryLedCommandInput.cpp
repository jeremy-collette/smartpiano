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
    if (available_bytes < 5)
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

    command_out->index = serial_.ReadByte();
    command_out->red = serial_.ReadByte();
    command_out->green = serial_.ReadByte();
    command_out->blue = serial_.ReadByte();
    command_out->white = serial_.ReadByte();
    logger_.Log(SmartPiano::TEST, "Got LED command: index=%d, on=%s"
        , command_out->index
        , command_out->red | command_out->green | command_out->blue | command_out->white ? "True" : "False");

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