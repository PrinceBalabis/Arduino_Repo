/**
 *  HMListenThread
 *  Idles until a message is received from a client.
 **/
static msg_t HNListenThread(void *arg) {
  Serial.print(F("HMListenThread begin, NodeID: "));
  Serial.println(nodeID);

  while (1) {
    if (msgReceived) { // Check message if a new message is received
      if (msgType == typeCommand) { // If its a simple command
        switch (msgContent) {
          case cmdToggleLights:
            toggleLights(); // Toggle lights
            break;
          case cmdSetLightsOn:
            setLightsOn();
            break;
          case cmdSetLightsOff:
            setLightsOff();
            break;
        }
      } else if (msgType == typeAsk) { // If its a question
        switch (msgContent) {
          case cmdGetLightsStatus:
            homeNetwork.respondToQuestion(msgSender, mainLightsState);
            break;
        }
      }
      msgReceived = false; // Listen for new message
    }
    chThdSleepMilliseconds(homeNetworkCheckMessageDelay); // Check every few ms if a message is received
  }
  return 0;
}
