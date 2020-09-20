import serial
from mido import MidiFile
import time

ready = 0
send = 0
time_scale = 1
with serial.Serial("/dev/ttyACM0", 115200) as ser:
    print("Waiting for Ready...")
    while ready == 0:
        line = ser.readline().strip()
        print("Received \"" + line + "\"")
        
        if (line == "Ready!"):
            ready = 1
        
    print("Beginning song...")
    time_index = 0
    for msg in MidiFile('mgs-jez.mid'):
        time.sleep(msg.time / time_scale)
        
        while send == 0 or ser.in_waiting > 0:
            line = ser.readline().strip()
            print("Received \"" + line + "\"")

            if (line == "STOP send"):
                send = 0
            elif (line == "OK send"):
                send = 1

        if (msg.type == "note_on" or msg.type == "note_off"):
            #print(msg.__dict__)
            packet = bytearray()
            packet.append(0x32)
            packet.append(int(msg.note))
            packet.append(int(msg.type == "note_on"))
            ser.write(packet)
            print("Wrote data: note=" + str(msg.note) + ", on=" + str(msg.type == "note_on"))
    time.sleep(5)
    print("Done!")
