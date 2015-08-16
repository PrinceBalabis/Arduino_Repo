/**
 * homeNetworkMessageReceived()
 * This function is executed automatically by the HomeNetwork Library when a message is received.
 */
void homeNetworkMessageReceived(uint16_t msgSender, unsigned char msgType, int32_t msgContent) {
  switch (msgType) {
    case HOME_TYPE_COMMAND: // If its a simple command
      Serial.print(F("Command"));
      //Send message to CommandExecutionerThread for decoding
      executeCommand(msgContent, msgSender);
      break;
    case HOME_TYPE_QUESTION: // If its a question
      Serial.print(F("Question"));
      switch (msgContent) {
          //No questions yet
      }
  }
}
