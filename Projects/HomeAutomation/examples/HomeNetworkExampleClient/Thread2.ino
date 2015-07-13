static msg_t Thread2(void *arg) {
  Serial.println(F("-------------------------------------------"));
  Serial.println(F("Example CLIENT for Prince Home Network"));
  Serial.print(F("This node ID: "));
  Serial.println(nodeID);
  chThdSleepMilliseconds(4500); // Give some time for HomeNetwork thread to start
  Serial.println(); // Extra row for easier serial reading

  while (1) {
    // Send message
    Serial.println(F("-------------------------------------------"));
    Serial.println(F("MESSAGE SEND PROGRAM"));
    uint16_t msgReceiver;
    uint8_t msgSent = homeNetwork.sendExampleDataToExampleServer(&msgReceiver);
    if (msgSent) {
      Serial.println(F("MESSAGE AWAY"));
    } else if (!msgSent) {
      Serial.println(F("ERROR!: Failed to send message to parent."));
    } else if (msgSent == 2) {
      Serial.println(F("FINALLY SENT MESSAGE AFTER SEVERAL RETRIES. BAD SIGNAL WITH PARENT!"));
    }
    Serial.print(F("SENDING MESSAGE TO NODE: "));
    Serial.println(msgReceiver);

    Serial.print(F("WAITING FOR RESPONSE FROM MESSAGE RECEIVER: "));
    // Wait for return-message to receive
    while (msgSender != msgReceiver) {
      chThdSleepMilliseconds(50); // Check every 25ms if message is received
    }

    //Print return-message
    Serial.println(F("MESSAGE RECEIVED: "));
    Serial.println(msgContent);
    Serial.println(); // Extra row for easier serial reading

    //Clear variables to reset
    msgSender = -1;
    msgContent = -1;

    chThdSleepMilliseconds(2000); // Redo this send program every 2 seconds
  }

  return 0;
}

