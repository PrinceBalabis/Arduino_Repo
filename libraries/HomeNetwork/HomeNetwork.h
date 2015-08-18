#ifndef __HOMENETWORK_H__
#define __HOMENETWORK_H__

/*
HomeNetwork.h - Library for Prince Home Automation & IOT network of RF24 nodes
*/
#include "RF24.h"
#include "RF24Network.h"
#include "nodesConfig.h"

//Enable NilSerial in both debug messages and Sketch(Sketch inherits defines from h-files)
//#define Serial NilSerial

class RF24;
class RF24Network;

class HomeNetwork
{
public:
  HomeNetwork(RF24& _radio, RF24Network& _network);
  void begin(uint16_t nodeID, void (* _pmsgReceivedF)(uint16_t,unsigned char,int32_t));

  bool setNetworkUpdateTime(int8_t _homeNetwork_autoUpdateTime);
  void setNetworkUpdateStatus(bool status);
  void setDebug(bool status);

  void sendFast(uint16_t msgReceiver, int32_t msgContent, unsigned char msgType);
  bool send(uint16_t msgReceiver, int32_t msgContent, unsigned char msgType);
  bool sendCommand(uint16_t msgReceiver, int32_t msgContent);
  bool sendQuestion(uint16_t msgReceiver, int32_t msgContent, int32_t *pmsgResponse);
  bool readAnswer(uint16_t *pmsgReceiver, const unsigned char msgType, int32_t *pmsgResponse, uint16_t timeout);

  void respondToQuestion(uint16_t _msgSender, int32_t _ResponseData);

  void update(); // Used by internal thread, NOT to be used by Sketch!
private:
  RF24& radio;
  RF24Network& network;
  void (* pmsgReceivedF)(uint16_t,unsigned char,int32_t);

  bool autoUpdateStatus = true;
  bool currentAutoUpdateStatus = true;
  bool debug = false;

  int8_t homeNetwork_autoUpdateTime;

  uint16_t read(int32_t *pmsgReceived, unsigned char *pmsgType);
};
#endif
