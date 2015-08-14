/**
 ** CommandExecutioner thread
 ** Executes commands
 **/

static bool commandOrigin = 0;
static int32_t commandToExecute = 0;

// Declare a semaphore with an inital counter value of zero.
SEMAPHORE_DECL(cmdExSem, 0);

static msg_t CommandExecutioner(void *arg)
{
  Serial.println(F("Started CommandExecutioner thread"));

  while (1)
  {
    // Wait for signal from either HNListenThread or Keypad Thread to continue
    chSemWait(&cmdExSem);

    bool sent;

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
            homeNetwork.sendCommand(HOME_PC_ID, HOME_PC_CMD_SPOTIFY_PLAYLIST_WORKOUT);
            Serial.println(F("Started Spotify Workout Playlist"));
            break;
          case BUTTON_PC_SPOTIFYPLAYLIST_DINNER:
            homeNetwork.sendCommand(HOME_PC_ID, HOME_PC_CMD_SPOTIFY_PLAYLIST_DINNER);
            Serial.println(F("Started Spotify Dinner Playlist"));
            break;
          case BUTTON_MAINLIGHTS_TOGGLE:
            homeNetwork.sendCommand(HOME_MAINLIGHTS_ID, HOME_MAINLIGHTS_CMD_MAINLIGHTS_TOGGLE);
            Serial.println(F("Toggled Main Lights"));
            break;
          case BUTTON_PAINTINGLIGHTS_TOGGLE:
            homeNetwork.sendCommand(HOME_RF433MHZ_ID, HOME_RF433MHZ_CMD_PAINTINGLIGHTS_TOGGLE);
            Serial.println(F("Toggled Painting Lights"));
            break;
          case BUTTON_SPEAKER_POWER:
            homeNetwork.sendCommand(HOME_SPEAKER_ID, HOME_SPEAKER_CMD_POWER_TOGGLE);
            Serial.println(F("Toggled Speaker Power"));
            break;
          case BUTTON_SPEAKER_VOLUME_UP:
            homeNetwork.sendCommand(HOME_SPEAKER_ID, HOME_SPEAKER_CMD_VOLUME_UP);
            Serial.println(F("Increased Speaker Volume"));
            break;
          case BUTTON_SPEAKER_VOLUME_DOWN:
            homeNetwork.sendCommand(HOME_SPEAKER_ID, HOME_SPEAKER_CMD_VOLUME_DOWN);
            Serial.println(F("Decreased Speaker Volume"));
            break;
          case BUTTON_SPEAKER_MUTE:
            homeNetwork.sendCommand(HOME_SPEAKER_ID, HOME_SPEAKER_CMD_MUTE_TOGGLE);
            Serial.println(F("Toggled Speaker Mute"));
            break;
          case BUTTON_SPEAKER_MODE:
            homeNetwork.sendCommand(HOME_SPEAKER_ID, HOME_SPEAKER_CMD_MODE_TOGGLE);
            Serial.println(F("Toggled Speaker Mode"));
            break;
          case BUTTON_PC_POWER:
            togglePCPowerSwitch();
            Serial.println(F("Toggled PC Power Switch"));
            break;
          case BUTTON_PC_MONITOR_DISABLE:
            homeNetwork.sendCommand(HOME_PC_ID, HOME_PC_CMD_MONITORS_DISABLE);
            Serial.println(F("Disabled Monitors"));
            break;
        }
    }

    if (sent != NULL) {
      Serial.print(F("Sent: "));
      Serial.println(sent);
    }
  }
  return 0;
}

/*
 * Run this function to enable CommandExecutionerThread to run
 */
void executeCommand(int32_t _commandToExecute, bool _commandOrigin) {
  commandToExecute = _commandToExecute;
  commandOrigin = _commandOrigin;
  chSemSignal(&cmdExSem);
}
