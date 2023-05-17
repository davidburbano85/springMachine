#define dirRot 3
#define pulRot 2

#define pulAv 4
#define dirAv 5
#define ena 7
#define finalCarrera 8
int estado = 0;
#define iniciocarrera 12
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
double newintervaloPulAv = 0;

int pasosPorRevPulRot = 800;
int pasosPorRevPulAv = 800;
unsigned int estadoDelProceso = 0;
int repetir = 0;

//--------DATOS USUARIO---------
double nvR = 0;
double nvAv = 0;
char dir1 = "";
double diametroMaterial = 0;
double vueltasCierre = 0;
int aumento = 0;
double vueltasFinalX = 0;
double vueltasAvance = 0;
double avancefinal = 0;

//-------------------------------

unsigned long vueltasDeseadasPulRot = 0;  // pasosPorRevPulRot * nvR;
double vueltasDeseadasPulAv = 0;          // pasosPorRevPulAv * nvAv;

char dir = "";

void setup() {
  pinMode(finalCarrera, INPUT);
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
    digitalWrite(13, HIGH);

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
        desajusteResorte();
        estadoDelProceso = 7;
        break;

      case 7:
        regresoAvance();
        //estadoDelProceso = 8;

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

  if (diametroMaterial > 0 && diametroMaterial < 2) {
    intervaloPulAv = 140;
    intervalPulRot = 140;
  }
  if (diametroMaterial >= 2 && diametroMaterial < 2.5) {
    intervaloPulAv = 180;
    intervalPulRot = 180;
  }
  if (diametroMaterial >= 2.5 && diametroMaterial < 3) {
    intervaloPulAv = 450;
    intervalPulRot = 450;
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
  //ROTACION
  unsigned long interRe = 2272;
  double pulsos = interRe * (nvR - vueltasCierre);
  double pulsosTotales = pulsos + (aumento * interRe);

  vueltasDeseadasPulRot = pulsosTotales;
  vueltasFinalX = nvR - vueltasCierre + aumento;
  //AVANCE
  vueltasAvance = nvAv * (nvR - vueltasCierre);
  avancefinal = diametroMaterial + vueltasAvance;

  vueltasDeseadasPulAv = (avancefinal * pasosPorRevPulAv) / 102UL;  // 102 es lo que avanza cada 800 pulsos
}
void calculosVueltasInicioFin() {
  unsigned long inter = 2272;
  unsigned long vueltasDeseadasPulRot1 = inter * (vueltasCierre / 2UL);

  unsigned long tiempoInicio3 = micros();
  unsigned long tiempoinicioavance = micros();
  unsigned long vueltasDadasRotor1 = 0;
  double mmXpulso = 0.13;
  double aumentoAlDiametro = 0.1;

  unsigned long pulsosapriete = vueltasCierre * (mmXpulso + diametroMaterial + aumentoAlDiametro);
  unsigned long intervalPulRotca = intervalPulRot;

  while (vueltasDadasRotor1 < vueltasDeseadasPulRot1) {
    unsigned long tiempoActual1 = micros();
    unsigned long tiempoactualavanceapriete = micros();
    if (tiempoActual1 - tiempoInicio3 >= intervalPulRotca && vueltasDadasRotor1 < vueltasDeseadasPulRot1) {
      tiempoInicio3 += intervalPulRotca;
      digitalWrite(pulRot, !digitalRead(pulRot));
      if (digitalRead(pulRot)) vueltasDadasRotor1++;

      unsigned long nuevointervaloapriete = (vueltasDeseadasPulRot1 / pulsosapriete) * intervaloPulAv;
      if (tiempoactualavanceapriete - tiempoinicioavance >= nuevointervaloapriete) {
        tiempoinicioavance += nuevointervaloapriete;
        digitalWrite(pulAv, !digitalRead(pulAv));
        digitalWrite(dirAv, LOW);
      }
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
    unsigned long intervalPulRoten = intervalPulRot;


    if (tiempoActual - tiempoInicio1 >= intervalPulRoten && vueltasDadasRotor < vueltasDeseadasPulRot) {
      tiempoInicio1 += intervalPulRoten;

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
}

void desajusteResorte() {

  unsigned long vueltasDeseadasPulRot2 = 2272 * 2;
  unsigned long tiempoInic = micros();
  unsigned long vueltasDadasRotor3 = 0;
  unsigned long intervalPulRota = 200;
  if (dir1 == 'D') {
    digitalWrite(dirRot, LOW);
  }
  if (dir1 == 'I') {
    digitalWrite(dirRot, HIGH);
  }
  delay(700);
  unsigned long tiempoInicio4 = micros();
  while (vueltasDadasRotor3 < vueltasDeseadasPulRot2) {
    unsigned long tiempoActualde = micros();
    if (tiempoActualde - tiempoInicio4 >= intervalPulRota && vueltasDadasRotor3 < vueltasDeseadasPulRot2) {
      tiempoInicio4 += intervalPulRota;
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

  if (corte == 1) {
    unsigned long tiempoInicio5 = micros();
    unsigned long vueltasDadasAvance1 = 0;
    int newinter = 800;

    while (estadoInicio != 1) {
      unsigned long tiempoActual3 = micros();
      if (tiempoActual3 - tiempoInicio5 >= newinter) {
        tiempoInicio5 += newinter;
        digitalWrite(pulAv, !digitalRead(pulAv));
        digitalWrite(dirAv, HIGH);
      }
      estadoInicio = digitalRead(iniciocarrera);
    }

    if (estadoInicio == 1) {
      estadoDelProceso = 8;
    }
  }
}

void repiteResorte() {
  if (repetir >= 1) {
    Serial.println("c1");
    while (Serial.available() == 0) {};
    int recibe = Serial.parseInt();
    if (recibe == 1) {
      estadoDelProceso = 2;


      realizarCalculos();
      estadoDelProceso = 3;

      calculosVueltasInicioFin();
      estadoDelProceso = 4;

      encenderMotores();
      estadoDelProceso = 5;

      calculosVueltasInicioFin();
      estadoDelProceso = 6;

      desajusteResorte();
      estadoDelProceso = 7;

      regresoAvance();
      estadoDelProceso = 8;

      repetir--;
    };
  }
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
  estadoInicio = digitalRead(iniciocarrera);
  if (estadoInicio == 0) {

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
      intervaloPulAv = 800;
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
  } else {
    Serial.println("g1");
  }
}
