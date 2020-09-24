from datetime import datetime


class Printer:
    def printmsg(self, msg):
        print("[" + str(datetime.now().time()) + "] " + msg)
