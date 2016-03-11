// If a thread weirdly crashes then increase the stack value

#include <NilRTOS.h>
#include <NilSerial.h>
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include <HomeNetwork.h>
#include "config.h"
#include <SoftwareSerial.h>
#include <Wire.h>

#define Serial NilSerial

RF24 radio(RF24_PIN_CE, RF24_PIN_CSN);
RF24Network network(radio);
HomeNetwork homeNetwork(radio, network);

byte callbackCommand = 0;

void setup() {
  Serial.begin(115200);

  Serial.println(F("Home Network HomeControl Node"));

  // Start I²C bus as a slave
  Wire.begin(TWI_SLAVE_ID);
  // Set the callback to call when data is received.
  Wire.onReceive(receiveCommand);
  Wire.onRequest(requestCallback);

  SPI.begin(); // SPI is used by homeNetwork
  // Initialize Home Network
  //homeNetwork.setDebug(true); // Enable debug on home Network Library
  homeNetwork.begin(NODEID, &homeNetworkMessageReceived);
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
  Serial.println(F(""));

  // Delay for one second.
  // Must not sleep in loop so use nilThdDelayMilliseconds().
  // Arduino delay() can also be used in loop().
  nilThdDelayMilliseconds(1000);
}

