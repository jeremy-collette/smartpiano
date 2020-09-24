import time

class LedBarPiano:
    def __init__(self, midifile, ledBar, time_scale):
        self.last_update_time = 0
        self.midifile = midifile
        self.ledBar = ledBar
        self.time_scale = time_scale
        
    def play(self):  
        print("Beginning song...")

        delay_start = time.time()
        while not self.midifile.is_eof():
            msg =  self.midifile.get_next_note()
            delay = time.time() - delay_start
            self._delay(msg.time - delay)
            delay_start = time.time()

            self._play_midi_note(msg)
            self._update_if_needed()

        self.ledBar.update()
        print("Done!")

    def _play_midi_note(self, msg):
        index = (msg.note - 30) * 2   
        r = g = b = w = 0

        if (msg.on):
            r = 255 if msg.track % 2 == 0 else 0
            b = 0 if msg.track % 2 == 0 else 255

        self.ledBar.set_led(index, (r, g, b, w))
        self.ledBar.set_led(index + 1, (r, g, b, w))        

    # This delay function will delay incrementally while updating the LedBar
    def _delay(self, duration):
        updated = False
        while (duration > 0):
            # We already updated during this delay, just wait the rest and return
            if (updated == True):                
                time.sleep(duration / self.time_scale)
                return

            to_delay = 0.1
            if (duration < 0.1):
                to_delay = duration

            time.sleep(to_delay / self.time_scale)            
            updated = self._update_if_needed()
            duration -= to_delay

    def _update_if_needed(self):
        if (time.time() - self.last_update_time > 0.1):
            self.last_update_time = time.time()
            self.ledBar.update()
            return True

