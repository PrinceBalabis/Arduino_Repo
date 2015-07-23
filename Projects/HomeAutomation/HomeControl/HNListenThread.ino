/**
 *  HMListenThread
 *  Idles until a message is received from a client.
 **/

static msg_t HNListenThread(void *arg) {
  Serial.println(F("HMListenThread started, dont forget to have a unique nodeID!"));

  while (1) {
    if (msgReceived) { // Check message if a new message is received

      if (msgType == typeCommand) { // If its a simple command
        switch (msgContent) {
          case cmdSetPCOn:
            executeCommand = cmdSetPCOn;
            // Signal CommandExecutionerThread to run command
            chSemSignal(&cmdExSem);
        }
      } else if (msgType == typeAsk) { // If its a question
      }

      msgReceived = false; // Listen for new message
    }
    chThdSleepMilliseconds(homeNetworkCheckMessageDelay); // Check every few ms if a message is received
  }
  return 0;
}
