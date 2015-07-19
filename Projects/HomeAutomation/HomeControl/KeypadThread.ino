//------------------------------------------------------------------------------
// Thread for listening for keypad presses

// Needed global Keypad variables
int state = RELEASED;

//Code that shows the the keypad connections to the arduino terminals
byte rowPins[4] = {
  18, 19, 5, 4
}; //Rows 0 to 3
byte colPins[4] = {
  17, 16, 15, 14
}; //Columns 0 to 3

char keymap[4][4] =
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

int keymapName[4][4] =
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
Keypad keypad = Keypad(
                  makeKeymap(keymap), rowPins, colPins, 4, 4
                );

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

static msg_t KeypadThread(void *arg) {
  Serial.println(F("Keypad listener started"));
  keypad.addEventListener(keypadEvent); // Add an event listener for this keypad
  keypad.setHoldTime(10); // Makes sure "PRESSED" commands doesn't runs twice
  keypad.setDebounceTime(1); //Time untill a new key is accepted
  int lastState = 0;
  unsigned long previousTimer = 0;

  while (1) {
    // Update keypad, needs to run in a loop for keypad library to work
    uint8_t keyName = getKeyName(keypad.getKey());

    // This runs all the time when no key is pressed
    if (state == RELEASED ) {
      keyName = 0; // Clear keyName if no button is pressed, this is to fix bug in library

      if (lastState != RELEASED) { // Runs just once after a button is released
        lastState = RELEASED;
        previousTimer = 0;
        setPCPowerSwitch(FALSE);
        Serial.println(F("No key is pressed, running cleanup"));
      }
    }
    // This runs when a key is pressed
    else if (state != RELEASED)
    {
      lastState = state;
    }
    // The different commands for the buttons
    if (nBPowerButton == keyName && state == PRESSED) // Run once
    {
      //toggleSpeakerPower();
    }
    else if (nBMuteButton == keyName && state == PRESSED) // Run once
    {
      //toggleSpeakerMuteCommand();
    }
    else if (nBUpVolButton == keyName && state != RELEASED) // "While holding"
    {
      //sendSpeakerUpVolCommand(previousTimer);
    }
    else if (nBDownVolButton == keyName && state != RELEASED) // "While holding"
    {
      //sendSpeakerDownVolCommand(previousTimer);
    }
    else if (pcPowerButton == keyName && state == PRESSED )
    {
      executeCommand = pcPowerButton;

      // Signal CommandExecutionerThread to run command
      chSemSignal(&cmdExSem);
    }
    else if (lightDiningTableButton == keyName && state == PRESSED )
    {
      executeCommand = lightDiningTableButton;

      // Signal CommandExecutionerThread to run command
      chSemSignal(&cmdExSem);
    }
    else if (lightMainButton == keyName && state == PRESSED)
    {
      executeCommand = lightMainButton;

      // Signal CommandExecutionerThread to run command
      chSemSignal(&cmdExSem);
    }
    chThdSleepMilliseconds(50); // Sleep to let other threads do some work
  }
}

/**
 *  This function is an event which only runs when the key state is changed
 **/
void keypadEvent(KeypadEvent key) {
  //  switch (keypad.getState()) {
  state = keypad.getState();
  //    case PRESSED:
  //      Serial.println(F("PRESSED"));
  //      state = PRESSED;
  //      break;
  //
  //    case HOLD:
  //      state = HOLD;
  //      break;
  //
  //    case RELEASED:
  //      Serial.println(F("RELEASED"));
  //      state = RELEASED;
  //      break;
  //  }
}

























