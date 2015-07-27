/**
 ** CommandExecutioner thread
 ** Executes commands
 **/

int32_t executeCommand = 0;

// Declare a semaphore with an inital counter value of zero.
SEMAPHORE_DECL(cmdExSem, 0);

static msg_t CommandExecutioner(void *arg)
{
  Serial.println(F("CommandExecutioner thread started"));

  while (1)
  {
    // Wait for signal from either HNListenThread or Keypad Thread to run this loop
    chSemWait(&cmdExSem);

    switch (executeCommand) {
      case cmdToggleSpeakerPower:
        toggleSpeakerPower();
        break;
      case cmdSetSpeakerPowerOn:
        sendSpeakerPowerOnCommand();
        break;
      case cmdSetSpeakerPowerOff:
        sendSpeakerPowerOffCommand();
        break;
      case cmdToggleSpeakerMute:
        toggleSpeakerMuteCommand();
        break;
      case cmdSetSpeakerMuteOn:
        sendSpeakerMuteOnCommand();
        break;
      case cmdSetSpeakerMuteOff:
        sendSpeakerMuteOffCommand();
        break;
      case cmdSetSpeakerVolumeUp:
        sendSpeakerUpVolCommand();
        break;
      case cmdSetSpeakerVolumeDown:
        sendSpeakerDownVolCommand();
        break;
      case cmdToggleSpeakerMode:
        toggleSpeakerModeCommand();
        break;
    }
  }
  return 0;
}
