//------------------------------------------------------------------------------
// thread 2
// This thread prints out the current sense of the motors, which basically
// tells how much current the motors are drawing.
// FIR filters are used 

// Low pass filter config
float filterVal;       // this determines smoothness  - .0001 is max  1 is off (no smoothing)
float smootheds1;
float smootheds2;
float s1Val;
float s2Val;

static msg_t Thread2(void *arg) {

  while (1) {
    if(motorPowerState){
      s1Val = analogRead(s1) * 3; // gives a gain to the read values
      smootheds1 = smooth(s1Val ,0.0001, smootheds1);
      Serial.print(smootheds1);
      Serial.print(F(" - "));
      s2Val = analogRead(s2) * 3; // gives a gain to the read values
      smootheds2 = smooth(s2Val, 0.0001, smootheds2);
      Serial.print(smootheds2);
      Serial.println();
    }
    chThdSleepMilliseconds(50);
  }
}

// Signal smoothing
int smooth(int data, float filterVal, float smoothedVal){
  if (filterVal > 1){      // check to make sure param's are within range
    filterVal = .99;
  }
  else if (filterVal <= 0){
    filterVal = 0;
  }
  smoothedVal = (data * (1 - filterVal)) + (smoothedVal  *  filterVal);
  return (int)smoothedVal;
}


