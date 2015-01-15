//------------------------------------------------------------------------------
// Thread for listening for keypad presses

// Needed global Keypad variables
int state = RELEASED;

//Code that shows the the keypad connections to the arduino terminals
byte rowPins[4] = {
  18, 19, 5, 4 }; //Rows 0 to 3
byte colPins[4] = {
  17, 16, 15, 14 }; //Columns 0 to 3

char keymap[4][4] =
{
  {
    'a', 'b', 'c', 'd'        }
  ,
  {
    'e', 'f', 'g', 'h'        }
  ,
  {
    'i', 'j', 'k', 'l'         }
  ,
  {
    'm', 'n', 'o', 'p'         }
};

int keymapName[4][4] =
{
  {
    1, 2, 3, 4         }
  ,
  {
    5, 6, 7, 8         }
  ,
  {
    9, 10, 11, 12         }
  ,
  {
    13, 14, 15, 16         }
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

static msg_t Thread1(void *arg) {
  Serial.println(F("Keypad listener started"));
  keypad.addEventListener(keypadEvent); // Add an event listener for this keypad
  keypad.setHoldTime(10); // Makes sure "PRESSED" commands doesn't runs twice
  unsigned long previousTimer = 0;
  int previousState = 0;

  while (1) {
    // Update keypad, needs to run in a loop for keypad library to work
    uint8_t keyName = getKeyName(keypad.getKey()); 

    // This runs all the time when no key is pressed
    if(state == RELEASED ){
      keyName = 0; // Clear keyName if no button is pressed, this is to fix bug in library

      if(previousState != RELEASED) { // Runs just once after a button is released
        previousState = RELEASED;
        previousTimer = 0;
        setPCPowerSwitch(FALSE);
        Serial.println(F("No key is pressed, running cleanup"));
      }
    }
    // This runs when a key is pressed
    else if(state != RELEASED)
    {
      previousState = state;
    }


    // The different commands for the buttons
    if (nBPowerButton == keyName && state == PRESSED) // Run once
    { 
      toggleSpeakerPower();
    } 
    else if (nBMuteButton == keyName && state == PRESSED) // Run once
    { 
      toggleSpeakerMuteCommand();
    } 
    else if (nBUpVolButton == keyName && state != RELEASED) // "While holding"
    { 
      sendSpeakerUpVolCommand(previousTimer);
    }
    else if (nBDownVolButton == keyName && state != RELEASED) // "While holding"
    { 
      sendSpeakerDownVolCommand(previousTimer);
    }
    else if (pcPowerButton == keyName && state == PRESSED ) 
    { 
      setPCPowerSwitch(TRUE);
    }
    else if (lightDiningTableButton == keyName && state == PRESSED ) 
    { 
      toggleDiningTableSwitch();
    }
        else if (lightBedButton == keyName && state == PRESSED ) 
    { 
      Serial.println(F("Notifies the RF24 to send data"));
      // Lock access to data.
      chMtxLock(&dataMutex);

      // Copy tmp variables to shared data.
      dataX = 3; // Send 01 which is the code to toggle lights
      dataY = voiceRecog; // Send the receiver of the code which is the code to toggle lights

        // Unlock data access.
      chMtxUnlock();
    }
    else if (lightMainButton == keyName && state == PRESSED) 
    {
      Serial.println(F("Notifies the RF24 to send data"));
      // Lock access to data.
      chMtxLock(&dataMutex);

      // Copy tmp variables to shared data.
      dataX = 01; // Send 01 which is the code to toggle lights
      dataY = mainLights; // Send the receiver of the code which is the code to toggle lights

        // Unlock data access.
      chMtxUnlock();
    } 
    else if(dataX == diningTableOn && dataY == -1) // Asking to toggle Speaker
    {
      setDiningTableSwitchOn();
      Serial.println(F("Turned on dining table lights"));
      // Lock access to data.
      chMtxLock(&dataMutex);

      dataX = -1;
      dataY = -1;

      // Unlock data access.
      chMtxUnlock();
    }
    else if(dataX == diningTableOff && dataY == -1) // Asking to toggle Speaker
    {
      setDiningTableSwitchOff();
      Serial.println(F("Turned off dining table lights"));

      // Lock access to data.
      chMtxLock(&dataMutex);

      dataX = -1;
      dataY = -1;

      // Unlock data access.
      chMtxUnlock();
    }
    else if(dataX == diningTableToggle && dataY == -1) // Asking to toggle Speaker
    {
      toggleDiningTableSwitch();
      Serial.println(F("Toggled dining table lights"));

      // Lock access to data.
      chMtxLock(&dataMutex);

      dataX = -1;
      dataY = -1;

      // Unlock data access.
      chMtxUnlock();
    }
    else if(dataX == speakerPowerToggle && dataY == -1) // Asking to toggle Speaker
    {
      toggleSpeakerPower();

      // Lock access to data.
      chMtxLock(&dataMutex);

      dataX = -1;
      dataY = -1;

      // Unlock data access.
      chMtxUnlock();
    }
    else if(dataX == speakerPowerOn && dataY == -1) // Asking to turn on speaker
    {
      sendSpeakerPowerOnCommand();

      // Lock access to data.
      chMtxLock(&dataMutex);

      dataX = -1;
      dataY = -1;

      // Unlock data access.
      chMtxUnlock();
    }
    else if(dataX == speakerPowerOff && dataY == -1) // Asking to turn off speaker
    {
      sendSpeakerPowerOffCommand();

      // Lock access to data.
      chMtxLock(&dataMutex);

      dataX = -1;
      dataY = -1;

      // Unlock data access.
      chMtxUnlock();
    }

    else if(dataX == speakerVolumeUp && dataY == -1)
    {
      sendSpeakerUpVolCommandOnce();

      // Lock access to data.
      chMtxLock(&dataMutex);

      dataX = -1;
      dataY = -1;

      // Unlock data access.
      chMtxUnlock();
    }
    else if(dataX == speakerVolumeDown && dataY == -1)
    {
      sendSpeakerDownVolCommandOnce();

      // Lock access to data.
      chMtxLock(&dataMutex);

      dataX = -1;
      dataY = -1;

      // Unlock data access.
      chMtxUnlock();
    }
    else if(dataX == speakerMuteToggle && dataY == -1)
    {
      toggleSpeakerMuteCommand();

      // Lock access to data.
      chMtxLock(&dataMutex);

      dataX = -1;
      dataY = -1;

      // Unlock data access.
      chMtxUnlock();
    }
    else if(dataX == speakerMuteOn && dataY == -1)
    {
      sendSpeakerMuteOnCommand();

      // Lock access to data.
      chMtxLock(&dataMutex);

      dataX = -1;
      dataY = -1;

      // Unlock data access.
      chMtxUnlock();
    }
    else if(dataX == speakerMuteOff && dataY == -1)
    {
      sendSpeakerMuteOffCommand();

      // Lock access to data.
      chMtxLock(&dataMutex);

      dataX = -1;
      dataY = -1;

      // Unlock data access.
      chMtxUnlock();
    }

    chThdSleepMilliseconds(50); // Sleep to let other threads do some work
  } 
  return 0;
}

/**
 *  This function is an event which only runs when the key state is changed
 **/
void keypadEvent(KeypadEvent key){
  switch (keypad.getState()){

  case PRESSED:
    Serial.println(F("PRESSED"));    
    state = PRESSED;
    break;

  case HOLD:
    state = HOLD;
    break;

  case RELEASED:
    Serial.println(F("RELEASED"));
    state = RELEASED;  
    break;
  }
}


