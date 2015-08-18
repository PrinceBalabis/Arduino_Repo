/**
 * homeNetworkMessageReceived()
 * This function is executed automatically by the HomeNetwork Library when a message is received.
 */
void homeNetworkMessageReceived(uint16_t msgSender, unsigned char msgType, int32_t msgContent) {
  switch (msgType) {
        case HOME_TYPE_COMMAND: // If its a simple command
          switch (msgContent) {
            case HOME_SPEAKER_CMD_POWER_TOGGLE:
              executeCommand = HOME_SPEAKER_CMD_POWER_TOGGLE;
              nilSemSignal(&cmdExSem);
              break;
            case HOME_SPEAKER_CMD_POWER_ON:
              executeCommand = HOME_SPEAKER_CMD_POWER_ON;
              nilSemSignal(&cmdExSem);
              break;
            case HOME_SPEAKER_CMD_POWER_OFF:
              executeCommand = HOME_SPEAKER_CMD_POWER_OFF;
              nilSemSignal(&cmdExSem);
              break;
            case HOME_SPEAKER_CMD_MUTE_TOGGLE:
              executeCommand = HOME_SPEAKER_CMD_MUTE_TOGGLE;
              nilSemSignal(&cmdExSem);
              break;
            case HOME_SPEAKER_CMD_VOLUME_UP:
              executeCommand = HOME_SPEAKER_CMD_VOLUME_UP;
              nilSemSignal(&cmdExSem);
              break;
            case HOME_SPEAKER_CMD_VOLUME_DOWN:
              executeCommand = HOME_SPEAKER_CMD_VOLUME_DOWN;
              nilSemSignal(&cmdExSem);
              break;
            case HOME_SPEAKER_CMD_MODE_TOGGLE:
              executeCommand = HOME_SPEAKER_CMD_MODE_TOGGLE;
              nilSemSignal(&cmdExSem);
              break;
          }
          break;
        case HOME_TYPE_QUESTION: // If its a question
          //Questions here
          break;
      }
}

/**
*  Thread for the Home Network
**/
NIL_WORKING_AREA(homeNetworkThread, 32); // 32 bytes seems to work fine even with Home Network debug on
NIL_THREAD(HomeNetworkThread, arg)
{
  Serial.println("Started HomeNetworkThread");
  // The thread stops at this function, this function has a loop which keeps the network
  // auto updated and executes 'homeNetworkMessageReceived()' when a message is received
  // This function has to run on a thread or else home network wont work.
  homeNetwork.update();
}

