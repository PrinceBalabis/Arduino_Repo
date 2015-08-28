/**
 ** CommandExecutioner thread
 ** Executes commands
 **/

int32_t commandToExecute = 0;

// Declare a semaphore with an inital counter value of zero.
SEMAPHORE_DECL(cmdExSem, 0);

NIL_WORKING_AREA(commandExecutioner, 150); // 100 bytes seems to work fine
NIL_THREAD(CommandExecutioner, arg)
{
  Serial.println(F("Started CommandExecutioner thread, waiting for command to be executed"));

  while (TRUE)
  {
    // Wait for signal to run
    nilSemWait(&cmdExSem);

    switch (commandToExecute) {
      case HOME_PC_CMD_MONITORS_DISABLE:
        pcDisableMonitors();
        Serial.println(F("Disabled Monitors"));
        break;
      case HOME_PC_CMD_MONITORS_ENABLE:
        pcEnableMonitors();
        Serial.println(F("Enabled Monitors"));
        break;
      case HOME_PC_CMD_VOLUME_UP_BUNCH:
        pcIncreaseVolume();
        Serial.println(F("Increased Volume"));
        break;
      case HOME_PC_CMD_VOLUME_DOWN_BUNCH:
        pcDecreaseVolume();
        Serial.println(F("Decreased Volume"));
        break;
      case HOME_PC_CMD_VOLUME_PRESET_LOW:
        pcSetVolumePresetLow();
        Serial.println(F("Decreased Volume"));
        break;
      case HOME_PC_CMD_VOLUME_PRESET_MEDIUM:
        pcSetVolumePresetMedium();
        Serial.println(F("Decreased Volume"));
        break;
      case HOME_PC_CMD_VOLUME_PRESET_MAX:
        pcSetVolumePresetMax();
        Serial.println(F("Decreased Volume"));
        break;
      case HOME_PC_CMD_SPOTIFY_PLAYLIST_WORKOUT:
        pcSpotifyStartPlaylistWorkout();
        Serial.println(F("Started Spotify Workout Playlist"));
        break;
      case HOME_PC_CMD_SPOTIFY_PLAYLIST_DINNER:
        pcSpotifyStartPlaylistDinner();
        Serial.println(F("Started Spotify Dinner Playlist"));
        break;
    }
  }
}

/*
 * Run this function to enable CommandExecutionerThread to run
 */
void executeCommand(int32_t _commandToExecute) {
  commandToExecute = _commandToExecute;
  nilSemSignal(&cmdExSem);
}
