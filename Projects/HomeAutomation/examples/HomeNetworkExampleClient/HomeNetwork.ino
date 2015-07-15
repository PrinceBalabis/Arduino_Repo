/**
 *  Prince Home Network IOT Listener
 **/
RF24 radio(8, 9); // CE & CSN pins
RF24Network network(radio);
HomeNetwork homeNetwork(radio, network);

/**
 *  Thread for the Home Network
 **/
static msg_t Thread1(void *arg)
{
  chThdSleepMilliseconds(4000); // If this thread starts too fast, the Arduino will crash!

  SPI.begin(); // SPI is used by the RF24 module
  homeNetwork.begin(nodeID); // Run RF24 config for the customized Prince Home Automation and IOT Network

  // The thread stops at this function, this function has a loop which keeps the network
  // auto updated and executes 'homeNetworkMessageReceived()' when a message is received
  // This function has to run on a thread or else home network wont work.
  homeNetwork.autoUpdate(&homeNetworkMessageReceived);

  return 0;
}

