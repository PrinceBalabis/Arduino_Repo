/* PWM test

  Rough PWM test with one of the onboard LEDs

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

// constants won't change. Used here to set a pin number :
const int ledPinESP =  D0;// LED on ESP on pin D4(Must call D4 in code)
const int ledPinBoard =  D4; // LED on board on pin D0(Must call D0 in code)

void setup() {
  // Wait some time, in order to allow ESP8266 to boot
  delay(2000);

  // set the digital pin as output:
  pinMode(ledPinESP, OUTPUT);
  pinMode(ledPinBoard, OUTPUT);

}

void loop() {
  // Turn LED OFF

  analogWrite(ledPinESP, 0);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second

  // Turn LED on: 25 Percent Intensity

  analogWrite(ledPinESP, 255);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second

  // Turn LED on: 25 Percent Intensity

  analogWrite(ledPinESP, 512);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second

  // Turn LED on: 75 Percent Intensity

  analogWrite(ledPinESP, 767);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second

  // Turn LED on: 100 Percent Intensity

  analogWrite(ledPinESP, 1023);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second


}
