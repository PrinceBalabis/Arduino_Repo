/**
   This Sketch gives an example how to read digital pin
   This example reads digital pin 4 and 5

   Atmega328 pin mapping:
   http://www.jameco.com/Jameco/workshop/JamecoBuilds/arduinocircuit_fig12.jpg
*/

void setup() {
  Serial.begin(115200);
  Serial.println(F("Started reading digital pin"));

  DDRD = ~(1 << 4); // Sets pin 4 as input
  DDRD = ~(1 << 5); // Sets pin 5 as input
  // DDRD = ~B00110000 // This can be used instead to set both pin 4 and 5 as input

  PORTD = (1 << 4); // Set pullup
  PORTD = (1 << 5); // Set pullup
}

void loop() {
  Serial.print(PIND & (1 << 4) > 0);
  Serial.print(F(" -- "));
  Serial.println(PIND & (1 << 5) > 0);
  delay(100);
}
