/**
 ** CommandExecutioner thread
 ** Executes commands
 **/

int32_t executeCommand = 0;

// Declare a semaphore with an inital counter value of zero.
SEMAPHORE_DECL(cmdExSem, 0);

static msg_t CommandExecutioner(void *arg)
{
  Serial.println(F("Started CommandExecutioner thread"));

  while (1)
  {
    // Wait for signal from either HNListenThread or Keypad Thread to run this loop
    chSemWait(&cmdExSem);

    switch (executeCommand) {
      case cmdSetPCOn:
        setPCPowerSwitchOnMomentarily();
        break;
      case MainLightsButton:
        homeNetwork.toggleMainLights();
        break;
      case paintingLightsButton:
        homeNetwork.togglePaintingLights();
        break;
      case computerPowerButton:
        togglePCPowerSwitch();
        break;
      case speakerPowerButton:
        homeNetwork.toggleSpeakerPower();
        break;
      case speakerUpVolButton:
        homeNetwork.setSpeakerVolumeUp();
        break;
      case speakerDownVolButton:
        homeNetwork.setSpeakerVolumeDown();
        break;
      case speakerMuteButton:
        homeNetwork.toggleSpeakerMute();
        break;
      case speakerModeButton:
        homeNetwork.toggleSpeakerMode();
        break;
    }
  }
  return 0;
}
