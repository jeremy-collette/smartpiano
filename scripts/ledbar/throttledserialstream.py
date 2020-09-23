class ThrottledSerialStream:
    def __init__(self, serialStream):
        self.serialStream = serialStream
        self.canSend = 0

    def send_packet(self, data):
    	self._wait_for_ok()

        self.serialStream.send_packet(data)

    def read_line(self):
        line = self.serialStream.read_line().strip()
        return line

    def available_bytes(self):
        return self.serialStream.available_bytes()

    def _wait_for_ok(self):
    	while self.canSend == 0 or self.available_bytes() > 0:
    		print("Waiting for START")
    		print("Available bytes: " + str(self.available_bytes()))
    		line = self.read_line()
    		print("Received " + line)
    		if (line == "START"):
    			self.canSend = 1
    		elif (line == "STOP"):
    			self.canSend = 0
    			# Send ACK
    			self.serialStream.send_packet([0x1])