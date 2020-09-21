import serial
from mido import MidiFile
import time

ready = 0
send = 0
time_scale = 1

def send_packet(ser, data):
    packet = bytearray()
    for d in data:
        packet.append(d)
    ser.write(packet)

def send_midi_message(ser, msg):    
    global send
    while send == 0 or ser.in_waiting > 0:
        line = ser.readline().strip()
        print("Received \"" + line + "\"")

        if (line == "STOP"):
            print("Got stop!")
            send = 0
        elif (line == "START"):
            send = 1

    if (msg.type == "note_on" or msg.type == "note_off"):            
        is_on = int(msg.type == "note_on" and msg.velocity != 0)            
        send_packet(ser, [0x32, int(msg.note), is_on])        
        print("Wrote data: note=" + str(msg.note) + ", on=" + str(is_on))

# TODO Correlate note with track info
##mid = MidiFile('Sweden_Minecraft.mid')
##for i, track in enumerate(mid.tracks):
##    #print(track[i][0].__dict__)
##    for msg in track:
##        print msg.__dict__

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
    #for msg in MidiFile('Sweden_Minecraft.mid'):
        time.sleep(msg.time / time_scale)
        send_midi_message(ser, msg)

time.sleep(5)
print("Done!")

