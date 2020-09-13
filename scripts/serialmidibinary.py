import serial
from mido import MidiFile
import time

time_scale = 1
with serial.Serial("/dev/ttyACM0", 115200) as ser:
    time_index = 0
    for msg in MidiFile('mgs-jez.mid'):
        time.sleep(msg.time / time_scale)
        if (msg.type == "note_on" or msg.type == "note_off"):
            #print(msg.__dict__)
            packet = bytearray()
            packet.append(0x32)
            packet.append(int(msg.note))
            packet.append(int(msg.type == "note_on"))
            ser.write(packet)
            print("Wrote data: note=" + str(msg.note) + ", on=" + str(msg.type == "note_on"))

