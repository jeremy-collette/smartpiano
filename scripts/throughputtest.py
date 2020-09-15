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

def send_commands(indexes, state):
    packet = bytearray()
    for i in range(0, len(indexes)):
        index = indexes[i]
        print("Turning " + state + " LED " + str(index))
        packet.append(0x32)
        packet.append(index)
        packet.append(state == "on")
    ser.write(packet)

while True:
    with serial.Serial("/dev/ttyACM0", 115200) as ser:
        for j in reversed(range(0, 2)):
            if (j == 1):
                state = "on"
            else:
                state = "off"

            i = 0
            while i < 144:
                indexes = range(i, min(i+25,144))
                send_commands(indexes, state)
                i += len(indexes)
                time.sleep(1)
                

