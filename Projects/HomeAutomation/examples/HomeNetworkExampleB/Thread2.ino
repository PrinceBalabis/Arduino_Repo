/**
 *  Thread2
 *  Asks a question to server every few seconds
 **/

static msg_t Thread2(void *arg) {
  Serial.println(F("Thread2 begin"));

  uint32_t count = 0;

  while (1) {

    // Ask question to ExampleNodeA
    Serial.print(count++);
    int32_t msgResponse;
    bool msgSent = homeNetwork.askExampleDataA(&msgResponse);
    if (msgSent) {
      Serial.println(F(":Received"));
    } else if (!msgSent) {
      Serial.println(F(":Timeout!"));
    }

    chThdSleepMilliseconds(1); // Redo this send program every few moments, give enough time for other threads to run
  }
  return 0;
}

