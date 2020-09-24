import serial
from midifile import MidiFile
from serialstream import SerialStream
from ledbar import LedBar
from smartpianoclient import SmartPianoClient
from printer import Printer
from autoledbar import AutoLedBar


class SmartPianoFactory:
    def __init__(self, serial_port="/dev/ttyACM0", baud=115200, num_leds=144):
        self.num_leds = num_leds
        self.printer = Printer()

        ser = serial.Serial(serial_port, baud)
        self.serial_stream = SerialStream(ser, self.printer)

    def create_led_bar_client(self):
        led_bar = LedBar(self.serial_stream, self.printer, self.num_leds)
        led_bar.init()
        return led_bar

    def create_auto_led_bar_client(self, auto_update_span=0.2):
        led_bar = self.create_led_bar_client()
        return AutoLedBar(led_bar, auto_update_span, self.printer)
        return led_bar

    def create_smart_piano_client(self, midi_filename, time_scale=1.0, left_hand_color=(10, 10, 255, 0),
                                  right_hand_color=(255, 10, 10, 0)):
        auto_led_bar = self.create_auto_led_bar_client()
        midi_file = MidiFile(midi_filename)
        led_bar_piano = SmartPianoClient(midi_file, auto_led_bar, time_scale, self.printer, left_hand_color,
                                         right_hand_color)
        return led_bar_piano
