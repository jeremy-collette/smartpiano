import serial, time, sys
from mido import MidiFile
from datetime import datetime 
from serialstream import SerialStream
from throttledserialstream import ThrottledSerialStream
from ledbar import LedBar

with serial.Serial("/dev/ttyACM0", 115200) as ser:
    time.sleep(10)

    throttledSerialStream = ThrottledSerialStream(SerialStream(ser))
    ledBar = LedBar(throttledSerialStream)

    for i in range(0, 144):
        print("Turning on " + str(i))
        ledBar.set_led(i, (255, 0, 0, 0))
        time.sleep(1)

    #while True:
    #    index = int(input("Enter LED index: "))
    #    r = int(input("R: "))
    #    g = int(input("G: "))
    #    b = int(input("B: "))
    #    w = int(input("W: "))
    #
    #    ledBar.set_led(index, (r, g, b, w))