/**
 *  Prince Home Network IOT Example Client
 *  Start Server first before starting the Client!!!!!
 *  This library needs following peripherals:
 *    - SPI
 *    - ChibiOS
 *
 **/

#include <NilRTOS.h>
#include <NilSerial.h>
#include <SPI.h>
#include <RF24.h>
#include <RF24Network.h>
#include <HomeNetwork.h>
#include <NewRemoteTransmitter.h>
#include <EEPROM.h>
#include "config.h"

RF24 radio(RF24_PIN_CE, RF24_PIN_CSN);
RF24Network network(radio);
HomeNetwork homeNetwork(radio, network);

void setup() {
  Serial.begin(115200);
  Serial.println(F("RF 433 MHz Controller"));

  SPI.begin(); // SPI is used by homeNetwork

  homeNetwork.setDebug(true); // Enable debug on home Network Library
  homeNetwork.begin(NODEID, &homeNetworkMessageReceived);

  Serial.println(F("Basic system booted up! Starting RTOS..."));

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
