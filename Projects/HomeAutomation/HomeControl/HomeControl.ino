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

RF24 radio(homeNetworkCEPin, homeNetworkCSNPin);
RF24Network network(radio);
HomeNetwork homeNetwork(radio, network, &homeNetwork);

void setup() {
  Serial.begin(115200);

  // PC Power switch setup
  pcPowerSetup();

  chBegin(mainThread);
  // chBegin never returns, main thread continues with mainThread()
  while (1);
}

// If a thread weirdly crashes then increase the stack value
static WORKING_AREA(keypadCommandThread, 16); //8 bytes crash - 16 bytes works great
static WORKING_AREA(keypadUpdaterThread, 64); //32 bytes crash - 64 bytes works great
static WORKING_AREA(commandExecutioner, 8); //4 bytes crash - 8 bytes works great

void mainThread() {
  SPI.begin(); // SPI is used by homeNetwork
  chThdSleepMilliseconds(1000);

  // CommandExecutioner thread which executes commands
  chThdCreateStatic(commandExecutioner, sizeof(commandExecutioner), NORMALPRIO + 3, CommandExecutioner, NULL);
  chThdSleepMilliseconds(1000);

  // Home Network Thread
  homeNetwork.begin(nodeID);
  chThdSleepMilliseconds(1000);

  // Keypad threads
  chThdCreateStatic(keypadUpdaterThread, sizeof(keypadUpdaterThread), NORMALPRIO + 1, KeypadUpdaterThread, NULL);
  chThdSleepMilliseconds(1000);
  chThdCreateStatic(keypadCommandThread, sizeof(keypadCommandThread), NORMALPRIO + 1, KeypadCommandThread, NULL);

  Serial.println(F("Home Network Listen Thread started"));
  homeNetwork.setAutoUpdateTime(homeNetworkAutoUpdateTime);

  // This infinite loop is used to get incoming home network messages
  while (1) {
    // Pauses here untill a message is received
    homeNetwork.waitForIncomingMessage();
    Serial.print(F("New Message.. "));

    //Get received message
    uint16_t msgSender;
    unsigned char msgType;
    int32_t msgContent;
    homeNetwork.getIncomingMessage(&msgSender, &msgType, &msgContent);

    //Send message to CommandExecutionerThread for decoding
    executeCommand(msgContent);
  }
}

void loop() {
  // not used
}
