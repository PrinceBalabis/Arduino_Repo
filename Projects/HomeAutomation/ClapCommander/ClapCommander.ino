#include <ChibiOS_AVR.h>
#include "config.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>

static WORKING_AREA(waThread2, 64);
static WORKING_AREA(waThread1, 64);

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

  // start blink thread
  chThdCreateStatic(waThread1, sizeof(waThread1),
    NORMALPRIO + 2, Thread1, NULL);

  chThdCreateStatic(waThread2, sizeof(waThread2),
    NORMALPRIO + 1, Thread2, NULL);

}

//------------------------------------------------------------------------------
void loop() {
  // not used
}

