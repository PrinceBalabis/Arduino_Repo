/**
 *  Thread2
 *  Idles until a message is received from a client.
 **/
static msg_t Thread2(void *arg) {
  Serial.println(F("\n\n--------------------------------------------------------------- \nExample SERVER for Prince Home Network"));
  
  chThdSleepMilliseconds(2100); // Give some time for HomeNetwork thread to start

  while (1) {
    // Wait for message to receive
    Serial.println(F("-------------STARTING: Server Program----------------- \nIdle and waiting for client"));

    while (msgReceived == 0) {
      chThdSleepMilliseconds(20); // Check every few ms if a message is received
    }
    chThdSleepMilliseconds(500); // Check every few ms if a message is received
    if (msgContent == cmdExampleCommand) {
      // Send return-message back to client
      uint8_t msgSent = homeNetwork.write(msgSender, cmdExampleResponceData, msgTypeResponse);
      Serial.print("Client has a question \nSending response back: ");
      Serial.println(cmdExampleResponceData);

      if (msgSent) {
        Serial.println(F("Message sent"));
      } else if (!msgSent) {
        Serial.println(F("ERROR!: Failed to send message to parent."));
      } else if (msgSent == 2) {
        Serial.println(F("OBS! FINALLY SENT MESSAGE AFTER SEVERAL RETRIES. BAD SIGNAL WITH PARENT!"));
      }
    }

    Serial.println(F("---------------DONE: Server Program-------------------\n"));

    msgReceived = 0;
    chThdSleepMilliseconds(100); // Redo this send program every 200 ms
  }

  return 0;
}

/**
 * homeNetworkMessageReceived()
 * This function is executed automatically by the HomeNetwork Library when a message is received.
 */
void homeNetworkMessageReceived(int16_t _msgSender, unsigned char _msgType, int32_t _msgReceived) {
  // Save received data to global variables to be used by other threads
  msgSender = _msgSender;
  msgType = _msgType;
  msgContent = _msgReceived;
  msgReceived = 1;

  Serial.print(F("-------------Received Data Raw----------------- \nRaw Message sender: "));
  Serial.println(_msgSender);
  Serial.print(F("Raw Type content: "));
  Serial.write(_msgType);
  Serial.print(F("\nRaw Message content: "));
  Serial.println(_msgReceived);
  Serial.println(F("-----------------------------------------------"));
}

