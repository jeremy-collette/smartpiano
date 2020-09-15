#include <Arduino.h>

#include "Delayer.h"
#include "FastLedDisplay.h"
//#include "MockLedCommandInput.h"
#include "SerialBinaryLedCommandInput.h"
#include "SerialLogger.h"
#include "SmartPiano.h"

// TODO(@jez): remove
#include "LedCommand.h"
#include <FastLED.h>

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
    auto leds = new CRGB[144];
    FastLED.addLeds<WS2812, 8, GRB>(leds, 144);

    Serial.begin(115200U);
    char buffer[128];
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

        if (header != 0x32)
        {
            snprintf(buffer, 128, "Invalid header %d!", header);
            Serial.println(buffer);
            continue;
        }
        auto key = Serial.read();
        auto on = Serial.read();

        snprintf(buffer, 128, "Header = %d, Key = %d, On = %d", header, key, on);
        Serial.println(buffer);

        if (key < 0 || key >= 144)
        {
            snprintf(buffer, 128, "Invalid key %d!", key);
            Serial.println(buffer);
            continue;
        }

        auto color = on ? CRGB::Red : CRGB::Black;
        leds[key] = color;

        if (commands % 10 == 0)
        {
            commands = 0;
            FastLED.show();
        }
        //delay(10);
    }
}