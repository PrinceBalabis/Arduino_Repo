/*
  ---------------------------------------------------------------

   Task to continously read the wall switches
  ---------------------------------------------------------------
*/
class WallSwitchTask : public Task {
  protected:
    void setup() {
      // Initialize the reading of digital pins
      pinMode(leftWallSwitchPin, INPUT);
      pinMode(rightWallSwitchPin, INPUT);
      //Set initial states
      leftSwitchState = digitalRead(leftWallSwitchPin);
      rightSwitchState = digitalRead(rightWallSwitchPin);
      // Enable interrupts
      //attachInterrupt(digitalPinToInterrupt(leftWallSwitchPin), ::leftWallSwitchInterruptWrap, CHANGE);
      //attachInterrupt(digitalPinToInterrupt(rightWallSwitchPin), ::rightWallSwitchInterruptWrap, CHANGE);

      Serial.print("Started WallSwitch Task");
      delay(100); // Some time for serial buffer to empty
      taskCeilingLightsStarted = 1; // Declare that WallSwitchTask has been started
    }

    void loop()  {
      yield(); // Allow other essential backgrund tasks to run
      delay(wallSwitchUpdateExecutionFrequency); // How often to check if the wall switches has been pressed
      //Serial.println("Running");

      if (leftSwitchState != digitalRead(leftWallSwitchPin)) {
        Serial.print(F("Left switch triggered: "));
        toggleCeilingLights();
        leftSwitchState = !leftSwitchState;
      } else if (rightSwitchState != digitalRead(rightWallSwitchPin)) {
        Serial.print(F("Right switch triggered: "));
        toggleCeilingLights();
        //togglePaintingLights();
        rightSwitchState = !rightSwitchState;
      }
      //      if (leftInterruptDetected > 0) {
      //        //Serial.print("Interrupt for Left switch...");
      //        if (leftInterruptDetected - lastLeftInterruptDetected > interruptCoolDown) {
      //          Serial.println("Left Switch toggled");
      //          toggleCeilingLights();
      //          lastLeftInterruptDetected = leftInterruptDetected; // Save last interrupt detected
      //        } else {
      //          //Serial.println("On cooldown");
      //        }
      //        leftInterruptDetected = 0;
      //      }

      //      if (rightInterruptDetected > 0) {
      //  Serial.print("Interrupt for Right switch");
      //        if (rightInterruptDetected - lastRightInterruptDetected > interruptCoolDown) {
      //          Serial.println("Right Switch toggled");
      //          //        toggleCeilingLights();
      //          //        //togglePaintingLights();
      //          lastRightInterruptDetected = rightInterruptDetected; // Save last interrupt detected
      //        } else {
      //          //Serial.println("On cooldown");
      //        }
      //        rightInterruptDetected = 0;
      //      }
    }
  public:
    // This is the function which is called upon interrupt
    // Keep this function as short as possible so it does not cause program malfunction,
    // as this functin will be ran at any time in the runtime if interrupt is triggered
    // Best to just use a variable which is modified in this function, then
    // use a loop to check if the variable has changed
    void leftWallSwitchInterrupt() {
      //Serial.println("Left");
      leftInterruptDetected = micros(); // Store current time(program runtime)
    }
    void rightWallSwitchInterrupt() {
      Serial.println("Right");
      rightInterruptDetected = micros(); // Store current time(program runtime)
    }
  private:
    // Switch state variables
    bool leftSwitchState = 0;
    bool rightSwitchState = 0;

} wallswitch_task;
