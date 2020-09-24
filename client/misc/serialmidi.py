import serial
from mido import MidiFile
import time
import json

time_scale = 1
with serial.Serial("/dev/ttyACM0", 115200) as ser:
    time_index = 0
    for msg in MidiFile('mgs-jez.mid'):
        time.sleep(msg.time / time_scale)
        if (msg.type == "note_on" or msg.type == "note_off" and int(msg.note) >= 59):
            command = { 
                "key": str(msg.note), 
                "on": str(int(msg.type == "note_on")) 
            }
            data = json.dumps(command)
            print(data)
            data += '\n'
            ser.write(data)

