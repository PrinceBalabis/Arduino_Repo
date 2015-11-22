#include <NilRTOS.h>
#include <NilSerial.h>
#include "config.h"

#define Serial NilSerial

uint32_t coinAmount = 0;

void setup() {

  Serial.begin(115200);  //Begin serial communcation
  Serial.println(F("Started System..."));
  
  nilSysBegin();
}

void loop() {
  // Not used.
}
