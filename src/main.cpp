#include <Arduino.h>

#include "ArduinoDelayer.h"
#include "ArduinoSerialLogger.h"
#include "MockMidiInput.h"
#include "FastLedNoteDisplay.h"
#include "SmartPiano.h"

void setup() {

}

void loop() {
  auto baud = 9600U;
  auto buffer_size = 256U;
  unsigned char level_mask = SmartPiano::DEBUG | SmartPiano::INFO | SmartPiano::WARNING | SmartPiano::ERROR; //| SmartPiano::NOISY;
  SmartPiano::ArduinoSerialLogger logger { baud, buffer_size, level_mask };
  logger.Initialize();

  SmartPiano::MockMidiInput midi_input { logger };

  auto num_leds = 144U;
  SmartPiano::FastLedNoteDisplay note_display { num_leds, logger };
  note_display.Initialize();

  SmartPiano::ArduinoDelayer delayer;

  while (true)
  {
    SmartPiano::SmartPiano smart_piano { midi_input, note_display, delayer, logger };
    smart_piano.Run();
  }
}