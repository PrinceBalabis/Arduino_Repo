/**
 *  HMListenThread
 *  Idles until a message is received from a client.
 **/

static msg_t HNListenThread(void *arg) {
  chThdSleepMilliseconds(2000); // Needs to wait for other threads to start or else Arduino might crash
  
  Serial.println(F("HMListenThread started, dont forget to have a unique nodeID!"));

  while (1) {
    if (msgReceived) { // Check message if a new message is received
      if (msgType == typeCommand) { // If its a simple command
        switch (msgContent) {
          case cmdToggleSpeakerPower:
            toggleSpeakerPower();
            
            break;
        }

      } else if (msgType == typeAsk) { // If its a question
        //Questions here
        switch (msgContent) {
          case cmdExampleAskCommand:
            // Send return-message back to client
            homeNetwork.respondToQuestion(msgSender, cmdExampleResponseData);
            break;
        }
      }
      msgReceived = false; // Listen for new message
    }
    chThdSleepMilliseconds(homeNetworkCheckMessageDelay); // Check every few ms if a message is received
  }
  return 0;
}
