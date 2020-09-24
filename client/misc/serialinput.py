import serial
import json

with serial.Serial("/dev/ttyACM0", 115200) as ser:
    while True:
        key_inpt = raw_input("Enter key (-1 to quit): ")
        if (key_inpt == "-1"): break        
        on_inpt = raw_input("On (y/n): ")
        command = { 
            "key": key_inpt, 
            "on": str(int(on_inpt == "y")) 
        }
        data = json.dumps(command)        
        print(data)
        data += '\n'
        ser.write(data)


