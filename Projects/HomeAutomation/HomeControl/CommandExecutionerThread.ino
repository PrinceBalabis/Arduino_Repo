/**
 ** CommandExecutioner thread
 ** Executes commands received from other RF24 units
 **/

int32_t executeCommand = 0;

// Declare a semaphore with an inital counter value of zero.
SEMAPHORE_DECL(cmdExSem, 0);

static msg_t CommandExecutioner(void *arg)
{
  chThdSleepMilliseconds(2000); // Needs to wait for other threads to start or else Arduino might crash
  Serial.println(F("Started CommandExecutioner thread"));

  while (1)
  {
    // Wait for signal from either HNListenThread or Keypad Thread to run this loop
    chSemWait(&cmdExSem);

    switch (executeCommand) {
      case MainLightsButton:
        homeNetwork.toggleMainLights();
        break;
      case paintingLightsButton:
        homeNetwork.togglePaintingLights();
        break;
      case computerPowerButton:
        togglePCPowerSwitch();
        break;
      case speakerPowerButton:
        homeNetwork.toggleSpeakerPower();
        break;
    }
  }
}
