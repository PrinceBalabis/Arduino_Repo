/*
 *  This Sketch is to make a "universal home control".
 *  Controlling PC, lights, speaker & other home electronics
 *  Hardware needed:
 *  - NPN transistor for PC Power switch
 *
 * WARNING: Don't use Digital Pin 10 even if its not used, its reserved by SPI library!
 */
// If a thread weirdly crashes then increase the stack value

// Needed libraries & config
#include <NilRTOS.h>
#include <NilSerial.h>
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include <Keypad.h>
#include <NewRemoteTransmitter.h>
#include <HomeNetwork.h>
#include "config.h"

RF24 radio(RF24_PIN_CE, RF24_PIN_CSN);
RF24Network network(radio);
HomeNetwork homeNetwork(radio, network);

void setup() {
  Serial.begin(115200);
  Serial.println(F("HomeControl Node"));

  // PC Power switch setup
  pcPowerSetup();

  SPI.begin(); // SPI is used by homeNetwork

  // Home Network Thread
  homeNetwork.setDebug(true); // Enable debug on home Network Library
  homeNetwork.begin(NODEID, &homeNetworkMessageReceived);
  homeNetwork.setNetworkUpdateTime(HOME_AUTOUPDATE_DELAY);

  Serial.println(F("System booted up!"));

  nilSysBegin(); // Start Nil RTOS.
}

void loop() {
  printStackInfo(); // Print stack information
}

void printStackInfo() {
  nilPrintStackSizes(&Serial);
  nilPrintUnusedStack(&Serial);
  Serial.println();

  // Delay for one second.
  // Must not sleep in loop so use nilThdDelayMilliseconds().
  // Arduino delay() can also be used in loop().
  nilThdDelayMilliseconds(1000);
}


