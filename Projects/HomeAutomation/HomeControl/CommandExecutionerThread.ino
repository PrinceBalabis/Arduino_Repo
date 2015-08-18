/**
 ** CommandExecutioner thread
 ** Executes commands
 **/

static bool commandOrigin = 0;
static int32_t commandToExecute = 0;

// Declare a semaphore with an inital counter value of zero.
SEMAPHORE_DECL(cmdExSem, 0);

NIL_WORKING_AREA(commandExecutioner, 65); //65 bytes works great
NIL_THREAD(CommandExecutioner, arg)
{
  Serial.println(F("Started CommandExecutioner thread"));

  while (TRUE)
  {
    // Wait for signal from either HNListenThread or Keypad Thread to continue
    nilSemWait(&cmdExSem);

    bool sent = false;

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
            sent = homeNetwork.sendCommand(HOME_PC_ID, HOME_PC_CMD_SPOTIFY_PLAYLIST_WORKOUT);
            Serial.print(F("Starting Spotify Workout Playlist"));
            break;
          case BUTTON_PC_SPOTIFYPLAYLIST_DINNER:
            sent = homeNetwork.sendCommand(HOME_PC_ID, HOME_PC_CMD_SPOTIFY_PLAYLIST_DINNER);
            Serial.print(F("Starting Spotify Dinner Playlist"));
            break;
          case BUTTON_MAINLIGHTS_TOGGLE:
            sent = homeNetwork.sendCommand(HOME_MAINLIGHTS_ID, HOME_MAINLIGHTS_CMD_MAINLIGHTS_TOGGLE);
            Serial.print(F("Toggling Main Lights"));
            break;
          case BUTTON_PAINTINGLIGHTS_TOGGLE:
            sent = homeNetwork.sendCommand(HOME_RF433MHZ_ID, HOME_RF433MHZ_CMD_PAINTINGLIGHTS_TOGGLE);
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
            sent = homeNetwork.sendCommand(HOME_SPEAKER_ID, HOME_SPEAKER_CMD_MODE_TOGGLE);
            Serial.print(F("Toggling Speaker Mode"));
            break;
          case BUTTON_PC_POWER:
            togglePCPowerSwitch();
            Serial.print(F("Toggling PC Power Switch"));
            break;
          case BUTTON_PC_MONITOR_DISABLE:
            sent = homeNetwork.sendCommand(HOME_PC_ID, HOME_PC_CMD_MONITORS_DISABLE);
            Serial.print(F("Disabling Monitors"));
            break;
        }
    }

    if (sent) {
      Serial.println(".. Done!");
    } else if (!sent) {
      Serial.println(".. Couldn't send!");
    }
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
