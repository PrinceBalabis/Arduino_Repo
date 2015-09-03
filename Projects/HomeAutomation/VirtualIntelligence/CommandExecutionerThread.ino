/**
 ** CommandExecutioner thread
 ** Executes commands
 **/

static bool commandOrigin = 0;
static int32_t commandToExecute = 0;
static uint16_t nodeToSendTo = 0;

// Declare a semaphore with an inital counter value of zero.
SEMAPHORE_DECL(cmdExSem, 0);

NIL_WORKING_AREA(commandExecutioner, 100); //65 bytes works great
NIL_THREAD(CommandExecutioner, arg)
{
  Serial.println(F("Started CommandExecutioner thread"));

  while (TRUE)
  {
    // Wait for signal from either HNListenThread or Keypad Thread to continue
    nilSemWait(&cmdExSem);

    bool sent = false;

    switch (commandOrigin) {
      case COMMANDEXECUTIONER_MSGORIGIN_HOMENETWORK: // If the command is from Home Network
        switch (commandToExecute) {
          case CMD_DONE:
            easyvr.playSound(1, EasyVR::VOL_FULL);
            Serial.println(F("CMD_DONE"));
            break;
        }
        break;
      case COMMANDEXECUTIONER_MSGORIGIN_LOCAL: // If the command is from local origin(Voice control)
        switch (commandToExecute) {
            homeNetwork.sendCommand(nodeToSendTo, commandToExecute);
        }
    }

    if (sent) {
      Serial.println(".. Done!");
    } else if (!sent) {
      Serial.println(".. Couldn't send!");
    }
  }
}

/*
 * Run this function to enable CommandExecutionerThread to run
 */
void executeCommand(int32_t _commandToExecute) {
  commandToExecute = _commandToExecute;
  commandOrigin = COMMANDEXECUTIONER_MSGORIGIN_LOCAL;
  nilSemSignal(&cmdExSem);
}

/*
 * Run this function to enable CommandExecutionerThread to run
 */
void executeHomeNetworkCommand(int32_t _commandToExecute, bool _nodeToSendTo) {
  commandToExecute = _commandToExecute;
  nodeToSendTo = _nodeToSendTo;
  commandOrigin = COMMANDEXECUTIONER_MSGORIGIN_HOMENETWORK;
  nilSemSignal(&cmdExSem);
}
