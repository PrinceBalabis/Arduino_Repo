/*
 * PCController
 * This is to an Arduino connected to a PC as a HID keyboard device(must be HID-capable CPU like Atmega32u4)
 * 
 * Requirements:
 * -Arduino Pro Micro(5V version)
 * -NRF24L01+ Module with 5V module adapter(Because VCC is 3.3V on the module)
 * -NirCmd Installed with shortcuts created+enabled keyboard shortcuts("Shortcut Key" in shortcut properties)
 */

#include <ChibiOS_AVR.h>
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include <HomeNetwork.h>
#include "config.h"

//Variables which stores the received values from other nodes
//Regularly check msgReceived variable if a message is received in thread
bool msgReceived = false;
uint16_t msgSender = -1;
unsigned char msgType = 'Z';
int32_t msgContent = -1;

RF24 radio(homeNetworkCEPin, homeNetworkCSNPin);
RF24Network network(radio);
HomeNetwork homeNetwork(radio, network, &homeNetwork);

void setup() {
//  Serial.begin(115200);

//  while (!Serial) {
//    ; // wait for serial port to connect. Needed for Leonardo only
//  }
  
  chBegin(mainThread);
  // chBegin never returns, main thread continues with mainThread()

  while (1);
}

static WORKING_AREA(hNListenThread, 124);
static WORKING_AREA(commandExecutioner, 124);

void mainThread() {
  SPI.begin(); // SPI is used by homeNetwork
  chThdSleepMilliseconds(1000);

  homeNetwork.begin(nodeID, &msgReceived, &msgSender, &msgType, &msgContent);
  chThdSleepMilliseconds(1000);

  chThdCreateStatic(commandExecutioner, sizeof(commandExecutioner), NORMALPRIO + 2, CommandExecutioner, NULL);
  chThdSleepMilliseconds(1000);

  chThdCreateStatic(hNListenThread, sizeof(hNListenThread), NORMALPRIO + 1, HNListenThread, NULL);

  while (1);
}

void loop() {
  // not used
}
