/**
 *  ExampleSendThread
 *  Sends a messeger to Node A every few moments
 **/

static msg_t ExampleSendThread(void *arg) {
  Serial.println(F("ExampleSendThread begin"));

  uint32_t count = 0;

  while (1) {
    chThdSleepMilliseconds(1643); // Redo this send program every few moments, give enough time for other threads to run

    // Ask question to ExampleNodeA
    Serial.print(count++);
    int32_t msgResponse;
    bool msgSent = homeNetwork.askExampleDataB(&msgResponse);
    if (msgSent) {
      Serial.println(F(":Received"));
    } else if (!msgSent) {
      Serial.println(F(":Timeout!"));
    }


  }
  return 0;
}

