from tkinter import *
import tkinter as tk
import threading, serial


    #**********************ARDUINO*************************
     # ***************************************************
      # *************************************************
    
arduino= serial.Serial('COM3', 9600)

      #**********************TKINTER*************************
       # ***************************************************
        # *************************************************


ventana = tk.Tk()
ventana.title('Spring Machine CNC TT-110')
ventana.geometry('900x600')
#ventana.colormapwindows = 'black'
#           *********las cajas van a de izquierda a derecha******


caja_principal = tk.Frame(ventana, bg='orangered')
caja_principal.pack(expand=True, fill='both')

caja_fondo_negro = tk.Frame(ventana, bg='black')
caja_fondo_negro.place(relwidth=.975, relheight=.975, relx=.015, rely=.015)

primer_caja = tk.Frame(caja_fondo_negro, bg='orangered')
primer_caja.place(relwidth=.39, relheight=.48, relx=.008, rely=.010, )

segunda_caja = tk.Frame(caja_fondo_negro, bg='orangered')
segunda_caja.place(relwidth=.59, relheight=.48, relx=.402, rely=.010)


final_caja = tk.Frame(caja_fondo_negro, bg='',)
final_caja.place(relwidth=.984, relheight=.48, relx=.008, rely=.5, )



        #*********************************LABELS*************************
         #*************************************************************
          #**********************************************************



intro = tk.Label(segunda_caja, text="", justify='left', bg='black', fg='orangered', font='bold 13')
intro.place(relheight=1, relwidth=1, relx=0, rely=0)

caja_botones = tk.Label(final_caja, bg='orangered').place(relheight=.48, relwidth=.498, relx=0.0, rely=0)


mensaje='''SPRING MACHINE'''
marca = tk.Label(final_caja, text=mensaje, justify='left', bg='orangered', font='bold 30')
marca.place(relheight=.48, relwidth=.498, relx=.505, rely=0)

mensaje = '''1ro CLICK EN INICIAR O SIGUIENTE
2do INTRODUZCA 1 EN LA CAJA BLANCA
3ro CLICK EN INGRESAR DATOS
4to CLICK EN INICIAR O SIGUIENTE'''

info = tk.Label(final_caja, text=mensaje, justify='left', bg='orangered', font='bold 10')
info.place(relheight=.5, relwidth=.498, relx=0, rely=0.5)


mensaje = '''5to EN LA CAJA NEGRA APARECEN 
  NUEVAS INSTRUCCIONES LEER Y APLICAR
6to AHORA EN ADELANTE CLICK EN INGRESAR 
  DATOS Y LUEGO EN SIGUIENTE
'''
info2 = tk.Label(final_caja, text=mensaje, justify='left', bg='orangered', font='bold 10')
info2.place(relheight=.5, relwidth=.498, relx=.505, rely=0.5)

diseñada_por = tk.Label(caja_fondo_negro, bg='black', font='bold 12', fg='orangered',
                        text=' Copyright Designed and crafted by David Burbano, Tramart CNC-2023')
diseñada_por.place(relheight=.06, relwidth=1, relx=0, rely=.95)


#       ***************coordenada y medidas*************


class Coord:
    def __init__(self, corX, corY, alto, largo):
        self.corX = corX
        self.corY = corY
        self.ancho = alto
        self.largo = largo
    corX = .025
    corY = .025
    alto = .26
    largo = .47

#                       *********INPUTS*********

e_caja1 = tk.Entry(primer_caja, bg='white', fg='orangered', font='bold 15')
e_caja1.place(relheight=.10, relwidth=.55, relx=.18, rely=.45)



        # ***********************FUNCIONES ENVIO Y RECEPCION ***************
          #************************ DE DATOS A ARDUINO******************** 
            #**********************************************************

vieneIno=[]

def leeArduino():
    leerArduino=arduino.readline().decode()
    print(leerArduino)
    vieneIno.append(leerArduino)
    mensajeaintro()

def escribeArduino(escritura):
     escritura=escritura     
     arduino.write(escritura.encode())

def respuestas():
        respuesta= e_caja1.get()
        e_caja1.delete(0, END)
        r1=threading.Thread(target=escribeArduino, args=(respuesta, ))
        r1.start()

def mensajeaintro():
     intro.config(text=vieneIno)

def cerrar():
   intro.config(text='')
   arduino.close()   
   arduino.readline().decode().strip()
   reset=111
   arduino.write(reset.encode())

def reinicio():  
    arduino.open()  



        #********************************BOTONES******************************
          #*****************************************************************
           #***************************************************************


mensaje = '''Iniciar 
o siguiente'''
boton_caja1 = tk.Button(caja_botones, text=mensaje, bg='green', fg='black',  font='30', command=leeArduino)
boton_caja1.place(relheight=.12, relwidth=.19, relx=0.05, rely=.55)

mensaje = 'Eliminar'
eliminar_datos = tk.Button(caja_botones, text=mensaje, command=cerrar, bg='red', fg='white', font='12')
eliminar_datos.place(relheight=.12, relwidth=.2, relx=0.28, rely=.55)

mensaje = '''ingresar
datos'''
boton_caja1 = tk.Button(primer_caja, text=mensaje, bg='black', fg='orangered', font='12', command=respuestas)
boton_caja1.place(relheight=.29, relwidth=.29, relx=0.18, rely=.65)

mensaje = '''reiniciar'''
boton_caja1 = tk.Button(primer_caja, text=mensaje, bg='red', fg='black', font='20', command=reinicio)
boton_caja1.place(relheight=.19, relwidth=.19, relx=0.78, rely=.75)








ventana.mainloop()





