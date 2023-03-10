import serial
import time




# ARDUINO
# def comunicar(loquesea):

#     arduino=serial.Serial('COM3', 9600)
#     time.sleep(2)
#     arduino.write(loquesea.encode())
#     arduino.close()


def comunicarArduino(respuesta):   
     arduino= serial.Serial('COM3', 9600)
     respuestaDeTKinter=respuesta  
     print(respuestaDeTKinter)   

     for i in range(6) :                  
          leerArduino=arduino.readline().decode()  
          arduino.write(respuestaDeTKinter.encode())
          print(leerArduino)
     arduino.close()  

#     leerArduino=arduino.readline().decode().strip()
#     print(leerArduino)
#     responderArduino=input(respuesta)
#     arduino.write(responderArduino.encode())

#     leerArduino=arduino.readline().decode().strip()
#     print(leerArduino)
#     responderArduino=input(respuesta )
#     arduino.write(responderArduino.encode())

#     leerArduino=arduino.readline().decode().strip()
#     print(leerArduino)
#     responderArduino=input(respuesta )
#     arduino.write(responderArduino.encode())

#     leerArduino=arduino.readline().decode().strip()
#     print(leerArduino)


#     leerArduino=arduino.readline().decode().strip()
#     print(leerArduino)

#     leerArduino=arduino.readline().decode().strip()
#     print(leerArduino)
#     responderArduino=input(respuesta )
#     arduino.write(responderArduino.encode())

#     leerArduino=arduino.readline().decode().strip()
#     print(leerArduino)
 
     # arduino.close()




    

