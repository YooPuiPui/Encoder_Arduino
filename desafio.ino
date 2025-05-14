// pines
const int pin1 = 2;
const int pin2 = 3;

volatile long Posicion = 0; // la posicion actual
volatile long PulsosTotales = 0; // el total de pulsos

const float pi = 3.1416;
const float R = 3.25;
const int N = 4360;

float distancia_total = 0;

bool midiendo = false;
unsigned long ultimaActividad = 0;
const unsigned long tiempoInactividad = 2000; // 2 segundos

long lastPos = 0; // para comparar cambios de posicion

void setup(){
    pinMode(pin1, INPUT_PULLUP);
    pinMode(pin2, INPUT_PULLUP);

    Serial.begin(9600);

    Serial.println("Asegurate de que el encoder este en el punto cero\n");
    Serial.println("Presiona ENTER para iniciar la medicion.");

    Posicion = 0;
    PulsosTotales = 0;

    while(true){
        if(Serial.available()){
            char c = Serial.read();
            if(c == '\n' || c == '\r') {
                midiendo = true;
                ultimaActividad = millis();
                Serial.println("Iniciando medicion...");
                attachInterrupt(digitalPinToInterrupt(pin1), encoderISR, CHANGE);
                break;
            }
        }
    }
}

void loop(){
    if(midiendo) {
        if(Posicion != lastPos){
            lastPos = Posicion;
            ultimaActividad = millis();

            /*
            // Mostrar info en tiempo real
            float parcial = ((2 * pi * R) / N) * PulsosTotales;
            Serial.print("Pulsos: ");
            Serial.print(PulsosTotales);
            Serial.print(" | Distancia parcial: ");
            Serial.println(parcial, 2);
            */
        }

        if(millis() - ultimaActividad > tiempoInactividad){
            midiendo = false;
            detachInterrupt(digitalPinToInterrupt(pin1));

            distancia_total = ((2 * pi * R) / N) * PulsosTotales;
            distancia_total -= 1.0; // compensar bloque
            if (distancia_total < 0) distancia_total = 0;

            Serial.println("\n--- MEDICION FINALIZADA ---");
            Serial.print("Distancia total recorrida: ");
            Serial.print(distancia_total, 2);
            Serial.println(" cm");
        }
    }
}


void encoderISR(){
    static unsigned long lastTime = 0;
    unsigned long now = micros(); 

    if(now - lastTime > 1000){
        bool A = digitalRead(pin1);
        bool B = digitalRead(pin2);

        PulsosTotales++;
        if(A == B) Posicion++;
        else Posicion--;

        lastTime = now;
    }
}
