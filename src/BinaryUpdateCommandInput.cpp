#include "BinaryUpdateCommandInput.h"

namespace SmartPiano
{

BinaryUpdateCommandInput::BinaryUpdateCommandInput(
    InputStreamInterface& input_stream
    , LoggerInterface& logger)
        : input_stream_{input_stream}
        , logger_{logger}
{

}

bool BinaryUpdateCommandInput::Initialize()
{
    return true;
}

bool BinaryUpdateCommandInput::TryGetNextCommand(UpdateCommand* command_out)
{
    // TODO(@jeremy): move this out
    while (input_stream_.AvailableBytes()
        && input_stream_.PeekByte() != 0x93
        && input_stream_.PeekByte() != 0x32)
    {
        input_stream_.ReadByte();
    }

    if (input_stream_.PeekByte() != 0x93)
    {
        return false;
    }
    input_stream_.ReadByte();

    return true;
}

void BinaryUpdateCommandInput::Tick(int delta)
{
    // Do nothing
}

bool BinaryUpdateCommandInput::IsEof()
{
    return false;
}

}