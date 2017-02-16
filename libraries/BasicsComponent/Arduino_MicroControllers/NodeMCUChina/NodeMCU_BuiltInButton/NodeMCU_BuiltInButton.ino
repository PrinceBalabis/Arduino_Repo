/*
 * The NodeMCU has a built-in programmable button on pin 16(same as board LED)
 * This code will make so whenever the button is pressed, the LED on the ESP(pin 2) is toggled

 
  MAJOR BUG:
  If it cannot connect to the Wi-Fi hotspot, try reconnecting the power/USB cable to reset the ESP

  Put a large capacitor(or even better, several small ones) between 5V/VIN and Ground to improve reliability

  Remember to install the CH340G drivers.

  Board settings:
  -NodeMCU 1.0(ESP-12E)
  -80MHz
  -921600
  -4M(3M)
  
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

