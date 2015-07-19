/**
 *  Thread2
 *  Idles until a message is received from a client.
 **/

static msg_t Thread2(void *arg) {
  Serial.println(F("Thread2 begin"));

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
    chThdSleepMilliseconds(homeNetworkCheckMessageDelay); // Check every few ms if a message is received
  }
  return 0;
}
