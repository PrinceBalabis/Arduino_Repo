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

  while (1)
  {
    // Wait for signal to run
    nilSemWait(&cmdExSem);

    switch (commandOrigin) {
      case COMMANDEXECUTIONER_MSGORIGIN_LOCAL: // Command that came from the internet
        switch (commandToExecute) {
          case CMD_MAINLIGHTS_TOGGLE:
            Serial.println(F("Toggle Main Lights command!"));
            homeNetwork.sendCommand(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_CMD_MAINLIGHTS_TOGGLE);
            break;
          case QSN_MAINLIGHTS_STATUS:

            break;
          case CMD_APARTMENT_SHUTDOWN:
            Serial.println(F("Shut-down Apartment Command!"));
            shutdownApartment();
            break;
          case CMD_APARTMENT_STARTUP:
            Serial.println(F("Start-up Apartment Command!"));
            startupApartment();
            break;
          case CMD_APARTMENT_TOGGLE:
            Serial.println(F("Toggle Apartment Command!"));
            if (askApartmentStatus()) {
              shutdownApartment();
            } else {
              startupApartment();
            }
            break;
          case CMD_PAINTINGLIGHTS_TOGGLE:
            Serial.println(F("Painting Lights Toggle Command!"));
            homeNetwork.sendCommand(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_CMD_PAINTINGLIGHTS_TOGGLE);
            break;
          case CMD_SPEAKER_MUTE_TOGGLE:
            Serial.println(F("Speaker Mute Toggle Command!"));
            homeNetwork.sendCommand(HOME_SPEAKER_ID, HOME_SPEAKER_CMD_MUTE_TOGGLE);
            break;
          case CMD_SPEAKER_MODE_TOGGLE:
            Serial.println(F("Speaker Mode Toggle Command!"));
            homeNetwork.sendCommand(HOME_SPEAKER_ID, HOME_SPEAKER_CMD_MODE_TOGGLE);
            break;
          case CMD_APARTMENT_MOOD_TOGGLE:
            Serial.println(F("Apartment Mood Toggle Command!"));
            toggleApartmentMood();
            break;
        }
        break;
      case COMMANDEXECUTIONER_MSGORIGIN_HOMENETWORK: // Command that came from HomeNetwork
        pauseWebserver = true;
        while (!webserverIsPaused)
          nilThdSleepMilliseconds(5); // Give time for webserver to pause

        switch (commandToExecute) {
          case HOME_WEBSERVER_CMD_MONITOR_DISABLE:
            if (!sendGetRequest(1, 192, 168, 1, 2, 5060)) {
              Serial.println(F("Couldnt connect to server!"));
            } else {
              Serial.println(F("Disabled Monitors!"));
            }
            break;
          case HOME_WEBSERVER_CMD_MONITOR_ENABLE:
            if (!sendGetRequest(2, 192, 168, 1, 2, 5060)) {
              Serial.println(F("Couldnt connect to server!"));
            } else {
              Serial.println(F("Enabled Monitors!"));
            }
            break;
          case HOME_WEBSERVER_CMD_SPOTIFY_CHILL:
            if (!sendGetRequest(3, 192, 168, 1, 2, 5060)) {
              Serial.println(F("Couldnt connect to server!"));
            } else {
              Serial.println(F("Started Spotify Chill Playlist!"));
            }
            break;
          case HOME_WEBSERVER_CMD_SPOTIFY_DINNER:
            if (!sendGetRequest(4, 192, 168, 1, 2, 5060)) {
              Serial.println(F("Couldnt connect to server!"));
            } else {
              Serial.println(F("Started Spotify Dinner Playlist!"));
            }
            break;
          case HOME_WEBSERVER_CMD_SPOTIFY_WORKOUT:
            if (!sendGetRequest(5, 192, 168, 1, 2, 5060)) {
              Serial.println(F("Couldnt connect to server!"));
            } else {
              Serial.println(F("Started Spotify Workout Playlist!"));
            }
            break;
          case HOME_WEBSERVER_CMD_SPOTIFY_WORK:
            if (!sendGetRequest(6, 192, 168, 1, 2, 5060)) {
              Serial.println(F("Couldnt connect to server!"));
            } else {
              Serial.println(F("Started Spotify Work Playlist!"));
            }
            break;
        }
        pauseWebserver = false;
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
  homeNetwork.sendCommand(HOME_SPEAKER_ID, HOME_SPEAKER_CMD_POWER_OFF);

  if (!sendGetRequest(1, 192, 168, 1, 2, 5060)) {
    Serial.println(F("Couldnt connect to server!"));
  } else {
    Serial.println(F("Disabled Monitors!"));
  }

  Serial.println(F("Shut-down Apartment!"));
}

void startupApartment() {
  homeNetwork.sendCommand(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_CMD_MAINLIGHTS_ON); // Turn on main lights!
  homeNetwork.sendCommand(HOME_SPEAKER_ID, HOME_SPEAKER_CMD_POWER_ON); // Turn on speaker!
  homeNetwork.sendCommand(HOME_HOMECONTROL_ID, HOME_HOMECONTROL_CMD_PC_ON); // Turn on PC!
  if (!sendGetRequest(2, 192, 168, 1, 2, 5060)) {
    Serial.println(F("Couldnt connect to server!"));
  } else {
    Serial.println(F("Enabled Monitors!"));
  }
  Serial.println(F("Started-up Apartment!"));
}

bool askApartmentStatus() {
  int32_t status;
  if (!homeNetwork.sendQuestion(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_QSN_MAINLIGHTS_STATUS, &status)) {
    Serial.print(F("Couldn't get an answer from Main Lights & 433MHz controller Node!->"));
  }
  else if (status) {
    Serial.print(F("Main lights are on!->"));
    return true;
  }

  if (homeNetwork.sendQuestion(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_QSN_PAINTINGLIGHTS_STATUS, &status)) {
    Serial.print(F("Painting lights are on!->"));
    return true;
  }

  if (!homeNetwork.sendQuestion(HOME_SPEAKER_ID, HOME_SPEAKER_QSN_POWER_STATUS, &status)) {
    Serial.print(F("Couldn't get an answer from Speaker Node!->"));
  }
  else if (status) {
    Serial.print(F("Speaker is on!->"));
    return true;
  }

  return false;
}

void toggleApartmentMood() {
  int32_t status;

  if (!homeNetwork.sendQuestion(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_QSN_MAINLIGHTS_STATUS, &status)) {
    Serial.print(F("Couldn't get an answer from Main Lights & 433MHz controller Node!->"));
  }
  else if (status) {
    Serial.print(F("Main lights are on!->"));
    homeNetwork.sendCommand(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_CMD_MAINLIGHTS_OFF);
    homeNetwork.sendCommand(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_CMD_PAINTINGLIGHTS_ON);
  }
  else if (status) {
    Serial.print(F("Painting lights are on!->"));
    homeNetwork.sendCommand(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_CMD_MAINLIGHTS_ON);
    homeNetwork.sendCommand(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_CMD_PAINTINGLIGHTS_OFF);
  } else {
    //If both Main lights and painting lights are off, toggle painting lights on
    homeNetwork.sendCommand(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_CMD_PAINTINGLIGHTS_ON);
  }
}

