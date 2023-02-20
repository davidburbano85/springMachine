from tkinter import *
import tkinter as tk
import arduino as ar


ventana = tk.Tk()
ventana.title('Spring Machine CNC TT-110')
ventana.geometry('800x400')
ventana.colormapwindows = 'red'


caja_principal = tk.Frame(ventana, bg='orangered')
caja_principal.pack(expand=True, fill='both')

caja_fondo_negro = tk.Frame(ventana, bg='black')
caja_fondo_negro.place(relwidth=.975, relheight=.975, relx=.015, rely=.015)

final_caja = tk.Frame(caja_fondo_negro, bg='',)
final_caja.place(relwidth=.984, relheight=.48, relx=.008, rely=.5, )
mensaje = '''
SUGERENCIAS:
* Siempre revisar los datos ingresados
* hacer mantenimiento preventivo a la maquina
'''
intro = tk.Label(final_caja, text=mensaje, justify='left', bg='orangered',
                 font='bold 13').place(relheight=.48, relwidth=.498, relx=0, rely=0)
caja_botones = tk.Label(final_caja, bg='orangered').place(
    relheight=.48, relwidth=.498, relx=0.502, rely=0)

mensaje = '''SPRING MACHINE'''
marca = tk.Label(final_caja, text=mensaje, justify='left', bg='orangered',
                 font='bold 20').place(relheight=.47, relwidth=1, relx=0, rely=0.5)

diseñada_por = tk.Label(caja_fondo_negro, bg='black', font='bold 12', fg='orangered',
                        text=' Copyright Designed and crafted by David Burbano, Tramart CNC-2023')
diseñada_por.place(relheight=.07, relwidth=1, relx=0, rely=.95)
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

    mensaje = """Por favor ingrese
    número de 
      vueltas """
    dato_X = tk.Label(primer_caja, text=mensaje,
                      justify='left', bg='orangered', font='bold 11')
    dato_X.place(relx=corX, rely=corY, relwidth=largo, relheight=alto)

    mensaje = """Por favor ingrese
           la direccion, en sentido 
         horario: 1 antiorario: 0 """
    dato_X_giro = tk.Label(primer_caja, text=mensaje,
                           bg='orangered', font='bold 11')
    dato_X_giro.place(relx=corX*17, rely=corY, relwidth=largo, relheight=alto)

    mensaje = """Por favor ingrese
    el paso del 
    resorte """
    dato_Y = tk.Label(segunda_caja, text=mensaje,
                      bg='orangered', font='bold 11')
    dato_Y.place(relx=corX, rely=corY, relwidth=largo, relheight=alto)

    # mensaje = """Por favor ingrese
    #        la direccion, en sentido 
    #       horario 1 y antiorario 0 """
    # dato_X = tk.Label(segunda_caja, text=mensaje,
    #                   justify='center', bg='orangered', font='bold 11')
    # dato_X.place(relx=corX*18, rely=corY, relwidth=largo, relheight=alto)

    mensaje = """Por favor ingrese
    distancia en Z """

    mensaje = """Por favor
    ingrese el radio """


def suma():  # esto solo es de ejemplo eliminar cuando ya este toda la programacion
    print('suma')


mensaje = '''Ingresa 
Datos'''  # para los botones


#                       *********INPUTS*********
e_caja1 = Entry(primer_caja, bg='black', fg='orangered', font='bold 15')
e_caja1.place(relheight=.10, relwidth=.25, relx=.12, rely=.45)


e_caja2 = tk.Entry(segunda_caja, bg='black', fg='orangered', font='bold 15')
e_caja2.place(relheight=.10, relwidth=.25, relx=.12, rely=.45)

e_caja3 = tk.Entry(caja_botones, bg='black', fg='orangered', font='bold 15')
e_caja3.place(relheight=.05, relwidth=.2, relx=.65, rely=.55)

e_caja4 = Entry(primer_caja, bg='black', fg='orangered', font='bold 15')
e_caja4.place(relheight=.10, relwidth=.25, relx=.58, rely=.45)

# e_caja5 = Entry(segunda_caja, bg='black', fg='orangered', font='bold 15')
# e_caja5.place(relheight=.10, relwidth=.25, relx=.58, rely=.45)

# ***********************FUNCIONES ENVIO DE DATOS A ARDUINO***************************

# ESTA ES LA ORIGINAL
# def save_data():#como es un evento toca colocarle tipo evento a la funcion
#         datos=e_caja2.get()
#         ar.comunicar(datos)


def save_data():
    datos = e_caja1.get()
    ar.comunicar(datos)


def save_data2():
    datos2 = e_caja2.get()
    ar.comunicar2(datos2)


def save_data3():
    datos3 = e_caja3.get()
    ar.comunicar3(datos3)


def save_data4():
    datos4 = e_caja4.get()
    ar.comunicar4(datos4)


def repeat_data():
    repeat = e_caja3.get()
    ar.cycles(repeat)


#                   ****************BOTONES***************
mensaje = '''ingresar
datos'''
boton_caja1 = tk.Button(primer_caja, text=mensaje, bg='black',
                        fg='orangered', font='12', command=save_data)
boton_caja1.place(relheight=.19, relwidth=.19, relx=0.15, rely=.65)

mensaje = '''ingresar
datos'''
boton_caja2 = tk.Button(segunda_caja, text=mensaje, bg='black',
                        fg='orangered', font='12', command=save_data2)
boton_caja2.place(relheight=.19, relwidth=.19, relx=0.15, rely=.65)
mensaje = '''ingresar
datos'''
boton_caja1_col2 = tk.Button(
    primer_caja, text=mensaje, bg='black', fg='orangered', font='12', command=save_data3)
boton_caja1_col2.place(relheight=.19, relwidth=.19, relx=.6, rely=.65)

# mensaje = '''ingresar
# datos'''
# boton_caja2_col2 = tk.Button(segunda_caja, text=mensaje,
#                              bg='black', fg='orangered', font='12', command=save_data4)
# boton_caja2_col2.place(relheight=.19, relwidth=.19, relx=.6, rely=.65)


mensaje = 'Repetir'
repeat_button = tk.Button(caja_botones, text=mensaje,
                          bg='green', fg='white', font='12', command=repeat_data)
repeat_button.place(relheight=.08, relwidth=.1, relx=0.65, rely=.63)
# aceptaR.bind('<Button-1>', save_data) #llama a las secuenvias de los eventos a atender

variablesfloat = tk.DoubleVar()  # estas son variables fltantes en tkinter

# print(datas2)
mensaje = 'Eliminar'
eliminar_datos = tk.Button(caja_botones, text=mensaje, command=suma, bg='red',
                           fg='white', font='12').place(relheight=.08, relwidth=.1, relx=.77, rely=.63)

ventana.mainloop()
