/*
    This Sketch is to make a "universal home control".
    Controlling PC, lights, speaker & other home electronics
    Hardware needed:
    - NPN transistor for PC Power switch to pin 6
    - Audio Switch to pin 7
   WARNING: Don't use Digital Pin 10 even if its not used, its reserved by SPI library!
*/
// If a thread weirdly crashes then increase the stack value

// Needed libraries & config
#include <NilRTOS.h>
#include <NilSerial.h>
#include <Keypad.h>
#include "config.h"
#include <Wire.h>

#define Serial NilSerial

static byte command;

void setup() {
  Serial.begin(115200);
  Serial.println(F("HomeControl"));

  // PC Power switch setup
  pcPowerSetup();

  // Audio Switch setup
  audioSwitchSetup();
  
  Serial.println(F("Basic system booted up! Starting RTOS..."));

  nilSysBegin(); // Start Nil RTOS.
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


