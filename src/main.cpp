#include <Arduino.h>

#include "Delayer.h"
#include "FastLedDisplay.h"
//#include "MockLedCommandInput.h"
#include "SerialBinaryLedCommandInput.h"
#include "SerialLogger.h"
#include "SmartPiano.h"

// TODO(@jez): remove
#include "LedCommand.h"

void setup() {

}

// void loop() {
//   auto baud = 115200U;
//   auto buffer_size = 256U;
//   unsigned char level_mask = SmartPiano::TEST | SmartPiano::WARNING | SmartPiano::ERROR;
//     //SmartPiano::DEBUG | SmartPiano::INFO | SmartPiano::WARNING | SmartPiano::ERROR /*| SmartPiano::NOISY*/ | SmartPiano::TEST;
//   SmartPiano::SerialLogger logger { baud, buffer_size, level_mask };
//   logger.Initialize();

//    //SmartPiano::MockLedCommandInput led_command_input { logger };
//   SmartPiano::SerialBinaryLedCommandInput led_command_input { logger };

//   auto num_leds = 144U;
//   SmartPiano::FastLedDisplay led_display { num_leds, logger };
//   led_display.Initialize();

//   SmartPiano::Delayer delayer;

//   while (true)
//   {
//     SmartPiano::SmartPiano smart_piano { led_command_input, led_display, delayer, logger };
//     smart_piano.Run();
//   }
// }


void loop()
{
    auto baud = 115200U;
    auto buffer_size = 256U;
    unsigned char level_mask = 0;
    SmartPiano::SerialLogger logger { baud, buffer_size, level_mask };
    logger.Initialize();

    auto num_leds = 144U;
    SmartPiano::FastLedDisplay led_display { num_leds, logger };
    led_display.Initialize();

    Serial.begin(115200U);
    char buffer[256];
    Serial.println("Ready!");

    auto commands = 0;
    while (true)
    {
        if (Serial.available() < 3)
        {
            continue;
        }
        ++commands;

        auto header = Serial.read();
        auto key = Serial.read();
        auto on = Serial.read();

        snprintf(buffer, 256, "Header = %d, Key = %d, On = %d", header, key, on);
        Serial.println(buffer);

        SmartPiano::LedCommand command;
        command.index = key;
        command.red = on ? 255 : 0;
        command.green = 0;
        command.blue = 0;
        command.white = 0;

        led_display.ExecuteLedCommand(command);
        if (commands % 10 == 0)
        {
            led_display.Tick(0);
        }
        //delay(10);
    }
}