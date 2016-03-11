/**
 ** CommandExecutioner thread
 ** Executes commands
 **/

static bool commandOrigin = 0;
static int32_t nodeToSendTo = 0;
static int32_t commandToExecute = 0;

// Declare a semaphore with an inital counter value of zero.
SEMAPHORE_DECL(cmdExSem, 0);

NIL_WORKING_AREA(commandExecutioner, 160); // bytes works great
NIL_THREAD(CommandExecutioner, arg)
{
  Serial.println(F("Started CommandExecutioner thread"));

  while (1)
  {
    // Wait for signal to run
    nilSemWait(&cmdExSem);

    bool sent = sent;

    switch (commandOrigin) {
      case COMMANDEXECUTIONER_MSGORIGIN_KEYPAD: // Command came from keypad
        Serial.println(F("Relaying keypad command to HomeNetwork"));
        sent = (bool)homeNetwork.sendCommand(nodeToSendTo, commandToExecute);
        break;
      case COMMANDEXECUTIONER_MSGORIGIN_HOMENETWORK: // Normal Command that came from the HomeNetwork
        switch (commandToExecute) {
          case HOME_HOMECONTROL_CMD_PC_ON:
            while (callbackCommand != 0) // Wait untill last callbackCommand is used
              nilThdSleepMilliseconds(1);
            callbackCommand = HOME_HOMECONTROL_CMD_PC_ON;
            Serial.println(F("Powered up PC"));
            break;
        }
        break;
    }

    if (sent) {
      Serial.println(F("Command done"));
    } else {
      Serial.println(F("FAILED TO SEND COMMAND"));
    }

  }
}

/*
   Run this function to enable CommandExecutionerThread to run
*/
void executeCommand(bool _commandOrigin, uint16_t _nodeToSendTo, uint16_t _commandToExecute) {
  commandOrigin = _commandOrigin;
  nodeToSendTo = _nodeToSendTo;
  commandToExecute = _commandToExecute;
  nilSemSignal(&cmdExSem);
}

