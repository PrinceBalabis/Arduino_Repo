#include <Wire.h>
#include <ChibiOS_AVR.h>
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include <HomeNetwork.h>
#include "config.h"

//Variables for data to share between threads
volatile bool msgReceived = false;
volatile uint16_t msgSender = -1;
volatile int32_t msgContent = -1;
volatile unsigned char msgType = 'Z';

static WORKING_AREA(waThread1, 124);
static WORKING_AREA(waThread2, 124);

void setup() {
  Serial.begin(9600);
  // wait for USB Serial
  while (!Serial) {}
  delay(1000);
  
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


