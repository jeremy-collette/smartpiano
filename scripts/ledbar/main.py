import serial, time, sys
from mido import MidiFile
from datetime import datetime 
from serialstream import SerialStream
from throttledserialstream import ThrottledSerialStream
from ledbar import LedBar
from printer import Printer

time_scale = 1
file_name = "../mgs-jez.mid"
midi_file = MidiFile(file_name)
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
    printer = Printer()
    serialStream = SerialStream(ser, printer)
    ledBar = LedBar(serialStream, printer)
    ledBar.init()

    print("Beginning song...")

    i = 0
    last_update_time = time.time()
    delay_start = time.time()
    for msg in midi_file:
        if (msg.type != "note_on" and msg.type != "note_off"): 
            continue

        delay = time.time() - delay_start
        time_to_sleep = msg.time - delay
        if (time_to_sleep > 0):
            time.sleep(msg.time / time_scale)
        
        delay_start = time.time()

        track = msg_tracks[i][1]
        i += 1
        if (msg.type == "note_on" or msg.type == "note_off"):
            #if (track == 1): continue           

            index = (msg.note - 30) * 2   
            is_on = int(msg.type == "note_on" and msg.velocity != 0)
            r = 0
            g = 0
            b = 0
            w = 0

            if (is_on):
                r = 255 if track % 2 == 0 else 0
                g = 0
                b = 0 if track % 2 == 0 else 255
                w = 0

            ledBar.set_led(index, (r, g, b, w))
            ledBar.set_led(index + 1, (r, g, b, w))
            ledBar.update()
       
        time_since_update = time.time() - last_update_time
        print(time_since_update)
        if (time_since_update >= 0.25):
            ledBar.update()
            last_update_time = time.time()

    #for on in reversed(range(0, 2)):
    #    for i in range(0, 144):
    #        printer.printmsg("Turning on " + str(i))
    #        ledBar.set_led(i, (0, on * 255, 0, 0))
    #        #time.sleep(0.01)
    #        ledBar.update()

    #while True:
    #    index = int(input("Enter LED index: "))
    #    r = int(input("R: "))
    #    g = int(input("G: "))
    #    b = int(input("B: "))
    #    w = int(input("W: "))
    #
    #    ledBar.set_led(index, (r, g, b, w))