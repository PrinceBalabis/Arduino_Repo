//------------------------------------------------------------------------------
// RF24 Mesh Node Thread

RF24 radio(8,9); // CE & CSN pins
RF24Network network(radio);

/**
 *  This function runs the command it receives from other nodes
 **/
void runCommand(int32_t command){
  if (speakerPower == command)
  {
    dataX = 01;
    Serial.println(F("Toggled Speaker power"));
  }
  else if (speakerVolumeUp == command)
  {
    dataX = 02;
    Serial.println(F("Increased Speaker volume"));
  }
  else if (speakerVolumeDown == command)
  {
    dataX = 03;
    Serial.println(F("Decreased Speaker volume"));
  }
  else if (speakerMute == command)
  {
    dataX = 04;
    Serial.println(F("Muted Speaker"));
  }
}

/**
 *  RF24 thread
 **/
static msg_t Thread2(void *arg) 
{
  chThdSleepMilliseconds(5000);  //Give KeypadListener thread some time to start
  Serial.println(F("Started rf24 thread"));

  SPI.begin();
  radio.begin(); // Initialize radio
  network.begin(/*channel*/ 90, nodeID);

  initTweaks(); // Run RF24 tweaks

    while (1) {
    network.update(); // Check the network regularly

    // Lock access to data.
    chMtxLock(&dataMutex);

    // Copy shared data to tmp variables.
    int msgContent = dataX;
    int msgNode = dataY;

    if(msgNode == -1 )
    {

      int32_t msgReceived;
      readMessage(&msgReceived);

      // Put code in this if-statement which should occur when a message is received
      if(msgReceived != -1){
        runCommand(msgReceived);
        Serial.println(F("Received Data"));
      }
    } 
    else if(msgNode >= 0)
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
      while(!msgSent && !timeout){
        msgSent = sendMessage(msgNode, msgContent);
        if (msgSent)
        {
          Serial.println(F("PARENT PICKED UP MESSAGE"));
        } 
        else if (millis() - started_waiting_at > timeoutTime ){
          timeout = true;
        }
        else if(!msgSent){
          Serial.println(F("ERROR!: Failed to send message to parent. retrying..."));
          chThdSleepMilliseconds(20);
        }
        Serial.println(); // Extra row for easier serial reading
      }

      // Clear message and receiver content
      dataX = -1;
      dataY = -1;

    }
    // Unlock data access.
    chMtxUnlock();
    chThdSleepMilliseconds(50);  //Give other thread some time to run
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

  if(sendDone){
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
void readMessage(int32_t *pmsgReceived){
  if (network.available()){
    RF24NetworkHeader header;
    network.read(header, pmsgReceived, sizeof(int32_t)); // Read message and store to msgReceived variable
  }
  else {
    *pmsgReceived = -1;
  }
}

/**
 *  initTweaks
 *  Runs commands to tweak the radio communication according to settings in config.h
 */
void initTweaks(void){
  radio.setRetries(retryDelay, retryTimes); // Set delay between retries & # of retires for a "radio.write" command
  radio.setPALevel(powerAmplifierLevel); // Set power amplifier to highest
  radio.setDataRate(dataRate); // Set data rate to 250kpbs
}













