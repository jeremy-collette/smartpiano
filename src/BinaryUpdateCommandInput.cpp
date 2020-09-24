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