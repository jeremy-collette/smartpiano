import time


class SmartPianoClient:
    def __init__(self, midi_file, auto_led_bar, time_scale, printer, left_hand_color, right_hand_color):
        self.last_update_time = 0
        self.midi_file = midi_file
        self.auto_led_bar = auto_led_bar
        self.time_scale = time_scale
        self.printer = printer
        self.left_hand_color = left_hand_color
        self.right_hand_color = right_hand_color

    def play_song(self):
        self.printer.printmsg("Beginning song...")

        delay_start = time.time()
        while not self.midi_file.is_eof():
            msg = self.midi_file.get_next_note()
            # Get the amount of time we've already been delayed and
            # subtract it from the amount we will wait to play note
            time_delayed = time.time() - delay_start
            self._delay(msg.time - time_delayed)
            delay_start = time.time()

            self._play_midi_note(msg)
            self.auto_led_bar.tick()

        self.auto_led_bar.update()
        self.printer.printmsg("Done!")

    def _play_midi_note(self, msg):
        index = (msg.note - 30) * 2

        if msg.track == 1:
            color = self.left_hand_color
        else:
            color = self.right_hand_color

        r = g = b = w = 0
        if msg.on:
            r = color[0]
            g = color[1]
            b = color[2]
            w = color[3]

        self.auto_led_bar.set_led(index, r, g, b, w)
        self.auto_led_bar.set_led(index + 1, r, g, b, w)

    # This delay function will delay incrementally while tick'ing the LedBar
    def _delay(self, duration):
        updated = False
        while duration > 0:
            to_delay = 0.1
            if duration < 0.1:
                to_delay = duration

            # Even though we only want to delay some small amount (e.g. 0.1),
            # the call to auto_led_bar.tick() will cause some additional delay
            # due to serial communications. So let's see how long the delay
            # really took and subtract it from the total delay time (duration).
            #
            # TODO: can we call auto_led_bar.tick() first and then call time.sleep
            # with the remaining time we want to delay for?
            delay_start = time.time()
            time.sleep(to_delay / self.time_scale)
            self.auto_led_bar.tick()
            time_delayed = time.time() - delay_start
            duration -= time_delayed
