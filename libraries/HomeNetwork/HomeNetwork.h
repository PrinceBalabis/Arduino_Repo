#ifndef __HOMENETWORK_H__
#define __HOMENETWORK_H__

/*
  HomeNetwork.h - Library for Prince Home Automation & IOT network of RF24 nodes
*/
#include <SPI.h>
#include "RF24.h"
#include "radioConfig.h"
#include <stddef.h>
#include <stdint.h>
#include "nodesConfig.h"
#include "RF24Network.h"
#include "HomeNetwork.h"

class RF24;
class RF24Network;

class HomeNetwork
{
  public:
	HomeNetwork(RF24& _radio, RF24Network& _network);
	void begin(uint16_t nodeID);
	void update(void);
	bool available(void);
  uint8_t write(uint16_t msgReceiver, int32_t msgContent, unsigned char msgType);
	uint16_t read(int32_t *pmsgReceived);

	// Add new home commands here!
	uint8_t sendExampleDataToExampleServer(uint16_t *pmsgReceiver);
	uint8_t toggleMainLights(uint16_t *pmsgReceiver);
	// uint8_t setMainLightsOn();
	// uint8_t setMainLightsOff();
	// uint8_t togglePaintingLights();
	// uint8_t setPaintingLightsOn();
	// uint8_t setPaintingLightsOff();
	// uint8_t toggleSpeakerPower();
	// uint8_t setSpeakerPowerOn();
	// uint8_t setSpeakerPowerOff();
	// uint8_t shutdownAll();
	// uint8_t enterSleepMode();
	// uint8_t leavingApartment();
	// uint8_t exitSleepMode();
	// uint8_t setPartyMode();

  private:
  	RF24& radio;
  	RF24Network& network;
};
#endif