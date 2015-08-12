/**
 * homeNetworkMessageReceived()
 * This function is executed automatically by the HomeNetwork Library when a message is received.
 */
void homeNetworkMessageReceived(uint16_t msgSender, unsigned char msgType, int32_t msgContent) {
  Serial.print(F("New Message.. "));

   switch (msgType) {
    case typeCommand: // If its a simple command
      switch (msgContent) {
        case NODE_MAINLIGHTS_CMD_MAINLIGHTS_TOGGLE:
          toggleLights();
          break;
        case NODE_MAINLIGHTS_CMD_MAINLIGHTS_ON:
          setMainLights(true);
          break;
        case NODE_MAINLIGHTS_CMD_MAINLIGHTS_OFF:
          setMainLights(false);
          break;
      }
      break;
    case typeAsk: // If its a question
      switch (msgContent) {
        case NODE_MAINLIGHTS_QSN_MAINLIGHTS_STATUS:
          homeNetwork.respondToQuestion(msgSender, mainLightsStatus);
          Serial.println(F("Main Lights Status question"));
          break;
      }
      break;
  }
}
