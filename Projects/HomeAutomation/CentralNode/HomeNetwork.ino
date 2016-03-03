/**
   homeNetworkMessageReceived()
   This function is executed automatically by the HomeNetwork Library when a message is received.
*/
void homeNetworkMessageReceived(uint16_t msgSender, unsigned char msgType, int32_t msgContent) {
  callbackCommand = msgContent; // Save message command to queue which is to be sent to HomeControl
}

/**
   Thread for the Home Network
**/
NIL_WORKING_AREA(homeNetworkThread, 100); // bytes seems to work fine even with Home Network debug on
NIL_THREAD(HomeNetworkThread, arg)
{
  Serial.println(F("Started HomeNetworkThread"));
  // The thread stops at this function, this function has a loop which keeps the network
  // auto updated and executes 'homeNetworkMessageReceived()' when a message is received
  // This function has to run on a thread or else home network wont work.
  homeNetwork.update();
}
