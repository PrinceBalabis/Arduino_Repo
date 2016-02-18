/**
*  HomeNetwork.cpp
* BE CAREFUL WITH SERIAL PRINTS!
* TOO MANY SERIAL PRINTS AND COMMANDS WONT WORK CORRECTLY!!
*/

#include "HomeNetwork.h"
#include "homeNetworkConfig.h"
#include <NilRTOS.h>
#include <NilSerial.h>

HomeNetwork::HomeNetwork(RF24& _radio, RF24Network& _network): radio(_radio), network(_network)
{
}

void HomeNetwork::begin(uint16_t nodeID, void (* _pmsgReceivedF)(uint16_t,unsigned char,int32_t))
{
  delay(2000); //Give some time for capacitor to charge up and stabilize before initializing RF24 module!
  radio.begin(); // Initialize radio
  network.begin(HOME_SETTING_CHANNEL, nodeID); // Start mesh Network
  // Radio settings must be run after network.begin
  radio.setPALevel(HOME_SETTING_POWERAMPLIFIERLEVEL);
  radio.setDataRate(HOME_SETTING_DATARATE);
  network.txTimeout = 0; // Set to 0 to use the normal auto retry period defined by radio.setRetries()
  radio.setRetries(HOME_SETTING_RETRY_DELAY, HOME_SETTING_RETRY_TIMES);

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

  pmsgReceivedF = _pmsgReceivedF;
  homeNetwork_autoUpdateTime = HOME_SETTING_DEFAULT_TIME_NETWORKAUTOUPDATE;
}

/*

*/
bool HomeNetwork::setNetworkUpdateTime(int8_t _homeNetwork_autoUpdateTime)
{
  if(_homeNetwork_autoUpdateTime < 0 || _homeNetwork_autoUpdateTime > 127 ) { // If its a negative value, or outside the boundaries of int8_t, then set to default
    homeNetwork_autoUpdateTime = HOME_SETTING_DEFAULT_TIME_NETWORKAUTOUPDATE;
    return true;
  } else {
    homeNetwork_autoUpdateTime = _homeNetwork_autoUpdateTime;
    return false;
  }
}

void HomeNetwork::update()
{
  while (1) {

    // Get stuck in this loop while its ment to be paused
    if(!autoUpdateStatus){
      currentAutoUpdateStatus = false;
      while(!autoUpdateStatus){
        nilThdSleepMilliseconds(1);  //Check if autoUpdate should unpause every few ms
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
      if(msgType == HOME_TYPE_COMMAND || msgType ==  HOME_TYPE_QUESTION){ //A Command/Question w/ confirmation request
        if(debug)
          Serial.print(F("msgType: Normal msgType w/ confirmation->"));
        // SPAM CONFIRMATION MESSAGE BACK TO MAKE SURE IT GET RECEIVED!!!
        for(uint8_t i=0 ; i<HOME_SETTING_DEFAULT_SPAM_CONFIRMATION_TIMES ; i++){
          sendFast(msgSender, msgContent, HOME_TYPE_CONFIRMATION); // Send back confirmation
        }
        pmsgReceivedF(msgSender, msgType, msgContent); // deliver message to Sketch
      } else if(msgType == HOME_TYPE_COMMAND_FAST){ // Fast command, no confirmation message back
        if(debug)
          Serial.print(F("Command fast->"));
        pmsgReceivedF(msgSender, HOME_TYPE_COMMAND, msgContent); // deliver message to Sketch
      } else if(msgType ==  HOME_TYPE_QUESTION_FAST){// Fast question, no confirmation message back
        if(debug)
          Serial.print(F("Question fast->"));
        pmsgReceivedF(msgSender, HOME_TYPE_QUESTION, msgContent); // deliver message to Sketch
      }
      else {
        // Useless spam or trash talk gets here, like HOME_TYPE_CONFIRMATION-messages or HOME_TYPE_RESPONSE-messages
      }
    }

    nilThdSleepMilliseconds(homeNetwork_autoUpdateTime);  //Give other threads some time to run
  }
}

void HomeNetwork::setNetworkUpdateStatus(bool status)
{
  // set autoUpdate to either enabled or disabled
  autoUpdateStatus = status;

  if(status){
    // Wait for autoUpdate to pause
    while(!currentAutoUpdateStatus){
      nilThdSleepMilliseconds(1); // Check if autoUpdate status changed every few ms
    }
  }
}

void HomeNetwork::setDebug(bool status){
  debug = status;
}

void HomeNetwork::sendFast(uint16_t msgReceiver, int32_t msgContent, unsigned char msgType)
{
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

bool HomeNetwork::send(uint16_t msgReceiver, int32_t msgContent, unsigned char msgType, uint8_t retryTimes, uint16_t timeout)
{
  if(debug)
    Serial.print(F("send()->"));

  setNetworkUpdateStatus(false); // Pause autoUpdate

  // Set receiver of message
  RF24NetworkHeader header(msgReceiver, msgType);

  int32_t msgResponse;
  bool answerReceived;

  for(uint8_t i=0 ; i<retryTimes ; i++){
    // network.write() function returns wether someone picked up a message,
    // doesn't have to be the node you are trying to send to,
    // could be a parent node, or any node in between. So its not very useful as "sent successful"-verification
    network.write(header, &msgContent, sizeof(msgContent));

    // Read answer and send back
    answerReceived = readAnswer(&msgReceiver, HOME_TYPE_CONFIRMATION, &msgResponse, timeout);
    if(answerReceived){
      break; // when answer is received stop resending message
    } else {
      if(debug)
        Serial.print(F("FAILED to send...Resending->"));
    }
  }

  setNetworkUpdateStatus(true); // Resume autoUpdate

  if(answerReceived && msgContent == msgResponse){
    return true;
  } else{
    return false;
  }
}

// This function acts as a default send function but with default retry time and timeout
bool HomeNetwork::send(uint16_t msgReceiver, int32_t msgContent, unsigned char msgType){
  return send(msgReceiver, msgContent, msgType, HOME_SETTING_DEFAULT_SEND_RETRY_TIMES, HOME_SETTING_DEFAULT_TIMEOUT_CONFIRMATION);
}

bool HomeNetwork::sendCommand(uint16_t msgReceiver, int32_t msgContent){
  if(debug)
    Serial.print(F("sendCommand()->"));
  return send(msgReceiver, msgContent, HOME_TYPE_COMMAND);
}

bool HomeNetwork::sendCommand(uint16_t msgReceiver, int32_t msgContent, uint8_t retryTimes, uint16_t timeout){
  if(debug)
    Serial.print(F("sendCommand()->"));
  return send(msgReceiver, msgContent, HOME_TYPE_COMMAND, retryTimes, timeout);
}

/**
* sendQuestion
* This function sends a question to a receiver, both which are set in parameter
* A response is expected
* returns whether answer was received or not
**/
bool HomeNetwork::sendQuestion(uint16_t msgReceiver, int32_t msgContent, int32_t *pmsgResponse, uint16_t timeout){

  setNetworkUpdateStatus(false); // Pause autoUpdate

  if(debug)
    Serial.print(F("sendQuestion()->"));
  // Send question
  bool answerReceived;
  for(int i = 0; i < HOME_SETTING_DEFAULT_QUESTION_RETRY_TIMES; i++){
    sendFast(msgReceiver, msgContent, HOME_TYPE_QUESTION_FAST); // Send question
    answerReceived = readAnswer(&msgReceiver, HOME_TYPE_RESPONSE, pmsgResponse, timeout); // Read answer and send back
    if(answerReceived)
      break;
  }

  setNetworkUpdateStatus(true); // Resume autoUpdate

  if(answerReceived){
    if(debug)
      Serial.print(F("Answer received->"));
    return true;
  } else {
    if(debug)
      Serial.print(F("NO ANSWER WAS RECEIVED! ->"));
    return false;
  }
}

bool HomeNetwork::sendQuestion(uint16_t msgReceiver, int32_t msgContent, int32_t *pmsgResponse){
  sendQuestion(msgReceiver, msgContent, pmsgResponse, HOME_SETTING_DEFAULT_TIMEOUT_ANSWER);
}


/**
* readAnswer
* returns true if answer is received, false if it is not
**/
bool HomeNetwork::readAnswer(uint16_t *pmsgReceiver, const unsigned char msgType, int32_t *pmsgResponse, uint16_t timeout)
{
  int32_t msgSenderReceived = -1;
  unsigned char msgTypeReceived = 'Z';
  int32_t msgReceived = 0;

  unsigned long started_waiting_at = millis();
  while (1) {
    network.update(); // Check the network regularly for the entire network to function properly
    if (millis() - started_waiting_at > timeout) {
      if(debug)
        Serial.print(F("TIMED OUT! NO ANSWER RECEIVED!->"));
      return false;
    }
    if(network.available())
    {
      msgSenderReceived = read(&msgReceived, &msgTypeReceived);
      if(msgSenderReceived == *pmsgReceiver && msgTypeReceived == msgType){
        break;
      } else if(msgSenderReceived != *pmsgReceiver){
        if(debug)
          Serial.print(F("MESSAGE RECEIVED WAS NOT FROM CORRECT NODE!->"));
        return false;
      } else if(msgTypeReceived != msgType){
        if(debug)
          Serial.print(F("MESSAGE RECEIVED HAS WRONG MESSAGE TYPE!->"));
        return false;
      }
    }
    nilThdSleepMilliseconds(HOME_SETTING_DEFAULT_TIME_READ); // Check every few ms if answer-message is received
  }

  *pmsgResponse = msgReceived; // Save answer to variable

  return true;
}

void HomeNetwork::respondToQuestion(uint16_t _msgSender, int32_t _ResponseData) {
  if(debug)
    Serial.print(F("respondToQuestion()->"));
  // SPAM ANSWER MESSAGE BACK TO MAKE SURE IT GET RECEIVED!!!
  for(uint8_t i=0 ; i<HOME_SETTING_DEFAULT_SPAM_ANSWER_TIMES ; i++){
    sendFast(_msgSender, _ResponseData, HOME_TYPE_RESPONSE);
  }
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
