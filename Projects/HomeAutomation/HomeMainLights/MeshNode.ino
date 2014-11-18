//------------------------------------------------------------------------------
// Thread 3

RF24 radio(8,9);
RF24Network network(radio);      // Network uses that radio

static msg_t Thread3(void *arg) {
  
  SPI.begin();
  radio.begin();
  network.begin(/*channel*/ 90, /*node address*/ nodeID);

  initTweaks(); // Run network tweaks

    while (1) {
    network.update();                  // Check the network regularly

    int32_t cmdReceived;
    readMessage(&cmdReceived);

    // Put code in this if-statement which should occur when a message is received
    if(cmdReceived != -1){
      Serial.print("Command: "); // Print message
      Serial.println(cmdReceived); // Print message
      runMessageCommand(cmdReceived); // Run the command which the message points to
    }

    // Sleep for 5 milliseconds, to make time for other threads
    chThdSleepMilliseconds(5);
  }
  return 0;  
}

/**
 *  runMessageCommand
 *  This function reads the message and runs the command
 */
unsigned int runMessageCommand(unsigned int cmdReceived){
  if(cmdReceived == commandToggleLights){
    toggleLights(); // Toggle lights
  } 
  else if(cmdReceived == commandSetLightsOn){
    setLightsOn();
  } 
  else if(cmdReceived == commandSetLightsOff){
    setLightsOff();
  } 
  else {
    return 0;
  }
  return 1;
}


/**
 *  readMessage
 *  This function reads the message and stores it to the variable sent in parameter
 */
void readMessage(int32_t *pcmdReceived){
  if (network.available()){
    RF24NetworkHeader header;

    network.read(header, pcmdReceived, sizeof(int32_t)); // Read message and store to msgReceived variable
  }
  else {
    *pcmdReceived = -1;
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


