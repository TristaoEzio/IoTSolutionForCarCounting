int accumulator = 0;

/*  
  * Segment pins
  * a= 13
  * b= 12
  * c= 11
  * d= 10
  * e= 9
  * f= 8
  * g= 7
  * pushbutton Entry= 6
  * pushbutton Exit= 5
  * Led Entry= 4
  * Led Exit= 3
  * Led Free Slots= 2
  * Led Full Parking= 1
*/  

void setup() {
  for (int pin = 1; pin <= 13; pin++) {
    pinMode(pin, (pin == 6 || pin == 5) ? INPUT : OUTPUT);
  }
  Serial.begin(9600);
}

void updateDisplay(int number) {
  bool segments[10][7] = {
    {LOW, LOW, LOW, LOW, LOW, LOW, HIGH}, // 0
    {HIGH, LOW, LOW, HIGH, HIGH, HIGH, HIGH}, // 1
    {LOW, LOW, HIGH, LOW, LOW, HIGH, LOW}, // 2
    {LOW, LOW, LOW, LOW, HIGH, HIGH, LOW}, // 3
    {HIGH, LOW, LOW, HIGH, HIGH, LOW, LOW}, // 4
    {LOW, HIGH, LOW, LOW, HIGH, LOW, LOW}, // 5
    {LOW, HIGH, LOW, LOW, LOW, LOW, LOW}, // 6
    {LOW, LOW, LOW, HIGH, HIGH, HIGH, HIGH}, // 7
    {LOW, LOW, LOW, LOW, LOW, LOW, LOW}, // 8
    {LOW, LOW, LOW, LOW, HIGH, LOW, LOW} // 9
  };
  
  for (int i = 0; i < 7; i++) {
    digitalWrite(13 - i, segments[number][i]);
  }
}

void loop() {
  if (digitalRead(6) == HIGH && accumulator < 8) { // Entry
    accumulator++;
    delay(500); // Debounce
  }

  if (digitalRead(5) == HIGH && accumulator > 0) { // Exit
    accumulator--;
    delay(500); // Debounce
  }

  // LEDs for free slots and full parking
  digitalWrite(2, (accumulator < 8) ? HIGH : LOW);
  digitalWrite(1, (accumulator == 8) ? HIGH : LOW);

  // LEDs for entry and exit gates
  digitalWrite(4, (digitalRead(6) == HIGH && accumulator < 8) ? HIGH : LOW);
  digitalWrite(3, (digitalRead(5) == HIGH && accumulator > 0) ? HIGH : LOW);

  // Update the 7-segment display
  updateDisplay(accumulator);

  Serial.print("Cars in the parking lot: ");
  Serial.println(accumulator);
  delay(100);
}
