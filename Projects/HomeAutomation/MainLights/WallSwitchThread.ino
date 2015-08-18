//------------------------------------------------------------------------------
// WallSwitchThread

// If a thread weirdly crashes then increase the stack value
NIL_WORKING_AREA(wallSwitchThread, 0); // 0 bytes works great
NIL_THREAD(WallSwitchThread, arg) {

  Serial.println("Started WallSwitchThread");

  // Switch state variables
  bool leftSwitchState = 0;
  bool rightSwitchState = 0;

  // Setup switch pins
  pinMode(WALLSWITCH_PIN_LEFT, INPUT);
  pinMode(WALLSWITCH_PIN_RIGHT, INPUT);

  // Switch setup
  leftSwitchState = digitalRead(WALLSWITCH_PIN_LEFT);
  rightSwitchState = digitalRead(WALLSWITCH_PIN_RIGHT);

  while (TRUE) {
    if (leftSwitchState != digitalRead(WALLSWITCH_PIN_LEFT)) {
      Serial.print("Left switch triggered: ");
      toggleLights();
      leftSwitchState = !leftSwitchState;
    } else if (rightSwitchState != digitalRead(WALLSWITCH_PIN_RIGHT)) {
      Serial.print("Right switch triggered: ");
      toggleLights();
      rightSwitchState = !rightSwitchState;
    }

    // Sleep some milliseconds, to make time for other threads and to act as button debouncing
    nilThdSleepMilliseconds(WALLSWITCH_UPDATEDELAY);
  }
}
