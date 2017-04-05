/* Blink without Delay

  NodeMCU has two LEDs(one on the board, one on the ESP) on pin 16 and 2.
  NOTE FOR THE RED LED, LED TOGGLE IS INVERTED, HIGH IS OFF, LOW IS ON


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
#include <NewRemoteTransmitter.h>

// The code for the 433MHz receiver
#define LIGHTS_433MHZ_CODE 1

//Set pin in the second parameter
NewRemoteTransmitter transmitter(15303606, D7, 260, 2);


// constants won't change. Used here to set a pin number :
const int ledPinESP =  D0;// LED on ESP on pin D4(Must call D4 in code)
const int ledPinBoard =  D4; // LED on board on pin D0(Must call D0 in code)

// Variables will change :
int ledState = LOW;             // ledState used to set the LED

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change :
const long interval = 3000;           // interval at which to toggle (milliseconds)

void setup() {
  // Wait some time, in order to allow ESP8266 to boot
  delay(2000);

  // set the digital pin as output:
  pinMode(ledPinESP, OUTPUT);
  pinMode(ledPinBoard, OUTPUT);
}

void loop() {
  // here is where you'd put code that needs to be running all the time.

  // check to see if it's time to blink the LED; that is, if the
  // difference between the current time and last time you blinked
  // the LED is bigger than the interval at which you want to
  // blink the LED.
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH; //HIGH=OFF
    } else {
      ledState = LOW; //LOW=ON
    }

    // set the LED with the ledState of the variable:
    digitalWrite(ledPinBoard, ledState);
    digitalWrite(ledPinESP, ledState);
    transmitter.sendUnit(PAINTINGLIGHTS_433MHZ_CODE, ledState);

  }
}
