//------------------------------------------------------------------------------
// RF24 Mesh Node Thread

RF24 radio(8, 9); // CE & CSN pins
RF24Network network(radio);
HomeNetwork homeNetwork;

/**
 *  RF24 thread
 **/
static msg_t Thread1(void *arg)
{
  chThdSleepMilliseconds(4000);
  Serial.println(F("Started rf24 thread"));

  SPI.begin();
  radio.begin(); // Initialize radio
  network.begin(/*channel*/ 90, nodeID);

  homeNetwork.config(); // Run RF24 config for Prince Home Automation and IOT Network

  while (1) {
    network.update(); // Check the network regularly

    if (msgNode == -1 )
    {

      int32_t msgReceived;
      readMessage(&msgReceived);

      // Put code in this if-statement which should occur when a message is received
      if (msgReceived != -1) {
        msgContent = msgReceived;
        Serial.println(F("Received Data"));
      }
    }
    else if (msgNode >= 0)
    {
      Serial.println(F("MESSAGE SEND PROGRAM"));
      Serial.print(F("nodeID OF RECEIVER: "));
      Serial.println(msgNode);
      Serial.print(F("MESSAGE CONTENT: "));
      Serial.println(msgContent);

      // Send message to server, keep trying untill server confirms receiver gets the message
      bool msgSent = false;
      unsigned long started_waiting_at = millis();
      unsigned int timeoutTime = 200; // Amount of time to give trying to resend message to nodes
      bool timeout = false;
      bool sendDone = false;

      // Will try to keep send message untill receiver gets it
      while (!msgSent && !timeout) {
        msgSent = sendMessage(msgNode, msgContent);
        if (msgSent)
        {
          Serial.println(F("PARENT PICKED UP MESSAGE"));
        }
        else if (millis() - started_waiting_at > timeoutTime ) {
          timeout = true;
        }
        else if (!msgSent) {
          Serial.println(F("ERROR!: Failed to send message to parent. retrying..."));
          chThdSleepMilliseconds(20);
        }
        Serial.println(); // Extra row for easier serial reading
      }

      // Clear message and receiver content
      msgNode = -1;
      msgContent = -1;

    }
    // Unlock data access.
    chThdSleepMilliseconds(20);  //Give other thread some time to run
  }
}

/**
 *  sendMessage
 * This function sends the message to a receiver, both which are set in parameter
 **/
uint8_t sendMessage(uint16_t msgReceiver, int32_t msgContent)
{
  // Set receiver of message
  RF24NetworkHeader header(msgReceiver);

  // Sends message
  bool sendDone = network.write(header, &msgContent, sizeof(msgContent));

  if (sendDone) {
    return 1;
  }
  else {
    return 0;
  }
}

/**
 *  readMessage
 *  This function reads the message and stores it to the variable sent in parameter
 */
void readMessage(int32_t *pmsgReceived) {
  if (network.available()) {
    RF24NetworkHeader header;
    network.read(header, pmsgReceived, sizeof(int32_t)); // Read message and store to msgReceived variable
  }
  else {
    *pmsgReceived = -1;
  }
}

///**
// *  initTweaks
// *  Runs commands to tweak the radio communication according to settings in config.h
// */
//void initTweaks(void) {
//  radio.setRetries(retryDelay, retryTimes);
//  radio.setPALevel(powerAmplifierLevel);
//  radio.setDataRate(dataRate);
//}

void toggleMainLights() {
  msgNode = mainLights;
  msgContent = 01;
}

void setMainLightsOn() {
  msgNode = mainLights;
  msgContent = 02;
}

void setMainLightsOff() {
  msgNode = mainLights;
  msgContent = 03;
}

void togglePaintingLights() {
  msgNode = centralHomeControl;
  msgContent = 11;
}

void setPaintingLightsOn() {
  msgNode = centralHomeControl;
  msgContent = 9;
}

void setPaintingLightsOff() {
  msgNode = centralHomeControl;
  msgContent = 10;
}

void toggleSpeakerPower() {
  msgNode = centralHomeControl;
  msgContent = 01;
}

void setSpeakerPowerOn() {
  msgNode = centralHomeControl;
  msgContent = 02;
}

void setSpeakerPowerOff() {
  msgNode = centralHomeControl;
  msgContent = 03;
}

void shutdownAll() {
  setMainLightsOff();
  chThdSleepMilliseconds(20);
  setPaintingLightsOff();
  chThdSleepMilliseconds(1000);
  setSpeakerPowerOff();
}

void enterSleepMode() {
  shutdownAll();
}

void leavingApartment() {
  shutdownAll();
}

void exitSleepMode() {
  setMainLightsOn();
  chThdSleepMilliseconds(20);
  setSpeakerPowerOn();
}

void setPartyMode() {
  setPaintingLightsOn();
  chThdSleepMilliseconds(20);
  setMainLightsOff();
  chThdSleepMilliseconds(700);
  setSpeakerPowerOn();
}



