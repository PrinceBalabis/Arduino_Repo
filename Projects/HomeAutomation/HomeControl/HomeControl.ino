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
#include "config.h" // config file

//Variables which stores the received values from other nodes
//Regularly check msgReceived variable if a message is received in thread
bool msgReceived = false;
uint16_t msgSender = -1;
unsigned char msgType = 'Z';
int32_t msgContent = -1;

RF24 radio(homeNetworkCEPin, homeNetworkCSNPin);
RF24Network network(radio);
HomeNetwork homeNetwork(radio, network, &homeNetwork);

static WORKING_AREA(hNListenThread, 64);
static WORKING_AREA(keypadThread, 64);
static WORKING_AREA(waThread3, 64);

void setup() {
  Serial.begin(115200);

  // PC Power switch setup
  pcPowerSetup();

  chBegin(mainThread);
  // chBegin never returns, main thread continues with mainThread()
  while (1);
}

void mainThread() {
  SPI.begin(); // SPI is used by homeNetwork
  homeNetwork.begin(nodeID, &msgReceived, &msgSender, &msgType, &msgContent);

  // keypad listening thread
  chThdCreateStatic(keypadThread, sizeof(keypadThread), NORMALPRIO + 1, KeypadThread, NULL);

  // CommandExecutioner thread which executes commands
  chThdCreateStatic(waThread3, sizeof(waThread3), NORMALPRIO + 2, Thread3, NULL);
}

void loop() {
  // not used
}














