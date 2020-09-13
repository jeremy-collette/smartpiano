#include "SerialJsonLedCommandInput.h"

#include <Arduino.h>

namespace SmartPiano
{

SerialJsonLedCommandInput::SerialJsonLedCommandInput(LoggerInterface& logger)
    : logger_{logger}
{

}

bool SerialJsonLedCommandInput::Initialize()
{
    return true;
}


bool SerialJsonLedCommandInput::TryGetNextCommand(LedCommand* command_out)
{
    // TODO(jeremy): move this logic to tick
    //logger_.Log(LogLevel::TEST, "Test!");
    if (!Serial.available())
    {
        return false;
    }

    auto commandString = Serial.readStringUntil('\n');
    logger_.Log(LogLevel::TEST, commandString.c_str());

    auto err = deserializeJson(json_doc_, commandString);
    if (err != DeserializationError::Ok)
    {
        char buf[50];
        snprintf(buf, 50, "Deserialization error: %u", err.code());
        logger_.Log(LogLevel::WARNING, buf);
        return false;
    }
    //logger_.Log(LogLevel::TEST, "Deserialized successfully!");

    auto key = json_doc_["key"].as<uint8_t>();
    auto on = json_doc_["on"].as<uint8_t>();

    command_out->index = key;
    if (!on)
    {
        command_out->red = 0;
        command_out->green = 0;
        command_out->blue = 0;
        command_out->white = 0;
        return true;
    }

    if (key >= 60)
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

void SerialJsonLedCommandInput::Tick(int delta)
{
    // Do nothing
}

bool SerialJsonLedCommandInput::IsEof()
{
    return false;
}

}