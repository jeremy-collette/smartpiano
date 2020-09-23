class LedBar:
    def __init__(self, serialStream):
        self.serialStream = serialStream
        self.send = 0

    def set_led(self, index, color):      
        data = [0x32, index]
        for pixel in color:
            data.append(pixel)

        self.serialStream.send_packet(data)
        print("Wrote data: " + str(data))

    def update(self):
        print ("Sending update request...")
        self.serialStream.send_packet([0x1])

        print ("Waiting for ACK...")
        while True:
            data = self.serialStream.read_line().strip()
            print ("Received " + data)
            if (data == "OK"):
                return



