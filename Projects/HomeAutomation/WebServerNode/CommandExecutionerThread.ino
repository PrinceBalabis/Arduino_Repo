/**
 ** CommandExecutioner thread
 ** Executes commands
 **/

static bool commandOrigin = 0;
static int32_t commandToExecute = 0;

// Declare a semaphore with an inital counter value of zero.
SEMAPHORE_DECL(cmdExSem, 0);

NIL_WORKING_AREA(commandExecutioner, 100); // bytes works great
NIL_THREAD(CommandExecutioner, arg)
{
  Serial.println(F("Started CommandExecutioner thread"));

  while (TRUE)
  {
    // Wait for signal to run
    nilSemWait(&cmdExSem);

    int32_t status = -999;
    bool sent = false;

switch(commandOrigin){
  case COMMANDEXECUTIONER_MSGORIGIN_LOCAL: // Command that came from the internet
    switch(commandToExecute){
      case CMD_MAINLIGHTS_TOGGLE:
      sent = homeNetwork.sendCommand(HOME_MAINLIGHTS_ID, HOME_MAINLIGHTS_CMD_MAINLIGHTS_TOGGLE);
    }
  break;
  case COMMANDEXECUTIONER_MSGORIGIN_HOMENETWORK: // Command that came from HomeNetwork
      switch (commandToExecute) {
    }
  break;
}


    Serial.print(F("Sent: "));
    Serial.print(sent);
    if (status != -999) { // If the status variable was used in the example, print it out
      Serial.print(F(" Status: "));
      Serial.print(status);
    }
    Serial.println();
  }
}

/*
 * Run this function to enable CommandExecutionerThread to run
 */
void executeCommand(int32_t _commandToExecute, bool _commandOrigin) {
  commandToExecute = _commandToExecute;
  commandOrigin = _commandOrigin;
  nilSemSignal(&cmdExSem);
}
