import serial
from mido import MidiFile
import time, sys

ready = 0
send = 0
time_scale = 1

def send_packet(ser, data):
    packet = bytearray()
    for d in data:
        packet.append(d)
    ser.write(packet)

def send_midi_message(ser, msg, track):    
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
        send_packet(ser, [0x32, int(msg.note), is_on, int(track)])
        print("Wrote data: note=" + str(msg.note) + ", on=" + str(is_on) + ", track=" + str(track))

#midi_file = MidiFile('mgs-jez.mid'):
midi_file = MidiFile('Sweden_Minecraft.mid')
msg_tracks = []
for i,track in enumerate(midi_file.tracks):
    total_time = 0
    for msg in track:
        total_time += msg.time
        if (msg.type != "note_on" and msg.type != "note_off"):
            continue
        msg_tracks.append((total_time, i))
        #print(str(total_time) + " -> " + str(msg.note))
msg_tracks = sorted(msg_tracks, key=lambda x: x[0])

with serial.Serial("/dev/ttyACM0", 115200) as ser:
    print("Waiting for Ready...")
    while ready == 0:
        line = ser.readline().strip()
        print("Received \"" + line + "\"")
        
        if (line == "Ready!"):
            ready = 1
        
    print("Beginning song...")
    total_time = 0

    i = 0
    for msg in midi_file:
        total_time += msg.time
        if (msg.type != "note_on" and msg.type != "note_off"): 
            continue
        track = msg_tracks[i][1]
        i += 1
        #print ("Got track: " + str(track))
        time.sleep(msg.time / time_scale)
        send_midi_message(ser, msg, track)

time.sleep(5)
print("Done!")

