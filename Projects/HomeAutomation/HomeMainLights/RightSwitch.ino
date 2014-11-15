//------------------------------------------------------------------------------
// Thread 1

static msg_t Thread1(void *arg) {

  // Switch state variables
  int rightSwitchState = 0;

  // Setup switch pins
  pinMode(rightSwitchPin, INPUT);

  // Switch setup
  rightSwitchState = digitalRead(rightSwitchPin);

  while (1) {
    if (rightSwitchState != digitalRead(rightSwitchPin)) {
      Serial.println("Right switch triggered");
      toggleLights();
      rightSwitchState = !rightSwitchState;
      // Sleep for 100 milliseconds.
      chThdSleepMilliseconds(100);
    }
    // Sleep for 150 milliseconds, to make time for other threads
    chThdSleepMilliseconds(150);
  }
  return 0;  
}


