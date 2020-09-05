// TODO: don't include
#include <Arduino.h>

#include "SmartPiano.h"

namespace SmartPiano
{

SmartPiano::SmartPiano(
    LedCommandInputInterface& led_command_input
    , LedDisplayInterface& led_display
    , DelayerInterface& delayer
    , LoggerInterface& logger)
        : led_command_input_{led_command_input}
        , led_display_{led_display}
        , delayer_{delayer}
        , logger_{logger}
{
}

void SmartPiano::Run()
{
    logger_.Log(INFO, "Started running");
    while (!led_command_input_.IsEof())
    {
        logger_.Log(NOISY, "Tick");
        LedCommand led_command;
        while (led_command_input_.TryGetNextCommand(&led_command))
        {
            char buf[128];
            sprintf(buf, "Got note. Key = %u, On = %u", led_command.index, led_command.red | led_command.green | led_command.blue | led_command.white);
            logger_.Log(INFO, buf);
            led_display_.ExecuteLedCommand(led_command);
        }

        auto delta = 10;
        delayer_.Delay(delta);
        led_command_input_.Tick(delta);
    }
}

}