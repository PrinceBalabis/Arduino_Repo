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
      if (homeNetwork.askApartmentStatus()) {
        homeNetwork.shutdownApartment();
        setLED(LOW);
        Serial.println("Shut down apartment");
      } else {
        homeNetwork.startupApartment();
        setLED(HIGH);
        Serial.println("Started up apartment");
      }
      lastButtonStatus = HIGH;
      chThdSleepMilliseconds(buttonDebounceTime);
    } else if (!buttonStatus) {
      lastButtonStatus = LOW;
    }

    chThdSleepMilliseconds(buttonReadUpdateTime);
  }
  return 0;
}