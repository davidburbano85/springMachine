#define dirRot 3
#define pulRot 2

#define pulAv 4
#define dirAv 5
#define ena 7
#define finalCarrera 8
int estado = 0;
#define iniciocarrera 11
int estadoInicio = 0;

//ESTAS SON PARA LA ESTRUCTURA struct Movimientos
long valorFor = 0;
long valorEje = 0;

char claveFor = "";
char claveEje = "";

//ESTO ES COMO UN DICCIONARIO
struct Movimientos {
  char claveEje = "";
  long valorEje = 0;
  char dir = "";
};

int cantidadMovimientos = 2;

Movimientos* movimientos = new Movimientos[cantidadMovimientos];


unsigned long intervalPulRot = 0;  // 375en microsegundos
unsigned long intervaloPulAv = 0;  // 250  En microsegunndos
float newintervaloPulAv = 0;

int pasosPorRevPulRot = 800;
int pasosPorRevPulAv = 800;
unsigned int estadoDelProceso = 0;
int repetir = 0;

//--------DATOS USUARIO---------
float nvR = 0;
float nvAv = 0;
char dir1 = "";
float diametroMaterial = 0;
float vueltasCierre = 0;
int aumento = 0;
float vueltasFinalX = 0;
float vueltasAvance = 0;
float avancefinal = 0;

//-------------------------------


unsigned long vueltasDeseadasPulRot = 0;  // pasosPorRevPulRot * nvR;
float vueltasDeseadasPulAv = 0;           // pasosPorRevPulAv * nvAv;

char dir = "";



void setup() {
  pinMode(finalCarrera, INPUT);
  pinMode(13, OUTPUT);
  pinMode(iniciocarrera, INPUT);


  Serial.begin(9600);
  pinMode(pulRot, OUTPUT);
  pinMode(dirRot, OUTPUT);


  pinMode(pulAv, OUTPUT);
  pinMode(dirAv, OUTPUT);
  pinMode(ena, OUTPUT);
}


void loop() {

  estado = digitalRead(finalCarrera);
  if (estado == 0) {
    // digitalWrite(13, HIGH);

    switch (estadoDelProceso) {
      case 0:
        iniciar();
        break;

      case 1:
        cargarDatosDesdeSerial();
        estadoDelProceso = nvAv > 0 && nvR > 0 && dir1 != "" ? 2 : 1;
        //validar datos o si no mandar respuesta
        //Serial.print(String(estadoDelProceso) + " esto es el 1");
        break;

      case 2:
        realizarCalculos();
        estadoDelProceso = 3;
        break;

      case 3:
        calculosVueltasInicioFin();
        estadoDelProceso = 4;
        break;

      case 4:
        encenderMotores();
        estadoDelProceso = 5;
        break;

      case 5:
        calculosVueltasInicioFin();
        estadoDelProceso = 6;
        break;

      case 6:
        delay(500);
        desajusteResorte();
        estadoDelProceso = 7;
        break;

      case 7:
        regresoAvance();
        estadoDelProceso = 8;

        break;

      case 8:
        repiteResorte();
        //estadoDelProceso = 9;
        break;

      case 9:
        volverACero();
        break;
      case 10:
        joystick();
        estadoDelProceso = 11;
        break;
      case 11:
        ejecutarJoystick();
    }


  } else {
    estadoDelProceso = 0;
    digitalWrite(pulAv, LOW);
    digitalWrite(pulRot, LOW);
    // digitalWrite(13, LOW);
    Serial.println("g1");
  }
}

void iniciar() {
  unsigned int recibir;

  Serial.println("a1");
  while (Serial.available() <= 0) {}
  recibir = Serial.parseInt();
  if (recibir == 1) {

    Serial.println("a2");
    while (Serial.available() <= 0) {}
    recibir = Serial.parseInt();
    if (recibir == 1) {
      estadoDelProceso = 1;
    } else if (recibir == 0) {
      estadoDelProceso = 10;
    } else {
      estadoDelProceso = 0;
    }
  } else {
    estadoDelProceso = 0;
  }
}

void cargarDatosDesdeSerial() {
  //DATOS DE EL MATARIAL
  Serial.println("b5");
  while (Serial.available() <= 0) {}
  diametroMaterial = Serial.parseFloat();

  if (diametroMaterial > 0 && diametroMaterial <= 2) {
    intervaloPulAv = 100;
    intervalPulRot = 100;
  }
  if (diametroMaterial > 2 && diametroMaterial < 3) {
    intervaloPulAv = 250;
    intervalPulRot = 250;
  }
  if (diametroMaterial >= 3) {
    Serial.println("g1");
    while (diametroMaterial >= 3) {}
  }



  // ********DATOS PARA MOTOR DE ROTACION************ //
  Serial.println("b1");
  while (Serial.available() <= 0) {}
  nvR = Serial.parseFloat();

  Serial.println("b2");
  while (Serial.available() <= 0) {}
  dir1 = Serial.read();


  // ********DATOS PARA MOTOR DE AVANCE***********//

  Serial.println("b3");
  while (Serial.available() <= 0) {}
  nvAv = Serial.parseFloat();





  Serial.println("b6");
  while (Serial.available() <= 0) {}
  vueltasCierre = Serial.parseFloat();


  Serial.println("b7");
  while (Serial.available() <= 0) {}
  aumento = Serial.parseFloat();

  // ************DATOS PARA REPETIR RESORTES******//
  Serial.println("b4");
  while (Serial.available() <= 0) {}
  repetir = Serial.parseInt();
}

void realizarCalculos() {
  float pulsos = 2272 * (nvR - vueltasCierre);
  float pulsosTotales = pulsos + (aumento * 2272);

  vueltasDeseadasPulRot = pulsosTotales;
  vueltasFinalX = nvR - vueltasCierre + aumento;
  vueltasAvance = nvAv * (nvR - vueltasCierre);
  avancefinal = diametroMaterial + vueltasAvance;

  vueltasDeseadasPulAv = (avancefinal * 800) / 102;  // 102 es lo que avanza cada 800 pulsos
}
void calculosVueltasInicioFin() {
  unsigned long vueltasDeseadasPulRot1 = 2272 * (vueltasCierre / 2);

  unsigned long tiempoInicio3 = micros();
  unsigned long vueltasDadasRotor = 0;


  while (vueltasDadasRotor < vueltasDeseadasPulRot1) {
    unsigned long tiempoActual1 = micros();
    if (tiempoActual1 - tiempoInicio3 >= intervalPulRot && vueltasDadasRotor < vueltasDeseadasPulRot1) {
      tiempoInicio3 += intervalPulRot;
      digitalWrite(pulRot, !digitalRead(pulRot));
      if (digitalRead(pulRot)) vueltasDadasRotor++;
    }

    if (dir1 == 'D') {
      digitalWrite(dirRot, HIGH);
    }
    if (dir1 == 'I') {
      digitalWrite(dirRot, LOW);
    }
  }
}
void encenderMotores() {
  unsigned long tiempoInicio1 = micros();
  unsigned long tiempoInicio2 = micros();
  unsigned long vueltasDadasRotor = 0;


  if (dir1 == 'D') {
    digitalWrite(dirRot, HIGH);
  }
  if (dir1 == 'I') {
    digitalWrite(dirRot, LOW);
  }
  while (vueltasDadasRotor < vueltasDeseadasPulRot) {
    unsigned long tiempoActual2 = micros();
    unsigned long tiempoActual = micros();


    if (tiempoActual - tiempoInicio1 >= intervalPulRot && vueltasDadasRotor < vueltasDeseadasPulRot) {
      tiempoInicio1 += intervalPulRot;

      digitalWrite(pulRot, !digitalRead(pulRot));

      newintervaloPulAv = (vueltasDeseadasPulRot / vueltasDeseadasPulAv) * intervaloPulAv;

      if (tiempoActual2 - tiempoInicio2 >= newintervaloPulAv) {
        tiempoInicio2 += newintervaloPulAv;
        digitalWrite(pulAv, !digitalRead(pulAv));
        digitalWrite(dirAv, LOW);
      }



      if (digitalRead(pulRot)) {
        vueltasDadasRotor++;
      }
    }
  }
  vueltasDadasRotor = 0;
}

void desajusteResorte() {

  unsigned long vueltasDeseadasPulRot1 = 2272 * 2;

  unsigned long tiempoInicio3 = micros();
  unsigned long vueltasDadasRotor3 = 0;

  if (dir1 == 'D') {
    digitalWrite(dirRot, LOW);
  }
  if (dir1 == 'I') {
    digitalWrite(dirRot, HIGH);
  }

  while (vueltasDadasRotor3 < vueltasDeseadasPulRot1) {
    unsigned long tiempoActual1 = micros();
    if (tiempoActual1 - tiempoInicio3 >= intervalPulRot && vueltasDadasRotor3 < vueltasDeseadasPulRot1) {
      tiempoInicio3 += intervalPulRot;
      digitalWrite(pulRot, !digitalRead(pulRot));
      if (digitalRead(pulRot)) vueltasDadasRotor3++;
    }
  }
}
void regresoAvance() {

  Serial.println("f1");  //regreso de avance
  while (Serial.available() <= 0) {}
  int corte = Serial.parseInt();  //una vez se corte el material se da la orden para que el carro vuelva

  estadoInicio = digitalRead(iniciocarrera);
  Serial.println(estadoInicio);

  if (corte == 1) {
    unsigned long tiempoInicio3 = micros();
    unsigned long vueltasDadasAvance1 = 0;
    int newinter = 800;

    //while (vueltasDadasAvance1 < vueltasDeseadasPulAv) {
    while (estadoInicio != 1) {
      unsigned long tiempoActual1 = micros();
      if (tiempoActual1 - tiempoInicio3 >= newinter) {
        tiempoInicio3 += newinter;
        digitalWrite(pulAv, !digitalRead(pulAv));
        digitalWrite(dirAv, HIGH);
        // } else {
        //   Serial.println(estadoInicio);
        //   estadoDelProceso = 8;
      }
      estadoInicio = digitalRead(iniciocarrera);
    }
    Serial.println(estadoInicio);

    if (estadoInicio == 1) {
      estadoDelProceso = 8;
    }
  }
}

void repiteResorte() {
  // while (true) {
  if (repetir >= 1) {
    Serial.println("c1");
    while (Serial.available() == 0) {};
    int recibe = Serial.parseInt();
    if (recibe == 1) {
      estadoDelProceso = 2;
      repetir--;
    };
  }
  //  break;
  // }
}

void volverACero() {
  Serial.println("d1");
  while (Serial.available() == 0) {};
  int reciben = Serial.parseInt();
  if (reciben == 1) {
    estadoDelProceso = 1;
  } else if (reciben == 0) {
    Serial.println("d2");
  }
}
void joystick() {
  Serial.println("e1");
  while (!Serial.available()) {}
  valorEje = Serial.parseInt();
  Serial.println("e2");
  while (!Serial.available()) {}
}
void ejecutarJoystick() {
  int ejeX = 1;
  int ejeY = 1;
  int ejeZ = 1;
  int ejeA = 1;
  int ejeB = 1;



  claveEje = Serial.read();
  if (claveEje == 'r') {
    joystick();
  }



  if (claveEje == 'd') {
    digitalWrite(dirAv, !digitalRead(dirAv));
    digitalWrite(dirRot, !digitalRead(dirRot));
  }

  if (claveEje == 'x') {
    intervalPulRot = 650;
    unsigned long vueltasDeseadaspulRot = ejeX * valorEje;
    unsigned long tiempoInicioX = micros();
    unsigned long vueltasDadasX = 0;
    while (vueltasDadasX < vueltasDeseadaspulRot) {
      unsigned long tiempoActualX = micros();
      if (tiempoActualX - tiempoInicioX >= intervalPulRot && vueltasDadasX < vueltasDeseadaspulRot) {
        tiempoInicioX += intervalPulRot;
        digitalWrite(pulRot, !digitalRead(pulRot));
        if (digitalRead(pulRot)) vueltasDadasX++;
      }
    }
    digitalWrite(pulRot, LOW);
  }
  if (claveEje == 'y') {
    intervaloPulAv = 650;
    unsigned long vueltasDeseadaspulAv = ejeY * valorEje;
    unsigned long tiempoInicioY = micros();
    unsigned long vueltasDadasY = 0;
    while (vueltasDadasY < vueltasDeseadaspulAv) {
      unsigned long tiempoActualY = micros();
      if (tiempoActualY - tiempoInicioY >= intervaloPulAv && vueltasDadasY < vueltasDeseadaspulAv) {
        tiempoInicioY += intervaloPulAv;
        digitalWrite(pulAv, !digitalRead(pulAv));
        if (digitalRead(pulAv)) vueltasDadasY++;
      }
    }
    digitalWrite(pulAv, LOW);
  }
}
