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
      case HOME_SPEAKER_CMD_POWER_TOGGLE:
        toggleSpeakerPower();
        break;
      case HOME_SPEAKER_CMD_POWER_ON:
        sendSpeakerPowerOnCommand();
        break;
      case HOME_SPEAKER_CMD_POWER_OFF:
        sendSpeakerPowerOffCommand();
        break;
      case HOME_SPEAKER_CMD_MUTE_TOGGLE:
        toggleSpeakerMuteCommand();
        break;
      case HOME_SPEAKER_CMD_MUTE_ON:
        sendSpeakerMuteOnCommand();
        break;
      case HOME_SPEAKER_CMD_MUTE_OFF:
        sendSpeakerMuteOffCommand();
        break;
      case HOME_SPEAKER_CMD_VOLUME_UP:
        sendSpeakerUpVolCommand();
        break;
      case HOME_SPEAKER_CMD_VOLUME_DOWN:
        sendSpeakerDownVolCommand();
        break;
      case HOME_SPEAKER_CMD_MODE_TOGGLE:
        toggleSpeakerModeCommand();
        break;
    }
  }
  return 0;
}
