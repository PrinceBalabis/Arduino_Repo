/**
 *  HMListenThread
 *  Idles until a message is received from a client.
 **/

static msg_t HNListenThread(void *arg) {
  chThdSleepMilliseconds(2500); // Needs to wait for other threads to start or else Arduino might crash

  Serial.println(F("HMListenThread started, dont forget to have a unique nodeID!"));

  while (1) {
    if (msgReceived) { // Check message if a new message is received
      if (msgType == typeCommand) { // If its a simple command
        switch (msgContent) {
          case cmdToggleSpeakerPower:
            executeCommand = cmdToggleSpeakerPower;
            // Signal CommandExecutionerThread to run command
            chSemSignal(&cmdExSem);
            break;
          case cmdToggleSpeakerMute:
            executeCommand = cmdToggleSpeakerMute;
            // Signal CommandExecutionerThread to run command
            chSemSignal(&cmdExSem);
            break;
          case cmdSetSpeakerVolumeUp:
            executeCommand = cmdSetSpeakerVolumeUp;
            // Signal CommandExecutionerThread to run command
            chSemSignal(&cmdExSem);
            break;
          case cmdSetSpeakerVolumeDown:
            executeCommand = cmdSetSpeakerVolumeDown;
            // Signal CommandExecutionerThread to run command
            chSemSignal(&cmdExSem);
            break;
          case cmdToggleSpeakerMode:
            executeCommand = cmdToggleSpeakerMode;
            // Signal CommandExecutionerThread to run command
            chSemSignal(&cmdExSem);
            break;
        }

      } else if (msgType == typeAsk) { // If its a question
        //Questions here
      }
      msgReceived = false; // Listen for new message
    }
    chThdSleepMilliseconds(homeNetworkCheckMessageDelay); // Check every few ms if a message is received
  }
  return 0;
}
