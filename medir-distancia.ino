const int pin1 = 2;
const int pin2 = 3;

volatile long Pos = 0;
long lastPos = 0;

const float pi = 3.1416;
const float R = 3.25;
const int N = 4860;

float distance = 0;

void setup() {
  pinMode(pin1, INPUT_PULLUP);
  pinMode(pin2, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("MEASURING WHEEL");

  attachInterrupt(digitalPinToInterrupt(pin1), encoderISR, CHANGE);

  Pos = 0;
  lastPos = 0;
  Serial.println("Posición inicial: 0 cm");
}

void loop() {
  distance = ((2 * pi * R) / N) * Pos;

  if (Pos != lastPos) {
    Serial.print("Pos: ");
    Serial.print(Pos);
    Serial.print(" | Distance: ");
    Serial.print(distance, 2);
    Serial.println(" cm");
    lastPos = Pos;
  }
}

void encoderISR() {
  static unsigned long lastTime = 0;
  unsigned long now = micros();

  if (now - lastTime > 1000) {
    bool A = digitalRead(pin1);
    bool B = digitalRead(pin2);

    if (A == B)
      Pos++;
    else
      Pos--;

    lastTime = now;
  }
}
