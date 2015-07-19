/**
 ** CommandExecutioner thread
 ** Executes commands received from other RF24 units
 **/

int32_t executeCommand = 0;

// Declare a semaphore with an inital counter value of zero.
SEMAPHORE_DECL(cmdExSem, 0);

static msg_t CommandExecutioner(void *arg)
{
  Serial.println(F("Started CommandExecutioner thread"));

  while (1)
  {
    Serial.println(F("Command Executioner IDLE"));
    // Wait for signal from either HNListenThread or Keypad Thread to run this loop
    chSemWait(&cmdExSem);
    Serial.println(F("Command Executioner ACTIVE"));

    switch (executeCommand) {
      case pcPowerButton:
        togglePCPowerSwitch();
        break;
      case lightMainButton:
        homeNetwork.toggleMainLights();
        break;
      case lightDiningTableButton:
        toggleDiningTableSwitch();
        break;
    }
  }
}















