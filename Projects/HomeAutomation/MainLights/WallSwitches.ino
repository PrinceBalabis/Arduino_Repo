//------------------------------------------------------------------------------
// WallSwitchThread

static msg_t WallSwitchThread(void *arg) {

  // Switch state variables
  int leftSwitchState = 0;
  int rightSwitchState = 0;

  // Setup switch pins
  pinMode(leftSwitchPin, INPUT);
  pinMode(rightSwitchPin, INPUT);

  // Switch setup
  leftSwitchState = digitalRead(leftSwitchPin);
  rightSwitchState = digitalRead(rightSwitchPin);

  while (1) {
    if (leftSwitchState != digitalRead(leftSwitchPin)) {
      Serial.print("Left switch triggered: ");
      toggleLights();
      leftSwitchState = !leftSwitchState;
    } else if (rightSwitchState != digitalRead(rightSwitchPin)) {
      Serial.print("Right switch triggered: ");
      toggleLights();
      rightSwitchState = !rightSwitchState;
    }

    // Sleep for 150 milliseconds, to make time for other threads and to act as button debouncing
    chThdSleepMilliseconds(100);
  }
  return 0;
}


