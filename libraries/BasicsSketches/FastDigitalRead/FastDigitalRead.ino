/**
 * This Sketch gives an example how to read digital pin
 * This example reads digital pin 4 and 5
 *
 * Atmega328 pin mapping:
 * http://www.jameco.com/Jameco/workshop/JamecoBuilds/arduinocircuit_fig12.jpg
 */

void setup() {
  Serial.begin(115200);
  Serial.println(F("Started reading digital pin"));

  DDRD &= ~B00110000; // pin 4 and 5 set as input
  PORTD |= _BV(PD4); // Set pullup
  PORTD |= _BV(PD5); // Set pullup
}

void loop() {

  Serial.print(PIND & (1 << 4) > 0);
  Serial.print(F(" -- "));
  Serial.println(PIND & (1 << 5) > 0);
  delay(100);
}
