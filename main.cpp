#define TRIG_PIN_ENTRY 2
#define ECHO_PIN_ENTRY 3
#define TRIG_PIN_EXIT 4
#define ECHO_PIN_EXIT 5
#define LED_PIN_ENTRY 8
#define LED_PIN_EXIT 9

int carCount = 0;

void setup() {
  pinMode(TRIG_PIN_ENTRY, OUTPUT);
  pinMode(ECHO_PIN_ENTRY, INPUT);
  pinMode(TRIG_PIN_EXIT, OUTPUT);
  pinMode(ECHO_PIN_EXIT, INPUT);
  pinMode(LED_PIN_ENTRY, OUTPUT);
  pinMode(LED_PIN_EXIT, OUTPUT);
  Serial.begin(9600);
}

long readDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  long distance = (duration / 2) / 29.1;
  return distance;
}

void loop() {
  long distanceEntry = readDistance(TRIG_PIN_ENTRY, ECHO_PIN_ENTRY);
  long distanceExit = readDistance(TRIG_PIN_EXIT, ECHO_PIN_EXIT);

  if (distanceEntry < 10) { // Adjust distance threshold as needed
    carCount++;
    digitalWrite(LED_PIN_ENTRY, HIGH);
    delay(1000); // Prevent double counting
    digitalWrite(LED_PIN_ENTRY, LOW);
  }
  
  if (distanceExit < 10) { // Adjust distance threshold as needed
    carCount--;
    digitalWrite(LED_PIN_EXIT, HIGH);
    delay(1000); // Prevent double counting
    digitalWrite(LED_PIN_EXIT, LOW);
  }
  
  Serial.print("Cars in the parking lot: ");
  Serial.println(carCount);
  delay(500);
}
