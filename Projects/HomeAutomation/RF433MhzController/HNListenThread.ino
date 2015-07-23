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
          case cmdSetPaintingLightsOn:
            setPaintingLightsOn();
            Serial.println(F("Turned Painting Lights on"));
            break;
          case cmdSetPaintingLightsOff:
            setPaintingLightsOff();
            Serial.println(F("Turned Painting Lights off"));
            break;
          case cmdTogglePaintingLights:
            togglePaintingLights();
            Serial.println(F("Toggled Painting Lights"));
            break;
          case cmdSetSpeakerPowerSwitchOn:
            setSpeakerPowerSwitchOn();
            Serial.println(F("Turned Speaker on"));
            break;
          case cmdSetSpeakerPowerSwitchOff:
            setSpeakerPowerSwitchOff();
            Serial.println(F("Turned Speaker off"));
            break;
          case cmdToggleSpeakerPowerSwitch:
            toggleSpeakerPowerSwitch();
            Serial.println(F("Toggled Speaker"));
            break;
        }
      } else if (msgType == typeAsk) { // If its a question
        switch (msgContent) {
          case cmdGetPaintingLightsStatus:
            homeNetwork.respondToQuestion(msgSender, getPaintingLightStatus());
            Serial.println(F("Answered: Painting lights status"));
            break;
          case cmdGetSpeakerPowerStatus:
            homeNetwork.respondToQuestion(msgSender, getSpeakerPowerSwitchStatus());
            Serial.println(F("Answered: Speaker status"));
            break;
        }
      }
      msgReceived = false; // Listen for new message
    }
    chThdSleepMilliseconds(homeNetworkCheckMessageDelay); // Check every few ms if a message is received
  }
  return 0;
}
