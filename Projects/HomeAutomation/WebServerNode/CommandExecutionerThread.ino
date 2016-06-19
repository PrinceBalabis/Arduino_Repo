/**
 ** CommandExecutioner thread
 ** Executes commands
 **/

static bool commandOrigin = 0;
static int32_t commandToExecute = 0;

// Declare a semaphore with an inital counter value of zero.
SEMAPHORE_DECL(cmdExSem, 0);

NIL_WORKING_AREA(commandExecutioner, 140); // bytes works great
NIL_THREAD(CommandExecutioner, arg)
{
  Serial.println(F("Started CommandExecutioner thread"));

  while (TRUE)
  {
    executionerIdle = 1;
    // Wait for signal to run
    nilSemWait(&cmdExSem);
    executionerIdle = 0;


    switch (commandOrigin) {
      case COMMANDEXECUTIONER_MSGORIGIN_LOCAL: // Command that came from the internet
        switch (commandToExecute) {
          case QSN_MAINLIGHTS_STATUS:
            Serial.println(F("Status of Central Lights!"));
            homeNetwork.sendQuestion(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_QSN_MAINLIGHTS_STATUS, &answer, 200);
            break;
          case CMD_MAINLIGHTS_TOGGLE:
            Serial.println(F("Toggle Central Lights command!"));
            homeNetwork.sendCommand(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_CMD_MAINLIGHTS_TOGGLE);
            homeNetwork.sendQuestion(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_QSN_MAINLIGHTS_STATUS, &answer, 200);
            break;
          case CMD_MAINLIGHTS_ON:
            Serial.println(F("Turn Central Lights command on!"));
            homeNetwork.sendCommand(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_CMD_MAINLIGHTS_ON);
            homeNetwork.sendQuestion(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_QSN_MAINLIGHTS_STATUS, &answer, 200);
            break;
          case CMD_MAINLIGHTS_OFF:
            Serial.println(F("Turn Central Lights command off!"));
            homeNetwork.sendCommand(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_CMD_MAINLIGHTS_OFF);
            homeNetwork.sendQuestion(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_QSN_MAINLIGHTS_STATUS, &answer, 200);
            break;
          case QSN_PAINTINGLIGHTS_STATUS:
            Serial.println(F("Painting Lights Status Command!"));
            homeNetwork.sendQuestion(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_QSN_PAINTINGLIGHTS_STATUS, &answer, 200);
            break;
          case CMD_PAINTINGLIGHTS_TOGGLE:
            Serial.println(F("Painting Lights Toggle Command!"));
            homeNetwork.sendCommand(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_CMD_PAINTINGLIGHTS_TOGGLE);
            homeNetwork.sendQuestion(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_QSN_PAINTINGLIGHTS_STATUS, &answer, 200);
            break;
          case CMD_PAINTINGLIGHTS_ON:
            Serial.println(F("Painting Lights command on!"));
            homeNetwork.sendCommand(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_CMD_PAINTINGLIGHTS_ON);
            homeNetwork.sendQuestion(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_QSN_PAINTINGLIGHTS_STATUS, &answer, 200);
            break;
          case CMD_PAINTINGLIGHTS_OFF:
            Serial.println(F("Painting Lights command off!"));
            homeNetwork.sendCommand(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_CMD_PAINTINGLIGHTS_OFF);
            homeNetwork.sendQuestion(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_QSN_PAINTINGLIGHTS_STATUS, &answer, 200);
            break;
          case QSN_APARTMENT_STATUS:
            Serial.println(F("Checking Apartment Status"));
            answer = askApartmentStatus();
            break;
          case CMD_APARTMENT_SHUTDOWN:
            Serial.println(F("Shut-down Apartment Command!"));
            shutdownApartment();
            answer = 0;
            break;
          case CMD_APARTMENT_STARTUP:
            Serial.println(F("Start-up Apartment Command!"));
            startupApartment();
            answer = 1;
            break;
          case CMD_APARTMENT_TOGGLE:
            Serial.println(F("Toggle Apartment Command!"));
            if (askApartmentStatus()) {
              shutdownApartment();
              answer = 0;
            } else {
              startupApartment();
              answer = 1;
            }
            break;
          //          case CMD_SPEAKER_MUTE_TOGGLE:
          //            Serial.println(F("Speaker Mute Toggle Command!"));
          //            homeNetwork.sendCommand(HOME_SPEAKER_ID, HOME_SPEAKER_CMD_MUTE_TOGGLE);
          //            break;
          //          case CMD_SPEAKER_MODE_TOGGLE:
          //            Serial.println(F("Speaker Mode Toggle Command!"));
          //            homeNetwork.sendCommand(HOME_SPEAKER_ID, HOME_SPEAKER_CMD_MODE_TOGGLE);
          //            break;
          case CMD_APARTMENT_MOOD_TOGGLE:
            Serial.println(F("Apartment Mood Toggle Command!"));
            toggleApartmentMood();
            break;
          case QSN_APARTMENT_MOOD_STATUS:
            Serial.println(F("Checking Apartment Mood!"));
            askApartmentMood();
            break;

        }
        break;
      case COMMANDEXECUTIONER_MSGORIGIN_HOMENETWORK: // Command that came from HomeNetwork
        switch (commandToExecute) {
        }
        break;
    }
  }
}

/*
   Run this function to enable CommandExecutionerThread to run
*/
void executeCommand(int32_t _commandToExecute, bool _commandOrigin) {
  commandToExecute = _commandToExecute;
  commandOrigin = _commandOrigin;
  nilSemSignal(&cmdExSem);
}

void shutdownApartment() {
  homeNetwork.sendCommand(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_CMD_MAINLIGHTS_OFF);
  homeNetwork.sendCommand(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_CMD_PAINTINGLIGHTS_OFF);
  //  homeNetwork.sendCommand(HOME_SPEAKER_ID, HOME_SPEAKER_CMD_POWER_OFF);
  Serial.println(F("Shut-down Apartment!"));
}

void startupApartment() {
  homeNetwork.sendCommand(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_CMD_MAINLIGHTS_ON);
  //  homeNetwork.sendCommand(HOME_SPEAKER_ID, HOME_SPEAKER_CMD_POWER_ON); // Turn on speaker!
  //  homeNetwork.sendCommand(HOME_HOMECONTROL_ID, HOME_HOMECONTROL_CMD_PC_ON); // Turn on PC!
  Serial.println(F("Started-up Apartment!"));
}

bool askApartmentStatus() {
  if (!homeNetwork.sendQuestion(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_QSN_MAINLIGHTS_STATUS, &answer, 200)) {
    Serial.print(F("Couldn't get an answer from Central Lights Node!->"));
  }
  else if (answer) {
    Serial.print(F("Central lights are on!->"));
    return true;
  }

  else if (!homeNetwork.sendQuestion(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_QSN_PAINTINGLIGHTS_STATUS, &answer, 200)) {
    Serial.print(F("Couldn't get an answer from RF433MHz Node!->"));
  }
  else if (answer) {
    Serial.print(F("Painting lights are on!->"));
    return true;
  }

  return false;
}

bool askApartmentMood() {

  if (!homeNetwork.sendQuestion(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_QSN_MAINLIGHTS_STATUS, &answer, 200)) {
    Serial.print(F("Couldn't get an answer from Lights Node!->"));
    answer = 1;
    return 1;
  }
  else if (answer) {
    Serial.print(F("Central lights are on!->"));
    answer = 0;
    return 0;
  }
  else if (!homeNetwork.sendQuestion(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_QSN_PAINTINGLIGHTS_STATUS, &answer, 200)) {
    Serial.print(F("Couldn't get an answer from Lights Node!->"));
    answer = 1;
    return 1;
  }
  else if (answer) {
    Serial.print(F("Painting lights are on!->"));
    answer = 1;
    return 1;
  } else {
    //If both Main lights and painting lights are off
    answer = 0;
    return 0;
  }
}


void toggleApartmentMood() {
  if (!askApartmentMood()) {
    homeNetwork.sendCommand(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_CMD_MAINLIGHTS_OFF);
    homeNetwork.sendCommand(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_CMD_PAINTINGLIGHTS_ON);
    answer = 1;
  }
  else {
    homeNetwork.sendCommand(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_CMD_MAINLIGHTS_ON);
    homeNetwork.sendCommand(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_CMD_PAINTINGLIGHTS_OFF);
    answer = 0;
  }
}

