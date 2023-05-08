opciones_locales = {
    'a1': 'Conectando.... presione 1 para continuar',
    'a2': 'Presione 1 para crear RESORTES o 0 para JOYSTICK',
    'b1': 'Ingresa el número de vueltas del resorte',
    'b2': 'Ingresa la direccion: derecha"D", izquierda "I"',
    'b3': 'Ingresa el paso del resorte',
    'b4': 'Cuantos resortes desea crear',
    'b5': 'Por favor ingrese el diametro del material del resorte',
    'b6': 'Por favor ingrese las vueltas de apriete',
    'b7': 'Por favor ingrese las vueltas de aumento necesarias para eliminar retroceso',
    'd1': 'Si desea crear otro resorte marque uno, de lo contrario marque 0',
    'd2': 'Fin del trabajo, fue un gusto trabajar para ti',
    'c1': 'Presiones 1 para continuar con las repeticiones',
    'e1': 'Muliplique la velocidad: x1, x10, x100, x1000',
    'e2': '''Presione r para reajustar la velocidad y la nueva velocidad
    Presiones x para mover el eje de rotacion, 
    Presione y para avanzar y
    Presione d para cambiar de direccion''',
    'f1': 'por favor presione 1 para regresar la maquina a posicion inicial.',
    'g1': 'ingreso de datos incorrecto. Por favor reinicie',
 
}

claves_opciones = list(opciones_locales.keys())
valores_opciones = ''


def diccionario_variables(clavearduino):
    for clave in claves_opciones:
        if clave == clavearduino:
            valores_opciones = opciones_locales[clave]
            return valores_opciones











