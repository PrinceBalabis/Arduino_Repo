/*
 *  This Sketch is to make a "universal home control".
 *  Controlling PC, lights, speaker & other home electronics
 *  Hardware needed:
 *  - NPN transistor for PC Power switch
 *
 * WARNING: Don't use Digital Pin 10 even if its not used, its reserved by SPI library!
 */

// Needed libraries & config
#include <ChibiOS_AVR.h>
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include <Keypad.h>
#include <NewRemoteTransmitter.h>
#include <HomeNetwork.h>
#include "config.h"

RF24 radio(RF24_PIN_CE, RF24_PIN_CSN);
RF24Network network(radio);
HomeNetwork homeNetwork(radio, network, &homeNetwork);

void setup() {
  Serial.begin(115200);
  Serial.println(F("HomeControl Node"));

  // PC Power switch setup
  pcPowerSetup();

  chBegin(mainThread);
  // chBegin never returns, main thread continues with mainThread()
  while (1);
}

// If a thread weirdly crashes then increase the stack value
static WORKING_AREA(keypadCommandThread, 16); //8 bytes crash - 16 bytes works great
static WORKING_AREA(keypadUpdaterThread, 64); //32 bytes crash - 64 bytes works great
static WORKING_AREA(commandExecutioner, 64); //8 bytes crash - 16 bytes works great

void mainThread() {
  SPI.begin(); // SPI is used by homeNetwork

  // CommandExecutioner thread which executes commands
  chThdCreateStatic(commandExecutioner, sizeof(commandExecutioner), NORMALPRIO + 3, CommandExecutioner, NULL);

  // Home Network Thread
  //homeNetwork.setDebug(true); // Enable debug on home Network Library
  homeNetwork.begin(NODEID, &homeNetworkMessageReceived);

  // Keypad threads
  chThdCreateStatic(keypadUpdaterThread, sizeof(keypadUpdaterThread), NORMALPRIO + 1, KeypadUpdaterThread, NULL);
  chThdCreateStatic(keypadCommandThread, sizeof(keypadCommandThread), NORMALPRIO + 1, KeypadCommandThread, NULL);

  homeNetwork.setNetworkUpdateTime(HOME_AUTOUPDATE_DELAY);
  
  Serial.println(F("System booted up!"));

}

void loop() {
  // not used
}
