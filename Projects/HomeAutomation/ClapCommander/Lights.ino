//------------------------------------------------------------------------------
// Thread 1, turn the LED off when signalled by thread 2.

RF24 radio(8,9); 

//
// Topology
//
const uint64_t talking_pipes[5] = { 
  0xF0F0F0F0D2LL, 0xF0F0F0F0C3LL, 0xF0F0F0F0B4LL, 0xF0F0F0F0A5LL, 0xF0F0F0F096LL };
const uint64_t listening_pipes[5] = { 
  0x3A3A3A3AD2LL, 0x3A3A3A3AC3LL, 0x3A3A3A3AB4LL, 0x3A3A3A3AA5LL, 0x3A3A3A3A96LL };

static msg_t Thread1(void *arg) {
  
  radio.begin(); // Initialize radio
  // Tweaks optimized for compatability, reliability and driftsecurity
  radio.setRetries(5,15); // Set delay between retries & # of retires for a "radio.write" command
  radio.enableAckPayload(); // Must have Ack enables for this sketch
  radio.openReadingPipe(1,listening_pipes[nodeID]);
  radio.setPayloadSize(2);  // Set payload size to 1 bytes for sending int-values between 0-255
  radio.setPALevel(RF24_PA_HIGH); // Set power amplifier to highest
  radio.setDataRate(RF24_250KBPS); // Set data rate to 250kpbs
  radio.setCRCLength(RF24_CRC_16); // Set CRC length to 16


  while (!chThdShouldTerminate()) {
    // Wait for signal from thread 2.
    chSemWait(&sem);

    // Send message to server, keep trying untill server confirms receiver gets the message
    Serial.println("SENDING MESSAGE TO TOGGLE LIGHTS...");
    unsigned int msgSent = 0;
    unsigned long started_waiting_at = millis();
    unsigned int timeoutTime = 200; // Amount of time to give trying to resend message to nodes
    bool timeout = false;
    bool sendDone = false;

    // Will try to keep send message untill receiver gets it
    while(!msgSent && !timeout){
      msgSent = sendMessage(mainLights, cmdNRFToggleLights);
      if (msgSent)
      {
        Serial.println("RECEIVER NODE CONFIRMS MESSAGE RELIABILITY WITH ACK");
      } 
      else if (millis() - started_waiting_at > timeoutTime ){
        timeout = true;
        radio.startListening(); // Start listening for response from sender again
      }
      else if(!msgSent){
        Serial.println("ERROR!: Failed to send message to node. retrying...");
        chThdSleepMilliseconds(20);
      }
    }
    Serial.println(); //Extra row for easier serial reading

  }
  return 0;
}

unsigned int sendMessage(unsigned int msgReceiver, unsigned int msgContent){
  unsigned int msgPack;
  msgPack = (msgContent*10) + nodeID; // Pack receiver of message and message together

  // Stop listening so we can talk.
  radio.stopListening();

  // Sends response message, will keep trying to 
  //send message until an ack is returned from sender or timeout
  // Open the correct pipe for writing
  radio.openWritingPipe(listening_pipes[mainLights]);
  bool sendDone = false;
  sendDone = radio.write(&msgPack, sizeof(unsigned int)); // Send back received value
  bool gotAck = 0;
  if(sendDone)
    gotAck = waitAckPayload(msgPack);
  radio.startListening(); // Start listening for response from sender again
  if(gotAck){
    return 1;
  } 
  else {
    return 0;
  }
}

unsigned int waitAckPayload(unsigned int msgPack){
  unsigned long started_waiting_at = millis();
  unsigned int timeoutTime = 20; // Amount of time to wait for ACK (ms)
  bool timeout = false;
  unsigned int ack = -1;

  while(ack == -1 && !timeout){
    if ( radio.isAckPayloadAvailable() )
    {
      radio.read(&ack,sizeof(ack));
      if(ack == msgPack){
        return 1;
      }
    } 
    else if (millis() - started_waiting_at > timeoutTime ){
      timeout = true;
      return 0;
    }
  }
}
