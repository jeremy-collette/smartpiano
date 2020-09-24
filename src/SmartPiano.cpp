#include "SmartPiano.h"

namespace SmartPiano
{

SmartPiano::SmartPiano(
    LedCommandInputInterface& led_command_input
    , LedDisplayInterface& led_display
    , DelayerInterface& delayer
    , LoggerInterface& logger
    , UpdateCommandInputInterface& update_command_input)
        : led_command_input_{led_command_input}
        , led_display_{led_display}
        , delayer_{delayer}
        , logger_{logger}
        , update_command_input_{update_command_input}
{
}

void SmartPiano::Run()
{
    auto delta = 0;
    logger_.Log(INFO, "Started running");
    while (!led_command_input_.IsEof())
    {
        logger_.Log(NOISY, "Tick");

        auto got_command = false;
        do
        {
            LedCommand led_command;
            if (led_command_input_.TryGetNextCommand(&led_command))
            {
                got_command = true;

                logger_.Log(INFO, "Got LED command. Index = %u, Red = %u, Green = %u, Blue = %u, White = %u"
                    , led_command.index
                    , led_command.red
                    , led_command.green
                    , led_command.blue
                    , led_command.white);

                led_display_.ExecuteLedCommand(led_command);
            }

            UpdateCommand update_command;
            if (update_command_input_.TryGetNextCommand(&update_command))
            {
                got_command = true;

                logger_.Log(INFO, "Got Update command.");

                led_display_.ExecuteUpdateCommand(update_command);
            }
        } while(got_command);

        led_display_.Tick(delta);
        led_command_input_.Tick(delta);
        delta = 100;
        delayer_.Delay(delta);
    }
}

}