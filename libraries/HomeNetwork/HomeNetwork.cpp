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
  network.begin(channel, nodeID); // Start mesh Network
  radio.setRetries(retryDelay, retryTimes);
  radio.setPALevel(powerAmplifierLevel);
  radio.setDataRate(dataRate);
}

void HomeNetwork::update(void)
{
  network.update();
}

bool HomeNetwork::available(void)
{
  return network.available();
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
    msgSent = network.write(header, &msgContent, sizeof(msgContent));
    if (msgSent)
    {
      return 1;
    }
    else if(msgSent && retried){
      return 2;
    }
    else if (millis() - started_waiting_at > timeoutSendTime ) {
      timeout = true;
      return 0;
    }
    else if (!msgSent) {
      //Failed to send mesage, retrying...
      retried = true;
    }
  }
}

/**
*  read
*  This function reads the message and stores it to the variable sent in parameter
* returns the senders ID.int
*/
uint16_t HomeNetwork::read(int32_t *pmsgReceived) {
  if (available()) {
    // Save sender node ID of received message
     RF24NetworkHeader peekHeader;
     network.peek(peekHeader);
     uint16_t msgSender = peekHeader.from_node;

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

uint8_t HomeNetwork::sendExampleDataToExampleServer(uint16_t *pmsgReceiver) {
  // Send the ID of the receiver of the message so the thread will later know
  // the responce came from the right node.
  *pmsgReceiver = exampleServer;
  return write(*pmsgReceiver, exampleData, msgTypeAsk);
}

uint8_t HomeNetwork::toggleMainLights(uint16_t *pmsgReceiver) {
  // Send the ID of the receiver of the message so the thread will later know
  // the responce came from the right node.
  *pmsgReceiver = mainLights;
  return write(mainLights, toggleLights, msgTypeCommand);
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
