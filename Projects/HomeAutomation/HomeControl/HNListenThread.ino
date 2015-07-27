/**
 *  HMListenThread
 *  Idles until a message is received from a client.
 **/

static msg_t HNListenThread(void *arg) {
  Serial.println(F("HNListenThread started, dont forget to set a unique nodeID!"));
  homeNetwork.setAutoUpdateTime(homeNetworkAutoUpdateTime);

  while (1) {
    if (msgReceived) { // Check message if a new message is received
      homeNetwork.pauseAutoUpdate(true); // Pause network update in order to queue commands

      switch (msgType) {
        case typeCommand: // If its a simple command
          switch (msgContent) {
            case cmdSetPCOn:
              executeCommand = cmdSetPCOn;
              chSemSignal(&cmdExSem);
          }
          break;
          //    case typeAsk:
          //      break;
      }

      msgReceived = false; // Listen for new message
      homeNetwork.pauseAutoUpdate(false); // Resume network update in order to get queued commands
    }
    chThdSleepMilliseconds(homeNetworkCheckMessageDelay); // Check every few ms if a message is received
  }
  return 0;
}
