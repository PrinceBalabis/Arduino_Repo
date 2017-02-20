/*
   Reads a button connected to a pin
   and prints the value to serial whenever the button is pressed/not pressed
   The digital pin reads "1" when the pin is NOT pressed.
   It reads "0" when the pin is pressed.

   Image of the 4-button module:
   https://ae01.alicdn.com/kf/HTB1I_.fLXXXXXbuXXXXq6xXFXXXk/KC11C04-font-b-5-b-font-5X-with-UNO-R3-DUE-sketch-AD-Keypad-1-AD.jpg
*/

// Define button pins
const int buttonGND = 13; // The digital pin which is connected to GND on the module
const int buttons[] = {12, 11, 10, 9};

// Save the last state for each button
// Declare the array of size 4 with the value 0 to each index
bool lastButtonState[4] = {0};

// The setup routine runs once upon start
void setup() {
  // Initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // Initalize the digital pin connected to GND on the module
  pinMode(buttonGND, OUTPUT); // Set as output
  digitalWrite(buttonGND, LOW); // Set to LOW to emulate a GND pin

  // Initialize the keys pin as an input.
  //Also activates internal pull-up resistors
  for (int i = 0; i < 4; i++) {
    pinMode(buttons[i], INPUT_PULLUP);
  }
}
// The loop routine runs over and over again forever
void loop() {
  for (int i = 0; i < 4; i++) {
    bool buttonState = digitalRead(buttons[i]);
    if (buttonState != lastButtonState[i]) {
      Serial.print("Button ");
      Serial.print(i+1);
      Serial.print(": ");
      Serial.println(buttonState);
      lastButtonState[i] = buttonState;
    }
  }
  delay(10);
}

