/**
 *  ExampleSendThread
 *  Sends a messeger to Node A every few moments
 **/

static msg_t ExampleSendThread(void *arg) {
  Serial.println(F("ExampleSendThread begin"));

  uint32_t count = 0;

  while (1) {
    chThdSleepMilliseconds(2000);

    // Send command to toggle lights
    Serial.print(count++);
    bool msgSent = homeNetwork.toggleMainLights();
    if (msgSent) {
      Serial.println(F(":Received"));
    } else if (!msgSent) {
      Serial.println(F(":Timeout!"));
    }

    chThdSleepMilliseconds(2000);

    // Ask status of main lights
    Serial.print(count++);
    int32_t msgResponse;
    homeNetwork.askMainLightsStatus(&msgResponse);
    Serial.print(":Status:");
    Serial.println(msgResponse);
  }
  return 0;
}

