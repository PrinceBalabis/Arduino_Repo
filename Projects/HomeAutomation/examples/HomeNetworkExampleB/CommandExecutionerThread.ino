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

  uint32_t count = 0;

  while (1)
  {
    // Wait for signal from either HNListenThread or Keypad Thread to run this loop
    chSemWait(&cmdExSem);

    switch (executeCommand) {
      case cmdExampleAskCommand:
        // Ask question to ExampleNodeA
        Serial.print(count++);
        int32_t msgResponse;
        bool msgSent = homeNetwork.askExampleDataA(&msgResponse);
        if (msgSent) {
          Serial.println(F(":Received"));
        } else if (!msgSent) {
          Serial.println(F(":Timeout!"));
        }
        break;
    }
  }
  return 0;
}
