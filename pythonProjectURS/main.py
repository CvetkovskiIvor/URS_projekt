import serial, time

ser = serial.Serial()
ser.port = "/dev/ttyUSB0"
ser.baudrate = 4800
ser.bytesize = serial.SIXBITS
ser.parity = serial.PARITY_ODD
ser.stopbits = serial.STOPBITS_TWO

ser.timeout = 5

ser.xonxoff = False
ser.rtscts = False
ser.dsrdtr = False

try:
    ser.open()

except Exception as e:
    print ("error open serial port: " + str(e))
    exit()

if ser.isOpen():
    while True:
        read_data = ser.read(6)
        print("data recieved: " + read_data.decode('utf-8'))
else:
    print("Can not open serial port")