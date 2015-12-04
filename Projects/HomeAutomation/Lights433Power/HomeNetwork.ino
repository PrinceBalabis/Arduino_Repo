/**
   homeNetworkMessageReceived()
   This function is executed automatically by the HomeNetwork Library when a message is received.
*/

void homeNetworkMessageReceived(uint16_t msgSender, unsigned char msgType, int32_t msgContent) {
  Serial.print(F("New Message.. "));
  switch (msgType) {
    case HOME_TYPE_COMMAND: // If its a simple command
      switch (msgContent) {
        case HOME_LIGHTS433POWER_CMD_MAINLIGHTS_TOGGLE:
          toggleLights();
          break;
        case HOME_LIGHTS433POWER_CMD_MAINLIGHTS_ON:
          setMainLights(true);
          break;
        case HOME_LIGHTS433POWER_CMD_MAINLIGHTS_OFF:
          setMainLights(false);
          break;
        case HOME_LIGHTS433POWER_CMD_PAINTINGLIGHTS_ON:
          setPaintingLightsOn();
          Serial.println(F("Turned Painting Lights on"));
          break;
        case HOME_LIGHTS433POWER_CMD_PAINTINGLIGHTS_OFF:
          setPaintingLightsOff();
          Serial.println(F("Turned Painting Lights off"));
          break;
        case HOME_LIGHTS433POWER_CMD_PAINTINGLIGHTS_TOGGLE:
          Serial.print(F("Toggled Painting Lights..."));
          togglePaintingLights();
          break;
      }
      break;
    case HOME_TYPE_QUESTION: // If its a question
      switch (msgContent) {
        case HOME_LIGHTS433POWER_QSN_MAINLIGHTS_STATUS:
          homeNetwork.respondToQuestion(msgSender, mainLightsStatus);
          Serial.println(F("Lights status question"));
          break;
        case HOME_LIGHTS433POWER_QSN_PAINTINGLIGHTS_STATUS:
          homeNetwork.respondToQuestion(msgSender, getPaintingLightStatus());
          Serial.println(F("Answered Painting lights status"));
          break;
      }
      break;
  }
}

/**
   Thread for the Home Network
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

