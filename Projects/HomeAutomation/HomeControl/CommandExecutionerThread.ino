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
    
    bool sent = false;

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
        sent = homeNetwork.sendCommand(nodePC, cmdSetPCDisableMonitors);
        Serial.println(F("Disabled Monitors"));
        break;
      case pcSpotifyPlaylistWorkout:
        sent = homeNetwork.sendCommand(nodePC, cmdSetPCSpotifyPlaylistWorkout);
        Serial.println(F("Started Spotify Workout Playlist"));
        break;
      case pcSpotifyPlaylistDinner:
        sent = homeNetwork.sendCommand(nodePC, cmdSetPCSpotifyPlaylistDinner);
        Serial.println(F("Started Spotify Dinner Playlist"));
        break;
      case mainLightsButton:
        sent = homeNetwork.sendCommand(nodeMainLights, cmdToggleLights);
        Serial.println(F("Toggled Main Lights"));
        break;
      case paintingLightsButton:
        Serial.println(F("B4 Toggled Painting Lights"));
        sent = homeNetwork.sendCommand(nodeRF433MHz, cmdTogglePaintingLights);
        Serial.println(F("Toggled Painting Lights"));
        break;
      case speakerPowerButton:
        sent = homeNetwork.sendCommand(nodeSpeaker, cmdToggleSpeakerPower);
        Serial.println(F("Toggled Speaker Power"));
        break;
      case speakerUpVolButton:
        sent = homeNetwork.sendCommand(nodeSpeaker, cmdSetSpeakerVolumeUp);
        Serial.println(F("Increased Speaker Volume"));
        break;
      case speakerDownVolButton:
        sent = homeNetwork.sendCommand(nodeSpeaker, cmdSetSpeakerVolumeDown);
        Serial.println(F("Decreased Speaker Volume"));
        break;
      case speakerMuteButton:
        sent = homeNetwork.sendCommand(nodeSpeaker, cmdToggleSpeakerMute);
        Serial.println(F("Toggled Speaker Mute"));
        break;
      case speakerModeButton:
        sent = homeNetwork.sendCommand(nodeSpeaker, cmdToggleSpeakerMode);
        Serial.println(F("Toggled Speaker Mode"));
        break;
    }

    if (!sent)
      Serial.println(F("ERROR! Couldn't send command! Node may be offline!"));
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
