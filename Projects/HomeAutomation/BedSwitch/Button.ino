static msg_t ButtonThread(void *arg) {

  const int buttonPin = 2;     // the number of the pushbutton pin
  pinMode(buttonPin, INPUT);

  bool buttonStatus = 0; // variable for reading the pushbutton status
  bool lastButtonStatus = 0;

  chThdSleepMilliseconds(1000);

  while (1) {
    buttonStatus = digitalRead(buttonPin);
    
    if (buttonStatus && !lastButtonStatus) {
      homeNetwork.toggleMainLights();
      lastButtonStatus = HIGH;
      chThdSleepMilliseconds(200);
    } else if (!buttonStatus) {
      lastButtonStatus = LOW;
    }
    
    chThdSleepMilliseconds(1);
  }
  return 0;
}
