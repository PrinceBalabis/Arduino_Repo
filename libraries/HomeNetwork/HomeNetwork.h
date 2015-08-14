#ifndef __HOMENETWORK_H__
#define __HOMENETWORK_H__

/*
HomeNetwork.h - Library for Prince Home Automation & IOT network of RF24 nodes
*/
#include "RF24.h"
#include "RF24Network.h"
#include "nodesConfig.h"

class RF24;
class RF24Network;

class HomeNetwork
{
public:
  HomeNetwork(RF24& _radio, RF24Network& _network, HomeNetwork* _homeNetwork);
  void begin(uint16_t nodeID, void (* _pmsgReceivedF)(uint16_t,unsigned char,int32_t));

  void setNetworkUpdateTime(int8_t _homeNetwork_autoUpdateTime);
  void setNetworkUpdateStatus(bool status);

  void sendRAW(uint16_t msgReceiver, int32_t msgContent, unsigned char msgType);
  void send(uint16_t msgReceiver, int32_t msgContent, unsigned char msgType);
  void sendCommand(uint16_t msgReceiver, int32_t msgContent);
  bool sendQuestion(uint16_t msgReceiver, int32_t msgContent, int32_t *pmsgResponse);
  void respondToQuestion(uint16_t _msgSender, int32_t _ResponseData);

  void autoUpdate(); // Used by internal thread, NOT to be used by Sketch!
private:
  RF24& radio;
  RF24Network& network;
  HomeNetwork* homeNetwork;

  void (* pmsgReceivedF)(uint16_t,unsigned char,int32_t);

  int8_t homeNetwork_autoUpdateTime;

  bool autoUpdateStatus = true;
  bool currentAutoUpdateStatus = true;

  // Local communication functions
  uint16_t read(int32_t *pmsgReceived, unsigned char *pmsgType);
};
#endif
