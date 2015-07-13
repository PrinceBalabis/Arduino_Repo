static msg_t Thread2(void *arg) {
  Serial.println(F("-------------------------------------------"));
  Serial.println(F("Example SERVER for Prince Home Network"));
  Serial.print(F("This node ID: "));
  Serial.println(nodeID);
  chThdSleepMilliseconds(4000); // Give some time for HomeNetwork thread to start

  while (1) {
    // Wait for message to receive
    Serial.println(F("-------------------------------------------"));
    Serial.println(F("WAITING FOR MESSAGE"));
    while (msgContent == -1) {
      chThdSleepMilliseconds(50); // Check every 50ms if a message is received
    }

    if (msgContent == 12345) {
      // Send return-message back to client
      Serial.println(F("MESSAGE SEND PROGRAM TO CLIENT"));
      uint16_t msgReceiver = msgSender;
      uint8_t msgSent = homeNetwork.write(msgReceiver, 67890);
      if (msgSent) {
        Serial.println(F("MESSAGE AWAY"));
      } else if (!msgSent) {
        Serial.println(F("ERROR!: Failed to send message to parent."));
      } else if (msgSent == 2) {
        Serial.println(F("FINALLY SENT MESSAGE AFTER SEVERAL RETRIES. BAD SIGNAL WITH PARENT!"));
      }


    }
    
    //Clear variables to reset
    msgSender = -1;
    msgContent = -1;
    
    chThdSleepMilliseconds(100); // Redo this send program every 200 ms
  }

  return 0;
}

