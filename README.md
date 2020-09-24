# smartpiano

smartpiano is a free & open-source project that lights up keys on a piano or digital keyboard to play a selected MIDI song. This is achieved using a PC running the smartpiano client, an Arduino running the smartpiano server, and a strip of LEDs which are placed on the instrument. This repository contains all the instructions for assembling the project and the required source code to run on both the PC and Arduino.

**NOTE: Please note this project is still in alpha phase. Some features may be incomplete and/or may not meet quality standards. Show your support by reporting and/or fixing bugs.**

## License
smartpiano is released as free software under the GPLv3 license. Please note that there may be some conditions that apply to the free use and distribution of this software. Please see the LICENSE file for more information.

## Disclaimer of Warranty
Please note that this project is provided "as is", without warranty of any kind, either expressed or implied. If you choose to use the source code or software provided as part of this project, or choose to follow the instructions provided (here or anywhere else in the project) to assemble a smartpiano server (or any other device), please note that you are doing this at your own risk. Any instructions provided may be inaccurate or incomplete, or may be inapplicable to your situtation.

## Requirements
### Hardware
As mentioned above, smartpiano requires certain hardware to run. This list includes the hardware we are using. We recommend using the same hardware as us, but you may be able to tweek the smartpiano codebase to use your custom hardware:
  * Arduino Uno
  * WS2812B LED strip. 1 meter long with 144 LEDs
  * 220 ohm resistor
  * Breadboard and wires
  * USB to connect Arduino to PC
  * PC with USB connection
  * Piano or digital keyboard

### Software
  * Visual Studio Code with the PlatformIO plugin installed to build & upload the smartpiano server code to the Arduino
  * Python3 (with pip installed) to run the smartpiano client code
    - PyCharm is recommended for editing the smartpiano client code
  * A MIDI file to play

## Assembling the Arduino
To assemble the Arduino components, follow the following steps:
  1. Disconnect the Arduino from any power sources
  2. Connect the Arduino 5V power output to the breadboard
  3. Connect the Arduino GND input to the breadboard
  4. Connect a wire from 5V power on the breadboard to the connector that is marked 5V on the WS2812B LED strip
  5. Connect a wire from the GND on the breadboard to the connector that is marked GROUND on the WS2812B LED strip
  6. Connect a wire from digital pin 8 to the breadboard
  7. Put the 220 ohm resistor on the breadboard so it is connected to the wire coming from digital pin 8
  8. Connect a wire from the other end of the resistor to the connector that is marked DATA on the WS2812B LED strip


## Uploading code to the Arduino
  1. Open the "smartpiano" folder in Visual Studio Code
  2. Open the PlatformIO context menu, and click "Build"
  3. When the build completes, click "Upload"
  4. If you want to check that the code is running, click "Monitor"
  5. You should see the LED strip on the Arduino light up as the code is initialized

**NOTE: If you use the monitor, make sure you close it before you try to run the smartpiano client. Otherwise the client will not be able to connect to the Arduino using the serial port.**

## Running the client
Now that you have an Arduino running the smartpiano server code, you can connect to it using the client to play a song:
1. Navigate to the "client" folder in your favorite terminal.
2. Navigate to the "smartpianoclient" folder.
3. Install the required dependencies:
```sh
pip3 install serial==0.0.97
pip3 install mido==1.2.9
```
4. Run the client with no arguments to see available options:
```sh
python3 main.py
```
5. Run the client with a specified MIDI file:
```sh
python3 main.py "~/Desktop/some_midi_file.mid"
```

## Play at Carnegie Hall
Now that you're all setup and playing piano. It's time to practice, practice, practice!
