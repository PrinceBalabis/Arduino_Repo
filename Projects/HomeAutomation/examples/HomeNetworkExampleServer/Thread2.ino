/**
 *  Thread2
 *  Idles until a message is received from a client.
 **/

static msg_t Thread2(void *arg) {
  chThdSleepMilliseconds(3000); // Give some time for HomeNetwork thread to start

  while (1) {
    if (msgReceived) {
      if (msgContent == cmdExampleCommand) {
        // Send return-message back to client
        bool msgSent = homeNetwork.responseExampleDataToClient(msgSender, cmdExampleResponceData);
        if (msgSent) {
          Serial.println(F("Answered"));
        } else if (!msgSent) {
          Serial.println(F("Timeout"));
        }
      }
      msgReceived = false;
    }
    chThdSleepMilliseconds(40); // Check every few ms if a message is received
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
  //  Serial.println(msgSender);
  //  Serial.print(F("Raw Type content: "));
  //  Serial.write(msgType);
  //  Serial.print(F("\nRaw Message content: "));
  //  Serial.println(msgContent);
  //  Serial.println(F("-----------------------------------------------"));
}

