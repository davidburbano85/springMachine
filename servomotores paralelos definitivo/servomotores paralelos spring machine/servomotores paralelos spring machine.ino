#define dirRot 3
#define pulRot 2
#define enaRot 4

#define pulAv 5
#define dirAv 6
#define enaAv 7
#define pinLed 13

long intervalPulRot = 350;  // en microsegundos
long intervaloPulAv = 350;  // En microsegunndos
long intervaloPulLed = 1000000;

int pasosPorRevPulRot = 800;
int pasosPorRevPulAv = 800;
int estadoDelProceso = 0;

//--------DATOS USUARIO---------
unsigned long nvR = 0;
unsigned long nvAv = 0;
String dir = "";
//-------------------------------


unsigned long vueltasDeseadasPulRot = 0;  // pasosPorRevPulRot * nvR;
unsigned long vueltasDeseadasPulAv = 0;   // pasosPorRevPulAv * nvAv;


String msg1 = "Ingresa el # de vueltas al motor de rotacion: ";
String msg2 = "Ingresa el sentido de giro derecha: D, izquierda: I. ";
String msg3 = "Ingresa el Avance al motor de avance";
String msg4 = "para hacer otro resorte marque 1 para terminar marque 0";

void setup() {
  Serial.begin(9600);

  pinMode(pulRot, OUTPUT);
  pinMode(dirRot, OUTPUT);
  pinMode(enaRot, OUTPUT);

  pinMode(pinLed, OUTPUT);

  pinMode(pulAv, OUTPUT);
  pinMode(dirAv, OUTPUT);
  pinMode(enaAv, OUTPUT);
}

void loop() {

  switch (estadoDelProceso) {
    case 0:
      iniciar();
      break;
    case 1:
      cargarDatosDesdeSerial();
      estadoDelProceso = nvAv > 0 && nvR > 0 && dir != "" ? 2 : 1;
      //validar datos o si no mandar respuesta
      break;
    case 2:
      Serial.println("se cargaron todos los datos exitosamente");
      String datos = "Los datos cargados son: " + String(nvAv) + " " + String(nvR) + " " + dir + " y el estado es: " + String(estadoDelProceso);
      Serial.println(datos);
      realizarCalculos();
      while (Serial.available() <= 0) {}
      estadoDelProceso = Serial.parseInt();
    case 5:
      Serial.println("El estado ahora es " + String(estadoDelProceso));
      encenderMotores();
      break;
  }
}



void iniciar() {
  Serial.println("conectando...");
  while (Serial.available() <= 0) {}

  estadoDelProceso = Serial.available() > 0 ? 1 : 0;
  Serial.read();
  Serial.println("El estado del proceso es : " + String(estadoDelProceso));
}

// *****ENTRADAS DESDE SERIAL*************    / /
// ***************************************   / /
void cargarDatosDesdeSerial() {
  // ********DATOS PARA MOTOR DE ROTACION************ //
  Serial.println(msg1);
  while (Serial.available() <= 0) {}
  nvR = Serial.parseFloat();

  Serial.println(msg2);
  while (Serial.available() <= 0) {}
  dir = Serial.readString();


  // ********DATOS PARA MOTOR DE AVANCE***********//

  Serial.println(msg3);
  while (Serial.available() <= 0) {}
  nvAv = Serial.parseFloat();
}


void realizarCalculos() {
  vueltasDeseadasPulRot = pasosPorRevPulRot * (nvR - 4);
  vueltasDeseadasPulAv = pasosPorRevPulAv * (nvAv - 4);
  Serial.println("los pulsos para el avance son : " + String(vueltasDeseadasPulAv) + " y los pulsos de rotacion son :" + String(vueltasDeseadasPulRot));
}

void encenderMotores() {
  unsigned long tiempoInicio1 = micros();
  unsigned long tiempoInicio2 = micros();
  unsigned long vueltasDadasRotor = 0;
  unsigned long vueltasDadasAvance = 0;

  digitalWrite(enaAv, HIGH);
  digitalWrite(enaRot, HIGH);

  while (vueltasDadasRotor < vueltasDeseadasPulRot || vueltasDadasAvance < vueltasDeseadasPulAv) {
    unsigned long tiempoActual = micros();
    if (tiempoActual - tiempoInicio1 >= intervalPulRot && vueltasDadasRotor < vueltasDeseadasPulRot) {
      tiempoInicio1 += intervalPulRot;
      digitalWrite(pulRot, !digitalRead(pulRot));
      if (digitalRead(pulRot)) vueltasDadasRotor++;
    }
    if (tiempoActual - tiempoInicio2 >= intervaloPulAv && vueltasDadasAvance < vueltasDeseadasPulAv) {
      tiempoInicio2 += intervaloPulAv;
      digitalWrite(pulAv, !digitalRead(pulAv));
      if (digitalRead(pulAv)) vueltasDadasAvance++;
    }
  }

  digitalWrite(pulRot, LOW);
  digitalWrite(pulAv, LOW);
}


void pinTrece() {
  long contador = micros();
  static long buffer = 0;
  static float vueltasDadas = 0;
  if (contador - buffer > intervaloPulLed) {
    buffer = contador;
    digitalWrite(pinLed, !digitalRead(pinLed));
    vueltasDadas++;
  }
}
