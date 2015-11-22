#include <NilRTOS.h>
#include <NilSerial.h>
#include "config.h"
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#define Serial NilSerial

SEMAPHORE_DECL(semDisplay, 0);
SEMAPHORE_DECL(semLEDBuzzer, 0);

uint32_t coinAmount = 0; // Count of amount of coins inserted
double coinValue = 0.5; // Chosen coin value

void setup() {

  Serial.begin(115200);  //Begin serial communcation
  Serial.println(F("Started System..."));
  
  nilSysBegin();
}

void loop() {
  // Not used.
}
