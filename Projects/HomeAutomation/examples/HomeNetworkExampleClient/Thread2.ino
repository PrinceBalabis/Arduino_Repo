static msg_t Thread2(void *arg) {
  Serial.print(F("\n\n--------------------------------------------------------------- \nExample CLIENT for Prince Home Network \nThis node ID: "));
  Serial.println(nodeID);
  chThdSleepMilliseconds(4500); // Give some time for HomeNetwork thread to start

  while (1) {
    // Send message
    Serial.println(F("-------------Message Send Program Starting------------------"));

    uint16_t msgReceiver;
    uint8_t msgSent = homeNetwork.sendExampleDataToExampleServer(&msgReceiver);
    if (msgSent) {
      Serial.println(F("Message sent"));
    } else if (!msgSent) {
      Serial.println(F("ERROR!: Failed to send message to parent."));
    } else if (msgSent == 2) {
      Serial.println(F("OBS! FINALLY SENT MESSAGE AFTER SEVERAL RETRIES. BAD SIGNAL WITH PARENT!"));
    }
    Serial.print(F("Sent message to node: "));
    Serial.println(msgReceiver);

    Serial.println(F("Waiting for response..."));
    // Wait for return-message to receive
    while (msgSender != msgReceiver) {
      chThdSleepMilliseconds(25); // Check every 25ms if message is received
    }

    //Print return-message
    Serial.println(F("Response received: "));
    Serial.println(msgContent);

    //Clear variables to reset
    msgSender = -1;
    msgContent = -1;
    Serial.println(F("---------------Message Send Program Done-------------------"));

    chThdSleepMilliseconds(4000); // Redo this send program every 4 seconds
  }

  return 0;
}

