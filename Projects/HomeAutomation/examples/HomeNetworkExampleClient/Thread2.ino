/**
 *  Thread2
 *  Asks a question to server every few seconds
 **/

static msg_t Thread2(void *arg) {
  chThdSleepMilliseconds(4000); // Give some time for HomeNetwork thread to start

  int count = 0;

  while (1) {
    // Send message
    Serial.print(count++);
    int32_t msgResponse;
    uint8_t msgSent = homeNetwork.askExampleDataToExampleServer(&msgResponse);
    if (msgSent == 1) {
      Serial.println(F(":Received"));
    } else if (msgSent == 0) {
      Serial.println(F(":Timeout!"));
    }
    chThdSleepMilliseconds(100); // Redo this send program every moments
  }
  return 0;
}

/**
 * homeNetworkMessageReceived()
 * This function is executed automatically by the HomeNetwork Library when a message is received.
 */
void homeNetworkMessageReceived(uint16_t _msgSender, unsigned char _msgType, int32_t _msgReceived) {
  // Put code in this if-statement which should occur when a message is received
  // All this Example Client does is print out data received from server
  Serial.print(F("-------------Received Data Raw----------------- \nRaw Message sender: "));
  Serial.println(_msgSender);
  Serial.print(F("Raw Type content: "));
  Serial.write(_msgType);
  Serial.print(F("\nRaw Message content: "));
  Serial.println(_msgReceived);
  Serial.println(F("-----------------------------------------------"));
}

