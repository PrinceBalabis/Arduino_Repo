/*
  This Sketch is for Taijiuino or Arduino Due
  It blinks the RX and TX pins

 */


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(73, OUTPUT);
  pinMode(72, OUTPUT);

}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(73, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(72, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(73, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(72, HIGH);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
}
