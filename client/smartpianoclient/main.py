#!/usr/bin/python

import sys
from smartpianofactory import SmartPianoFactory

if __name__ == "__main__":
    if len(sys.argv) == 0:
        print("python main.py <MidiFileName>")
        sys.exit(1)

    #filename = "../beethoven_ode_to_joy_tracks.mid"
    filename = "../mgs-jez.mid"
    #filename = "../Sweden_Minecraft.mid"
    #filename = "../happy_birthday_tracks.mid"
    
    smart_piano_factory = SmartPianoFactory()
    smart_piano = smart_piano_factory.create_smart_piano_client(filename)
    smart_piano.play_song()