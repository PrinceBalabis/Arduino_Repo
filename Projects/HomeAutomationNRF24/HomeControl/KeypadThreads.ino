//------------------------------------------------------------------------------
// Thread for listening for keypad presses

// Declare a semaphore with an inital counter value of zero.
SEMAPHORE_DECL(cmdKeypadSem, 0);

// Needed global Keypad variables
static int state = RELEASED;
static char keyName = 'z';

//Code that shows the the keypad connections to the arduino terminals
byte rowPins[4] = { 8, 7, 6, 5 }; //Rows 0 to 3
byte colPins[4] = { 12, 11, 10, 9 }; //Columns 0 to 3

const char keymap[4][4] =
{
  {
    '1', '2', '3', 'A'
  }
  ,
  {
    '4', '5', '6', 'B'
  }
  ,
  {
    '7', '8', '9', 'C'
  }
  ,
  {
    '*', '0', '#', 'D'
  }
};

//const uint8_t keymapName[4][4] =
//{
//  {
//    1, 2, 3, 4
//  }
//  ,
//  {
//    5, 6, 7, 8
//  }
//  ,
//  {
//    9, 10, 11, 12
//  }
//  ,
//  {
//    13, 14, 15, 16
//  }
//};

// Instance of the Keypad class
Keypad keypad = Keypad(makeKeymap(keymap), rowPins, colPins, 4, 4);

/**
    Gets the key name(number) of the button
 **/
//uint8_t getKeyName(char keycode) {
//  for (int i = 0; i < 4; i++) {
//    for (int j = 0; j < 4; j++) {
//      if (keymap[i][j] == keycode) {
//        return keymapName[i][j];
//      }
//    }
//  }
//}

NIL_WORKING_AREA(keypadUpdaterThread, 150); // 64 bytes works great
NIL_THREAD(KeypadUpdaterThread, arg) {
  Serial.println(F("Started KeypadUpdaterThread thread"));

  keypad.addEventListener(keypadEvent); // Add an event listener for this keypad
  keypad.setHoldTime(10); // Makes sure "PRESSED" commands doesn't runs twice
  keypad.setDebounceTime(1); //Time until a new key is accepted

  while (1) {
    // Update keypad, needs to run in a loop for keypad library to work
    keypad.getKey();
    nilThdSleepMilliseconds(KEYPAD_UPDATE_TIME); // Keypad update frequency
  }
}

NIL_WORKING_AREA(keypadCommandThread, 50); // -12 bytes works great
NIL_THREAD(KeypadCommandThread, arg)
{
  Serial.println(F("Started KeypadCommandThread thread"));
  while (1) {
    // Wait for signal from KeypadEvent, it sends a signal whenever keypad status changes
    nilSemWait(&cmdKeypadSem);

    // Here are commands to run once when PRESSED
    if (state == PRESSED )
    {
      switch (keyName) {
        case BUTTON_MAINLIGHTS_TOGGLE:
          executeCommand(keyName, COMMANDEXECUTIONER_MSGORIGIN_KEYPAD);
          break;
        case BUTTON_PAINTINGLIGHTS_TOGGLE:
          executeCommand(keyName, COMMANDEXECUTIONER_MSGORIGIN_KEYPAD);
          break;
        case BUTTON_PC_POWER:
          executeCommand(keyName, COMMANDEXECUTIONER_MSGORIGIN_KEYPAD);
          break;
        case BUTTON_PC_SLEEP:
          executeCommand(keyName, COMMANDEXECUTIONER_MSGORIGIN_KEYPAD);
          break;
        case BUTTON_SPEAKER_POWER:
          executeCommand(keyName, COMMANDEXECUTIONER_MSGORIGIN_KEYPAD);
          break;
        case BUTTON_SPEAKER_MUTE:
          executeCommand(keyName, COMMANDEXECUTIONER_MSGORIGIN_KEYPAD);
          break;
        case BUTTON_SPEAKER_MODE:
          executeCommand(keyName, COMMANDEXECUTIONER_MSGORIGIN_KEYPAD);
          break;
      }
    }

    // Here are commands to run when a key is RELEASED
    else if (state == RELEASED )
    {
      switch (keyName) {
        case BUTTON_PC_POWER:
          executeCommand(keyName, COMMANDEXECUTIONER_MSGORIGIN_KEYPAD);
          break;
      }
    }

    // Commands to run while HOLDING a key down
    while (state == HOLD) {
      switch (keyName) {
        case BUTTON_SPEAKER_VOLUME_UP:
          executeCommand(keyName, COMMANDEXECUTIONER_MSGORIGIN_KEYPAD);
          break;
        case BUTTON_SPEAKER_VOLUME_DOWN:
          executeCommand(keyName, COMMANDEXECUTIONER_MSGORIGIN_KEYPAD);
          break;
      }
      // Some delay in order to execute hold commands in regular intervals
      nilThdSleepMilliseconds(KEYPAD_HOLD_UPDATE_TIME);
    }
  }
}

/**
    This function is an event which only runs when the key state is changed
 **/
void keypadEvent(KeypadEvent key) {
  //  keyName = getKeyName(key); // Save key which this event points to
  keyName = key;

  switch (keypad.getState()) {
    case PRESSED:
      Serial.print(F("Pressed key: "));
      Serial.println(key);
      state = PRESSED;
      nilSemSignal(&cmdKeypadSem);
      break;

    case HOLD:
      state = HOLD;
      Serial.print(F("Held key: "));
      Serial.println(key);
      nilSemSignal(&cmdKeypadSem);
      break;

    case RELEASED:
      Serial.print(F("Released key: "));
      Serial.println(key);
      state = RELEASED;
      nilSemSignal(&cmdKeypadSem);
      break;
  }
}
