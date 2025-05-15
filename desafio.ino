// Pines del encoder
const int pin1 = 2;
const int pin2 = 3;

volatile long Posicion = 0;        // Posición actual
volatile long PulsosTotales = 0;   // Total de pulsos

const float pi = 3.1416;
const float R = 3.25;              // Radio de la rueda en cm
const int N = 4360;                // Pulsos por vuelta

float distancia_total = 0;

bool midiendo = false;
unsigned long ultimaActividad = 0;
const unsigned long tiempoInactividad = 2000;  // 2 segundos sin pulsos

long ultimosPulsos = 0;

void setup() {
  pinMode(pin1, INPUT_PULLUP);
  pinMode(pin2, INPUT_PULLUP);

  Serial.begin(9600);

  Serial.println("===================================");
  Serial.println("ADVERTENCIA: Coloque el encoder en el punto cero.");
  Serial.println("Presione ENTER para iniciar la medición...");
  Serial.println("===================================");

  while (true) {
    if (Serial.available()) {
      char c = Serial.read();
      if (c == '\n' || c == '\r') {
        Serial.println("\nIniciando medición...");
        midiendo = true;
        ultimaActividad = millis();
        attachInterrupt(digitalPinToInterrupt(pin1), encoderISR, CHANGE);
        break;
      }
    }
  }
}

void loop() {
  if (midiendo) {
    // Si hubo nuevo pulso, actualizamos el tiempo de última actividad
    if (PulsosTotales != ultimosPulsos) {
      ultimaActividad = millis();
      ultimosPulsos = PulsosTotales;
    }

    // Verificar si pasaron 2 segundos sin pulsos nuevos
    if (millis() - ultimaActividad > tiempoInactividad) {
      midiendo = false;
      detachInterrupt(digitalPinToInterrupt(pin1));

      distancia_total = ((2 * pi * R) / N) * PulsosTotales;

      // Corrección por bloque (si es necesario)
      distancia_total -= 1.0;
      if (distancia_total < 0) distancia_total = 0;

      Serial.println("\n--- MEDICIÓN FINALIZADA ---");
      //Serial.print("Pulsos registrados: ");
      //Serial.println(PulsosTotales);
      Serial.print("Distancia total recorrida: ");
      Serial.print(distancia_total, 2);
      Serial.println(" cm");
    }
  }
}

void encoderISR() {
  static unsigned long lastTime = 0;
  unsigned long now = micros();

  if (now - lastTime > 1000) {
    bool A = digitalRead(pin1);
    bool B = digitalRead(pin2);

    PulsosTotales++;

    if (A == B)
      Posicion++;
    else
      Posicion--;

    lastTime = now;
  }
}
