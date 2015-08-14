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
    // Wait for signal to run
    chSemWait(&cmdExSem);

    int32_t status = -1;

    switch (commandToExecute) {
      case TESTING_CMD_MAINLIGHTS_TOGGLE:
        homeNetwork.sendCommand(NODE_MAINLIGHTS_ID, NODE_MAINLIGHTS_CMD_MAINLIGHTS_TOGGLE);
        break;
      case TESTING_QSN_MAINLIGHTS_STATUS:
        homeNetwork.sendQuestion(NODE_MAINLIGHTS_ID, NODE_MAINLIGHTS_QSN_MAINLIGHTS_STATUS, &status);
        break;
      case TESTING_CMD_SPEAKER_MUTE_TOGGLE:
        homeNetwork.sendCommand(NODE_SPEAKER_ID, NODE_SPEAKER_CMD_MUTE_TOGGLE);
        break;
      case TESTING_CMD_433MHZ_PAINTINGLIGHTS_TOGGLE:
        homeNetwork.sendCommand(NODE_RF433MHZ_ID, NODE_RF433MHZ_CMD_PAINTINGLIGHTS_TOGGLE);
        break;
    }
    Serial.print(F(" Status: "));
    Serial.print(status);
    Serial.println();
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
