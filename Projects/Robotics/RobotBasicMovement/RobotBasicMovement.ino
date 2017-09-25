/**
 *
 *
 */

#include <ChibiOS_AVR.h>

static WORKING_AREA(waThread1, 128);
static WORKING_AREA(waThread2, 128);
static WORKING_AREA(waThread3, 128);

int motorPowerState = 0;

//------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);

  chBegin(mainThread);
  // chBegin never returns, main thread continues with mainThread()
  while(1) {
  }
}
//------------------------------------------------------------------------------
// main thread runs at NORMALPRIO
void mainThread() {

  chThdCreateStatic(waThread1, sizeof(waThread1),
  NORMALPRIO + 2, Thread1, NULL);

  chThdCreateStatic(waThread2, sizeof(waThread2),
  NORMALPRIO + 1, Thread2, NULL);

  chThdCreateStatic(waThread3, sizeof(waThread3),
  NORMALPRIO, Thread3, NULL);

  while (1) {
  }
}
//------------------------------------------------------------------------------
void loop() {
  // not used
}


