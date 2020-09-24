import time

class LedBarPiano:
    def __init__(self, midi_file, auto_led_bar, time_scale, printer, left_hand_color, right_hand_color):
        self.last_update_time = 0
        self.midi_file = midi_file
        self.auto_led_bar = auto_led_bar
        self.time_scale = time_scale
        self.printer = printer
        self.left_hand_color = left_hand_color
        self.right_hand_color = right_hand_color
        
    def play(self):
        self.printer.printmsg("Beginning song...")

        delay_start = time.time()
        while not self.midi_file.is_eof():
            msg =  self.midi_file.get_next_note()
            delay = time.time() - delay_start
            self._delay(msg.time - delay)
            delay_start = time.time()

            self._play_midi_note(msg)
            self.auto_led_bar.tick()

        self.auto_led_bar.update()
        self.printer.printmsg("Done!")

    def _play_midi_note(self, msg):
        index = (msg.note - 30) * 2

        if (msg.track == 1):
            color = self.left_hand_color
        else:
            color = self.right_hand_color

        r = g = b = w = 0
        if (msg.on):
            r = color[0]
            g = color[1]
            b = color[2]
            w = color[3]

        self.auto_led_bar.set_led(index, r, g, b, w)
        self.auto_led_bar.set_led(index + 1, r, g, b, w)

    # This delay function will delay incrementally while tick'ing the LedBar
    def _delay(self, duration):
        updated = False
        while (duration > 0):
            to_delay = 0.1
            if (duration < 0.1):
                to_delay = duration

            time.sleep(to_delay / self.time_scale)            
            self.auto_led_bar.tick()
            duration -= to_delay


