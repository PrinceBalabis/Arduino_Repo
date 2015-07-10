static msg_t Thread2(void *arg) {
  chThdSleepMilliseconds(4500); // Give some time for HomeNetwork thread to start

  while (1) {
    Serial.println(F("MESSAGE SEND PROGRAM"));

    uint8_t msgSent = homeNetwork.toggleMainLights();
    if (msgSent) {
      Serial.println(F("MESSAGE AWAY"));
    } else if (!msgSent) {
      Serial.println(F("ERROR!: Failed to send message to parent."));
    } else {
      Serial.println(F("FINALLY SENT MESSAGE AFTER SEVERAL RETRIES. BAD SIGNAL WITH PARENT!"));
    }
    Serial.println(); // Extra row for easier serial reading

    chThdSleepMilliseconds(2000); // Redo this send program every 2 seconds
  }

  return 0;
}

