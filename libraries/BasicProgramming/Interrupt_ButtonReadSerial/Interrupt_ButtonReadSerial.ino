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

const int buttonPin = 12;     // the number of the pushbutton pin

void setup() {
  // Initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // Initialize the button pin as an input.
  // Also activate the internal pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);
  // Attach the pin to the button to interrupt
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonInterrupt, CHANGE);
}

void loop() {
  // Not used
}

/*
  The interrupt function which runs when the interrupt is triggered
  Keep interrupt function as short as possible so it doesn't affect other time sensitive stuff
  But of course most stuff that should have low response time should be here
*/
void buttonInterrupt() {
    Serial.println("asdadad");

  Serial.println(digitalRead(buttonPin));
}
