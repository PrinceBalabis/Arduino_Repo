/**
*  HomeNetwork.cpp
*/

#include "HomeNetwork.h"

HomeNetwork::HomeNetwork( RF24& _radio, RF24Network& _network ): radio(_radio), network(_network)
{
}

void HomeNetwork::begin(uint16_t nodeID)
{
  radio.begin(); // Initialize radio
  network.begin(homeNetwork_channel, nodeID); // Start mesh Network
  radio.setRetries(homeNetwork_retryDelay, homeNetwork_retryTimes);
  radio.setPALevel(homeNetwork_powerAmplifierLevel);
  radio.setDataRate(homeNetwork_dataRate);
  network.txTimeout = 200;
}

void HomeNetwork::autoUpdate(void (* pmsgReceivedF)(int16_t,unsigned char,int32_t))
{
  while(1)
  {
    if(!autoUpdatePaused){
      network.update(); // Check the network regularly for the entire network to function properly
      if(network.available())
      {
        int32_t msgReceived;
        unsigned char msgTypeReceived;
        int16_t msgSenderReceived = read(&msgReceived, &msgTypeReceived);
        pmsgReceivedF(msgSenderReceived, msgTypeReceived, msgReceived);
      }
    }
    chThdSleepMilliseconds(homeNetwork_autoUpdateTime);  //Give other threads some time to run
  }
}

/**
* write
* This function sends the message to a receiver, both which are set in parameter
**/
uint8_t HomeNetwork::write(uint16_t msgReceiver, int32_t msgContent, unsigned char msgType)
{
  // Set receiver of message
  RF24NetworkHeader header(msgReceiver, msgType);

  // Send message to server, keep trying untill server confirms receiver gets the message
  bool msgSent = false;
  unsigned long started_waiting_at = millis();
  bool timeout = false;
  bool sendDone = false;
  bool retried = false;

  // Will try to keep send message until receiver gets it
  while (!msgSent && !timeout) {
    Serial.print("BEFORE WRITE ");
    msgSent = network.write(header, &msgContent, sizeof(msgContent));
    Serial.print("AFTER WRITE ");
    if (msgSent)
    {
      Serial.print("sent");
      return 1;
    }
    else if(msgSent && retried){
      Serial.print("sent RETRIED");
      return 2;
    }
    else if (millis() - started_waiting_at > homeNetwork_timeoutSendTime ) {
      timeout = true;
      Serial.print("FAIL");
      return 0;
    }
    else if (!msgSent) {
      //Failed to send message, retrying...
      Serial.print("RETY");

      chThdSleepMilliseconds(20);
      retried = true;
    }
  }
  Serial.print("mmmmmmmmmmmmmmmmmmmmmmmmmmmm ");
}

/**
* writeQuestion
* This function sends the message to a receiver, both which are set in parameter
* Gets a response back
**/
uint8_t HomeNetwork::writeQuestion(uint16_t msgReceiver, int32_t msgContent, int32_t *pmsgResponce)
{
  autoUpdatePaused = true; // Pause listening for messages
  uint8_t msgSent = write(msgReceiver, msgContent, msgTypeAsk);
  if(msgSent == 1 || msgSent == 2){
    int16_t msgSenderReceived;
    int32_t msgReceived;
    unsigned char msgTypeReceived = 'Z';

    // Send message to server, keep trying untill server confirms receiver gets the message
    unsigned long started_waiting_at = millis();

    // Will wait a while
    while (msgSenderReceived != msgReceiver || msgTypeReceived != msgTypeResponse) {
      network.update(); // Check the network regularly for the entire network to function properly
      msgSenderReceived = read(&msgReceived, &msgTypeReceived);
      if (millis() - started_waiting_at > homeNetwork_timeoutAnswerTime ) {
        autoUpdatePaused = false; // Continue listening for messages
        return 0;
      }
      chThdSleepMilliseconds(1); // Check every 1ms if message is received
    }
    *pmsgResponce = msgReceived;
    autoUpdatePaused = false; // Continue listening for messages
    return msgSent;
  } else if(!msgSent){
    autoUpdatePaused = false; // Continue listening for messages
    return 0;
  }
}

/**
*  read
*  This function reads the message and stores it to the variable sent in parameter
* returns the senders ID.int - returns -1 if read was unsuccesful
*/
uint16_t HomeNetwork::read(int32_t *pmsgReceived, unsigned char *pmsgType) {
  if (network.available()) {
    Serial.println(F("NETWORK AVAILBABLE"));
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
  else {
    *pmsgReceived = -1;
    return -1;
  }
}

uint8_t HomeNetwork::askExampleDataToExampleServer(int32_t *pmsgResponse) {
  return writeQuestion(nodeExampleServer, cmdExampleCommand, pmsgResponse);
}

uint8_t HomeNetwork::toggleMainLights() {
  return write(nodeMainLights, cmdToggleLights, msgTypeCommand);
}

// uint8_t HomeNetwork::setMainLightsOn() {
//   msgNode = mainLights;
//   msgContent = 02;
// }

// uint8_t HomeNetwork::setMainLightsOff() {
//   msgNode = mainLights;
//   msgContent = 03;
// }

// uint8_t HomeNetwork::togglePaintingLights() {
//   msgNode = centralHomeControl;
//   msgContent = 11;
// }

// uint8_t HomeNetwork::setPaintingLightsOn() {
//   msgNode = centralHomeControl;
//   msgContent = 9;
// }

// uint8_t HomeNetwork::setPaintingLightsOff() {
//   msgNode = centralHomeControl;
//   msgContent = 10;
// }

// uint8_t HomeNetwork::toggleSpeakerPower() {
//   msgNode = centralHomeControl;
//   msgContent = 01;
// }

// uint8_t HomeNetwork::setSpeakerPowerOn() {
//   msgNode = centralHomeControl;
//   msgContent = 02;
// }

// uint8_t HomeNetwork::setSpeakerPowerOff() {
//   msgNode = centralHomeControl;
//   msgContent = 03;
// }

// uint8_t HomeNetwork::shutdownAll() {
//   setMainLightsOff();
//   setPaintingLightsOff();
//   setSpeakerPowerOff();
// }

// uint8_t HomeNetwork::enterSleepMode() {
//   shutdownAll();
// }

// uint8_t HomeNetwork::leavingApartment() {
//   shutdownAll();
// }

// uint8_t HomeNetwork::exitSleepMode() {
//   setMainLightsOn();
//   setSpeakerPowerOn();
// }

// uint8_t HomeNetwork::setPartyMode() {
//   setPaintingLightsOn();
//   setMainLightsOff();
//   chThdSleepMilliseconds(20);
//   setSpeakerPowerOn();
// }
