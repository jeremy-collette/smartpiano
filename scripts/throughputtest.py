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
        midi_note = index + 30
        print("Turning " + state + " note " + str(midi_note))
        packet.append(0x32)
        packet.append(midi_note)
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
            while i <= 73:
                #send_command(i, state)
                #i += 1
                #send_command(i, state)
                #i += 1
                indexes = range(i, i+10)
                send_commands(indexes, state)
                i += len(indexes)
                time.sleep(1)
                

