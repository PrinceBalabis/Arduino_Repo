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
  Shift Register
  ---------------------------------------------------------------
*/
const int serShiftRegister = D8;
const int rclkShiftRegister = D7;
const int srclckShiftRegister = D6;
const int number_of_74hc595s = 2; //Amount of shift registers to use

/*
  ---------------------------------------------------------------
  Pin-outs H-Bridge
  ---------------------------------------------------------------
*/
const int aMotor = 0; //Right Motor A
const int bMotor = 1; //Right Motor B
const int cMotor = 2; //Left Motor C
const int dMotor = 3; //Left Motor D
const int en1Motor = 4; // Right Motor
const int en2Motor = 5; // Left Motor
//const int s1 = A0; // Current sensor for right motor
//const int s2 = A1; // Current sensor for left motor
