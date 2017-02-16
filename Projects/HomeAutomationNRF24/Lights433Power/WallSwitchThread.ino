//------------------------------------------------------------------------------
// WallSwitchThread

// If a thread weirdly crashes then increase the stack value
NIL_WORKING_AREA(wallSwitchThread, 50); // 0 bytes works great
NIL_THREAD(WallSwitchThread, arg) {

  Serial.println(F("Started WallSwitchThread"));

  // Switch state variables
  bool leftSwitchState = 0;
  bool rightSwitchState = 0;

  // Setup switch pins as inputs
  //pinMode(4, INPUT);
  //pinMode(5, INPUT);
  DDRD &= ~B00110000;
  PORTD |= _BV(PD4); // Set pullup 
  PORTD |= _BV(PD5); // Set pullup 
  
  // Switch setup
  //  leftSwitchState = digitalRead(WALLSWITCH_PIN_LEFT);
  //  rightSwitchState = digitalRead(WALLSWITCH_PIN_RIGHT);
  leftSwitchState = LEFT_BUTTON_READ;
  rightSwitchState = RIGHT_BUTTON_READ;

  while (1) {
    if (leftSwitchState != LEFT_BUTTON_READ) {
      Serial.print(F("Left switch triggered: "));
      toggleLights();
      leftSwitchState = !leftSwitchState;
    } else if (rightSwitchState != RIGHT_BUTTON_READ) {
      Serial.print(F("Right switch triggered: "));
      togglePaintingLights();
      rightSwitchState = !rightSwitchState;
    }

    // Sleep some milliseconds, to make time for other threads and to act as button debouncing
    nilThdSleepMilliseconds(WALLSWITCH_UPDATEDELAY);
  }
}
