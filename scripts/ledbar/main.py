import serial
from midifile import MidiFile
from datetime import datetime 
from serialstream import SerialStream
from throttledserialstream import ThrottledSerialStream
from ledbar import LedBar
from ledbarpiano import LedBarPiano
from printer import Printer

if (__name__ == "__main__"):
    filename = "../Sweden_Minecraft.mid"
    time_scale = 1

    with serial.Serial("/dev/ttyACM0", 115200) as ser:
        midifile = MidiFile(filename)
        printer = Printer()
        serialStream = SerialStream(ser, printer)
        ledBar = LedBar(serialStream, printer)
        ledBar.init()
        ledBarPiano = LedBarPiano(midifile, ledBar, time_scale)

        ledBarPiano.play()


#for on in reversed(range(0, 2)):
#    for i in range(0, 144):
#        printer.printmsg("Turning on " + str(i))
#        ledBar.set_led(i, (0, on * 255, 0, 0))
#        #time.sleep(0.01)
#        ledBar.update()

#while True:
#    index = int(input("Enter LED index: "))
#    r = int(input("R: "))
#    g = int(input("G: "))
#    b = int(input("B: "))
#    w = int(input("W: "))
#
#    ledBar.set_led(index, (r, g, b, w))
