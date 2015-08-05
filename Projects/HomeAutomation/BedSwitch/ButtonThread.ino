static msg_t ButtonThread(void *arg) {

  const int buttonPin = 2;     // the number of the pushbutton pin
  pinMode(buttonPin, INPUT);

  bool buttonStatus = 0; // variable for reading the pushbutton status
  bool lastButtonStatus = 0;

  Serial.println(F("Started Button listener Thread"));

  while (1) {
    buttonStatus = digitalRead(buttonPin);

    if (buttonStatus && !lastButtonStatus) {
      Serial.println("Pressed button..");

      apartmentStatusUpdaterPaused = true; // Pause the apartment status polling
      while (!apartmentStatusUpdaterPauseExecuted) // Wait for the pause to happen
        chThdSleepMilliseconds(10);

      if (askApartmentStatus()) {
        shutdownApartment();
        setLED(LOW);
        Serial.println("Shut down apartment");
      } else {
        startupApartment();
        setLED(HIGH);
        Serial.println("Started up apartment");
      }
      lastButtonStatus = HIGH;
      chThdSleepMilliseconds(buttonDebounceTime);

      apartmentStatusUpdaterPaused = false; // Resume the apartment status polling

    } else if (!buttonStatus && lastButtonStatus) {
      lastButtonStatus = LOW;
      Serial.print("Disable button for ");
      Serial.print(buttonRepressTime);
      Serial.println(" seconds");
      chThdSleepMilliseconds(buttonRepressTime); // Wait 10 seconds before able to press button again
      Serial.println("Button is enabled again!");
    }

    chThdSleepMilliseconds(buttonReadUpdateTime);
  }
  return 0;
}

