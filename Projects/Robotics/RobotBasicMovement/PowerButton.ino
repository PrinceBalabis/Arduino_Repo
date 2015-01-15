//------------------------------------------------------------------------------
// thread 3
// This thread listens for the engine on/off button

const int motorButton = 6;
int lastState = 0; // Save last button state to prevent toggling when holding down button

static msg_t Thread3(void *arg) {
  pinMode(motorButton, INPUT);

  while (1) {
    if(digitalRead(motorButton) && lastState == 0){ // Toggle motorPowerState when button is pressed
      lastState = 1;
      chThdSleepMilliseconds(50);
      motorPowerState = !motorPowerState;
    } 
    else if(!digitalRead(motorButton))
      lastState = 0;
    chThdSleepMilliseconds(100);
  }
}












