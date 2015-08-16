#include <ChibiOS_AVR.h>
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include <HomeNetwork.h>
#include "config.h"

RF24 radio(RF24_PIN_CE, RF24_PIN_CSN);
RF24Network network(radio);
HomeNetwork homeNetwork(radio, network, &homeNetwork);

void setup() {
  Serial.begin(115200);
  Serial.println(F("Home Network Testing Node"));

  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  chBegin(mainThread);
  // chBegin never returns, main thread continues with mainThread()

  while (1);
}

// If a thread weirdly crashes then increase the stack value
static WORKING_AREA(commandExecutioner, 64);
static WORKING_AREA(exampleSendThread, 64);

void mainThread() {
  SPI.begin(); // SPI is used by homeNetwork

  chThdCreateStatic(commandExecutioner, sizeof(commandExecutioner), NORMALPRIO + 2, CommandExecutioner, NULL);
  
  homeNetwork.setDebug(true); // Enable debug on home Network Library
  homeNetwork.begin(NODEID, &homeNetworkMessageReceived);

  chThdCreateStatic(exampleSendThread, sizeof(exampleSendThread), NORMALPRIO + 1, ExampleSendThread, NULL);

  homeNetwork.setNetworkUpdateTime(HOME_SETTING_TIME_NETWORKAUTOUPDATE);

  Serial.println(F("System booted up!"));
}

void loop() {
  // not used
}
