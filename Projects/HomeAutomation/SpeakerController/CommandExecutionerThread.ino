/**
 ** CommandExecutioner thread
 ** Executes commands
 **/

static int32_t commandToExecute = 0;

// Declare a semaphore with an inital counter value of zero.
SEMAPHORE_DECL(cmdExSem, 0);

NIL_WORKING_AREA(commandExecutioner, 100); //52 bytes works great
NIL_THREAD(CommandExecutioner, arg)
{
  Serial.println(F("CommandExecutioner thread started"));

  while (1)
  {
    //Wait for signal from either HNListenThread or Keypad Thread to run this loop
    nilSemWait(&cmdExSem);

    switch (commandToExecute) {
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
}

/*
 * Run this function to enable CommandExecutionerThread to run
 */
void executeCommand(int32_t _commandToExecute) {
  commandToExecute = _commandToExecute;
  nilSemSignal(&cmdExSem);
}
