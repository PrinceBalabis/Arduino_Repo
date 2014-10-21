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
  {4, 8, 12, 16},
  {3, 7, 11, 15},
  {2, 6, 10, 14},
  {1, 5, 9, 13}
};

//Code that shows the the keypad connections to the arduino terminals
byte rowPins[4] = {9, 8, 7, 6}; //Rows 0 to 3
byte colPins[4] = {5, 4, 3, 2}; //Columns 0 to 3

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