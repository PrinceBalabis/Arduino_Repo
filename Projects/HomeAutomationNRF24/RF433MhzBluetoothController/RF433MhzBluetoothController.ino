/**
 *  Prince Home Network RF 433MHz & Bluetooth Controller
 *  This library needs following peripherals:
 *    - SPI
 *    - ChibiOS
 *
 * How to hack a Nut module to always broadcast signal:
 * You need two phones.
 * On your primary phone download Nut application and connect nut to the phone as normal.
 * Then delete app from phone
 * Download Nut into a second phone, and log in to the same account as your primary phone.
 * Delete the Nut that you connected in step 1
 * Done. Now the Nut is in a state that always thinks that its primary 
 * connection is your primary phone which means
 * it always broadcast a signal, which we will use for home automation. 
 * You can never use your nut for the normal purpose though....
 *
 **/

#include <NilRTOS.h>
#include <NilSerial.h>
#include <SPI.h>
#include <RF24.h>
#include <RF24Network.h>
#include <HomeNetwork.h>
#include <EEPROM.h>
#include "config.h"
#include <SoftwareSerial.h>

#define Serial NilSerial

RF24 radio(RF24_PIN_CE, RF24_PIN_CSN);
RF24Network network(radio);
HomeNetwork homeNetwork(radio, network);

SoftwareSerial bluetoothModule(2, 3);

String serialBuffer;

void setup() {
  Serial.begin(115200);
  Serial.println(F("RF 433 MHz & Bluetooth Controller"));

  bluetoothModule.begin(38400); // Your modules baud rate might be different

  SPI.begin(); // SPI is used by homeNetwork

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
  Serial.println();

  // Delay for one second.
  // Must not sleep in loop so use nilThdDelayMilliseconds().
  // Arduino delay() can also be used in loop().
  nilThdDelayMilliseconds(1000);
}

void(* resetFunc) (void) = 0; //declare reset function @ address 0

