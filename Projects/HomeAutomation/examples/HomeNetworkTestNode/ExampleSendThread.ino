/**
 *  ExampleSendThread
 *  Sends a messeger to Node A every few moments
 **/

static msg_t ExampleSendThread(void *arg) {
  Serial.println(F("Testing beginning"));

  while (1) {
    chThdSleepMilliseconds(TESTING_SEND_DELAY); // Redo this send program every few moments, give enough time for other threads to run
    executeCommand(TESTING_CHOSEN_COMMAND, COMMANDEXECUTIONER_MSGORIGIN_LOCAL);
  }
  return 0;
}

