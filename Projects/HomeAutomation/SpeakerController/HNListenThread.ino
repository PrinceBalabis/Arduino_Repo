/**
 *  HMListenThread
 *  Idles until a message is received from a client.
 **/

static msg_t HNListenThread(void *arg) {
  Serial.println(F("Home Network Listener started"));
  homeNetwork.setAutoUpdateTime(homeNetworkAutoUpdateTime);

  while (1) {
    if (msgReceived) { // Check message if a new message is received
      homeNetwork.pauseAutoUpdate(true); // Pause network update in order to queue commands

      switch (msgType) {
        case typeCommand: // If its a simple command
          switch (msgContent) {
            case cmdToggleSpeakerPower:
              executeCommand = cmdToggleSpeakerPower;
              chSemSignal(&cmdExSem);
              break;
            case cmdSetSpeakerPowerOn:
              executeCommand = cmdSetSpeakerPowerOn;
              chSemSignal(&cmdExSem);
              break;
            case cmdSetSpeakerPowerOff:
              executeCommand = cmdSetSpeakerPowerOff;
              chSemSignal(&cmdExSem);
              break;
            case cmdToggleSpeakerMute:
              executeCommand = cmdToggleSpeakerMute;
              chSemSignal(&cmdExSem);
              break;
            case cmdSetSpeakerVolumeUp:
              executeCommand = cmdSetSpeakerVolumeUp;
              chSemSignal(&cmdExSem);
              break;
            case cmdSetSpeakerVolumeDown:
              executeCommand = cmdSetSpeakerVolumeDown;
              chSemSignal(&cmdExSem);
              break;
            case cmdToggleSpeakerMode:
              executeCommand = cmdToggleSpeakerMode;
              chSemSignal(&cmdExSem);
              break;
          }
          break;
        case typeAsk: // If its a question
          //Questions here
          break;
      }

      msgReceived = false; // Listen for new message
      homeNetwork.pauseAutoUpdate(false); // Resume network update in order to get queued commands
    }
    chThdSleepMilliseconds(homeNetworkCheckMessageDelay); // Check every few ms if a message is received
  }
  return 0;
}
