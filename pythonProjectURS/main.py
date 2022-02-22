from datetime import datetime
import serial

ser = serial.Serial()
ser.port = "/dev/ttyUSB0"
ser.baudrate = 4800
ser.bytesize = serial.SEVENBITS
ser.parity = serial.PARITY_ODD
ser.stopbits = serial.STOPBITS_TWO

ser.timeout = 5

ser.xonxoff = False
ser.rtscts = False
ser.dsrdtr = False

cardArray = ["E45A681EC8", "8234547391", "804581C387", "91AA4E7306", "5302F3C361", "9C3B527386", "B7324373B5",
             "B7324373B5"]
activeCards = [-1]*8

try:
    ser.open()

except Exception as e:
    print("error open serial port: " + str(e))
    exit()

if ser.isOpen():
    while True:
        read_data = ser.read(100)
        serialOut = read_data.decode('utf-8')
        print(serialOut)
        if serialOut in cardArray:
            now = datetime.now()
            currTime = now.strftime("%H:%M:%S")
            print("Card detected!")
            index = cardArray.index(serialOut)

            activeCards[index] *= -1

            if activeCards[index] == 1:
                print("Card with id: " + serialOut + " entered at " + currTime)
            else:
                print("Card with id: " + serialOut + " exited at " + currTime)
        elif not serialOut:
            print("No card detected!")
        else:
            print("Error while reading card!")

else:
    print("Can not open serial port")
