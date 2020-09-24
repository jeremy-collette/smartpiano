import time


class LedBar:
    def __init__(self, serial_stream, printer, num_leds):
        self.serial_stream = serial_stream
        self.send = 0
        self.printer = printer
        self.num_leds = num_leds

    def init(self):
        self._wait_for_message(b"\x42")  # 0x42 is sent when device is ready
        self.clear()
        time.sleep(5)

    def set_led(self, index, r, g, b, w):
        data = [0x32, index, r, g, b, w]

        self.serial_stream.send_packet(data)
        self.printer.printmsg("Wrote data: " + str(data))

    def update(self):
        self.printer.printmsg("Sending update request...")
        self.serial_stream.send_packet([0x93])
        self._wait_for_message(b"\x64")  # 0x64 is sent back after update is complete

    def _wait_for_message(self, message):
        self.printer.printmsg("Waiting for \"" + str(message) + "\"...")
        while True:
            data = str(self.serial_stream.read_line().strip())
            self.printer.printmsg("Received \"" + data + "\"")
            if data == str(message):
                print("Got message!")
                return

    def clear(self):
        for i in range(0, self.num_leds):
            self.set_led(i, 0, 0, 0, 0)
            if i % 10 == 0:
                self.update()
        self.update()
