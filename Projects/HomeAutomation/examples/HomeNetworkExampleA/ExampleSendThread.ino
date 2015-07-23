/**
 *  ExampleSendThread
 *  Sends a messeger to Node A every few moments
 **/

static msg_t ExampleSendThread(void *arg) {
  Serial.println(F("ExampleSendThread begin"));

  uint32_t count = 0;

  while (1) {
    chThdSleepMilliseconds(1643); // Redo this send program every few moments, give enough time for other threads to run

    executeCommand = cmdExampleAskCommand;
    chSemSignal(&cmdExSem);
    
  }
  return 0;
}

