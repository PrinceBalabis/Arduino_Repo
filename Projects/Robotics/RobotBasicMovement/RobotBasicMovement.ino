/**
 *
 *
 */

#include <ChibiOS_AVR.h>
#include <firFilter.h>

static WORKING_AREA(waThread1, 64);
static WORKING_AREA(waThread2, 64);
static WORKING_AREA(waThread3, 64);

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
  NORMALPRIO + 1, Thread3, NULL);

  while (1) {
  }
}
//------------------------------------------------------------------------------
void loop() {
  // not used
}


