static msg_t Thread2(void *arg) {

  const int sleepButtonPin = 2;     // the number of the pushbutton pin
  const int wakeButtonPin = 3;     // the number of the pushbutton pin

  pinMode(sleepButtonPin, INPUT);
  pinMode(wakeButtonPin, INPUT);

  int sleepButton = 0; // variable for reading the pushbutton status
  int wakeButton = 0; // variable for reading the pushbutton status
  int lastSleepButton = 0;
  int lastWakeButton = 0;

  while (1) {
    sleepButton = digitalRead(sleepButtonPin);
    wakeButton = digitalRead(wakeButtonPin);

    if (sleepButton == HIGH && !lastSleepButton) {
      Serial.println("Sleep");
      enterSleepMode();
    } else if (wakeButton == HIGH && !lastWakeButton) {
      Serial.println("Wake");
      exitSleepMode();
    } else if (lastSleepButton) {
      lastSleepButton = 0;
    } else if (lastWakeButton) {
      lastWakeButton = 0;
    }

    chThdSleepMilliseconds(10);
  }

  return 0;
}

