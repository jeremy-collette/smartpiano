import serial
from midifile import MidiFile
from serialstream import SerialStream
from ledbar import LedBar
from ledbarpiano import LedBarPiano
from printer import Printer
from autoledbar import AutoLedBar

if (__name__ == "__main__"):
    #filename = "../beethoven_ode_to_joy_tracks.mid"
    filename = "../mgs-jez.mid"
    #filename = "../Sweden_Minecraft.mid"
    #filename = "../happy_birthday_tracks.mid"

    time_scale = 1
    num_leds = 144
    auto_update_span = 0.1
    left_hand_color = (10, 10, 255, 0)
    right_hand_color = (255, 10, 10, 0)

    with serial.Serial("/dev/ttyACM0", 115200) as ser:
        midifile = MidiFile(filename)
        printer = Printer()
        serial_stream = SerialStream(ser, printer)
        led_bar = LedBar(serial_stream, printer, num_leds)
        led_bar.init()
        auto_led_bar = AutoLedBar(led_bar, auto_update_span, printer)
        led_bar_piano = LedBarPiano(midifile, auto_led_bar, time_scale, printer, left_hand_color, right_hand_color)
        led_bar_piano.play()
