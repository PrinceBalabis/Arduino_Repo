/*
  ---------------------------------------------------------------

   Task to continously read the wall switches
  ---------------------------------------------------------------
*/
void initWallSwitches() {
  // Initialize the reading of digital pins
  pinMode(leftWallSwitchPin, INPUT_PULLUP);
  pinMode(rightWallSwitchPin, INPUT_PULLUP);
  // Enable interrupts
  unpauseInterrupts();
}
// Paramater: pointer to the last interrupt detected
// Returns: 1 if debounce detected, 0 if there is no debounce
// Calculates if a switch hes debounced, also detects if one switch debounces the other switch
bool debounceCalculation(volatile unsigned long *tempLastInterruptDetected) {
  unsigned long interruptDetected = millis(); // Store current time(program runtime)
  //Serial.print("Interrupt...");
  if (interruptDetected - *tempLastInterruptDetected > interruptDebounce && interruptDetected - lastInterruptDetected > interruptDebounce ) {
    *tempLastInterruptDetected = interruptDetected; // Save last interrupt detected for this switch
    lastInterruptDetected = interruptDetected; // Save last interrupt detected for both switches
    return 0;
  } else {
    //Serial.println("On cooldown");
    return 1;
  }
}

// This is the function which is called upon interrupt
// Keep this function as short as possible so it does not cause program malfunction,
// as this functin will be ran at any time in the runtime if interrupt is triggered
// Best to just use a variable which is modified in this function, then
// use a loop to check if the variable has changed
void leftWallSwitchInterrupt() {
  if (!debounceCalculation(&lastLeftInterruptDetected)) {
    Serial.print("Left switch triggered: ");
    toggleCeilingLights();
  }
}
void rightWallSwitchInterrupt() {
  if (!debounceCalculation(&lastRightInterruptDetected)) {
    Serial.print("Right switch triggered: ");
    toggleCeilingLights();
    //togglePaintingLights();
  }
}

// Enable interrupts
void unpauseInterrupts() {
  //Serial.println("Unpausing interrupts");
  attachInterrupt(digitalPinToInterrupt(leftWallSwitchPin), leftWallSwitchInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(rightWallSwitchPin), rightWallSwitchInterrupt, CHANGE);
}
// Disable interrupts
void pauseInterrupts() {
  //Serial.println("Pausing interrupts");
  detachInterrupt(digitalPinToInterrupt(leftWallSwitchPin));
  detachInterrupt(digitalPinToInterrupt(rightWallSwitchPin));
}
