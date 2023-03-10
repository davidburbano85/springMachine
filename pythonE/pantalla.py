from tkinter import *
import tkinter as tk
import arduino as ar
import threading



ventana = tk.Tk()
ventana.title('Spring Machine CNC TT-110')
ventana.geometry('700x600')
ventana.colormapwindows = 'red'


caja_principal = tk.Frame(ventana, bg='orangered')
caja_principal.pack(expand=True, fill='both')

caja_fondo_negro = tk.Frame(ventana, bg='black')
caja_fondo_negro.place(relwidth=.975, relheight=.975, relx=.015, rely=.015)

final_caja = tk.Frame(caja_fondo_negro, bg='',)
final_caja.place(relwidth=.984, relheight=.48, relx=.008, rely=.5, )


# mensaje = '''
# SUGERENCIAS:
# * Siempre revisar los datos ingresados
# * hacer mantenimiento preventivo a la maquina
# '''
arrayarduino=[]
datosar= ar.comunicarArduino()

def mensajesdeA():
    arrayarduino.append(datosar)
    print('esto es el array', arrayarduino)

    return(datosar)

mensajesdeA()

def texto():
    mensajes=arrayarduino
    intro.config(text=mensajes)



        
 
intro = tk.Label(final_caja, text="", justify='left', bg='orangered', font='bold 13')
intro.place(relheight=.48, relwidth=.498, relx=0, rely=0)
texto()
caja_botones = tk.Label(final_caja, bg='orangered').place(
    relheight=.48, relwidth=.498, relx=0.502, rely=0)
  

mensaje = '''SPRING MACHINE'''
marca = tk.Label(final_caja, text=mensaje, justify='left', bg='orangered',
                 font='bold 20').place(relheight=.47, relwidth=1, relx=0, rely=0.5)

diseñada_por = tk.Label(caja_fondo_negro, bg='black', font='bold 12', fg='orangered',
                        text=' Copyright Designed and crafted by David Burbano, Tramart CNC-2023')
diseñada_por.place(relheight=.06, relwidth=1, relx=0, rely=.95)
#           *********las cajas van a de izquierda a derecha******

primer_caja = tk.Frame(caja_fondo_negro, bg='orangered')
primer_caja.place(relwidth=.49, relheight=.48, relx=.008, rely=.010, )

segunda_caja = tk.Frame(caja_fondo_negro, bg='orangered')
segunda_caja.place(relwidth=.49, relheight=.48, relx=.502, rely=.010)

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


#                           **********LABELS*********

    # mensaje = """Por favor ingrese
    # número de 
    #   vueltas """
    # dato_X = tk.Label(primer_caja, text=mensaje,
    #                   justify='left', bg='orangered', font='bold 11')
    # dato_X.place(relx=corX, rely=corY, relwidth=largo, relheight=alto)

    # mensaje = """Por favor ingrese
    #        la direccion, para la 
    #      derecha: D izquierda: I """
    # dato_X_giro = tk.Label(primer_caja, text=mensaje,
    #                        bg='orangered', font='bold 11')
    # dato_X_giro.place(relx=corX*17, rely=corY, relwidth=largo, relheight=alto)

    # mensaje = """Por favor ingrese
    # el paso del 
    # resorte """
    # dato_Y = tk.Label(segunda_caja, text=mensaje,
    #                   bg='orangered', font='bold 11')
    # dato_Y.place(relx=corX, rely=corY, relwidth=largo, relheight=alto)

    # # mensaje = """Por favor ingrese
    # #        la direccion, en sentido 
    # #       horario 1 y antiorario 0 """
    # # dato_X = tk.Label(segunda_caja, text=mensaje,
    # #                   justify='center', bg='orangered', font='bold 11')
    # # dato_X.place(relx=corX*18, rely=corY, relwidth=largo, relheight=alto)

    # mensaje = """Por favor ingrese
    # distancia en Z """

    # mensaje = """Por favor
    # ingrese el radio """




mensaje = '''Ingresa 
Datos'''  # para los botones


#                       *********INPUTS*********
e_caja1 = tk.Entry(primer_caja, bg='black', fg='orangered', font='bold 15')
e_caja1.place(relheight=.10, relwidth=.55, relx=.25, rely=.45)


# e_caja2 = tk.Entry(segunda_caja, bg='black', fg='orangered', font='bold 15')
# e_caja2.place(relheight=.10, relwidth=.25, relx=.12, rely=.45)

# e_caja3 = tk.Entry(caja_botones, bg='black', fg='orangered', font='bold 15')
# e_caja3.place(relheight=.05, relwidth=.2, relx=.65, rely=.55)

# e_caja4 = tk.Entry(primer_caja, bg='black', fg='orangered', font='bold 15')
# e_caja4.place(relheight=.10, relwidth=.25, relx=.58, rely=.45)

# e_caja5 = tk.Entry(segunda_caja, bg='black', fg='orangered', font='bold 15')
# e_caja5.place(relheight=.10, relwidth=.25, relx=.58, rely=.45)




# ***********************FUNCIONES ENVIO DE DATOS A ARDUINO***************************
#       ************************************************************************


# ESTA ES LA ORIGINAL
# def save_data():#como es un evento toca colocarle tipo evento a la funcion
#         datos=e_caja2.get()
#         ar.comunicar(datos)

iniciar="0"# comienza la variable asi para que no inicie el programa

def inicio():##funcion de inicio
    iniciar="1" #este es el valor que cambio de 0 a 1
    return (iniciar)


def respuestas():
        respuesta= e_caja1.get()
        e_caja1.delete(0, END)
        r1=threading.Thread(target=comunicarArduino, args=(respuesta, ))
        r1.start()
        



def comunicarArduino(recibiendo):
     recibiendo=recibiendo
     ar.comunicarArduino(recibiendo)



# def respuesta1():    
#     respuesta1 = e_caja1.get()    #se guarda el valor de la caja 1
#     e_caja1.delete(0, END) #despues de guardado el valor se borra el contenido
#    # time.sleep(1)# le puse esto para que este acorde con las preguntas
#     ar.respuestauno(respuesta1)


# def respuesta2():
#     respuesta2= e_caja2.get()# este es el otro valor guardado 
#   #  time.sleep(1)
#     ar.respuestados(respuesta2)


# def respuesta3():    
#     respuesta3= e_caja3.get()
#     e_caja3.delete(0,END)
#   #  time.sleep(1)
#     ar.respuestatres(respuesta3)


# def respuesta4():
#     respuesta4= e_caja4.get()
#     e_caja4.delete(0,END)
#  #   time.sleep(1)
#     ar.respuestacuatro(respuesta4)
    

#     #aqui se envian todos los valores guardados a la funcion 
#     #comunicararduino

# def confirmar():
#     confirma=start()

 

#                   ****************BOTONES***************

mensaje = '''Iniciar'''
boton_caja1 = tk.Button(caja_botones, text=mensaje, bg='black', fg='orangered',  font='20', command='')
boton_caja1.place(relheight=.19, relwidth=.12, relx=0.51, rely=.52)



mensaje = '''ingresar
datos'''
boton_caja1 = tk.Button(primer_caja, text=mensaje, bg='black',
                        fg='orangered', font='12', command=respuestas)
boton_caja1.place(relheight=.19, relwidth=.19, relx=0.15, rely=.65)

# mensaje = '''ingresar
# datos'''
# boton_caja2 = tk.Button(segunda_caja, text=mensaje, bg='black',
#                         fg='orangered', font='12', command=respuesta2)
# boton_caja2.place(relheight=.19, relwidth=.19, relx=0.15, rely=.65)
# mensaje = '''ingresar
# datos'''
# boton_caja1_col2 = tk.Button(primer_caja, text=mensaje, bg='black', fg='orangered', font='12', command=respuesta3)
# boton_caja1_col2.place(relheight=.19, relwidth=.19, relx=.6, rely=.65)

# mensaje = '''confirmar 
# datos'''
# boton_caja2_col2 = tk.Button(segunda_caja, text=mensaje,
#                               bg='green', fg='white', font='16', command=respuesta4)
# boton_caja2_col2.place(relheight=.19, relwidth=.19, relx=.6, rely=.65)


# mensaje = 'Repetir'
# repeat_button = tk.Button(caja_botones, text=mensaje,
#                           bg='green', fg='white', font='12', command="repeat_data")
# repeat_button.place(relheight=.08, relwidth=.1, relx=0.65, rely=.63)
# # aceptaR.bind('<Button-1>', save_data) #llama a las secuenvias de los eventos a atender

#variablesfloat = tk.DoubleVar()  # estas son variables fltantes en tkinter

# print(datas2)
mensaje = 'Eliminar'
eliminar_datos = tk.Button(caja_botones, text=mensaje, command='', bg='red', 
                           fg='white', font='12').place(relheight=.08, relwidth=.1, relx=.77, rely=.63)

ventana.mainloop()
