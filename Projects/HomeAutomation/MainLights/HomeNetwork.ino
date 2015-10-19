/**
 * homeNetworkMessageReceived()
 * This function is executed automatically by the HomeNetwork Library when a message is received.
 */

void homeNetworkMessageReceived(uint16_t msgSender, unsigned char msgType, int32_t msgContent) {
  Serial.print(F("New Message.. "));
  switch (msgType) {
    case HOME_TYPE_COMMAND: // If its a simple command
      switch (msgContent) {
        case HOME_MAINLIGHTS_CMD_MAINLIGHTS_TOGGLE:
          toggleLights();
          break;
        case HOME_MAINLIGHTS_CMD_MAINLIGHTS_ON:
          setMainLights(true);
          break;
        case HOME_MAINLIGHTS_CMD_MAINLIGHTS_OFF:
          setMainLights(false);
          break;
      }
      break;
    case HOME_TYPE_QUESTION: // If its a question
      switch (msgContent) {
        case HOME_MAINLIGHTS_QSN_MAINLIGHTS_STATUS:
          homeNetwork.respondToQuestion(msgSender, mainLightsStatus);
          Serial.println(F("Lights status question"));
          break;
      }
      break;
  }
}

/**
*  Thread for the Home Network
**/
NIL_WORKING_AREA(homeNetworkThread, 170); // 100 bytes seems to work fine even with Home Network debug on
NIL_THREAD(HomeNetworkThread, arg)
{
  Serial.println("Started HomeNetworkThread");
  // The thread stops at this function, this function has a loop which keeps the network
  // auto updated and executes 'homeNetworkMessageReceived()' when a message is received
  // This function has to run on a thread or else home network wont work.
  homeNetwork.update();
}

