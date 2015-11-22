#include <NilRTOS.h>
#include <NilSerial.h>
#include "config.h"
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#define Serial NilSerial

SEMAPHORE_DECL(semDisplay, 0);
SEMAPHORE_DECL(semLEDBuzzer, 0);

//Global coin variables
uint32_t coinAmount = 0; // Count of amount of coins inserted
double coinValue = 0.25; // Chosen coin value
double coinTotal = 0; // Chosen coin value

//Delays
uint16_t coinSensorLagTime = KR_025_LAG_TIME; // Sleep a little in order to correct bug where the empty coin circle in danish coins will make the coin counter think its two coins.
uint16_t coinSensorPollingTime = KR_025_POLLING_TIME; //get sensor value every chosen millisecond

void setup() {

  //Serial.begin(115200);  //Begin serial communcation
  //Serial.println(F("Started System..."));

  nilSysBegin();
}

void loop() {
  // Not used.
}
