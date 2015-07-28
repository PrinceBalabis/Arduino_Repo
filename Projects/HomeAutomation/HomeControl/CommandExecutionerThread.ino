/**
 ** CommandExecutioner thread
 ** Executes commands
 **/

int32_t commandToExecute = 0;

// Declare a semaphore with an inital counter value of zero.
SEMAPHORE_DECL(cmdExSem, 0);

static msg_t CommandExecutioner(void *arg)
{
  Serial.println(F("Started CommandExecutioner thread, waiting for command to be executed"));

  while (1)
  {
    // Wait for signal from either HNListenThread or Keypad Thread to continue
    chSemWait(&cmdExSem);

    switch (commandToExecute) {
      case cmdSetPCOn:
        setPCPowerSwitchOnMomentarily();
        Serial.println(F("Turned PC on"));
        break;
      case pcPowerButton:
        togglePCPowerSwitch();
        Serial.println(F("Toggled PC Power Switch"));
        break;
      case pcDisableMonitorButton:
        homeNetwork.sendCommand(nodePC, cmdSetPCDisableMonitors);
        Serial.println(F("Disabled Monitors"));
        break;
      case pcSpotifyPlaylistWorkout:
        homeNetwork.sendCommand(nodePC, cmdSetPCSpotifyPlaylistWorkout);
        Serial.println(F("Started Spotify Workout Playlist"));
        break;
      case pcSpotifyPlaylistDinner:
        homeNetwork.sendCommand(nodePC, cmdSetPCSpotifyPlaylistDinner);
        Serial.println(F("Started Spotify Dinner Playlist"));
        break;
      case mainLightsButton:
        homeNetwork.sendCommand(nodeMainLights, cmdToggleLights);
        Serial.println(F("Toggled Main Lights"));
        break;
      case paintingLightsButton:
        homeNetwork.sendCommand(nodeRF433MHz, cmdTogglePaintingLights);
        Serial.println(F("Toggled Painting Lights"));
        break;
      case speakerPowerButton:
        homeNetwork.sendCommand(nodeSpeaker, cmdToggleSpeakerPower);
        Serial.println(F("Toggled Speaker Power"));
        break;
      case speakerUpVolButton:
        homeNetwork.sendCommand(nodeSpeaker, cmdSetSpeakerVolumeUp);
        Serial.println(F("Increased Speaker Volume"));
        break;
      case speakerDownVolButton:
        homeNetwork.sendCommand(nodeSpeaker, cmdSetSpeakerVolumeDown);
        Serial.println(F("Decreased Speaker Volume"));
        break;
      case speakerMuteButton:
        homeNetwork.sendCommand(nodeSpeaker, cmdToggleSpeakerMute);
        Serial.println(F("Toggled Speaker Mute"));
        break;
      case speakerModeButton:
        homeNetwork.sendCommand(nodeSpeaker, cmdToggleSpeakerMode);
        Serial.println(F("Toggled Speaker Mode"));
        break;
    }
  }
  return 0;
}

/*
 * Run this function to enable CommandExecutionerThread to run
 */
void executeCommand(int32_t _commandToExecute) {
  commandToExecute = _commandToExecute;
  chSemSignal(&cmdExSem);
}
