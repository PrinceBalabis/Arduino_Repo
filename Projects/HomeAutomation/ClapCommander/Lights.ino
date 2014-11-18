//------------------------------------------------------------------------------
// Thread 1, Signal main lights to toggle

RF24 radio(8,9); 
RF24Network network(radio);

static msg_t Thread1(void *arg) {

  SPI.begin();
  radio.begin(); // Initialize radio
  network.begin(/*channel*/ 90, nodeID);

  // Tweaks optimized for compatability, reliability and driftsecurity
  initTweaks();

  while (!chThdShouldTerminate()) {
    // Wait for signal from thread 2.
    chSemWait(&sem);

    network.update();  // Check the network regularly

    // Send message to server, keep trying untill server confirms receiver gets the message
    Serial.println("SENDING MESSAGE TO TOGGLE LIGHTS...");
    bool msgSent = 0;
    unsigned long started_waiting_at = millis();
    unsigned int timeoutTime = 200; // Amount of time to give trying to resend message to nodes
    bool timeout = false;
    bool sendDone = false;

    // Will try to keep send message untill receiver gets it
    while(!msgSent && !timeout){
      msgSent = sendMessage(mainLights, cmdNRFToggleLights);
      if (msgSent)
      {
          Serial.println("PARENT PICKED UP MESSAGE");
      } 
      else if (millis() - started_waiting_at > timeoutTime ){
        timeout = true;
      }
      else if(!msgSent){
          Serial.println("ERROR!: Failed to send message to parent. retrying...");
      }
    }
    Serial.println(); //Extra row for easier serial reading
  }
  return 0;
}

/**
 *  sendMessage
 * This function sends the message to a receiver, both which are set in parameter
 **/
uint8_t sendMessage(uint16_t msgReceiver, int32_t msgContent){
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
 *  initTweaks
 *  Runs commands to tweak the radio communication according to settings in config.h
 */
void initTweaks(void){
  radio.setRetries(retryDelay, retryTimes); // Set delay between retries & # of retires for a "radio.write" command
  radio.setPALevel(powerAmplifierLevel); // Set power amplifier to highest
  radio.setDataRate(dataRate); // Set data rate to 250kpbs
}


