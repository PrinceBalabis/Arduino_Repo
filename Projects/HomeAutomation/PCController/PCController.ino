/*
 * PCController
 * This is to an Arduino connected to a PC as a HID keyboard device(must be HID-capable CPU like Atmega32u4)
 *
 * Requirements:
 * -Arduino Pro Micro(5V version)
 * -NRF24L01+ Module with 5V module adapter(Because VCC is 3.3V on the module)
 * -NirCmd Installed with shortcuts created+enabled keyboard shortcuts("Shortcut Key" in shortcut properties)
 */

#include <NilRTOS.h>
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include <HomeNetwork.h>
#include "config.h"

RF24 radio(RF24_PIN_CE, RF24_PIN_CSN);
RF24Network network(radio);
HomeNetwork homeNetwork(radio, network);

void setup() {
  Serial.begin(115200);

  //  while (!Serial) {
  //    ; // wait for serial port to connect. Needed for Leonardo only
  //  }

  SPI.begin(); // SPI is used by homeNetwork

  // Initialize Home Network
  homeNetwork.setDebug(true); // Enable debug on home Network Library
  homeNetwork.begin(NODEID, &homeNetworkMessageReceived);
  homeNetwork.setNetworkUpdateTime(HOME_AUTOUPDATE_DELAY);

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


