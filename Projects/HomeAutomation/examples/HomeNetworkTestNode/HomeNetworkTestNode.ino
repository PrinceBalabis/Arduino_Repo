// If a thread weirdly crashes then increase the stack value

#include <NilRTOS.h>
#include <NilSerial.h>
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include <HomeNetwork.h>
#include "config.h"

RF24 radio(RF24_PIN_CE, RF24_PIN_CSN);
RF24Network network(radio);
HomeNetwork homeNetwork(radio, network);

#define Serial NilSerial

void setup() {
  Serial.begin(115200);
  Serial.println(F("Home Network Testing Node"));
  
  SPI.begin(); // SPI is used by homeNetwork

  // Initialize Home Network
  homeNetwork.setDebug(true); // Enable debug on home Network Library
  homeNetwork.begin(NODEID, &executeHomeNetworkCommand);
  homeNetwork.setNetworkUpdateTime(HOME_SETTING_TIME_NETWORKAUTOUPDATE);
  
  
  Serial.println(F("Basic system booted up! Starting RTOS..."));

  nilSysBegin(); // Start Nil RTOS.
}

void loop() {
  //printStackInfo(); // Print stack information
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


