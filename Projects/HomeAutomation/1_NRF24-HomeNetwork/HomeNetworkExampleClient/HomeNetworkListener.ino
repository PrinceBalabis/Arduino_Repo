//------------------------------------------------------------------------------
// RF24 Mesh Node Thread
RF24 radio(8, 9); // CE & CSN pins
RF24Network network(radio);
HomeNetwork homeNetwork(radio, network);

/**
 *  RF24 thread
 **/
static msg_t Thread1(void *arg)
{
  chThdSleepMilliseconds(4000);
  Serial.println(F("Started rf24 thread"));
  SPI.begin();
  homeNetwork.begin(nodeID); // Run RF24 config for Prince Home Automation and IOT Network

  while (1) {
    homeNetwork.update(); // Check the network regularly

    int32_t msgReceived;
    homeNetwork.read(&msgReceived);

    // Put code in this if-statement which should occur when a message is received
    if (msgReceived != -1) {
      msgContent = msgReceived;
      Serial.println(F("Received Data"));
    }

    chThdSleepMilliseconds(50);  //Give other thread some time to run
  }
}

