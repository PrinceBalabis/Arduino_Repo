/**
 *  Thread2
 *  Asks a question to server every few seconds
 **/

static msg_t Thread2(void *arg) {
  chThdSleepMilliseconds(5000); // Give some time for HomeNetwork thread to start
  Serial.println(F("thread2 begin"));

  uint32_t count = 0;

  while (1) {

    // Ask question to server demo
    Serial.print(count++);
    
    int32_t msgResponse;
    bool msgSent = homeNetwork.askExampleDataToExampleServer(&msgResponse);
    if (msgSent == 1) {
      Serial.println(F(":Received"));
    } else if (msgSent == 0) {
      Serial.println(F(":Timeout!"));
    }
    chThdSleepMilliseconds(1); // Redo this send program every few moments, give enough time for other threads to run
  }
  return 0;
}

