from datetime import datetime

class SerialStream:
    def __init__(self, serial):
        self.serial = serial

    def send_packet(self, data):
        print(str(datetime.now().time()) + " Sending packet...")
        packet = bytearray()
        for d in data:
            packet.append(d)
        self.serial.write(packet)
        print(str(datetime.now().time()) + " Sent!")

    def read_line(self):
        line = self.serial.readline().strip()
        return line

    def available_bytes(self):
        return self.serial.in_waiting