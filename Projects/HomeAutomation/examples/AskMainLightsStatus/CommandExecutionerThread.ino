/**
 ** CommandExecutioner thread
 ** Executes commands
 **/

int32_t executeCommand = 0;

// Declare a semaphore with an inital counter value of zero.
SEMAPHORE_DECL(cmdExSem, 0);

static msg_t CommandExecutioner(void *arg)
{
  Serial.println(F("Started CommandExecutioner thread, waiting for command to be executed"));

  while (1)
  {
    // Wait for signal to run
    chSemWait(&cmdExSem);

    switch (executeCommand) {
      case cmdGetLightsStatus:
        int32_t mainLightsStatus;
        bool sent = homeNetwork.sendQuestion(nodeMainLights, cmdGetLightsStatus, &mainLightsStatus);
        Serial.print(F("Sent: "));
        Serial.print(sent);
        Serial.print(F(" Status: "));
        Serial.print(mainLightsStatus);
        Serial.println();
        break;
    }
  }
  return 0;
}
