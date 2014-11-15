#include <ChibiOS_AVR.h>
#include "config.h"
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

// Declare a semaphore with an inital counter value of zero.
SEMAPHORE_DECL(sem, 0);

// 64 byte stack beyond task switch and interrupt needs
static WORKING_AREA(waThread1, 64);

// 64 byte stack beyond task switch and interrupt needs
static WORKING_AREA(waThread2, 64);

// 64 byte stack beyond task switch and interrupt needs
static WORKING_AREA(waThread3, 64);

//------------------------------------------------------------------------------
void setup() {

  Serial.begin(57600);

  initLights();

  chBegin(chSetup);
  // chBegin never returns, main thread continues with mainThread()
  while(1) {
  }
}

//------------------------------------------------------------------------------
// main thread runs at NORMALPRIO
void chSetup() {

  chThdCreateStatic(waThread1, sizeof(waThread1),
  NORMALPRIO + 2, Thread1, NULL);

  chThdCreateStatic(waThread2, sizeof(waThread2),
  NORMALPRIO + 1, Thread2, NULL);

  chThdCreateStatic(waThread3, sizeof(waThread3),
  NORMALPRIO + 1, Thread3, NULL);

}

//------------------------------------------------------------------------------
void loop() {
  // not used
}




