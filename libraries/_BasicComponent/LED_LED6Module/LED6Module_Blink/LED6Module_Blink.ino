/*
  Blinks the 6 LEDs on the module after each other
*/

// Define LED pins
//const int LedGND = 13; // GND pin on the LED module
const int leds[] = {13, 12, 11, 10, 9, 8}; // Actual pins to toggle the LEDs

//const int L1 = 5; // D1 pin on the LED module
//const int L2 = 4; // D2 pin on the LED module
//const int L3 = 3; // D3 pin on the LED module
//const int L4 = 2; // D4 pin on the LED module
//const int L5 = 1; // D5 pin on the LED module
//const int L6 = 0; // D6 pin on the LED module

// The setup routine runs once upon start
void setup() {
  // Initialize the leds pin as an output.
  //pinMode(LedGND, OUTPUT);
  //Set the digital pin to LOW, to emulate a GND pin
  //digitalWrite(LedGND, LOW);

  for (int i = 0; i < 5; i++) {
    pinMode(leds[i], OUTPUT);
  }
}
// The loop routine runs over and over again forever
void loop() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(leds[i], HIGH);
    delay(500);
    digitalWrite(leds[i], LOW);
    delay(500);
  }
}

