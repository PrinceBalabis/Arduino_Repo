/*
   Reads a button connected to a pin
   and continously prints the value to serial.
   The digital pin reads "1" when the pin is NOT pressed.
   It reads "0" when the pin is pressed.

   Having the pull-up resistor activated(INPUT_PULLUP) means there is no need
   to have the pushbuttons "open pin" connected to 3.3V.
*/

// Define button pins
const int K1 = 13; // Button K1
const int K2 = 12; // Button K2
const int K3 = 11; // Button K3
const int K4 = 10; // Button K4
// Define LED pins
const int LGND = 6; // GND pin on the LED module
const int L1 = 5; // D1 pin on the LED module
const int L2 = 4; // D2 pin on the LED module
const int L3 = 3; // D3 pin on the LED module
const int L4 = 2; // D4 pin on the LED module
const int L5 = 1; // D5 pin on the LED module
const int L6 = 0; // D6 pin on the LED module

bool buttonState = 0; // For saving the current pushbutton status

// The setup routine runs once upon start
void setup() {
  // Initialize the keys pin as an input.
  //Also activates internal pull-up resistors
  pinMode(K1, INPUT_PULLUP);
  pinMode(K2, INPUT_PULLUP);
  pinMode(K3, INPUT_PULLUP);
  pinMode(K4, INPUT_PULLUP);
  // Initialize the leds pin as an output.
  pinMode(LGND, OUTPUT);
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);
  pinMode(L4, OUTPUT);
  pinMode(L5, OUTPUT);
  pinMode(L6, OUTPUT);
  //Set the digital pin to LOW, to emulate a GND pin
  digitalWrite(LGND, LOW);
}
// The loop routine runs over and over again forever
void loop() {
  buttonState = digitalRead(K1);
  digitalWrite(L1, buttonState); //
  buttonState = digitalRead(K2);
  digitalWrite(L2, buttonState); //
  buttonState = digitalRead(K3);
  digitalWrite(L3, buttonState); //
  buttonState = digitalRead(K4);
  digitalWrite(L4, !buttonState); //
  digitalWrite(L5, HIGH); // turn the LED on (HIGH is the voltage level)
  digitalWrite(L6, HIGH); // turn the LED on (HIGH is the voltage level)
}

