/**
 *  HMListenThread
 *  Idles until a message is received from a client.
 **/
static msg_t HNListenThread(void *arg) {
  chThdSleepMilliseconds(2000); // Needs to wait for other threads to start or else Arduino might crash
  Serial.print(F("HMListenThread begin, NodeID: "));
  Serial.println(nodeID);

  while (1) {
    if (msgReceived) { // Check message if a new message is received
      if (msgType == typeCommand) { // If its a simple command
        switch (msgContent) {
          case cmdSetPaintingLightsOn:
            setPaintingLightsOn(); // Toggle lights
            break;
          case cmdSetPaintingLightsOff:
            setPaintingLightsOff();
            break;
          case cmdTogglePaintingLights:
            togglePaintingLights();
            break;
          case cmdSetSpeakerPowerSwitchOn:
            setSpeakerPowerSwitchOn();
            break;
          case cmdSetSpeakerPowerSwitchOff:
            setSpeakerPowerSwitchOff();
            break;
          case cmdToggleSpeakerPowerSwitch:
            toggleSpeakerPowerSwitch();
            break;
        }
      } else if (msgType == typeAsk) { // If its a question
        switch (msgContent) {
          case cmdGetPaintingLightsStatus:
            homeNetwork.respondToQuestion(msgSender, getPaintingLightStatus());
            break;
          case cmdGetSpeakerPowerStatus:
            homeNetwork.respondToQuestion(msgSender, getSpeakerPowerSwitchStatus());
            break;
        }
      }
      msgReceived = false; // Listen for new message
    }
    chThdSleepMilliseconds(homeNetworkCheckMessageDelay); // Check every few ms if a message is received
  }
  return 0;
}
