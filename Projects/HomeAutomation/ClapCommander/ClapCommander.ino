#include <Wire.h>
#include <ChibiOS_AVR.h>
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include "config.h"

static WORKING_AREA(waThread2, 128);
static WORKING_AREA(waThread1, 128);

// Declare a semaphore with an inital counter value of zero.
SEMAPHORE_DECL(sem, 0);

//------------------------------------------------------------------------------
void setup() {
  
  Serial.begin(57600);

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

}

//------------------------------------------------------------------------------
void loop() {
  // not used
}

