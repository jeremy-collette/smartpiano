import serial
from mido import MidiFile
import time

def send_command(index, state):
    print("Turning " + state + " LED " + str(index) + " and " + str(index+1))
    midi_note = index + 30

    packet = bytearray()
    packet.append(0x32)
    packet.append(midi_note)
    packet.append(state == "on")
    ser.write(packet)

def send_data(data):
    packet = bytearray()
    for d in data:
        packet.append(d)
    ser.write(packet)

while True:
    with serial.Serial("/dev/ttyACM0", 115200) as ser:
        send_data(range(0, 256))
        print("Send data!")
        raw_input("Press enter ")


