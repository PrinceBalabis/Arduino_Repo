/**
 * homeNetworkMessageReceived()
 * This function is executed automatically by the HomeNetwork Library when a message is received.
 */
void homeNetworkMessageReceived(uint16_t msgSender, unsigned char msgType, int32_t msgContent) {
  switch (msgType) {
    case HOME_TYPE_COMMAND: // If its a simple command
      switch (msgContent) {
        case HOME_RF433MHZ_CMD_PAINTINGLIGHTS_ON:
          setPaintingLightsOn();
          Serial.println(F("Turned Painting Lights on"));
          break;
        case HOME_RF433MHZ_CMD_PAINTINGLIGHTS_OFF:
          setPaintingLightsOff();
          Serial.println(F("Turned Painting Lights off"));
          break;
        case HOME_RF433MHZ_CMD_PAINTINGLIGHTS_TOGGLE:
          togglePaintingLights();
          Serial.println(F("Toggled Painting Lights"));
          break;
      }
      break;
    case HOME_TYPE_QUESTION: // If its a question
      switch (msgContent) {
        case HOME_RF433MHZ_QSN_PAINTINGLIGHTS_STATUS:
          homeNetwork.respondToQuestion(msgSender, getPaintingLightStatus());
          Serial.println(F("Answered Painting lights status"));
          break;
      }
      break;
  }
}

/**
*  Thread for the Home Network
**/
NIL_WORKING_AREA(homeNetworkThread, 150); // 36 bytes seems to work fine even with Home Network debug on
NIL_THREAD(HomeNetworkThread, arg)
{
  Serial.println("Started HomeNetworkThread");
  // The thread stops at this function, this function has a loop which keeps the network
  // auto updated and executes 'homeNetworkMessageReceived()' when a message is received
  // This function has to run on a thread or else home network wont work.
  homeNetwork.update();
}
