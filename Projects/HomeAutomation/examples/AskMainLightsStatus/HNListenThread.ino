/**
 *  HNListenThread
 *  Idles until a message is received from a client.
 **/

static msg_t HNListenThread(void *arg) {
  Serial.println(F("HMListenThread started, dont forget to have a unique nodeID!"));

  while (1) {
    if (msgReceived) { // Check message if a new message is received
      bool msgSent = false;

      if (msgType == typeCommand) { // If its a simple command
        //Commands here
      } else if (msgType == typeAsk) { // If its a question
        //Questions here
        switch (msgContent) {
        }
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
