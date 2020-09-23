import serial
from midifile import MidiFile
from serialstream import SerialStream
from ledbar import LedBar
from ledbarpiano import LedBarPiano
from printer import Printer

if (__name__ == "__main__"):
    filename = "../beethoven_ode_to_joy_tracks.mid"
    time_scale = 1
    num_leds = 144

    with serial.Serial("/dev/ttyACM0", 115200) as ser:
        midifile = MidiFile(filename)
        printer = Printer()
        serial_stream = SerialStream(ser, printer)
        led_bar = LedBar(serial_stream, printer, num_leds)
        led_bar.init()
        led_bar_piano = LedBarPiano(midifile, led_bar, time_scale)
        led_bar_piano.play()
