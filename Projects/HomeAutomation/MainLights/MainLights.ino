#include <ChibiOS_AVR.h>
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include <HomeNetwork.h>
#include "config.h"
#include <EEPROM.h>

RF24 radio(homeNetworkCEPin, homeNetworkCSNPin);
RF24Network network(radio);
HomeNetwork homeNetwork(radio, network, &homeNetwork);

void setup() {
  Serial.begin(115200);

  initLights();

  chBegin(mainThread);

  while (1);
}

// If a thread weirdly crashes then increase the stack value
static WORKING_AREA(wallSwitchThread, 4); // 4 bytes works great

void mainThread() {
  SPI.begin(); // SPI is used by homeNetwork
  chThdSleepMilliseconds(1000);

  homeNetwork.begin(nodeID);
  chThdSleepMilliseconds(1000);

  chThdCreateStatic(wallSwitchThread, sizeof(wallSwitchThread), NORMALPRIO + 2, WallSwitchThread, NULL);
  chThdSleepMilliseconds(1000);

  Serial.println(F("Home Network Listen Thread started"));
  homeNetwork.setAutoUpdateTime(homeNetworkAutoUpdateTime);

  // This infinite loop is used to get incoming home network messages
  while (1) {
    // Pauses here untill a message is received
    homeNetwork.waitForIncomingMessage();
    Serial.print(F("New Message.. "));

    //Get received message
    uint16_t msgSender;
    unsigned char msgType;
    int32_t msgContent;
    homeNetwork.getIncomingMessage(&msgSender, &msgType, &msgContent);

    //Send message for decoding
    decodeMessage(&msgSender, &msgType, &msgContent);
  }
}

void loop() {
  // not used
}




