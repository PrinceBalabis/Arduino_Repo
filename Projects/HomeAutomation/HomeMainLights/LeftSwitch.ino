//------------------------------------------------------------------------------
// Thread 2

static msg_t Thread2(void *arg) {

  // Switch state variables
  int leftSwitchState = 0;

  // Setup switch pins
  pinMode(leftSwitchPin, INPUT);

  // Switch setup
  leftSwitchState = digitalRead(leftSwitchPin);

  while (1) {
    if (leftSwitchState != digitalRead(leftSwitchPin)) {
      Serial.println("Left switch triggered");
      toggleLights();
      leftSwitchState = !leftSwitchState;
      // Sleep for 100 milliseconds.
      chThdSleepMilliseconds(100);
    } 
    // Sleep for 150 milliseconds, to make time for other threads
    chThdSleepMilliseconds(150);
  }
  return 0;  
}


