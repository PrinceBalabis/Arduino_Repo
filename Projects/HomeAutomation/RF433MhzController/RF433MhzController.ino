/**
 *  Prince Home Network IOT Example Client
 *  Start Server first before starting the Client!!!!!
 *  This library needs following peripherals:
 *    - SPI
 *    - ChibiOS
 *
 **/

#include <ChibiOS_AVR.h>
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include <HomeNetwork.h>
#include <NewRemoteTransmitter.h>
#include "config.h"
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

void mainThread() {
  SPI.begin(); // SPI is used by homeNetwork

  //homeNetwork.setDebug(true); // Enable debug on home Network Library
  homeNetwork.begin(NODEID, &homeNetworkMessageReceived);


  Serial.println(F("RF 433 MHz Controller fully started!"));
}

void loop() {
  // not used
}
