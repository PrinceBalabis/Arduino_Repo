static msg_t Thread2(void *arg) {
  chThdSleepMilliseconds(4000);

  while (1) {
    //Serial.println(F("MESSAGE SEND PROGRAM"));

//    uint8_t msgSent = homeNetwork.toggleMainLights();
    //homeNetwork.toggleMainLights();
//    if (msgSent) {
//      Serial.println(F("PARENT PICKED UP MESSAGE"));
//    } else if (!msgSent) {
//      Serial.println(F("ERROR!: Failed to send message to parent. After "));
//    } else {
//      Serial.println(F("PARENT FINALLY PICKED UP MESSAGE AFTER COUPLE RETRIES. BAD SIGNAL!"));
//    }
//    Serial.println(); // Extra row for easier serial reading
    
    chThdSleepMilliseconds(2000);
  }

  return 0;
}

