#include <FreeRTOS_AVR.h>
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include <HomeNetwork.h>
#include "config.h"
#include <EEPROM.h>

RF24 radio(RF24_PIN_CE, RF24_PIN_CSN);
RF24Network network(radio);
HomeNetwork homeNetwork(radio, network);

void setup() {
  Serial.begin(115200);
  Serial.println(F("MainLights Node"));

  initLights();

  SPI.begin(); // SPI is used by homeNetwork

  xTaskCreate(WallSwitchThread, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL);

  //homeNetwork.setDebug(true); // Enable debug on home Network Library
  homeNetwork.begin(HOME_NODEID, &homeNetworkMessageReceived);
  homeNetwork.setNetworkUpdateTime(HOME_AUTOUPDATE_DELAY);

  Serial.println(F("System booted up!"));

  vTaskStartScheduler(); // start FreeRTOS
  Serial.println(F("Insufficient RAM"));
}

void loop() {
  // not used
}




