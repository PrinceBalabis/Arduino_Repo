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
        break;
      case pcPowerButton:
        togglePCPowerSwitch();
        break;
      case pcDisableMonitorButton:
        homeNetwork.sendCommand(nodePC, cmdSetPCSetMonitorsOff);
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

/*
 * Run this function to enable CommandExecutionerThread to run
 */
void executeCommand(int32_t _commandToExecute) {
  commandToExecute = _commandToExecute;
  chSemSignal(&cmdExSem);
}
