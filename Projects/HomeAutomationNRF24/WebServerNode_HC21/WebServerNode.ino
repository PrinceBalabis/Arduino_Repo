/*
 * * Make sure the HC-21 has at least 200-300 mA!!!! (by using separate power supply)
 * Runs at 3.3V
 *
 * How to Send a GET HTTP Request from a simple internet browser:
 * Enter this in browser to send command 1
 * http://princehome.duckdns.org:9500/1
 */
// If a thread weirdly crashes then increase the stack value

#include <NilRTOS.h>
#include <NilSerial.h>
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include <HomeNetwork.h>
#include "config.h"
#include <SoftwareSerial.h>

#define Serial NilSerial

RF24 radio(RF24_PIN_CE, RF24_PIN_CSN);
RF24Network network(radio);
HomeNetwork homeNetwork(radio, network);

SoftwareSerial hc21(2, 3);

bool pauseWebserver = false;
bool webserverIsPaused = false;

void setup() {
  Serial.begin(115200);

  Serial.println(F("Home Network Webserver Node"));

  hc21.begin(38400); // Your modules baud rate might be different

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

void(* resetFunc) (void) = 0; //declare reset function @ address 0

