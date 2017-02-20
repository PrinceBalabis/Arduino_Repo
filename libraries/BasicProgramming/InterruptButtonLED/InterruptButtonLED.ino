// constants won't change. They're used here to
// set pin numbers:
const int buttonInterruptPin = 0;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  pinMode(ledPin, OUTPUT);
  attachInterrupt(buttonInterruptPin, buttonPress, CHANGE);
}

void loop() {
    digitalWrite(ledPin, buttonState);
}

void buttonPress() {
  if (buttonState) {
    buttonState = 0;
  } else {
    buttonState = 1;
  }
}
