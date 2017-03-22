/*
  Blinks the 6 LEDs on the module after each other
*/

// Define LED pins
const uint8_t leds[] = {13, 12, 11, 10, 9, 8}; // Actual pins to toggle the LEDs
const uint8_t amountOfLeds = sizeof(leds) / sizeof(uint8_t);

// The setup routine runs once upon start
void setup() {
  // Initialize pins connected to LEDs as output
  for (int i = 0; i < amountOfLeds; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

// The loop routine runs over and over again forever
void loop() {
  // Blink the LEDs one at a time
  for (int i = 0; i < amountOfLeds; i++) {
    digitalWrite(leds[i], HIGH);
    delay(250);
    digitalWrite(leds[i], LOW);
    delay(250);
  }
}

