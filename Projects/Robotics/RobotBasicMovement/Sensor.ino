//------------------------------------------------------------------------------
// thread 2
// This thread prints out the current sense of the motors, which basically
// tells how much current the motors are drawing.


static msg_t Thread2(void *arg) {

  while (1) {
    if(motorPowerState){
      int s1Val = analogRead(s1) * 3; // gives a gain to the read values
      Serial.print(s1Val);
      Serial.print(F(" - "));
      int s2Val = analogRead(s2) * 3; // gives a gain to the read values
      Serial.print(s2Val);
      Serial.println();
    }
    chThdSleepMilliseconds(50);
  }
}
