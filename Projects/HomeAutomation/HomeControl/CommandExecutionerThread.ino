/**
 ** CommandExecutioner thread
 ** Executes commands
 **/

int32_t executeCommand = 0;

// Declare a semaphore with an inital counter value of zero.
SEMAPHORE_DECL(cmdExSem, 0);

static msg_t CommandExecutioner(void *arg)
{
  Serial.println(F("Started CommandExecutioner thread, waiting for command to be executed"));

  while (1)
  {
    // Wait for signal from either HNListenThread or Keypad Thread to continue
    chSemWait(&cmdExSem);

    switch (executeCommand) {
      case cmdSetPCOn:
        setPCPowerSwitchOnMomentarily();
        break;
      case computerPowerButton:
        togglePCPowerSwitch();
        break;
      case pcDisableMonitorButton:
        homeNetwork.sendCommand(nodePC, cmdSetPCDisableMonitors);
        break;
      case mainLightsButton:
        homeNetwork.sendCommand(nodeMainLights, cmdToggleLights);
        break;
      case paintingLightsButton:
        homeNetwork.sendCommand(nodeRF433MHz, cmdTogglePaintingLights);
        break;
      case speakerPowerButton:
        homeNetwork.sendCommand(nodeSpeaker, cmdToggleSpeakerPower);
        break;
      case speakerUpVolButton:
        homeNetwork.sendCommand(nodeSpeaker, cmdSetSpeakerVolumeUp);
        break;
      case speakerDownVolButton:
        homeNetwork.sendCommand(nodeSpeaker, cmdSetSpeakerVolumeDown);
        break;
      case speakerMuteButton:
        homeNetwork.sendCommand(nodeSpeaker, cmdToggleSpeakerMute);
        break;
      case speakerModeButton:
        homeNetwork.sendCommand(nodeSpeaker, cmdToggleSpeakerMode);
        break;
    }
  }
  return 0;
}
