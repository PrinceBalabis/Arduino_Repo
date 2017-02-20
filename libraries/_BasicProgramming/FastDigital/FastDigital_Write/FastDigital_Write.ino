/**
   This Sketch gives an example how to blink LED on pin 13 and pin 2
   on and off

   Atmega328 pin mapping:
   http://www.jameco.com/Jameco/workshop/JamecoBuilds/arduinocircuit_fig12.jpg

   More to read:
   http://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit-in-c-c
*/
#define LED_13_PIN 5
#define LED_13_OUTPUT_INIT (DDRB |= _BV(LED_13_PIN))
#define LED_13_ON (PORTB |= _BV(LED_13_PIN))
#define LED_13_OFF (PORTB &= ~_BV(LED_13_PIN))
#define LED_13_TOGGLE (PORTB ^= _BV(LED_13_PIN))


#define LED_2_PIN 2
#define LED_2_OUTPUT_INIT (DDRD |= _BV(LED_2_PIN))
#define LED_2_ON (PORTD |= _BV(LED_2_PIN))
#define LED_2_OFF (PORTD &= ~_BV(LED_2_PIN))
#define LED_2_TOGGLE (PORTD ^= _BV(LED_2_PIN))

void setup() {
  LED_13_OUTPUT_INIT; // Set LED on pin 13 as output
  LED_2_OUTPUT_INIT; // Set LED on pin 2 as output
}

void loop() {
  LED_13_ON; // Set pin 13 on
  LED_2_ON; // Set pin 2 on
  delay(1000);
  LED_13_OFF; // Set pin 13 off
  LED_2_OFF; // Set pin 2 off
  delay(1000);
  LED_13_TOGGLE; // Toggle pin 13, in this case it sets ON
  LED_2_TOGGLE; // Toggle pin 2, in this case it sets ON
  delay(1000);
  LED_13_TOGGLE; // Toggle pin 13, in this case it sets OFF
  LED_2_TOGGLE; // Toggle pin 2, in this case it sets OFF
  delay(1000);
}
