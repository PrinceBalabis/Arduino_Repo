/*
   Web Server

   Circuit:
   Ethernet shield attached to pins 10, 11, 12, 13

   Run this command where AA is node which is a number betwen 0-99 and BB which is command and between 0-99
   http://192.168.1.16:9500/?AA-BB
   Example of normal command:
   Toggle Main Lights(Normal command with node and command as "node-command" format)
   http://192.168.1.16:9500/?2-3

   To run a macro command, have AA as 0, example:
   Toggle Apartment Mood(Macro command with node and command as "0-command" format)
   http://192.168.1.16:9500/?0-5

*/

#include <NilRTOS.h>
#include <NilSerial.h>
#include <SPI.h>
#include <Ethernet.h>
#include "config.h"
#include <Wire.h>

#define Serial NilSerial

String node1;
String node2;
String command1;
String command2;

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


