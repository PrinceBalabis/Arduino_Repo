/**
 *  ExampleSendThread
 *  Sends a messeger to Node A every few moments
 **/

static msg_t ExampleSendThread(void *arg) {
  Serial.println(F("ExampleSendThread begin"));

  while (1) {
    chThdSleepMilliseconds(1943); // Redo this send program every few moments, give enough time for other threads to run

    executeCommand = cmdExampleAskCommand;
    chSemSignal(&cmdExSem);

  }
  return 0;
}

