#define sensorEntrada 2 // Entry sensor pin
#define sensorSaida 3 // Exit sensor pin
#define ledEntrada 8 // Entry LED pin
#define ledSaida 9 // Exit LED pin

int carCount = 0;

void setup() {
  pinMode(sensorEntrada, INPUT);
  pinMode(sensorSaida, INPUT);
  pinMode(ledEntrada, OUTPUT);
  pinMode(ledSaida, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(sensorEntrada) == HIGH) {
    carCount++;
    digitalWrite(ledEntrada, HIGH);
    delay(500); // Debounce
    digitalWrite(ledEntrada, LOW);
  }
  
  if (digitalRead(sensorSaida) == HIGH) {
    carCount--;
    digitalWrite(ledSaida, HIGH);
    delay(500); // Debounce
    digitalWrite(ledSaida, LOW);
  }
  
  Serial.print("Cars in the parking lot: ");
  Serial.println(carCount);
  delay(100);
}
