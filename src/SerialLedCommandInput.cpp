#include "SerialLedCommandInput.h"

#include <Arduino.h>
#include <ArduinoJson.h>

namespace SmartPiano
{

// TODO(@jeremy): move
StaticJsonDocument<128> doc;

SerialLedCommandInput::SerialLedCommandInput(LoggerInterface& logger)
    : logger_{logger}
{

}

bool SerialLedCommandInput::Initialize()
{
    return true;
}

bool SerialLedCommandInput::TryGetNextCommand(LedCommand* command_out)
{
    // TODO(jeremy): move this logic to tick
    //logger_.Log(LogLevel::TEST, "Test!");
    if (!Serial.available())
    {
        return false;
    }

    auto commandString = Serial.readStringUntil('\n');
    logger_.Log(LogLevel::TEST, commandString.c_str());

    auto err = deserializeJson(doc, commandString);
    if (err != DeserializationError::Ok)
    {
        char buf[50];
        snprintf(buf, 50, "Deserialization error: %u", err.code());
        logger_.Log(LogLevel::WARNING, buf);
        return false;
    }
    //logger_.Log(LogLevel::TEST, "Deserialized successfully!");

    auto key = doc["key"].as<uint8_t>();
    auto on = doc["on"].as<uint8_t>();

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

void SerialLedCommandInput::Tick(int delta)
{
    // Do nothing
}

bool SerialLedCommandInput::IsEof()
{
    return false;
}

}