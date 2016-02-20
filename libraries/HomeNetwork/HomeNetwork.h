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

  /*****************************************************************************************
  PUBLIC FUNCTIONS START
  *****************************************************************************************/
  /*
  Function which runs when this class is objectified. Pointer-objects in parameter is saved locally to be easily accessed from this class.
  */
  HomeNetwork(RF24& _radio, RF24Network& _network);
  /*
  Start the NRF24 Home Network and make it LIVE
  */
  void begin(uint16_t nodeID, void (* _pmsgReceivedF)(uint16_t, unsigned char, int32_t));

  /*
  How often to auto-update the RF24 Home Network(polling time)
  */
  bool setNetworkUpdateTime(int8_t _homeNetwork_autoUpdateTime);
  /*
  Enable or disable network auto-updates. Need to disable auto-update when sending messages or questions and expecting to receive specific
  messages. Re-enable again to listen for messages received.
  */
  void setNetworkUpdateStatus(bool status);
  /*
  Enable or disable debug mode. Prints more detailed network message information.
  */
  void setDebug(bool status);

  /*
  Send a message, this is faster than just send(), but at the cost of not waiting for any "confirmation" message. This means that
  the system does not know if the receiver of the messaged received the actual message.
  */
  // void sendFast(uint16_t msgReceiver, int32_t msgContent, unsigned char msgType);
  /*
  Similar to sendFast(), but this is slower and waits for a confirmation message to be received. This function is safer than sendFast()
  because using this function you actually know if the receiver actually received the message.
  Returns if the message was sent successfully.
  */
// bool send(uint16_t msgReceiver, int32_t msgContent, unsigned char msgType);
  /*
  Similar to the previous send(), but here you can specify how many retries to send the message before giving up, and the time to
  wait until doing another retry.
  Returns if the message was sent successfully.
  */
  bool send(uint16_t msgReceiver, int32_t msgContent, unsigned char msgType, uint8_t sendTries, uint16_t responsetimeout);
  /*
  Sends a command.
  Returns if the message was sent successfully.
  */
// bool sendCommand(uint16_t msgReceiver, int32_t msgContent);
  /*
  Similar to the previous sendCommand(), but here you can specify how many retries to send the message before giving up, and the time to
  wait until doing another retry.
  Returns if the message was sent successfully.
  */
// bool sendCommand(uint16_t msgReceiver, int32_t msgContent, uint8_t retryTimes, uint16_t timeout);
  /*
  Sends a question. Specify a int32_t pointer in the paramter to which the answer to the question should be stored
  Returns if the message was sent successfully.
  */
// bool sendQuestion(uint16_t msgReceiver, int32_t msgContent, int32_t *pmsgResponse);
  /*
  Similar to the previous sendCommand(), but here you can specify how many retries to send the message before giving up, and the time to
  wait until doing another retry. Specify a int32_t pointer in the paramter to which the answer to the question should be stored
  Returns if the message was sent successfully.
  */
// bool sendQuestion(uint16_t msgReceiver, int32_t msgContent, int32_t *pmsgResponse, uint16_t timeout);

  /*
  Function which is ran to send an answer to a question received from another node. Important to run this as fast as possible after receiving a question,
  as the other node will be waiting for the answer.
  */
// void respondToQuestion(uint16_t _msgSender, int32_t _ResponseData);

  /*
  Function needs to be executed in a thread in the Sketch. Execution will be stuck infinitely in this thread.
  This function must be run in order for home network to function properly.
  */
  void update();

  /*****************************************************************************************
  PUBLIC FUNCTIONS END
  *****************************************************************************************/
private:
  RF24& radio;
  RF24Network& network;
  void (* pmsgReceivedF)(uint16_t, unsigned char, int32_t);

  bool autoUpdateStatus = true;
  bool currentAutoUpdateStatus = true;
  bool debug = false;

  int8_t homeNetwork_autoUpdateTime;

  struct payload_t { // Structure of our payload
    int32_t msgContent;
    unsigned long arrendID;
  };
};
#endif
