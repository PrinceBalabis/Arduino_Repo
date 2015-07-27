/**
 *  HNListenThread
 *  Idles until a message is received from a client.
 **/
static msg_t HNListenThread(void *arg) {
  Serial.println(F("Home Network Listen Thread started"));
  homeNetwork.setAutoUpdateTime(homeNetworkAutoUpdateTime);

  while (1) {
    if (msgReceived) { // Check message if a new message is received
      homeNetwork.pauseAutoUpdate(true); // Pause network update in order to queue commands

      switch (msgType) {
        case typeCommand: // If its a simple command
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
          break;
        case typeAsk: // If its a question
          switch (msgContent) {
            case cmdGetLightsStatus:
              homeNetwork.respondToQuestion(msgSender, mainLightsState);
              break;
          }
          break;
      }

      homeNetwork.pauseAutoUpdate(false); // Resume network update in order to get queued commands
      msgReceived = false; // Listen for new message
    }
    chThdSleepMilliseconds(homeNetworkCheckMessageDelay); // Check every few ms if a message is received
  }
  return 0;
}
