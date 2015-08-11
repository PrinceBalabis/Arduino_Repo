/**
 *  HMListenThread
 *  Idles until a message is received from a client.
 **/

static msg_t HNListenThread(void *arg) {
  Serial.println(F("Home Network listener started"));
  homeNetwork.setAutoUpdateTime(homeNetworkAutoUpdateTime);

  while (1) {
    // Pause loop while waiting for a message
    chSemWait(&homeNetworkSem);

    switch (msgType) {
      case typeCommand: // If its a simple command, relay it to CommandExecutionerThread
        executeCommand(msgContent);
        Serial.print(F("Received command..."));
        break;

      case typeAsk: // If its a question, do some things
        //Questions here
        switch (msgContent) {
        }
    }

    homeNetwork.pauseAutoUpdate(false); // Resume network update in order to get queued commands
  }
  return 0;
}
