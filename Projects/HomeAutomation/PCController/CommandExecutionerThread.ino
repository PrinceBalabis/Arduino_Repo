/**
 ** CommandExecutioner thread
 ** Executes commands
 **/

int32_t executeCommand = 0;

// Declare a semaphore with an inital counter value of zero.
SEMAPHORE_DECL(cmdExSem, 0);

static msg_t CommandExecutioner(void *arg)
{
  Serial.println(F("Started CommandExecutioner thread"));

  while (1)
  { Serial.println(F("wait"));
    // Wait for signal from either HNListenThread or Keypad Thread to run this loop
    chSemWait(&cmdExSem);
    Serial.println(F("commandex"));
    switch (executeCommand) {
      case cmdToggleLights:
      Serial.println(F("tiggkelightsruyn"));
        int32_t msgResponse;
        bool msgSent = homeNetwork.toggleMainLights();
        Serial.println(msgSent);

    }
  }
  return 0;
}
