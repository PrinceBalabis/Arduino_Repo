#include <IRremote.h>

/*
*  Program to turn on and off an RGB-LED Module with an IR-remote.
*  Can individually turn on the different red green blue leds.
*
*  On/Off  -  Turns off/on all RGB-leds
*  0  -  Turns on all RGB-leds
*  1  -  Turns on green led
*  2  -  Turns on blue led
*  3  -  Turns on red led
*
*  By Prince Balabis
*/

// Change pins to yours
int led_green = 9;
int led_blue = 10;
int led_red = 8;
int led_ir = 11;

// Variables used for operations
int rgbState = 0;
int greenState = 0;
int blueState = 0;
int redState = 0;
IRrecv irrecv(led_ir);
decode_results results;

void setup() {
  pinMode(led_green, OUTPUT);
  pinMode(led_blue, OUTPUT);
  pinMode(led_red, OUTPUT);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    if (results.value == 0xFFA25D)  { // On/Off
      rgbState = !rgbState;
      greenState = !greenState;
      blueState = !blueState;
      redState = !redState;
      digitalWrite(led_green, rgbState);
      digitalWrite(led_blue, rgbState);
      digitalWrite(led_red, rgbState);
    }
    else if (rgbState && results.value == 0xFF6897) { // 0
      greenState = true;
      blueState = true;
      redState = true;
      digitalWrite(led_green, HIGH);
      digitalWrite(led_blue, HIGH);
      digitalWrite(led_red, HIGH);
    }
    else if (rgbState && results.value == 0xFF30CF) { // 1
      greenState = !greenState;
      digitalWrite(led_green, greenState);
    }
    else if (rgbState && results.value == 0xFF18E7) { // 2
      blueState = !blueState;
      digitalWrite(led_blue, blueState);
    }
    else if (rgbState && results.value == 0xFF7A85) { // 3
      digitalWrite(led_red, !redState);
      redState = !redState;
    }
    irrecv.resume(); // Receive the next value
  }
}
