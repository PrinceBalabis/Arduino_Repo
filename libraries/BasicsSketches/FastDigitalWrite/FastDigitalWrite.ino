/**
 * This Sketch gives an example how to blink LED on pin 13
 * on and off
 * 
 * Atmega328 pin mapping:
 * http://www.jameco.com/Jameco/workshop/JamecoBuilds/arduinocircuit_fig12.jpg
 */

void setup() {
   DDRB |= B00100000; // Set LED on board as output
}

void loop() {
  PORTB |= _BV(PB5); // Toggle on
  delay(1000);
  PORTB &= ~_BV(PB5); // Toggle off
  delay(1000);
}
