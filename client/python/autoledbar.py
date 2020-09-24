import time


class AutoLedBar:
    def __init__(self, led_bar, auto_update_span, printer):
        self.led_bar = led_bar
        self.auto_update_span = auto_update_span
        self.printer = printer
        self.last_update_time = 0

    def tick(self):
        if time.time() - self.last_update_time > self.auto_update_span:
            self.printer.printmsg("AutoLedBar update!")
            self.last_update_time = time.time()
            self.led_bar.update()

    def init(self):
        self.led_bar.init()

    def set_led(self, index, r, g, b, w):
        self.led_bar.set_led(index, r, g, b, w)
        self.tick()

    def update(self):
        self.led_bar.update()

    def clear(self):
        self.led_bar.clear()
