/**
 ** CommandExecutioner thread
 ** Executes commands
 **/

bool commandOrigin = 0;
int32_t commandToExecute = 0;

// Declare a semaphore with an inital counter value of zero.
SEMAPHORE_DECL(cmdExSem, 0);

NIL_WORKING_AREA(commandExecutioner, 130); //65 bytes works great
NIL_THREAD(CommandExecutioner, arg)
{
  Serial.println(F("Started CommandExecutioner thread"));

  while (1)
  {
    // Wait for signal from either HNListenThread or Keypad Thread to continue
    nilSemWait(&cmdExSem);

    bool sent = true;

    switch (commandOrigin) {
      case COMMANDEXECUTIONER_MSGORIGIN_HOMENETWORK: // If the command is from Home Network
        switch (commandToExecute) {
          case HOME_HOMECONTROL_CMD_PC_ON:
            setPCPowerSwitchOnMomentarily();
            Serial.println(F("Turned PC on"));
            break;
        }
        break;
      case COMMANDEXECUTIONER_MSGORIGIN_LOCAL: // If the command is from local origin(keypad)
        switch (commandToExecute) {
          case BUTTON_PC_SPOTIFYPLAYLIST_WORKOUT:
            sent = homeNetwork.sendCommand(HOME_WEBSERVER_ID, HOME_WEBSERVER_CMD_SPOTIFY_WORKOUT);
            Serial.print(F("Starting Spotify Workout Playlist"));
            break;
          case BUTTON_PC_SPOTIFYPLAYLIST_DINNER:
            sent = homeNetwork.sendCommand(HOME_WEBSERVER_ID, HOME_WEBSERVER_CMD_SPOTIFY_DINNER);
            Serial.print(F("Starting Spotify Dinner Playlist"));
            break;
          case BUTTON_PC_SPOTIFYPLAYLIST_CHILL:
            sent = homeNetwork.sendCommand(HOME_WEBSERVER_ID, HOME_WEBSERVER_CMD_SPOTIFY_CHILL);
            Serial.print(F("Starting Spotify Chill Playlist"));
            break;
          case BUTTON_PC_SPOTIFYPLAYLIST_WORK:
            sent = homeNetwork.sendCommand(HOME_WEBSERVER_ID, HOME_WEBSERVER_CMD_SPOTIFY_WORK);
            Serial.print(F("Starting Spotify Work Playlist"));
            break;
          case BUTTON_MAINLIGHTS_TOGGLE:
            sent = homeNetwork.sendCommand(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_CMD_MAINLIGHTS_TOGGLE);
            Serial.print(F("Toggling Main Lights"));
            break;
          case BUTTON_PAINTINGLIGHTS_TOGGLE:
            sent = homeNetwork.sendCommand(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_CMD_PAINTINGLIGHTS_TOGGLE, 1, 1000); // Painting lights node takes a while to respond due to 433MHz commands taking forever to send, thats why its best to just retry once, in order to make sure it doesnt get spammed with retries
            Serial.print(F("Toggling Painting Lights"));
            break;
          case BUTTON_SPEAKER_POWER:
            sent = homeNetwork.sendCommand(HOME_SPEAKER_ID, HOME_SPEAKER_CMD_POWER_TOGGLE);
            Serial.print(F("Toggling Speaker Power"));
            break;
          case BUTTON_SPEAKER_VOLUME_UP:
            sent = homeNetwork.sendCommand(HOME_SPEAKER_ID, HOME_SPEAKER_CMD_VOLUME_UP);
            Serial.print(F("Increasing Speaker Volume"));
            break;
          case BUTTON_SPEAKER_VOLUME_DOWN:
            sent = homeNetwork.sendCommand(HOME_SPEAKER_ID, HOME_SPEAKER_CMD_VOLUME_DOWN);
            Serial.print(F("Decreasing Speaker Volume"));
            break;
          case BUTTON_SPEAKER_MUTE:
            sent = homeNetwork.sendCommand(HOME_SPEAKER_ID, HOME_SPEAKER_CMD_MUTE_TOGGLE);
            Serial.print(F("Toggling Speaker Mute"));
            break;
          case BUTTON_SPEAKER_MODE:
            toggleAudioSwitch();
            Serial.print(F("Toggling Speaker Mode"));
            break;
          case BUTTON_PC_POWER:
            togglePCPowerSwitch();
            Serial.print(F("Toggling PC Power Switch"));
            break;
          case BUTTON_PC_MONITOR_DISABLE:
            sent = homeNetwork.sendCommand(HOME_WEBSERVER_ID, HOME_WEBSERVER_CMD_MONITOR_DISABLE);
            Serial.print(F("Disabling Monitors"));
            break;
        }
    }

    if (sent) {
      Serial.println(F(".. Done!"));
    } else if (!sent) {
      Serial.println(F(".. Couldn't send!"));
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
