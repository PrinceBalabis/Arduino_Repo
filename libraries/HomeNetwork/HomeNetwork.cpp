/**
*  HomeNetwork.cpp
*/

#include "HomeNetwork.h"
#include <ChibiOS_AVR.h>
#include "homeNetworkConfig.h"

HomeNetwork::HomeNetwork( RF24& _radio, RF24Network& _network, HomeNetwork* _homeNetwork): radio(_radio), network(_network), homeNetwork(_homeNetwork)
{
}

/**
*  Thread for the Home Network
**/
// Declare a semaphore with an inital counter value of zero.
static WORKING_AREA(homeNetworkThread, 64); // 16 bytes crash - 32 bytes seems to work
static msg_t HomeNetworkThread(void *_homeNetwork)
{
  HomeNetwork* homeNetwork = ((HomeNetwork*)_homeNetwork);

  // The thread stops at this function, this function has a loop which keeps the network
  // auto updated and executes 'homeNetworkMessageReceived()' when a message is received
  // This function has to run on a thread or else home network wont work.
  homeNetwork->autoUpdate();

  return 0;
}

void HomeNetwork::begin(uint16_t nodeID, void (* _pmsgReceivedF)(uint16_t,unsigned char,int32_t))
{
  pmsgReceivedF = _pmsgReceivedF;
  homeNetwork_autoUpdateTime = HOME_SETTING_DEFAULT_TIME_NETWORKAUTOUPDATE;
  chThdCreateStatic(homeNetworkThread, sizeof(homeNetworkThread), NORMALPRIO + 3, HomeNetworkThread, homeNetwork);

  radio.begin(); // Initialize radio
  network.begin(HOME_SETTING_CHANNEL, nodeID); // Start mesh Network
  radio.setPALevel(HOME_SETTING_POWERAMPLIFIERLEVEL);
  radio.setDataRate(HOME_SETTING_DATARATE);
}

void HomeNetwork::setNetworkUpdateTime(int8_t _homeNetwork_autoUpdateTime)
{
  if(_homeNetwork_autoUpdateTime < 0) // If less than 0 then set to default
  homeNetwork_autoUpdateTime = HOME_SETTING_DEFAULT_TIME_NETWORKAUTOUPDATE;
  else
  homeNetwork_autoUpdateTime = _homeNetwork_autoUpdateTime;
}

void HomeNetwork::autoUpdate()
{
  while (1) {

    // Get stuck in this loop while its ment to be paused
    if(!autoUpdateStatus){
      currentAutoUpdateStatus = false;
      while(!autoUpdateStatus){
        chThdSleepMilliseconds(10);  //Check if autoUpdate should unpause every few ms
      }
      currentAutoUpdateStatus = true;
    }

    network.update(); // Check the network regularly for the entire network to function properly
    if(network.available())
    {
      // Send incoming message to Sketch function, if its just a command, send the confirmation
      unsigned char msgType;
      int32_t msgContent;
      uint16_t msgSender = read(&msgContent, &msgType);
      if(msgType == HOME_TYPE_COMMAND){ // if its just a command, send the confirmation message back
        sendFast(msgSender, msgContent, HOME_TYPE_CONFIRMATION);
      }
      pmsgReceivedF(msgSender, msgType, msgContent);
    }

    chThdSleepMilliseconds(homeNetwork_autoUpdateTime);  //Give other threads some time to run
  }
}

void HomeNetwork::setNetworkUpdateStatus(bool status)
{

  // set autoUpdate()
  autoUpdateStatus = status;

  if(status){
    // Wait for autoUpdate to pause
    while(!currentAutoUpdateStatus);
  }
}


/**
* sendRAW
* This function sends the message to a receiver, both which are set in parameter
* This function differs from send function by that this sends a message WITHOUT
* waiting for a confirmation-message back from the receiver of the initial message
**/
void HomeNetwork::sendFast(uint16_t msgReceiver, int32_t msgContent, unsigned char msgType)
{
  // Set receiver of message
  RF24NetworkHeader header(msgReceiver, msgType);

  // network.write() function returns wether someone picked up a message,
  // doesn't have to be the node you are trying to send to,
  // but could be a parent node. So its not very useful.
  network.write(header, &msgContent, sizeof(msgContent));
}

/**
* send
* This function sends the message to a receiver, both which are set in parameter
* This function differs from send function by that this sends a message AND
* waits for a confirmation-message back from the receiver of the initial message
**/
bool HomeNetwork::send(uint16_t msgReceiver, int32_t msgContent, unsigned char msgType)
{
  setNetworkUpdateStatus(false); // Pause autoUpdate
  while(currentAutoUpdateStatus) // Wait for Network autoUpdate to pause
  chThdSleepMilliseconds(1);

  // Set receiver of message
  RF24NetworkHeader header(msgReceiver, msgType);

  // network.write() function returns wether someone picked up a message,
  // doesn't have to be the node you are trying to send to,
  // but could be a parent node. So its not very useful.
  network.write(header, &msgContent, sizeof(msgContent));

  // Read answer and send back
  int32_t msgResponse;
  const bool answerReceived = readAnswer(&msgReceiver, HOME_TYPE_CONFIRMATION, &msgResponse);

  setNetworkUpdateStatus(false); // Resume autoUpdate

  if(msgContent == msgResponse)
  return true;
  else
  return false;

}

bool HomeNetwork::sendCommand(uint16_t msgReceiver, int32_t msgContent){
  return send(msgReceiver, msgContent, HOME_TYPE_COMMAND);
}

/**
* sendQuestion
* This function sends a question to a receiver, both which are set in parameter
* A response is expected
* returns whether answer was received or not
**/
bool HomeNetwork::sendQuestion(uint16_t msgReceiver, int32_t msgContent, int32_t *pmsgResponse){
  setNetworkUpdateStatus(false); // Pause autoUpdate
  while(currentAutoUpdateStatus); // Wait for Network autoUpdate to pause

  // Send question
  sendFast(msgReceiver, msgContent, HOME_TYPE_QUESTION); // Send question

  // Read answer and send back
  const bool answerReceived = readAnswer(&msgReceiver, HOME_TYPE_QUESTION, pmsgResponse);

  setNetworkUpdateStatus(false); // Resume autoUpdate

  return answerReceived;
}

/**
* readAnswer
* returns true if answer is received, false if it is not
**/
bool HomeNetwork::readAnswer(uint16_t *pmsgReceiver, const unsigned char msgType, int32_t *pmsgResponse)
{
  // Wait for answer, will wait untill received or timeout
  bool answerTimeout = false;

  int32_t msgSenderReceived = -1;
  unsigned char msgTypeReceived = 'Z';
  int32_t msgReceived = 0;

  unsigned long started_waiting_at = millis();
  while ((msgSenderReceived != *pmsgReceiver || msgTypeReceived != msgType) && !answerTimeout) {
    network.update(); // Check the network regularly for the entire network to function properly
    if(network.available())
    {
      msgSenderReceived = read(&msgReceived, &msgTypeReceived);
    }
    if (millis() - started_waiting_at > HOME_SETTING_DEFAULT_TIMEOUT_ANSWERTIME && msgSenderReceived == -1) {
      return false;
    }
    chThdSleepMilliseconds(HOME_SETTING_DEFAULT_TIME_RESPONSE); // Check every few ms if answer-message is received
  }

  *pmsgResponse = msgReceived; // Save answer to variable

  return true;
}

void HomeNetwork::respondToCommand(uint16_t _msgSender, int32_t _ResponseData) {
  send(_msgSender, _ResponseData, HOME_TYPE_CONFIRMATION);
}

void HomeNetwork::respondToQuestion(uint16_t _msgSender, int32_t _ResponseData) {
  send(_msgSender, _ResponseData, HOME_TYPE_RESPONSE);
}


/**
*  read
*  This function reads the message and stores it to the variable sent in parameter
* returns the senders ID.int - returns -1 if read was unsuccesful
*/
uint16_t HomeNetwork::read(int32_t *pmsgReceived, unsigned char *pmsgType) {
  // Save sender node ID of received message
  RF24NetworkHeader peekHeader;
  network.peek(peekHeader);
  uint16_t msgSender = peekHeader.from_node;
  *pmsgType = peekHeader.type;

  // Save received message content
  RF24NetworkHeader readHeader;
  network.read(readHeader, pmsgReceived, sizeof(int32_t)); // Read message and store to msgReceived variable

  return msgSender;
}
