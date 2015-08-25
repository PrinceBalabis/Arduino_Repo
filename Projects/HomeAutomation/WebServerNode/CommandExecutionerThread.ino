/**
 ** CommandExecutioner thread
 ** Executes commands
 **/

static bool commandOrigin = 0;
static int32_t commandToExecute = 0;

// Declare a semaphore with an inital counter value of zero.
SEMAPHORE_DECL(cmdExSem, 0);

NIL_WORKING_AREA(commandExecutioner, 100); // bytes works great
NIL_THREAD(CommandExecutioner, arg)
{
  Serial.println(F("Started CommandExecutioner thread"));

  while (TRUE)
  {
    // Wait for signal to run
    nilSemWait(&cmdExSem);

    int32_t status = -999;
    bool sent = false;

    switch (commandOrigin) {
      case COMMANDEXECUTIONER_MSGORIGIN_LOCAL: // Command that came from the internet
        switch (commandToExecute) {
          case CMD_MAINLIGHTS_TOGGLE:
            Serial.println(F("Toggle Main Lights command!"));
            sent = homeNetwork.sendCommand(HOME_MAINLIGHTS_ID, HOME_MAINLIGHTS_CMD_MAINLIGHTS_TOGGLE);
            break;
          case QSN_MAINLIGHTS_STATUS:

            break;
          case CMD_APARTMENT_SHUTDOWN:
            Serial.println(F("Shut down apartment command!"));
            shutdownApartment();
            break;
          case CMD_APARTMENT_STARTUP:
            Serial.println(F("Start up apartment command!"));
            startupApartment();
            break;
          case CMD_APARTMENT_TOGGLE:
            Serial.println(F("Toggle apartment command!"));
            if (askApartmentStatus()) {
              shutdownApartment();
            } else {
              startupApartment();
            }
            break;
        }
        break;
      case COMMANDEXECUTIONER_MSGORIGIN_HOMENETWORK: // Command that came from HomeNetwork
        switch (commandToExecute) {
        }
        break;
    }


    Serial.print(F("Sent: "));
    Serial.print(sent);
    if (status != -999) { // If the status variable was used in the example, print it out
      Serial.print(F(" Status: "));
      Serial.print(status);
    }
    Serial.println();
  }
}

/*
 * Run this function to enable CommandExecutionerThread to run
 */
void executeCommand(int32_t _commandToExecute, bool _commandOrigin) {
  commandToExecute = _commandToExecute;
  commandOrigin = _commandOrigin;
  nilSemSignal(&cmdExSem);
}

void shutdownApartment() {
  homeNetwork.sendCommand(HOME_MAINLIGHTS_ID, HOME_MAINLIGHTS_CMD_MAINLIGHTS_OFF);
  homeNetwork.sendCommand(HOME_RF433MHZ_ID, HOME_RF433MHZ_CMD_PAINTINGLIGHTS_OFF);
  homeNetwork.sendCommand(HOME_SPEAKER_ID, HOME_SPEAKER_CMD_POWER_OFF);
  homeNetwork.sendCommand(HOME_PC_ID, HOME_PC_CMD_MONITORS_DISABLE);
  Serial.println(F("Shut down apartment!"));
}

void startupApartment() {
  homeNetwork.sendCommand(HOME_PC_ID, HOME_PC_CMD_MONITORS_ENABLE); // Turn on PC monitors!
  homeNetwork.sendCommand(HOME_MAINLIGHTS_ID, HOME_MAINLIGHTS_CMD_MAINLIGHTS_ON); // Turn on main lights!
  homeNetwork.sendCommand(HOME_SPEAKER_ID, HOME_SPEAKER_CMD_POWER_ON); // Turn on speaker!
  Serial.println(F("Started up apartment!"));
}

bool askApartmentStatus() {

  int32_t mainLightStatus;
  if (!homeNetwork.sendQuestion(HOME_MAINLIGHTS_ID, HOME_MAINLIGHTS_QSN_MAINLIGHTS_STATUS, &mainLightStatus)) {
    Serial.print(F("Couldn't get an answer from Main Lights Node!->"));
    mainLightStatus = 0;
  }
  else if (mainLightStatus) {
    Serial.print(F("Main lights are on!->"));
    return true;
  }


  int32_t paintingLightsStatus;
  if (!homeNetwork.sendQuestion(HOME_RF433MHZ_ID, HOME_RF433MHZ_QSN_PAINTINGLIGHTS_STATUS, &paintingLightsStatus)) {
    Serial.print(F("Couldn't get an answer from RF433MHz Node!->"));
    paintingLightsStatus = 0;
  }
  else if (paintingLightsStatus) {
    Serial.print(F("Painting lights are on!->"));
    return true;
  }

  int32_t speakerPowerSwitchStatus;
  if (!homeNetwork.sendQuestion(HOME_RF433MHZ_ID, HOME_RF433MHZ_QSN_SPEAKER_POWER_STATUS, &speakerPowerSwitchStatus)) {
    Serial.print(F("Couldn't get an answer from RF433MHz Node!->"));
    speakerPowerSwitchStatus = 0;
  }
  else if (speakerPowerSwitchStatus) {
    Serial.print(F("Speaker is on!->"));
    return true;
  }

  return false;

}
