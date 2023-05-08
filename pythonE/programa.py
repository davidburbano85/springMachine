from tkinter import *
import tkinter as tk
import threading, serial
from variables import *
import variables as va

    #**********************ARDUINO*************************
     # ***************************************************
      # *************************************************
    
arduino= serial.Serial('COM3', 9600)
vieneIno=[]
arduinoPantalla=[]
diccionario=''

      #**********************TKINTER*************************
       # ***************************************************
        # *************************************************

ventana = tk.Tk()
ventana.title('Spring Machine CNC TT-110')
ventana.geometry('1400x650')

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

def mensajeaintro():
  global intro
  intro = tk.Label(segunda_caja, text="", justify='center', bg='black', fg='orangered', font='bold 13')
  intro.place(relheight=1, relwidth=1, relx=0, rely=0)
  if  vieneIno==[]:
      intro.config(text='''Te damos la bienvenida,
      gracias por adquirir nuestros equipos, somos TramarT CNC. 
      antes de  dar clic en SIGUIENTE para comenzar la comunicacion
      con tu maquina te sugerimos 
      leer las INSTRUCCIONES.''')
  else:
      intro.config(text=arduinoPantalla)

caja_botones = tk.Label(final_caja, bg='orangered').place(relheight=.48, relwidth=.498, relx=0.0, rely=0)

mensaje='''SPRING MACHINE'''
marca = tk.Label(final_caja, text=mensaje, justify='left', bg='orangered', font='bold 30')
marca.place(relheight=.48, relwidth=.498, relx=.505, rely=0)

mensaje = '''1ro CLICK EN INICIAR O SIGUIENTE
2do INTRODUZCA 1 EN LA CAJA GRIS
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

e_caja1 = tk.Entry(primer_caja, bg='gray62', fg='orangered', font='bold 15')
e_caja1.place(relheight=.10, relwidth=.85, relx=.08, rely=.45)

        # ***********************FUNCIONES ENVIO Y RECEPCION ***************
          #************************ DE DATOS A ARDUINO******************** 
            #**********************************************************

mensajeaintro()

def leeArduino():
    leerArduino=arduino.readline().decode().strip()
    vieneIno.append(leerArduino)
    e_caja1.focus_set()
    for clave in vieneIno:
        diccionario=diccionario_variables(clave)
        if diccionario:
            arduinoPantalla.append(diccionario)
        if len(arduinoPantalla)>1:
            arduinoPantalla.pop(0)
    mensajeaintro()

def escribeArduino(escritura):
     escritura=escritura     
     arduino.write(escritura.encode())

def respuestas():
        respuesta= e_caja1.get()
        r1=threading.Thread(target=escribeArduino, args=(respuesta, ))
        r1.start()
        e_caja1.delete(0, END)
        botones()

def cerrar():
   intro.config(text='')
   intro.destroy()
   arduino.close()   
   boton_caja2.place( relheight=.05, relwidth=.09, relx=0.093, rely=.52)

def reinicio():  
    arduino.open()  
    leeArduino()
    boton_caja2.place_forget()
    e_caja1.place(relheight=.10, relwidth=.85, relx=.08, rely=.45)
    
def botones(valor):
    arduino.write(valor.encode())
    print(valor)
    #e_caja1.place_forget()


        #********************************BOTONES******************************
          #*****************************************************************
           #***************************************************************


mensaje = '''Siguiente'''
boton_caja1 = tk.Button(primer_caja, text=mensaje, bg='black', fg='orangered',  font='30', command=leeArduino)
boton_caja1.place(  relheight=.14, relwidth=.24, relx=0.18, rely=.65)
e_caja1.bind("<Key-n>", lambda event:leeArduino())

mensaje = 'Eliminar Todo'
eliminar_datos = tk.Button(caja_botones, text=mensaje, command=cerrar, bg='black', fg='orangered', font='12')
eliminar_datos.place(relheight=.05, relwidth=.12, relx=0.24, rely=.52)

mensaje = '''ingresar
datos'''
ingresar = tk.Button(primer_caja, text=mensaje, bg='black', fg='orangered', font='12', command=respuestas)
ingresar.place( relheight=.14, relwidth=.31, relx=0.58, rely=.65)
e_caja1.bind("<Return>", lambda event:respuestas())


mensaje = '''reiniciar'''
boton_caja2 = tk.Button(caja_botones, text=mensaje, bg='black', fg='orangered', font='20', command=reinicio)

#     ////////////////BOTONES DE DIRECCION///////////////////////

boton_Rotar=tk.Button(caja_botones, text='Rotar', bg='black', fg='orangered',font='bold 12',  command=lambda:botones("x") )
boton_Rotar.place(relheight=.05, relwidth=.092, relx=.09, rely=.65)

boton_Avance=tk.Button(caja_botones, text='Avance', bg='black', fg='orangered',font='bold 12',  command=lambda:botones("y") )
boton_Avance.place(relheight=.05, relwidth=.12, relx=.24, rely=.65)

boton_Cambio=tk.Button(caja_botones, text='Cambio de giro', bg='black', fg='orangered',font='bold 12',  command=lambda:botones("d") )
boton_Cambio.place(relheight=.05, relwidth=.27, relx=.09, rely=.585)

#       ///////////TECLAS PARA EL CONTROL INALAMBRICO/////////////////////

e_caja1.bind("<Key-y>", lambda event:botones("y"))

e_caja1.bind("<Key-x>", lambda event:botones("x"))

e_caja1.bind("<Key-d>", lambda event:botones("d"))




ventana.mainloop()





