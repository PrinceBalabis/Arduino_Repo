NIL_WORKING_AREA(ledBuzzer, 128);
NIL_THREAD(LedBuzzer, arg) {
  Serial.println(F("Started LED & Buzzer..."));

  pinMode(LED_BUZZER_PIN, OUTPUT);
  digitalWrite(LED_BUZZER_PIN, LOW);

  while (TRUE) {
    nilSemWait(&semLEDBuzzer); // Wait for a sign to run the beep
    //Serial.println(F("Blinking & Buzzing once"));

    digitalWrite(LED_BUZZER_PIN, HIGH);
    nilThdSleepMilliseconds(LED_BUZZER_BEEP_LENGTH); // Beep length
    digitalWrite(LED_BUZZER_PIN, LOW);
    
    nilThdSleepMilliseconds(LED_BUZZER_BEEP_SILENT_DIVIDER); // Silent length to divide separate beeps/flashes
  }
}
