/*
 *  
 *  Relay/Main Lights
 *  433MHz Transmitter connected to pin 7
 *  Ceiling lights relay/ceiling light pin to A0
 *  Left button to 4
 *  Right button to 5
 */

#include <NilRTOS.h>
#include <NilSerial.h>
#include <SPI.h>
#include <RF24.h>
#include <RF24Network.h>
#include <HomeNetwork.h>
#include <NewRemoteTransmitter.h>
#include <EEPROM.h>
#include "config.h"
#include <EEPROM.h>
#define Serial NilSerial

RF24 radio(RF24_PIN_CE, RF24_PIN_CSN);
RF24Network network(radio);
HomeNetwork homeNetwork(radio, network);

void setup() {
  Serial.begin(115200);
  Serial.println(F("Lights & 433MHz Controller(Power) Node"));

  initLights();

  SPI.begin(); // SPI is used by homeNetwork

  // Initialize Home Network
  //homeNetwork.setDebug(true); // Enable debug on home Network Library
  homeNetwork.begin(HOME_NODEID, &homeNetworkMessageReceived);
  homeNetwork.setNetworkUpdateTime(HOME_AUTOUPDATE_DELAY);

  Serial.println(F("Basic system booted up! Starting RTOS..."));

  nilSysBegin(); // Start Nil RTOS.
}

//------------------------------------------------------------------------------
// Loop is the idle thread.  The idle thread must not invoke any
// kernel primitive able to change its state to not runnable.
void loop() {
  //printStackInfo(); // Print stack information
}

void printStackInfo() {
  nilPrintStackSizes(&Serial);
  nilPrintUnusedStack(&Serial);
  Serial.println(F(""));

  // Delay for one second.
  // Must not sleep in loop so use nilThdDelayMilliseconds().
  // Arduino delay() can also be used in loop().
  nilThdDelayMilliseconds(1000);
}

