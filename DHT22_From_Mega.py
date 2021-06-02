import serial, string, time, os

FileName = '/home/pi/testi.csv'

def printTemps(strIn3):
    meas = strIn3.split(",")
    try:
        last = meas[16]
        last = last[0:5] #remove /r/n
#         print(meas)
        print("TimeStamp: " + meas[0])
        print("Sensor 1: Temp=" + meas[1] + "*C  Humidity=" + meas[2] + "%")
        print("Sensor 2: Temp=" + meas[3] + "*C  Humidity=" + meas[4] + "%")
        print("Sensor 3: Temp=" + meas[5] + "*C  Humidity=" + meas[6] + "%")
        print("Sensor 4: Temp=" + meas[7] + "*C  Humidity=" + meas[8] + "%")
        print("Sensor 5: Temp=" + meas[9] + "*C  Humidity=" + meas[10] + "%")
        print("Sensor 6: Temp=" + meas[11] + "*C  Humidity=" + meas[12] + "%")
        print("Sensor 7: Temp=" + meas[13] + "*C  Humidity=" + meas[14] + "%")
        print("Sensor 8: Temp=" + meas[15] + "*C  Humidity=" + last + "%")
    except:
        print('No measurements received')
        pass
    
def replaceTS(strIn2,LL):
    returnString = "," #initialize string with separating commas
    measvalues = strIn2.split(",")
    savedvalues = LL.split(",")
    ts = int(measvalues[0]) + int(savedvalues[0]) #add first timestamp to last saved value timestamp
    measvalues[0] = str(ts)
    return (returnString.join(measvalues))
    
#try ttyACM0 and ttyACM1 for usb serial device
try:    
    ser = serial.Serial('/dev/ttyACM0', 9600, 8, 'N', 1, timeout=1)
    ser.flushInput()
    print(ser.name) #which porti is being used

except:
    pass
try:
    ser = serial.Serial('/dev/ttyACM1', 9600, 8, 'N', 1, timeout=1)
    ser.flushInput()
    print(ser.name) #which porti is being used
    
except:
    pass

#open csv file for data logging and create headers for the columns
try:
    f = open(FileName, 'a+')
    if os.stat(FileName).st_size == 0:
        f.write('TimeStamps,Temperature_1,Humidity_1,\
Temperature_2,Humidity_2,\
Temperature_3,Humidity_3,\
Temperature_4,Humidity_4,\
Temperature_5,Humidity_5,\
Temperature_6,Humidity_6,\
Temperature_7,Humidity_7,\
Temperature_8,Humidity_8\r\n')
        f.close()
        LastLine = 0; #no last line to use
        print('File created with column names')
    else:
        f = open(FileName, 'r')
        measLines = f.readlines() #all lines in file
        LastLine = measLines[-1] #last line written
        f.close()
except:
    pass

print("Press Ctrl + c to exit measurement loop")


try:
    while True:
        ser.write('a'.encode('utf-8')) #char a starts the measurement loop on mega
        strIn = ser.readline().decode('utf-8')
        if strIn:
#             print(strIn)
            try:
                if isinstance(LastLine, str):
                    strIn = replaceTS(strIn,LastLine)
                    print(strIn)
                     
                f = open(FileName, 'a+')
                f.write(strIn)
                printTemps(strIn)
            finally:
                f.close()
                
except KeyboardInterrupt:
    ser.write('b'.encode('utf-8')) #anything but char a stops loop and timestamps will reset on next char a on mega
    print('Exiting')
    pass
