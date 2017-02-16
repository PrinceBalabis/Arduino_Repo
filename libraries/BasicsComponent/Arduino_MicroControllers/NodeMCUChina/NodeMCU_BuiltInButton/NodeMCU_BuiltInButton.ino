/*
 * The NodeMCU has a built-in programmable button on pin 16(same as board LED)
 * This code will make so whenever the button is pressed, the LED on the ESP(pin 2) is toggled
 */


const int buttonPin = 16; // Button is same pin as the board LED
const int ledPinESP = 2;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPinESP, OUTPUT);
}

void loop() {
  if (digitalRead(buttonPin) == HIGH)
  {
    digitalWrite(ledPinESP, HIGH);
  }
  else
  {
    digitalWrite(ledPinESP, LOW);
    pinMode(buttonPin, OUTPUT);
    digitalWrite(buttonPin, HIGH);
    pinMode(buttonPin, INPUT);
  }
}

