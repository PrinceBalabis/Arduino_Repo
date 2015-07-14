static msg_t Thread2(void *arg) {
  Serial.print(F("\n\n--------------------------------------------------------------- \nExample CLIENT for Prince Home Network \nThis node ID: "));
  Serial.println(nodeID);
  chThdSleepMilliseconds(1700); // Give some time for HomeNetwork thread to start

  while (1) {
    // Send message
    Serial.println(F("-------------STARTING: Message Send Program-----------------"));

    uint16_t msgReceiver;
    int32_t msgResponse;
    uint8_t msgSent = homeNetwork.askExampleDataToExampleServer(&msgReceiver, &msgResponse);
    if (msgSent) {
      Serial.println(F("Response received: "));
      Serial.println(msgResponse);
    } else if (!msgSent) {
      Serial.println(F("ERROR!: Failed to send message to parent."));
    } else if (msgSent == 2) {
      Serial.println(F("OBS! FINALLY SENT MESSAGE AFTER SEVERAL RETRIES. BAD SIGNAL WITH PARENT!"));
    }

//    //Clear variables to reset
//    msgSender = -1;
//    msgContent = -1;
    Serial.println(F("---------------DONE: Message Send Program-------------------"));

    chThdSleepMilliseconds(4000); // Redo this send program every 4 seconds
  }

  return 0;
}

/**
 * homeNetworkMessageReceived()
 * This function is executed automatically by the HomeNetwork Library when a message is received.
 */
void homeNetworkMessageReceived(int16_t _msgSender, unsigned char _msgType, int32_t _msgReceived) {
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

