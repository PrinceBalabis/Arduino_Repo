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

NIL_WORKING_AREA(commandExecutioner, 150); // bytes works great
NIL_THREAD(CommandExecutioner, arg)
{
  Serial.println(F("Started CommandExecutioner thread"));

  uint32_t count = 1;

  while (1)
  {
    // Wait for signal to run
    nilSemWait(&cmdExSem);

    Serial.println(count++);
    homeNetwork.respondToQuestion(commandFromNode, 1);

    // Received commands from other node
    //    Serial.print(F("Node:"));
    //    Serial.println(commandFromNode);
    //    Serial.print(F("Message Type:"));
    //    Serial.println(commandType);
    //    Serial.print(F("Command:"));
    //    Serial.println(commandToExecute);
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
