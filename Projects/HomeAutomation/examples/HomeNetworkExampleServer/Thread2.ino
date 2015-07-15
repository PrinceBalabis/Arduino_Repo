/**
 *  Thread2
 *  Idles until a message is received from a client.
 **/

static msg_t Thread2(void *arg) {
  chThdSleepMilliseconds(2100); // Give some time for HomeNetwork thread to start

  int count = 0;

  while (1) {
    // Wait for message to receive
    while (msgReceived == false) {
      chThdSleepMilliseconds(40); // Check every few ms if a message is received
    }
    Serial.print(count++);
    if (msgContent == cmdExampleCommand) {
      // Send return-message back to client
      uint8_t msgSent = homeNetwork.write(msgSender, cmdExampleResponceData, msgTypeResponse);
      if (msgSent) {
        Serial.println(F(":Responded"));
      } else if (!msgSent) {
        Serial.println(F(":Timeout!"));
      }
    }

    msgReceived = 0;
  }

  return 0;
}

/**
 * homeNetworkMessageReceived()
 * This function is executed automatically by the HomeNetwork Library when a message is received.
 */
void homeNetworkMessageReceived(uint16_t _msgSender, unsigned char _msgType, int32_t _msgReceived) {
  // Save received data to global variables to be used by other threads
  msgSender = _msgSender;
  msgType = _msgType;
  msgContent = _msgReceived;
  msgReceived = true;
  //  Serial.print(F("-------------Received Data Raw----------------- \nRaw Message sender: "));
  //  Serial.println(_msgSender);
  //  Serial.print(F("Raw Type content: "));
  //  Serial.write(_msgType);
  //  Serial.print(F("\nRaw Message content: "));
  //  Serial.println(_msgReceived);
  //  Serial.println(F("-----------------------------------------------"));
}

