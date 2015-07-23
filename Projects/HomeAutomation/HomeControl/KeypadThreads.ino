//------------------------------------------------------------------------------
// Thread for listening for keypad presses

// Declare a semaphore with an inital counter value of zero.
SEMAPHORE_DECL(cmdKeypadSem, 0);

// Needed global Keypad variables
int state = RELEASED;
uint8_t keyName = 0;

//Code that shows the the keypad connections to the arduino terminals
byte rowPins[4] = { 18, 19, 5, 4 }; //Rows 0 to 3
byte colPins[4] = { 17, 16, 15, 14 }; //Columns 0 to 3

const char keymap[4][4] =
{
  {
    'a', 'b', 'c', 'd'
  }
  ,
  {
    'e', 'f', 'g', 'h'
  }
  ,
  {
    'i', 'j', 'k', 'l'
  }
  ,
  {
    'm', 'n', 'o', 'p'
  }
};

const uint8_t keymapName[4][4] =
{
  {
    1, 2, 3, 4
  }
  ,
  {
    5, 6, 7, 8
  }
  ,
  {
    9, 10, 11, 12
  }
  ,
  {
    13, 14, 15, 16
  }
};

// Instance of the Keypad class
Keypad keypad = Keypad(makeKeymap(keymap), rowPins, colPins, 4, 4);

/**
 *  Gets the key name(number) of the button
 **/
uint8_t getKeyName(char keycode) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (keymap[i][j] == keycode) {
        return keymapName[i][j];
      }
    }
  }
}

static msg_t KeypadUpdaterThread(void *arg) {
  chThdSleepMilliseconds(3000); // Needs to wait for other threads to start or else Arduino might crash
  Serial.println(F("Keypad listener started"));
  keypad.addEventListener(keypadEvent); // Add an event listener for this keypad
  keypad.setHoldTime(10); // Makes sure "PRESSED" commands doesn't runs twice
  keypad.setDebounceTime(1); //Time until a new key is accepted

  while (1) {
    // Update keypad, needs to run in a loop for keypad library to work
    keyName = getKeyName(keypad.getKey());
    chThdSleepMilliseconds(5); // Keypad update frequency
  }
  return 0;
}

static msg_t KeypadCommandThread(void *arg)
{
  chThdSleepMilliseconds(2500); // Needs to wait for other threads to start or else Arduino might crash

  uint8_t lastKeyPressed = 0;

  while (1) {
    // Wait for signal from KeypadEvent, it sends a signal whenever keypad status changes
    chSemWait(&cmdKeypadSem);

    // Store last key pressed
    if (keyName != 0) {
      lastKeyPressed = keyName;
    }

    // Here are commands to run when a key is released
    if (state == RELEASED )
    {
      if (computerPowerButton == lastKeyPressed)
      {
        executeCommand = computerPowerButton;

        // Signal CommandExecutionerThread to run command
        chSemSignal(&cmdExSem);
      }
      lastKeyPressed = 0; // Clear last key saved
    }

    // Here are commands to run once when pressed
    else if (state == PRESSED )
    {
      if (MainLightsButton == keyName)
      {
        executeCommand = MainLightsButton;
        // Signal CommandExecutionerThread to run command
        chSemSignal(&cmdExSem);
      }
      else if (paintingLightsButton == keyName)
      {
        executeCommand = paintingLightsButton;
        // Signal CommandExecutionerThread to run command
        chSemSignal(&cmdExSem);
      }
      else if (computerPowerButton == keyName)
      {
        executeCommand = computerPowerButton;
        // Signal CommandExecutionerThread to run command
        chSemSignal(&cmdExSem);
      }
      else if (speakerPowerButton == keyName)
      {
        executeCommand = speakerPowerButton;
        // Signal CommandExecutionerThread to run command
        chSemSignal(&cmdExSem);
      }
      else if (speakerMuteButton == keyName)
      {
        executeCommand = speakerMuteButton;
        // Signal CommandExecutionerThread to run command
        chSemSignal(&cmdExSem);
      }
      else if (speakerModeButton == keyName)
      {
        executeCommand = speakerModeButton;
        // Signal CommandExecutionerThread to run command
        chSemSignal(&cmdExSem);
      }
    }
    // Commands to run while holding
    while (state == HOLD) {
      if (speakerUpVolButton == lastKeyPressed)
      {
        executeCommand = speakerUpVolButton;

        // Signal CommandExecutionerThread to run command
        chSemSignal(&cmdExSem);
      }
      else if (speakerDownVolButton == lastKeyPressed)
      {
        executeCommand = speakerDownVolButton;

        // Signal CommandExecutionerThread to run command
        chSemSignal(&cmdExSem);
      }
      chThdSleepMilliseconds(150);
    }
  }
  return 0;
}

/**
 *  This function is an event which only runs when the key state is changed
 **/
void keypadEvent(KeypadEvent key) {
  switch (keypad.getState()) {
    case PRESSED:
      Serial.println(F("PRESSED"));
      state = PRESSED;
      chSemSignal(&cmdKeypadSem);
      break;

    case HOLD:
      state = HOLD;
      Serial.println(F("HOLD"));
      chSemSignal(&cmdKeypadSem);
      break;

    case RELEASED:
      Serial.println(F("RELEASED"));
      state = RELEASED;
      chSemSignal(&cmdKeypadSem);
      break;
  }
}
