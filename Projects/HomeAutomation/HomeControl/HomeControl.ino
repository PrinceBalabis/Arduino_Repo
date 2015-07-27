/*
 *  This Sketch is to make a "universal home control".
 *  Controlling PC, lights, speaker & other home electronics
 *  Hardware needed:
 *  - 940 nm IR LED with a resistor to pin 3
 *  - NPN transistor for PC Power switch
 *  - 433 MHz transmitter
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

//Variables which stores the received values from other nodes
//Regularly check msgReceived variable if a message is received in thread
bool msgReceived = false;
uint16_t msgSender = -1;
unsigned char msgType = 'Z';
int32_t msgContent = -1;

void setup() {
  Serial.begin(115200);

  // PC Power switch setup
  pcPowerSetup();

  chBegin(mainThread);
  // chBegin never returns, main thread continues with mainThread()
  while (1);
}

static WORKING_AREA(hNListenThread, 100);
static WORKING_AREA(keypadCommandThread, 100);
static WORKING_AREA(keypadUpdaterThread, 100);
static WORKING_AREA(commandExecutioner, 100);

void mainThread() {
  SPI.begin(); // SPI is used by homeNetwork
  chThdSleepMilliseconds(1000);

  // CommandExecutioner thread which executes commands
  chThdCreateStatic(commandExecutioner, sizeof(commandExecutioner), NORMALPRIO + 3, CommandExecutioner, NULL);
  chThdSleepMilliseconds(1000);

  // Home Network Threads
  chThdCreateStatic(hNListenThread, sizeof(hNListenThread), NORMALPRIO + 2, HNListenThread, NULL);
  chThdSleepMilliseconds(1000);
  homeNetwork.begin(nodeID, &msgReceived, &msgSender, &msgType, &msgContent);
  chThdSleepMilliseconds(1000);

  // Keypad threads
  chThdCreateStatic(keypadUpdaterThread, sizeof(keypadUpdaterThread), NORMALPRIO + 1, KeypadUpdaterThread, NULL);
  chThdSleepMilliseconds(1000);
  chThdCreateStatic(keypadCommandThread, sizeof(keypadCommandThread), NORMALPRIO + 1, KeypadCommandThread, NULL);

  Serial.println(F("Home Control fully started!"));
  Serial.println();
}

void loop() {
  // not used
}
