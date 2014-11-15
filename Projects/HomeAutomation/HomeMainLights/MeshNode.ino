//------------------------------------------------------------------------------
// Thread 3

RF24 radio(8,9);

static msg_t Thread3(void *arg) {

  const unsigned int timeoutTime = 2000;

  const uint64_t talking_pipes[5] = { 
    0xF0F0F0F0D2LL, 0xF0F0F0F0C3LL, 0xF0F0F0F0B4LL, 0xF0F0F0F0A5LL, 0xF0F0F0F096LL                       };
  const uint64_t listening_pipes[5] = { 
    0x3A3A3A3AD2LL, 0x3A3A3A3AC3LL, 0x3A3A3A3AB4LL, 0x3A3A3A3AA5LL, 0x3A3A3A3A96LL                       };

  // logic variables
  unsigned int msgSent, msgNode;

  radio.begin();

  /** 
   * ----------Tweaks Area Below----------
   */
  radio.setRetries(5,15); // Set delay between retries & # of retires for a "radio.write" command
  radio.openReadingPipe(1,listening_pipes[nodeID]);
  radio.setPayloadSize(2);  // Set payload size to 1 bytes for sending int-values between 0-255
  radio.setPALevel(RF24_PA_HIGH); // Set power amplifier to highest
  radio.setDataRate(RF24_250KBPS); // Set data rate to 250kpbs
  radio.setCRCLength(RF24_CRC_16); // Set CRC length to 16
  /** 
   * ----------Tweaks Area Above-----------
   */

  radio.enableAckPayload(); // Must have Ack enables for this sketch
  radio.startListening(); // Start listening for incoming messages

  while (1) {
    unsigned int msgSender, msgReceived;
    readMessage(&msgSender, &msgReceived);

    // Put code in this if-statement which should occur when a message is received
    if(msgReceived != 0){
      Serial.print("Node "); // Print message
      Serial.print(msgSender); // Print message
      Serial.print(": "); // Print message
      Serial.println(msgReceived); // Print message
      runMessageCommand(msgReceived); // Run the command which the message points to
    }

    // Sleep for 200 milliseconds, to make time for other threads
    chThdSleepMilliseconds(200);
  }
  return 0;  
}

/**
 *  readMessage
 *  This function reads the message and sender and stores it in the variables in the parameter
 */
void readMessage(unsigned int *pmsgSender, unsigned int *pmsgReceived){
  if (radio.available()){
    bool receiveDone = false;
    unsigned int msgPackReceived;
    while(!receiveDone)
      receiveDone = radio.read(&msgPackReceived, sizeof(unsigned int)); // Read message and store to msgPackReceived variable

    radio.writeAckPayload( 1, &msgPackReceived, sizeof(msgPackReceived) );

    // Extract the message pack, to know the sender and message
    *pmsgSender = msgPackReceived % 10;
    *pmsgReceived = (msgPackReceived % 1000) /10;
  } 
  else {
    *pmsgSender = 0;
    *pmsgReceived = 0;
  }
}

/**
 *  runMessageCommand
 *  This function reads the message and runs the command
 */
unsigned int runMessageCommand(unsigned int msgReceived){
  if(msgReceived == commandToggleLights){
    toggleLights(); // Toggle lights
  } 
  else if(msgReceived == commandSetLightsOn){
    setLightsOn();
  } 
  else if(msgReceived == commandSetLightsOff){
    setLightsOff();
  } 
  else {
    return 0;
  }
  return 1;
}



