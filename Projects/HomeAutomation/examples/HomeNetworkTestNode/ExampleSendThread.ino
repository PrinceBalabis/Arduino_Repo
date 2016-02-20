/**
    ExampleSendThread
    Sends a messeger to Node A every few moments
 **/

NIL_WORKING_AREA(exampleSendThread, 150);
NIL_THREAD(ExampleSendThread, arg) {
  Serial.println(F("Testing beginning"));

  for (int repeatStatus = 0; repeatStatus < TESTING_REPEATS; repeatStatus++) {
    nilThdSleepMilliseconds(TESTING_SEND_DELAY); // Redo this send program every few moments, give enough time for other threads to run
    executeCommand(TESTING_CHOSEN_COMMAND);
  }

  // Stop program when done sending command
  homeNetwork.setNetworkUpdateStatus(false); // Pause autoUpdate
  while (1)
  {
  }
}

