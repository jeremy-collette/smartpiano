#include <Arduino.h>

#include <FastLED.h>

void setup() {

}

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
        auto available_byes = Serial.available();
        if (available_byes < 3)
        {
            continue;
        }
        ++commands;

        snprintf(buffer, 128, "Available bytes: %d", available_byes);
        Serial.println(buffer);

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