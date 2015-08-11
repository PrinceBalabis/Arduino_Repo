/**
 *  HNListenThread
 *  Idles until a message is received from a client.
 **/

static msg_t HNListenThread(void *arg) {
  Serial.println(F("Home Network Listen Thread started"));
  homeNetwork.setAutoUpdateTime(homeNetworkAutoUpdateTime);

  while (1) {
    // Pause loop while waiting for a message
    chSemWait(&homeNetworkSem);

    switch (msgType) {
      case typeCommand: // If its a simple command
        switch (msgContent) {
          case cmdToggleLights:
            toggleLights(); // Toggle lights
            break;
          case cmdSetLightsOn:
            setMainLights(true);
            break;
          case cmdSetLightsOff:
            setMainLights(false);
            break;
        }
        break;
      case typeAsk: // If its a question
        switch (msgContent) {
          case cmdGetLightsStatus:
            homeNetwork.respondToQuestion(msgSender, mainLightsStatus);
//            Serial.println(F("Main Lights Status question"));
            break;
        }
        break;
    }

    homeNetwork.pauseAutoUpdate(false); // Resume network update in order to get queued commands
  }
  return 0;
}
