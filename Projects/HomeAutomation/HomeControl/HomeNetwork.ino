/**
 * homeNetworkMessageReceived()
 * This function is executed automatically by the HomeNetwork Library when a message is received.
 */
void homeNetworkMessageReceived(uint16_t msgSender, unsigned char msgType, int32_t msgContent) {
  switch (msgType) {
    case typeCommand: // If its a simple command
      Serial.print(F("Command"));
      //Send message to CommandExecutionerThread for decoding
      executeCommand(msgContent, COMMANDEXECUTIONER_MSGORIGIN_HOMENETWORK);
      break;
    case typeAsk: // If its a question
      Serial.print(F("Question"));
      switch (msgContent) {
          //No questions yet
      }
  }
}
