/*
 *  This Sketch is to make a "universal home control".
 *  Controlling PC, lights, speaker & other home electronics
 *  Hardware needed: 
 *  - 940 nm IR LED with a resistor to pin 3
 *  - NPN transistor for PC Power switch
 *  - 433 MHz transmitter
 */

// Needed libraries & config
#include <CIRremote.h>
#include <RCSwitch.h>
#include <Keypad.h>
#include <EEPROM.h>
#include "cnf.h" // config file

// Needed glbal EEPROM variables
int mainLightsAddress = 0; // EEPROM address 0

// Needed glbal Keypad variables
unsigned long currentTimer = 0;
unsigned long previousTimer = 0;
int keyHold = 0;
char keypressed;
int keyName;
int previousBtnChosen = 0;

// Instance of the IRsend class
IRsend irsend;

//Code that shows the the keypad connections to the arduino terminals
byte rowPins[4] = {11, 10, 9, 8}; //Rows 0 to 3
byte colPins[4] = {7, 6, 5, 4}; //Columns 0 to 3

char keymap[4][4] =
{
  {'a', 'b', 'c', 'd'},
  {'e', 'f', 'g', 'h'},
  {'i', 'j', 'k', 'l'},
  {'m', 'n', 'o', 'p'}
};

int keymapName[4][4] =
{
  {4, 8, 12, 16},
  {3, 7, 11, 15},
  {2, 6, 10, 14},
  {1, 5, 9, 13}
};

// Instance of the Keypad class
Keypad keypad = Keypad(
                  makeKeymap(keymap), rowPins, colPins, 4, 4
                );



// Instance of the RCSwitch class
RCSwitch mySwitch = RCSwitch();

/*
*  Gets the key name(number) of the button
*/
int getKeyName(char keycode) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (keymap[i][j] == keycode) {
        return keymapName[i][j];
      }
    }
  }
}

/*
* Main setup functin which calls other setup functions
*/
void setup()
{
  // Enable or not enable Serial depending on config
  serialSetup();

  // 433 MHz transmission setup
  switchesSetup();

  // PC Power switch setup
  pcPowerSetup();
}

/*
* Main loop function which listens for button presses
*/
void loop() {
  keypressed = keypad.waitForKey(); // Program is frozen until button-press
  keyName = getKeyName(keypressed); // Get keyname/keynumber
  int state = 0; // Private variable to store button state

  if (nBPowerButton == keyName) {
    sendPowerCommand();
  }
  while (nBUpVolButton == keyName && state != RELEASED) {
    sendUpVolCommand();
    state = getKeyState();
  }
  while (nBDownVolButton == keyName && state != RELEASED) {
    sendDownVolCommand();
    state = getKeyState();
  }
  if (nBMuteButton == keyName) {
    sendMuteCommand();
  }
  if (lightMainButton == keyName) {
    sendMainLightPing();
  }
  if (pcPowerButton == keyName) {
    sendPCPowerPing();
  }
  clearButton();
}


