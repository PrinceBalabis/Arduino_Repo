#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'S1', 'S2', 'S3', 'S4'},
  {'S5', 'S6', 'S7', 'S8'},
  {'S9', 'A', 'B', 'C'},
  {'D', 'E', 'F', 'G'}
};
byte colPins[ROWS] = {5, 4, 3, 2}; //connect to column pinouts
byte rowPins[COLS] = {6, 7, 8, 9}; //connect to row pinouts

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  Serial.begin(9600);
}

void loop() {
  char key = keypad.getKey();

  if (key != NO_KEY) {
    Serial.println(key);
  }
}
