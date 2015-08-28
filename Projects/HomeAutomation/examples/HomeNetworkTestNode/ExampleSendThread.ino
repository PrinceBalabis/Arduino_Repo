/**
 *  ExampleSendThread
 *  Sends a messeger to Node A every few moments
 **/
 
NIL_WORKING_AREA(exampleSendThread, 100);
NIL_THREAD(ExampleSendThread, arg) {
  Serial.println(F("Testing beginning"));

  while (TRUE) {
    nilThdSleepMilliseconds(TESTING_SEND_DELAY); // Redo this send program every few moments, give enough time for other threads to run
    executeCommand(TESTING_CHOSEN_COMMAND);
  }
}

