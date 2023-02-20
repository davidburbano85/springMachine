import serial
import time


# ARDUINO
# def comunicar(loquesea):

#     arduino=serial.Serial('COM3', 9600)
#     time.sleep(2)
#     arduino.write(loquesea.encode())
#     arduino.close()


def comunicar(denuevoloquesea):

    arduino = serial.Serial('COM3', 9600)
    time.sleep(2)
    arduino.write(denuevoloquesea.encode())
    arduino.close()


def comunicar2(denuevoloquese):

    arduino = serial.Serial('COM3', 9600)
    time.sleep(2)
    arduino.write(denuevoloquese.encode())
    arduino.close()


def comunicar3(denuevoloquese):

    arduino = serial.Serial('COM3', 9600)
    time.sleep(2)
    arduino.write(denuevoloquese.encode())
    arduino.close()


def comunicar4(denuevoloquese):

    arduino = serial.Serial('COM3', 9600)
    time.sleep(2)
    arduino.write(denuevoloquese.encode())
    arduino.close()
