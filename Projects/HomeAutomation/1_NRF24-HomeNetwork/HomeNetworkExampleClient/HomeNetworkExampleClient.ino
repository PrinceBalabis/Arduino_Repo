#include <Wire.h>
#include <ChibiOS_AVR.h>
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include <HomeNetwork.h>
#include "config.h"

// Variables for data to share between threads
bool dataBusy = false; // Used to make sure the shared variables are not used concurrently by two threads
volatile int msgNode = -1;
volatile int msgContent = -1;

static WORKING_AREA(waThread1, 64);
static WORKING_AREA(waThread2, 64);

void setup() {
  Serial.begin(9600);

  chBegin(mainThread);
  // chBegin never returns, main thread continues with mainThread()
  
  while (1);
}

void mainThread() {

  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO + 3, Thread1, NULL);

  chThdCreateStatic(waThread2, sizeof(waThread2), NORMALPRIO + 2, Thread2, NULL);

  while (1);
}

void loop() {
  // not used
}


