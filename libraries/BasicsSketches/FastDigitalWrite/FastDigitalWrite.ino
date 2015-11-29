/**
 * This Sketch gives an example how to blink LED on pin 13
 * on and off
 * 
 * Atmega328 pin mapping:
 * http://www.jameco.com/Jameco/workshop/JamecoBuilds/arduinocircuit_fig12.jpg
 */

void setup() {
   DDRB = (1 << 5); // Set LED on board as output
}

void loop() {
  PORTB = (1 << 5); // Toggle on
  delay(1000);
  PORTB = ~(1 << 5); // Toggle off
  delay(1000);
}
