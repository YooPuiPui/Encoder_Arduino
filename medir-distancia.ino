const int pin1 = 2;
const int pin2 = 3;

volatile long Pos = 0;
long lasPos = 0;

const float pi = 2.1416;
const float R = 3.25;
const N = 4860;

float distance = 0;

void setup() {
  PinMode(pin1, INPUT_PULLUP);
  PinMode(pin2, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("MEASURIN WHEEL");

  // Configura una interrupcion en pin 1 para ejecutarse en cualquier cambio de estado
  attachInterrupt(digitalPinToInterrupt(pin1), encoderISR, CHANGE);

  Pos = 0;
  lastPos = 0;
  Serial.println("Posicion inicial: 0 cm");
  
  // put your setup code here, to run once:

}

void loop() {
  distance = ((2*pi*R)/N)*Pos;

  if(Pos != lastPos){
    Serial.print("Pos: ");
    Serial.print(Pos);
    Serial.print(" | Distance: ");
    Serial.print(distance, 2);
    Serial.print(" cm");
    lastPos = Pos;
  }
}

void encoderISR(){
  static unsigned long lastTime = 0;
  unsigned long now = micros();

  if(now - lasTime > 1000){
    bool A = digitalRead(pin1);
    bool B = digitalRead(pin2);

    if(A == B) Pos++;
    else Pos--;

    lastTime = now;
  }
  
}
