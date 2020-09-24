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
    auto available_bytes = input_stream_.AvailableBytes();
    if (available_bytes < 5)
    {
        return false;
    }
    logger_.Log(SmartPiano::NOISY, "Available bytes: %d", available_bytes);

    char check_byte = input_stream_.ReadByte();
    if (check_byte != 0x32)
    {
        logger_.Log(SmartPiano::WARNING, "Got invalid check byte: %d", check_byte);
        return false;
    }

    command_out->index = input_stream_.ReadByte();
    command_out->red = input_stream_.ReadByte();
    command_out->green = input_stream_.ReadByte();
    command_out->blue = input_stream_.ReadByte();
    command_out->white = input_stream_.ReadByte();
    logger_.Log(SmartPiano::NOISY, "Got LED command: index=%d, on=%s"
        , command_out->index
        , command_out->red | command_out->green | command_out->blue | command_out->white ? "True" : "False");

    return true;
}

void BinaryLedCommandInput::Tick(int delta)
{
    // Do nothing
}

bool BinaryLedCommandInput::IsEof()
{
    return false;
}

}