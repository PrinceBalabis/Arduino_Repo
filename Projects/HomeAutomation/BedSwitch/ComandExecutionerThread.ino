/**
 ** CommandExecutioner thread
 ** Executes commands
 **/

static uint8_t commandToExecute = 0;

// Declare a semaphore with an inital counter value of zero.
SEMAPHORE_DECL(cmdExSem, 0);

NIL_WORKING_AREA(commandExecutioner, 130); //100 bytes works great
NIL_THREAD(CommandExecutioner, arg)
{
  Serial.println(F("CommandExecutioner thread started"));

  while (1)
  {
    // Wait for signal from either HNListenThread or Keypad Thread to run this loop
    nilSemWait(&cmdExSem);

    // Check apartment status
    bool apartmentStatus = askApartmentStatus();

    switch (commandToExecute) {
      case CMD_UPDATE_LED: // Update LED Status
        // What happens when apartment is either on or off
        if (apartmentStatus && !ledStatus) {
          setLED(HIGH);
          Serial.println(F("Apartment just went online, switching LED on!"));
        } else if (!apartmentStatus && ledStatus) {
          setLED(LOW);
          Serial.println(F("Apartment just went offline, switching LED off!"));
        } else if (apartmentStatus) {
          Serial.println(F("Apartment still ONLINE"));
        } else if (!apartmentStatus) {
          Serial.println(F("Apartment still OFFLINE"));
        }
        break;
      case CMD_APARTMENT_TOGGLE: // Button pressed, toggle apartment
        if (askApartmentStatus()) {
          shutdownApartment();
          setLED(LOW);
          Serial.println("Shut down apartment");
        } else {
          startupApartment();
          setLED(HIGH);
          Serial.println("Started up apartment");
        }
        break;
    }
  }
}

/*
 * Run this function to enable CommandExecutionerThread to run
 */
void executeCommand(uint8_t _commandToExecute) {
  commandToExecute = _commandToExecute;
  nilSemSignal(&cmdExSem);
}

// Returns true if a source is on, returns false if all is off
bool askApartmentStatus() {

  int32_t mainLightStatus;
  if (!homeNetwork.sendQuestion(HOME_MAINLIGHTS_ID, HOME_MAINLIGHTS_QSN_MAINLIGHTS_STATUS, &mainLightStatus, HOME_QUESTION_TIMEOUT)) {
    Serial.println(F("Couldn't get an answer from Main Lights Node!"));
    mainLightStatus = 0;
  }
  else if (mainLightStatus) {
    Serial.println(F("Main lights are on!->"));
    return true;
  }


  int32_t paintingLightsStatus;
  if (!homeNetwork.sendQuestion(HOME_RF433MHZ_ID, HOME_RF433MHZ_QSN_PAINTINGLIGHTS_STATUS, &paintingLightsStatus, HOME_QUESTION_TIMEOUT)) {
    Serial.println(F("Couldn't get an answer from RF433MHz Node!"));
    paintingLightsStatus = 0;
  }
  else if (paintingLightsStatus) {
    Serial.println(F("Painting lights are on!->"));
    return true;
  }

  int32_t speakerPowerSwitchStatus;
  if (!homeNetwork.sendQuestion(HOME_RF433MHZ_ID, HOME_RF433MHZ_QSN_SPEAKER_POWER_STATUS, &speakerPowerSwitchStatus, HOME_QUESTION_TIMEOUT)) {
    Serial.println(F("Couldn't get an answer from RF433MHz Node!"));
    speakerPowerSwitchStatus = 0;
  }
  else if (speakerPowerSwitchStatus) {
    Serial.println(F("Speaker is on!->"));
    return true;
  }

  return false;

}

bool shutdownApartment() {
  homeNetwork.sendCommand(HOME_MAINLIGHTS_ID, HOME_MAINLIGHTS_CMD_MAINLIGHTS_OFF);
  homeNetwork.sendCommand(HOME_RF433MHZ_ID, HOME_RF433MHZ_CMD_PAINTINGLIGHTS_OFF);
  homeNetwork.sendCommand(HOME_SPEAKER_ID, HOME_SPEAKER_CMD_POWER_OFF);
  homeNetwork.sendCommand(HOME_PC_ID, HOME_PC_CMD_MONITORS_DISABLE);
}

bool startupApartment() {
  homeNetwork.sendCommand(HOME_PC_ID, HOME_PC_CMD_MONITORS_ENABLE); // Turn on PC monitors!
  homeNetwork.sendCommand(HOME_MAINLIGHTS_ID, HOME_MAINLIGHTS_CMD_MAINLIGHTS_ON); // Turn on main lights!

  //nilThdSleepMilliseconds(4000); // Give some time for PC to wake before doing any more PC controls
  //homeNetwork.sendCommand(HOME_PC_ID, HOME_PC_CMD_SPOTIFY_PLAYLIST_WORKOUT); // Start Workout Playlist!!

  //nilThdSleepMilliseconds(5000); // Give some time for Spotify to start playlist
  homeNetwork.sendCommand(HOME_SPEAKER_ID, HOME_SPEAKER_CMD_POWER_ON); // Turn on speaker!
}
