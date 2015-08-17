/**
*  HomeNetwork.cpp
*/

#include "HomeNetwork.h"
#include <ChibiOS_AVR.h>
#include "homeNetworkConfig.h"

HomeNetwork::HomeNetwork(RF24& _radio, RF24Network& _network): radio(_radio), network(_network)
{
}

/**
*  Thread for the Home Network
**/
// Declare a semaphore with an inital counter value of zero.
static WORKING_AREA(homeNetworkThread, 64); // 32 bytes crash - 64 bytes seems to work
static msg_t HomeNetworkThread(void *homeNetwork)
{
  // The thread stops at this function, this function has a loop which keeps the network
  // auto updated and executes 'homeNetworkMessageReceived()' when a message is received
  // This function has to run on a thread or else home network wont work.
  ((HomeNetwork*)homeNetwork)->autoUpdate();

  return 0;
}

void HomeNetwork::begin(uint16_t nodeID, void (* _pmsgReceivedF)(uint16_t,unsigned char,int32_t))
{
  radio.begin(); // Initialize radio
  network.begin(HOME_SETTING_CHANNEL, nodeID); // Start mesh Network
  // Radio settings must be run after network.begin
  radio.setPALevel(HOME_SETTING_POWERAMPLIFIERLEVEL);
  radio.setDataRate(HOME_SETTING_DATARATE);

  //Clear all incoming queued messages that was received by RF24 module before Arduino completed boot
  // while(1){
  //   network.update(); // Check the network regularly for the entire network to function properly
  //   if(network.available()){
  //     read(NULL, NULL); // Destroy incoming messages
  //   } else {
  //     break;
  //   }
  //   chThdSleepMicroseconds(100); // Give system some time to run other stuff
  // }

  //Start Network Auto Update thread
  pmsgReceivedF = _pmsgReceivedF;
  homeNetwork_autoUpdateTime = HOME_SETTING_DEFAULT_TIME_NETWORKAUTOUPDATE;
  chThdCreateStatic(homeNetworkThread, sizeof(homeNetworkThread), NORMALPRIO + 3, HomeNetworkThread, this);
}

bool HomeNetwork::setNetworkUpdateTime(int8_t _homeNetwork_autoUpdateTime)
{
  if(_homeNetwork_autoUpdateTime < 0 || _homeNetwork_autoUpdateTime > 255 ) { // If less than 0 or bigger than 255 then set to default
    homeNetwork_autoUpdateTime = HOME_SETTING_DEFAULT_TIME_NETWORKAUTOUPDATE;
    return true;
  } else {
    homeNetwork_autoUpdateTime = _homeNetwork_autoUpdateTime;
    return false;
  }
}

void HomeNetwork::autoUpdate()
{
  while (1) {

    // Get stuck in this loop while its ment to be paused
    if(!autoUpdateStatus){
      currentAutoUpdateStatus = false;
      while(!autoUpdateStatus){
        chThdSleepMilliseconds(2);  //Check if autoUpdate should unpause every few ms
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
      if(debug)
      Serial.print("msgType:");
      if(msgType == HOME_TYPE_COMMAND || msgType ==  HOME_TYPE_QUESTION){ //A Command/Question w/ confirmation request
        if(debug)
        Serial.print("Normal msgType w/ confirmation->");
        sendFast(msgSender, msgContent, HOME_TYPE_CONFIRMATION); // Send back confirmation
        pmsgReceivedF(msgSender, msgType, msgContent); // deliver message to Sketch
      } else if(msgType == HOME_TYPE_COMMAND_FAST){ // Fast command, no confirmation message back
        if(debug)
        Serial.print("Command fast->");
        pmsgReceivedF(msgSender, HOME_TYPE_COMMAND, msgContent); // deliver message to Sketch
      } else if(msgType ==  HOME_TYPE_QUESTION_FAST){// Fast question, no confirmation message back
        if(debug)
        Serial.print("Question fast->");
        pmsgReceivedF(msgSender, HOME_TYPE_QUESTION, msgContent); // deliver message to Sketch
      }
      else { // default
        if(debug)
        Serial.print("default msgType->");
        pmsgReceivedF(msgSender, msgType, msgContent); //no confirmation message back, deliver message to Sketch
      }
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
    while(!currentAutoUpdateStatus){
      chThdSleepMilliseconds(1); // Check if autoUpdate status changed every few ms
    }
  }
}

/**
* setDebug
* This function is used to toggle debug messages on/off
**/
void HomeNetwork::setDebug(bool status){
  debug = status;
}

/**
* sendRAW
* This function sends the message to a receiver, both which are set in parameter
* This function differs from send function by that this sends a message WITHOUT
* waiting for a confirmation-message back from the receiver of the initial message
**/
void HomeNetwork::sendFast(uint16_t msgReceiver, int32_t msgContent, unsigned char msgType)
{
  if(debug)
  Serial.print("sendFast()->");

  switch(msgType){
    case HOME_TYPE_COMMAND:
    msgType = HOME_TYPE_COMMAND_FAST;
    break;
    case HOME_TYPE_QUESTION:
    msgType = HOME_TYPE_QUESTION_FAST;
    break;
  }

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
  if(debug)
  Serial.print("send()->");

  setNetworkUpdateStatus(false); // Pause autoUpdate

  // Set receiver of message
  RF24NetworkHeader header(msgReceiver, msgType);

  // network.write() function returns wether someone picked up a message,
  // doesn't have to be the node you are trying to send to,
  // could be a parent node, or any node in between. So its not very useful as "sent successful"-verification
  network.write(header, &msgContent, sizeof(msgContent));

  int32_t msgResponse;
  // Read answer and send back
  const bool answerReceived = readAnswer(&msgReceiver, HOME_TYPE_CONFIRMATION, &msgResponse, HOME_SETTING_DEFAULT_TIMEOUT_CONFIRMATION);

  setNetworkUpdateStatus(true); // Resume autoUpdate

  if(answerReceived && msgContent == msgResponse){
    return true;
  } else{
    return false;
  }
}

bool HomeNetwork::sendCommand(uint16_t msgReceiver, int32_t msgContent){
  if(debug)
  Serial.print("sendCommand()->");
  return send(msgReceiver, msgContent, HOME_TYPE_COMMAND);
}

/**
* sendQuestion
* This function sends a question to a receiver, both which are set in parameter
* A response is expected
* returns whether answer was received or not
**/
bool HomeNetwork::sendQuestion(uint16_t msgReceiver, int32_t msgContent, int32_t *pmsgResponse){
  if(debug)
  Serial.print("sendQuestion()->");

  setNetworkUpdateStatus(false); // Pause autoUpdate

  // Send question
  // bool questionSent = send(msgReceiver, msgContent, HOME_TYPE_QUESTION); // Send question
  sendFast(msgReceiver, msgContent, HOME_TYPE_QUESTION_FAST); // Send question
  if(debug){
    Serial.print("Question sent");
    // Serial.print(":");
    // Serial.print(questionSent);
    Serial.print("->");
  }
  bool answerReceived = false;
  // if(questionSent){
  // Read answer and send back
  answerReceived = readAnswer(&msgReceiver, HOME_TYPE_RESPONSE, pmsgResponse, HOME_SETTING_DEFAULT_TIMEOUT_ANSWER);
  // }
  if(debug){
    Serial.print("Answer received:");
    Serial.print(answerReceived);
    Serial.print("->");
  }


  setNetworkUpdateStatus(true); // Resume autoUpdate

  // if(!questionSent || !answerReceived){
  if(!answerReceived){

    return false;
  } else {
    return true;
  }
}

/**
* readAnswer
* returns true if answer is received, false if it is not
**/
bool HomeNetwork::readAnswer(uint16_t *pmsgReceiver, const unsigned char msgType, int32_t *pmsgResponse, uint16_t timeout)
{
  if(debug)
  Serial.print("readAnswer()->");
  int32_t msgSenderReceived = -1;
  unsigned char msgTypeReceived = 'Z';
  int32_t msgReceived = 0;

  unsigned long started_waiting_at = millis();
  while (1) {
    network.update(); // Check the network regularly for the entire network to function properly
    if (millis() - started_waiting_at > timeout) {
      if(debug)
      Serial.print("timeout_readanswer->");
      return false;
    }
    if(network.available())
    {
      msgSenderReceived = read(&msgReceived, &msgTypeReceived);
      if(debug)
      Serial.print("received answer: ");
      if(msgSenderReceived == *pmsgReceiver && msgTypeReceived == msgType){
        if(debug)
        Serial.print("correct->");
        break;
      } else {
        if(debug)
        Serial.print("not correct->");
      }
    }
    chThdSleepMilliseconds(HOME_SETTING_DEFAULT_TIME_READ); // Check every few ms if answer-message is received
  }
  if(debug)
  Serial.print("done read->");

  *pmsgResponse = msgReceived; // Save answer to variable

  return true;
}

void HomeNetwork::respondToQuestion(uint16_t _msgSender, int32_t _ResponseData) {
  if(debug)
  Serial.print("respondToQuestion()->");
  sendFast(_msgSender, _ResponseData, HOME_TYPE_RESPONSE);
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
