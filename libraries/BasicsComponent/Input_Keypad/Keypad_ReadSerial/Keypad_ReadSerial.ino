/**
* Just connect the keypad directly between digital pin 11 and 3
* Don't use pin D12 for the keypad! It's bugged!
*/

#include <Keypad.h>

char keymap[4][4] =
{
  {'a', 'b', 'c', 'd'},
  {'e', 'f', 'g', 'h'},
  {'i', 'j', 'k', 'l'},
  {'m', 'n', 'o', 'p'}
};

int keymapName[4][4] =
{
  {1, 2, 3, 4},
  {5, 6, 7, 8},
  {9, 10, 11, 12},
  {13, 14, 15, 16}
};

//Code that shows the the keypad connections to the arduino terminals
byte rowPins[4] = {7, 6, 5, 4}; //Rows 0 to 3
byte colPins[4] = {8, 9, 10, 11}; //Columns 0 to 3

//initializes an instance of the Keypad class
Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, 4, 4);

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
  Serial.begin(9600);
}

//If key is pressed, this key is stored in 'keypressed' variable
//If key is not equal to 'NO_KEY', then this key is printed out
//if count=17, then count is reset back to 0 (this means no key is pressed during the whole keypad scan process
void loop()
{
  char keypressed = myKeypad.getKey();
  if (keypressed != NO_KEY)
  {
    Serial.println(getKeyName(keypressed));
  }
}
