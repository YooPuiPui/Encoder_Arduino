const int pinA = 2;
volatile long pulsos = 0;


void setup() {
  Serial.begin(9600);
  pinMode(pinA, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(pinA), contarPulsos, RISING);

}

void loop() {

  Serial.print("Pulsos");
  Serial.println(pulsos);

  delay(500);
}

void contarPulsos(){
  pulsos++;
}
