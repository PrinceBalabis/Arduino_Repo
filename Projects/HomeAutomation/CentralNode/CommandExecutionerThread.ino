/**
 ** CommandExecutioner thread
 ** Executes commands
 **/

static int32_t commandToExecute = 0;

// Declare a semaphore with an inital counter value of zero.
SEMAPHORE_DECL(cmdExSem, 0);

//This function is used to send commands from HomeControl to HomeNetwork
NIL_WORKING_AREA(commandExecutioner, 180); // bytes works great
NIL_THREAD(CommandExecutioner, arg)
{
  Serial.println(F("Started CommandExecutioner thread"));

  while (1)
  {
    // Wait for signal to run
    nilSemWait(&cmdExSem);
    bool sent = true;

    switch (commandToExecute) {
      case BUTTON_MAINLIGHTS_TOGGLE:
        sent = homeNetwork.sendCommand(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_CMD_MAINLIGHTS_TOGGLE, 20);
        Serial.print(F("Toggling Main Lights"));
        break;
      case BUTTON_PAINTINGLIGHTS_TOGGLE:
        sent = homeNetwork.sendCommand(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_CMD_PAINTINGLIGHTS_TOGGLE, 20); // Painting lights node takes a while to respond due to 433MHz commands taking forever to send, thats why its best to just retry once, in order to make sure it doesnt get spammed with retries
        Serial.print(F("Toggling Painting Lights"));
        break;
    }

    if (sent) {
      Serial.println(F(".. Done!"));
    } else if (!sent) {
      Serial.println(F(".. Couldn't send!"));
    }
  }
}

/*
   Run this function to enable CommandExecutionerThread to run
*/
void executeCommand(uint16_t _commandToExecute) {
  commandToExecute = _commandToExecute;
  nilSemSignal(&cmdExSem);
}
