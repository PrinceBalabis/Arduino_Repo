/*
 *  hardware needed: 940 nm IR LED with a resistor to pin 3
 *  NextBase takes about 9 seconds to boot
 *  Volume option is between 0 and 30 in value
 */

// Needed libraries
#include <CIRremote.h>
IRsend irsend;

#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();

#include <Keypad.h>

#include <EEPROM.h>

// EEPROM variables
int mainLightsAddress = 0; // EEPROM address 0

// Button pins
const int powerButton = 1;
const int upVolButton = 2;
const int downVolButton = 3;
const int muteButton = 4;
const int MainLightButton = 5;

// NEXTBASE IR codes
const unsigned long power = 0xFFC23D;
const unsigned long mute = 0xFF02FD;
const unsigned long upVolume = 0xFFF00F;
const unsigned long downVolume = 0xFF708F;

// 433 MHZ transmitter pin
const int transm433Pin = 12;

// Put 1 to enable serial, 0 to disable
const int serialEnabled = 0;

// Variables needed for button hold timers
unsigned long currentTimer = 0;
unsigned long previousTimer = 0;

int previousBtnChosen = 0;

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

//Code that shows the the keypad connections to the arduino terminals
byte rowPins[4] = {11, 10, 9, 8}; //Rows 0 to 3
byte colPins[4] = {7, 6, 5, 4}; //Columns 0 to 3

//initializes an instance of the Keypad class
Keypad keypad = Keypad(makeKeymap(keymap), rowPins, colPins, 4, 4);

int keyHold = 0;
char keypressed;
int keyName;

int getKeyName(char keycode) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (keymap[i][j] == keycode) {
        return keymapName[i][j];
      }
    }
  }
}

void setup()
{
  // Enable or not enable Serial depending on config
  serialSetup();

  // 433 MHz transmission setup
  switchesSetup();
  
  
}

void loop() {
  keypressed = keypad.waitForKey();
  keyName = getKeyName(keypressed);
  int state = 0;

  if (powerButton == keyName) {
    sendPowerCommand();
  }
  while (upVolButton == keyName && state != RELEASED) {
    sendUpVolCommand();
    state = getKeyState();
  }
  while (downVolButton == keyName && state != RELEASED) {
    sendDownVolCommand();
    state = getKeyState();
  }
  if (muteButton == keyName) {
    sendMuteCommand();
  }
  if (MainLightButton == keyName) {
    sendMainLightPing();
  }
  clearButton();
}


