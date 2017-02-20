/*
   Attaches an interrupt to the pin connected to a button.
   Toggles the LED depending if the button is pressed  or not
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

const int buttonPin = 0;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

bool buttonState = 0; // variable for reading the pushbutton status

void setup() {
  pinMode(ledPin, OUTPUT); // Set led as output
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonInterrupt, CHANGE); // Attach the pin to the button to interrupt
}

void loop() {
  digitalWrite(ledPin, buttonState); // Toggle LED depending on the state of the button
  delay(10);
}

void buttonInterrupt() {
  if (buttonState) {
    buttonState = 0;
  } else {
    buttonState = 1;
  }
}
