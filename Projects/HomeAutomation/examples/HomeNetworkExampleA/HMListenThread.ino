/**
 *  HMListenThread
 *  Idles until a message is received from a client.
 **/

static msg_t HMListenThread(void *arg) {
  Serial.print(F("HMListenThread begin, NodeID: "));
  Serial.println(nodeID);
 
  while (1) {
    if (msgReceived) { // Check message if a new message is received
      bool msgSent = false;
      switch (msgContent) {
        case cmdExampleAskCommand:
          // Send return-message back to client
          msgSent = homeNetwork.respondToQuestion(msgSender, cmdExampleResponseData);
          break;
      }
      if (msgSent) {
        Serial.println(F("Answered"));
      } else if (!msgSent) {
        Serial.println(F("Timeout"));
      }
      msgReceived = false; // Listen for new message
    }
    chThdSleepMilliseconds(homeNetworkCheckMessageDelay); // Check every few ms if a message is received
  }
  return 0;
}
