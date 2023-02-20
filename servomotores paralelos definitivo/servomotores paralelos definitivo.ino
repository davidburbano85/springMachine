#define dirRot 3
#define pulRot 2
#define enaRot 4

#define pulAv 5
#define dirAv 6
#define enaAv 7
#define pinLed 13

bool checkPulLed = false;
bool checkPulRot = false;
bool checkPulAv = false;
bool validar = false;

long intervalPulRot = 100;
long intervaloPulAv = 375;
long intervaloPulLed = 1000000;

int pasosPorRevPulRot = 800;
int pasosPorRevPulAv = 800;
int estadoDelProceso = 0;

float nvR = 0;
float nvAv = 0;
String dir = "";


float vueltasDeseadasPulRot = 0;  // pasosPorRevPulRot * nvR;
float vueltasDeseadasPulAv = 0;   // pasosPorRevPulAv * nvAv;


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

  if (estadoDelProceso == 0) {
    iniciar();
  }

  if (estadoDelProceso == 1) {
    cargarDatosDesdeSerial();
    estadoDelProceso = nvAv > 0 && nvR > 0 && dir != "" ? 2 : 1;
    Serial.println(estadoDelProceso);

    //validar datos o si no mandar respuesta
  }

  if (estadoDelProceso == 2) {
    Serial.println("se cargaron todos los datos exitosamente");
    estadoDelProceso = 3;
    String datos = "Los datos cargados son: " + String(nvAv) + " " + String(nvR) + " " + dir;
    Serial.println(datos);
  }

  if (estadoDelProceso == 3) {
    while (Serial.available() <= 0) {}
    int estado = Serial.parseInt();
    estadoDelProceso = estado == 4 ? estado : 3;
    Serial.println("El estado del proceso es : " + String(estadoDelProceso));
  }
  if (estadoDelProceso == 4) {
    realizarCalculos();
    estadoDelProceso = 5;
    Serial.println("El estado del proceso es : " + String(estadoDelProceso));
  }

  if (estadoDelProceso = 5) {
    motorRotacion();
    motorAvance();
    pinTrece();
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
  vueltasDeseadasPulRot = pasosPorRevPulRot * nvR;
  vueltasDeseadasPulAv = pasosPorRevPulAv * nvAv;
  Serial.println("los pulsos para el avance son : " + String(vueltasDeseadasPulAv) + " y los pulsos de rotacion son :" + String(vueltasDeseadasPulRot));
}


void motorRotacion() {
  long contador = micros();
  static long buffer = 0;
  static float vueltasDadas = 0;
  if (contador - buffer > intervalPulRot && vueltasDadas < vueltasDeseadasPulRot) {
    buffer = contador;
    checkPulRot = !checkPulRot;
    digitalWrite(dirRot, (dir != "" && dir == "D") ? HIGH : LOW);

    if (!checkPulRot) vueltasDadas++;
    digitalWrite(pulRot, checkPulRot ? HIGH : LOW);
    digitalWrite(enaRot, HIGH);

    if (vueltasDadas == vueltasDeseadasPulRot) {
      digitalWrite(enaRot, LOW);
    }
      Serial.println( vueltasDeseadasPulRot);

  }
}
// *********MOTOR DE AVANCE************** //
void motorAvance() {
  long contador = micros();
  static long buffer = 0;
  static float vueltasDadas = 0;
  if (contador - buffer > intervaloPulAv && vueltasDadas < vueltasDeseadasPulAv) {
    buffer = contador;
    checkPulAv = !checkPulAv;
    if (!checkPulAv) vueltasDadas++;
    digitalWrite(pulAv, checkPulAv ? HIGH : LOW);
    digitalWrite(enaAv, HIGH);
    if (vueltasDadas == vueltasDeseadasPulAv) {
      digitalWrite(enaAv, LOW);
      Serial.println( vueltasDeseadasPulAv);
    }
  }
}
void pinTrece() {
  long contador = micros();
  static long buffer = 0;
  static float vueltasDadas = 0;
  if (contador - buffer > intervaloPulLed) {
    buffer = contador;
    checkPulLed = !checkPulLed;
    if (!checkPulLed) vueltasDadas++;
    digitalWrite(pinLed, checkPulLed ? HIGH : LOW);
  }
}
