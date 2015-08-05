/**
 *  HMListenThread
 *  Idles until a message is received from a client.
 **/

static msg_t HNListenThread(void *arg) {
  Serial.println(F("Home Network listener started"));
  homeNetwork.setAutoUpdateTime(homeNetworkAutoUpdateTime);

  while (1) {
    if (msgReceived) { // Check message if a new message is received
      homeNetwork.pauseAutoUpdate(true); // Pause network update in order to queue commands

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

      msgReceived = false; // Listen for new message
      homeNetwork.pauseAutoUpdate(false); // Resume network update in order to get queued commands
    }
    chThdSleepMilliseconds(homeNetworkCheckMessageDelay); // Check every few ms if a message is received
  }
  return 0;
}
