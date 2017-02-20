/*
   Reads a button connected to a pin
   and continously prints the value to serial.
   The digital pin reads "1" when the button is NOT pressed.
   It reads "0" when the button is pressed.

   Having the pull-up resistor activated(INPUT_PULLUP) means there is no need
   to have the pushbuttons "open pin" connected to 3.3V.

   The pushbutton has four pins, but they are joined connected 2 and 2.
   So the pins which are opposite each other(on each side of the button) are
   constantly connected(even when the pushbuttis not pressed/open circuit).
   When the pushbutton is pressed, all 4 pins are closed circuited.

   Circuit:
   Here we see the pingroups A and B, A1 and A2 are always connected even
   though the button is not pressed. Same goes for B1 and B2.
   When the button is pressed, the two groups are connected.
    (A1)   (B1)
     |     |
     |-----|
     |     |
    (A2)   (B2)

   Connection between Arduino and button:
   Ground -> A1 -> B1 - Digital pin
   or
   Ground -> A2 -> B2 - Digital pin
*/

const int buttonPin = 5; // Pin of the pushbutton
bool buttonState = 0; // Save the current state of the button

void setup() {
  // Initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // Initialize the button pin as an input.
  // Also activate the internal pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);
}
// the loop routine runs over and over again forever:
void loop() {
  buttonState = digitalRead(buttonPin); // Read the button state
  Serial.println(buttonState);
  delay(10);
}

