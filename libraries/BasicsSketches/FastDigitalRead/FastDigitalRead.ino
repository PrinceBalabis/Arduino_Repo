/**
   This Sketch gives an example how to read digital pin
   This example reads digital pin 4 and 5

   Atmega328 pin mapping:
   http://www.jameco.com/Jameco/workshop/JamecoBuilds/arduinocircuit_fig12.jpg

    More to read:
   http://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit-in-c-c
*/

#define PIN_1 4
#define PIN_1_INPUT_INIT (DDRD &= ~_BV(PIN_1))
#define PIN_1_SET_PULLUP (PORTD |= _BV(PIN_1))
#define PIN_1_READ (PIND & _BV(4) > 0)

#define PIN_2 5
#define PIN_2_INPUT_INIT (DDRD &= ~_BV(PIN_2))
#define PIN_2_SET_PULLUP (PORTD |= _BV(PIN_2))
#define PIN_2_READ (PIND & _BV(5) > 0)

void setup() {
  Serial.begin(115200);
  Serial.println(F("Started reading digital pin"));

  PIN_1_INPUT_INIT; // Sets pin 4 as input
  PIN_2_INPUT_INIT; // Sets pin 5 as input
  // DDRD = ~B00110000 // This can be used instead to set both pin 4 and 5 as input

  PIN_1_SET_PULLUP; // Set pullup
  PIN_2_SET_PULLUP; // Set pullup
}

void loop() {
  Serial.print(PIN_1_READ);
  Serial.print(F(" -- "));
  Serial.println(PIN_2_READ);
  delay(100);
}
