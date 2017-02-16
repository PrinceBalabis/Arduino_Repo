/**
    ExampleSendThread
    Sends a message to a node at a set interval for a limited amount of times
 **/

NIL_WORKING_AREA(exampleSendThread, 300);
NIL_THREAD(ExampleSendThread, arg) {
  /*************************************************************
     TWEAK MESSAGE AND SEND OPTIONS HERE
   *************************************************************/
  const uint32_t sendRepeats = 100; // Set amount of times to send message
  const uint32_t sendInterval = 0; // Set delay in between sending messages

  const int32_t msgContent = 1;
  const uint16_t msgReceiver = 00;
  const unsigned char msgType = 'A';
  const uint8_t sendTries = 2;
  const uint16_t responsetimeout = 2000;
  /*************************************************************/

  Serial.println(F("Testing beginning"));
  nilThdSleepMilliseconds(2000);
  uint32_t count = 1;
  for (int repeatStatus = 0; repeatStatus < sendRepeats; repeatStatus++) {
    Serial.print(count++);
    Serial.print(F(":"));
    int32_t msgResponse;
    if (homeNetwork.sendQuestion(msgReceiver, msgContent, &msgResponse, responsetimeout)) {
      Serial.print(F("Message successfully Received->"));
      Serial.println(msgResponse);
    } else {
      Serial.println(F("ERROR SENDING MESSAGE!"));
      while (1) {}
    }

    if (sendInterval > 0) {
      nilThdSleepMilliseconds(sendInterval);
    }
  }

  // Stop program when done sending command
  while (1)
  {
  }
}

