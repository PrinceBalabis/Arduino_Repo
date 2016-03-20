/**
 ** CommandExecutioner thread
 ** Executes commands
 **/

static bool commandOrigin = 0;
static uint16_t commandFromNode = 0;
static char commandType = 'Q';
static uint16_t commandToExecute = 0;

int32_t count = 1;

// Declare a semaphore with an inital counter value of zero.
SEMAPHORE_DECL(cmdExSem, 0);

NIL_WORKING_AREA(commandExecutioner, 200); // bytes works great
NIL_THREAD(CommandExecutioner, arg)
{
  Serial.println(F("Started CommandExecutioner thread"));

  while (1)
  {
    // Wait for signal to run
    nilSemWait(&cmdExSem);

    int32_t answer = -999;
    bool sentEnabled = true;
    bool sent = false;
    Serial.print(count++);
    Serial.print(F(":"));

    switch (commandOrigin) {
      case COMMANDEXECUTIONER_MSGORIGIN_LOCAL:
        switch (commandToExecute) {
          case TESTING_CMD_MAINLIGHTS_TOGGLE:
            sent = homeNetwork.sendCommand(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_CMD_MAINLIGHTS_TOGGLE);
            break;
          case TESTING_QSN_MAINLIGHTS_STATUS:
            sent = homeNetwork.sendQuestion(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_QSN_MAINLIGHTS_STATUS, &answer, 200);
            break;
          case TESTING_CMD_433MHZ_PAINTINGLIGHTS_TOGGLE:
            sent = homeNetwork.sendCommand(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_CMD_PAINTINGLIGHTS_TOGGLE);
            break;
          case TESTING_CMD_433MHZ_PAINTINGLIGHTS_STATUS:
            sent = homeNetwork.sendQuestion(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_QSN_PAINTINGLIGHTS_STATUS, &answer, 200);
            break;
          case TESTING_CMD_WEB_PC_SLEEP:
            sent = homeNetwork.sendCommand(HOME_PI_ID, HOME_PI_CMD_PC_SLEEP);
            break;
        }
        break;
      case COMMANDEXECUTIONER_MSGORIGIN_HOMENETWORK:
        // Received commands from other node
        sentEnabled = false;
        Serial.println(F("Received: "));
        Serial.println(commandFromNode);
        Serial.println(commandType);
        Serial.println(commandToExecute);
        Serial.println(F(""));
        break;
    }

    if (sentEnabled) {
      if (sent) {
        Serial.print(F("Sent"));
      } else {
        Serial.print(F("NOT SENT! FAILED, STOPPING PROGRAM!"));
        while (1) {}
      }
      if (answer != -999) { // If the status variable was used in the example, print it out
        Serial.print(F(", Answer: "));
        Serial.print(answer);
      }
    }
    Serial.println(F(""));
  }
}

/*
   Run this function to enable CommandExecutionerThread to run
*/
void executeCommand(int32_t _commandToExecute) {
  commandToExecute = _commandToExecute;
  commandOrigin = COMMANDEXECUTIONER_MSGORIGIN_LOCAL;
  nilSemSignal(&cmdExSem);
}

/**
   homeNetworkMessageReceived()
   This function is executed automatically by the HomeNetwork Library when a message is received.
*/
void executeHomeNetworkCommand(uint16_t msgSender, unsigned char msgType, int32_t msgContent) {
  commandFromNode = msgSender;
  commandType = msgType;
  commandToExecute = msgContent;
  commandOrigin = COMMANDEXECUTIONER_MSGORIGIN_HOMENETWORK;
  nilSemSignal(&cmdExSem);
}
