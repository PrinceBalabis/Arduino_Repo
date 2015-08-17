//940 nm IR LED with a 39-100ohm resistor to pin 3

#include <ChibiOS_AVR.h>
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include <HomeNetwork.h>
#include "config.h"
#include <CIRremote.h>
#include <EEPROM.h>

//Variables which stores the received values from other nodes
//Regularly check msgReceived variable if a message is received in thread
bool msgReceived = false;
uint16_t msgSender = -1;
unsigned char msgType = 'Z';
int32_t msgContent = -1;

RF24 radio(RF24_PIN_CE, RF24_PIN_CSN);
RF24Network network(radio);
HomeNetwork homeNetwork(radio, network, &homeNetwork);

void setup() {
  Serial.begin(115200);

  chBegin(mainThread);
  // chBegin never returns, main thread continues with mainThread()

  while (1);
}

// If a thread weirdly crashes then increase the stack value
static WORKING_AREA(commandExecutioner, 32); //1 bytes crash - 124 bytes works great

void mainThread() {
  SPI.begin(); // SPI is used by homeNetwork
  
  // CommandExecutioner thread which executes commands
  chThdCreateStatic(commandExecutioner, sizeof(commandExecutioner), NORMALPRIO + 3, CommandExecutioner, NULL);

  // Home Network Threads
  homeNetwork.setDebug(true); // Enable debug on home Network Library
  homeNetwork.begin(NODEID, &homeNetworkMessageReceived);

  Serial.println(F("Speaker Controller fully initialized!"));

  while (1);
}

void loop() {
  // not used
}
