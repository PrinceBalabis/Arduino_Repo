void setup() {
  for (int i = 3; i <= 9; i++) {
    pinMode(i, OUTPUT);   // turn the LED on (HIGH is the voltage level)
  }
}

void loop() {
  for (int i = 3; i <= 9; i++) {
    digitalWrite(i, HIGH);   // turn the LED on (HIGH is the voltage level)
  }
  delay(1000);               // wait for a second
  for (int i = 3; i <= 9; i++) {
    digitalWrite(i, LOW);   // turn the LED on (HIGH is the voltage level)
  }  delay(1000);               // wait for a second
}
