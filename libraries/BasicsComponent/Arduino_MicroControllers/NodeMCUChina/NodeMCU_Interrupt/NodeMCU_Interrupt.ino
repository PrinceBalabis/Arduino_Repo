/*

  DOES NOT SEEM TO WORK

*/

const uint8_t interruptPin = 4; // pin to interrupt
unsigned long interruptDetected = 0; // Has a value above 0 when an interrupt is detected

// This is the function which is called upon interrupt
void interruptFunction() {
  Serial.println("hi");

  interruptDetected = micros(); // Store current time(program runtime)
}

void setup() {
  delay(2000); // Wait some time, in order to allow ESP8266 to boot
  Serial.begin(115200);
  delay(100); // Some time for serial buffer to empty

  pinMode(interruptPin, OUTPUT);
  digitalWrite(interruptPin, 0);
  //CHANGE TO RISING OR FALLING DEPENDING ON YOUR GOALS
  attachInterrupt(digitalPinToInterrupt(interruptPin), interruptFunction, CHANGE);

  Serial.println(F(""));
  Serial.println("Started interrupt program");
  delay(100); // Some time for serial buffer to empty
}

void loop() {
  if (interruptDetected > 0) {
    Serial.println(interruptDetected);

    interruptDetected = 0;
  }

  Serial.println("k");

  delay(500);
}



