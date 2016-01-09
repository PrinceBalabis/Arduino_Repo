/*
   Web Server

   Circuit:
   Ethernet shield attached to pins 10, 11, 12, 13
    http://192.168.1.16:9500/?1
*/

#include <NilRTOS.h>
#include <NilSerial.h>
#include <SPI.h>
#include <Ethernet.h>
#include "config.h"
#include <Wire.h>

#define Serial NilSerial

String request;
String request2;
String tempS;

void setup() {
  Serial.begin(115200);
  Serial.println(F("Webserver"));

  // Start I²C bus as master
  Wire.begin();

  Serial.println(F("Basic system booted up! Starting RTOS..."));
  nilSysBegin();
}

void loop() {
  //printStackInfo(); // Print stack information
}

void printStackInfo() {
  nilPrintStackSizes(&Serial);
  nilPrintUnusedStack(&Serial);
  Serial.println(F(""));

  // Delay for one second.
  // Must not sleep in loop so use nilThdDelayMilliseconds().
  // Arduino delay() can also be used in loop().
  nilThdDelayMilliseconds(1000);
}


