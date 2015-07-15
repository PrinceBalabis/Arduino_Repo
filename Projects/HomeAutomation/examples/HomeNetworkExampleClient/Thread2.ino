/**
 *  Thread2
 *  Asks a question to server every few seconds
 **/

static msg_t Thread2(void *arg) {
  chThdSleepMilliseconds(5000); // Give some time for HomeNetwork thread to start

  uint32_t count = 0;

  while (1) {
    // Ask question to server demo
    Serial.print(count++);
    int32_t msgResponse;
    bool msgSent = homeNetwork.askExampleDataToExampleServer(&msgResponse);
    if (msgSent == 1) {
      Serial.println(F(":Received"));
    } else if (msgSent == 0) {
      Serial.println(F(":Timeout!"));
    }
    chThdSleepMilliseconds(1); // Redo this send program every few moments, give enough time for other threads to run
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

