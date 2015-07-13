static msg_t Thread2(void *arg) {
  Serial.print(F("\n\n--------------------------------------------------------------- \nExample CLIENT for Prince Home Network \nThis node ID: "));
  Serial.println(nodeID);
  chThdSleepMilliseconds(4500); // Give some time for HomeNetwork thread to start

  while (1) {
    // Send message
    Serial.println(F("-------------Message Send Program Starting------------------"));

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
    Serial.println(F("---------------Message Send Program Done-------------------"));

    chThdSleepMilliseconds(4000); // Redo this send program every 4 seconds
  }

  return 0;
}

void homeNetworkMessageReceived() {
  int16_t msgSenderReceived;
  int32_t msgReceived;
  unsigned char msgTypeReceived = 'Z';
  msgSenderReceived = homeNetwork.read(&msgReceived, &msgTypeReceived);

  // Put code in this if-statement which should occur when a message is received
  if (msgReceived != -1) {
//    msgSender = msgSenderReceived;
//    msgContent = msgReceived;
//    msgType = msgTypeReceived;
    Serial.print(F("---------------Received Data Raw------------------- \nRaw Message sender: "));
//    Serial.println(msgSender);
    Serial.println(msgSenderReceived);
    Serial.println(F("Raw Type content: "));
//    Serial.write(msgType);
    Serial.write(msgTypeReceived);
    Serial.print(F("\nRaw Message content: "));
//    Serial.println(msgContent);
    Serial.println(msgReceived);
    Serial.println(F("-----------------------------------------------"));
  }
}

