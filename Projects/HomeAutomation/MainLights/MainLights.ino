#include <ChibiOS_AVR.h>
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include <HomeNetwork.h>
#include "config.h"
#include <EEPROM.h>

RF24 radio(RF24_PIN_CE, RF24_PIN_CSN);
RF24Network network(radio);
HomeNetwork homeNetwork(radio, network, &homeNetwork);

void setup() {
  Serial.begin(115200);
  Serial.println(F("MainLights Node"));

  initLights();

  chBegin(mainThread);

  while (1);
}

// If a thread weirdly crashes then increase the stack value
static WORKING_AREA(wallSwitchThread, 4); // 4 bytes works great

void mainThread() {
  SPI.begin(); // SPI is used by homeNetwork

  chThdCreateStatic(wallSwitchThread, sizeof(wallSwitchThread), NORMALPRIO + 2, WallSwitchThread, NULL);

  homeNetwork.begin(HOME_NODEID, &homeNetworkMessageReceived);

  homeNetwork.setNetworkUpdateTime(HOME_AUTOUPDATE_DELAY);

  Serial.println(F("System booted up!"));
}

void loop() {
  // not used
}




