/**
*  HomeNetwork.cpp
*/

#include "HomeNetwork.h"

HomeNetwork::HomeNetwork( RF24& _radio, RF24Network& _network, HomeNetwork* _homeNetwork): radio(_radio), network(_network), homeNetwork(_homeNetwork)
{
}

/**
*  Thread for the Home Network
**/
static WORKING_AREA(homeNetworkThread, 64);
static msg_t HomeNetworkThread(void *_homeNetwork)
{
  chThdSleepMilliseconds(2000); // If this thread starts too fast, the Arduino will crash!

  SPI.begin(); // SPI is used by the RF24 module
  HomeNetwork* homeNetwork = ((HomeNetwork*)_homeNetwork);

  // The thread stops at this function, this function has a loop which keeps the network
  // auto updated and executes 'homeNetworkMessageReceived()' when a message is received
  // This function has to run on a thread or else home network wont work.
  homeNetwork->autoUpdate();

  return 0;
}

void HomeNetwork::begin(uint16_t nodeID, bool *_pmsgReceived, uint16_t *_pmsgSender, unsigned char *_pmsgType, int32_t *_pmsgContent)
{
  chThdCreateStatic(homeNetworkThread, sizeof(homeNetworkThread), NORMALPRIO + 3, HomeNetworkThread, homeNetwork);
  pmsgReceived = _pmsgReceived;
  pmsgSender = _pmsgSender;
  pmsgType = _pmsgType;
  pmsgContent = _pmsgContent;

  radio.begin(); // Initialize radio
  network.begin(homeNetwork_channel, nodeID); // Start mesh Network
  radio.setRetries(homeNetwork_retryDelay, homeNetwork_retryTimes);
  radio.setPALevel(homeNetwork_powerAmplifierLevel);
  radio.setDataRate(homeNetwork_dataRate);
  network.txTimeout = 400;
}

void HomeNetwork::autoUpdate()
{
  while (1) {
    while(autoUpdatePaused){
      autoUpdatePauseExecuted = true;
      chThdSleepMilliseconds(50);  //Give other threads some time to run
    }
    autoUpdatePauseExecuted = false;
    network.update(); // Check the network regularly for the entire network to function properly
    if(network.available())
    {
      *pmsgSender = read(pmsgContent, pmsgType);
      *pmsgReceived = true;
    }
    chThdSleepMilliseconds(homeNetwork_autoUpdateTime);  //Give other threads some time to run
  }
}

/**
* write
* This function sends the message to a receiver, both which are set in parameter
**/
bool HomeNetwork::write(uint16_t msgReceiver, int32_t msgContent, unsigned char msgType)
{

  // Set receiver of message
  RF24NetworkHeader header(msgReceiver, msgType);

  // Send message to server, keep trying untill server confirms receiver gets the message
  bool msgSent = network.write(header, &msgContent, sizeof(msgContent));

  if (msgSent) {
    return 1;
  }
  else {
    return 0;
  }
}

/**
* writeQuestion
* This function sends the message to a receiver, both which are set in parameter
* Gets a response back
**/
bool HomeNetwork::writeQuestion(uint16_t msgReceiver, int32_t msgContent, int32_t *pmsgResponse)
{
  autoUpdatePaused = true; // Pause listening for messages

  while(!autoUpdatePauseExecuted){
    chThdSleepMilliseconds(2); // Needed for stability, give autoupdate time to pause
  }

  // Send question, will retry until succeed or timeout
  uint16_t msgSenderReceived = -1;
  int32_t msgReceived = 0;
  unsigned char msgTypeReceived = 'Z';
  bool questionSent = false;
  unsigned long started_waiting_at = millis();
  bool questionTimeOut = false;
  while (!questionSent && !questionTimeOut) {
    network.update(); // Check the network regularly for the entire network to function properly
    questionSent = write(msgReceiver, msgContent, msgTypeAsk); // Send question
    if (millis() - started_waiting_at > homeNetwork_timeoutSendTime && !questionSent) {
      questionTimeOut = true;
    }
    chThdSleepMilliseconds(2); // Send every few ms
  }

  // Wait for answer, will wait untill received or timeout
  bool answerTimeout = false;

  // Only wait for answer if question was sent
  if(questionSent){
    //How long to wait for the answer
    started_waiting_at = millis();

    while ((msgSenderReceived != msgReceiver || msgTypeReceived != msgTypeResponse) && !answerTimeout) {
      network.update(); // Check the network regularly for the entire network to function properly
      if(network.available())
      {
        msgSenderReceived = read(&msgReceived, &msgTypeReceived);
      }
      if (millis() - started_waiting_at > homeNetwork_timeoutAnswerTime && msgSenderReceived == -1) {
        answerTimeout = true;
      }
      chThdSleepMilliseconds(2); // Check every few ms if message is received
    }

    *pmsgResponse = msgReceived; // Save answer to variable
  }
  autoUpdatePaused = false; // Continue listening for messages

  if(questionSent && !answerTimeout)
  return 1;
  else
  return 0;
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

bool HomeNetwork::askExampleDataToExampleServer(int32_t *pmsgResponse) {
  return writeQuestion(nodeExampleServer, cmdExampleCommand, pmsgResponse);
}

bool HomeNetwork::responseExampleDataToClient(uint16_t _msgSender, int32_t _cmdExampleResponceData) {
  return write(_msgSender, _cmdExampleResponceData, msgTypeResponse);
}

bool HomeNetwork::toggleMainLights() {
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
