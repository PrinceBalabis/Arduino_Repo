/*
   Arduino Uno only has interrupts on pin 2 and 3!

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

const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
// (Milliseconds)The amount of time to wait untill accepting another buttonpress
// 200ms seeems to be the sweet spot for buttons
const unsigned long interruptDebounce = 200;

volatile bool ledState = 0; // Save the current button state
volatile unsigned long lastinterruptDetected = 0; // Save last interrupt time
volatile unsigned long lastDetectionWasAPress = 0; // Save last pressed state
volatile uint16_t counter = 0; // Count amount of presses

void buttonInterrupt() {
  // Run time-sensitive function in the top of this function.
  unsigned long interruptDetected = millis(); // Store current time(program runtime)
  bool tempButtonState = digitalRead(buttonPin);

  //Serial.println("Interrupt...");
  if (interruptDetected - lastinterruptDetected > interruptDebounce && !lastDetectionWasAPress) {
    lastinterruptDetected = interruptDetected; // Save last interrupt detected
    lastDetectionWasAPress = 1;
    counter++; // Increment counter
    Serial.print(counter);
    Serial.print(": Accepted: ");
    Serial.println(tempButtonState); // You will see both 1 or 0 print out, because of the debouncing
    // Toggle LED
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
  } else {
    lastDetectionWasAPress = 0;
    //Serial.println("On cooldown");
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT); // Set led as output
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonInterrupt, CHANGE); // Attach the pin to the button to interrupt
  Serial.println("start...");
}

void loop() {
  // Not used
}

