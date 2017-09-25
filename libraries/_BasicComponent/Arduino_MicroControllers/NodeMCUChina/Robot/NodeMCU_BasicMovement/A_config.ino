/*
  ---------------------------------------------------------------
  This is the config tab.
  All tweakable settings are here.
  It must be named "A_" in the start of the tab-name or else it won't compile
  ---------------------------------------------------------------
*/


/*
  ---------------------------------------------------------------
  Pin-outs LED
  ---------------------------------------------------------------
*/
const int ledPinESP =  D4;// LED on ESP on pin D4(Must call D4 in code)
const int ledPinBoard =  D0; // LED on board on pin D0(Must call D0 in code)

/*
  ---------------------------------------------------------------
  Pin-outs H-Bridge
  ---------------------------------------------------------------
*/
const int aMotor = D8; //Right Motor A
const int bMotor = D7; //Right Motor B
const int cMotor = D6; //Left Motor C
const int dMotor = D5; //Left Motor D
const int en1Motor = D3; // Right Motor
const int en2Motor = D2; // Left Motor
//const int s1 = A0; // Current sensor for right motor
//const int s2 = A1; // Current sensor for left motor
