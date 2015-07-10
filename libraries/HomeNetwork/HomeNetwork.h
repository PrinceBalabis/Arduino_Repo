#ifndef __HOMENETWORK_H__
#define __HOMENETWORK_H__

/*
  HomeNetwork.h - Library for Prince Home Automation & IOT network of RF24 nodes
*/
#include "HomeNetworkAbilities.h"

class RF24;
class RF24Network;

class HomeNetwork
{
  public:

	HomeNetwork(RF24& _radio, RF24Network& _network);
	void begin(uint16_t nodeID);
	void update(void);
	bool available(void);
	uint8_t write(uint16_t msgReceiver, int32_t msgContent);
	void read(int32_t *pmsgReceived);


  private:
  	RF24& radio;
  	RF24Network& network;
};
#endif