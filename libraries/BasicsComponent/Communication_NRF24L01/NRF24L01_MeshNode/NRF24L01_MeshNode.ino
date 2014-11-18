
/*
 WARNING! DONT FORGET TO SET UNIQUE NODE ID IN config.h FOR EACH NODE!
 
 By: Prince Balabis
 */

// includes
#include <Wire.h>
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include "config.h"

RF24 radio(9,10); 
RF24Network network(radio);

unsigned long last_sent;  // When did we last send?

/**
 *  Setup
 */
void setup(void){

  Serial.begin(57600);

  SPI.begin();
  radio.begin(); // Initialize radio
  network.begin(/*channel*/ 90, nodeID);

  initTweaks(); // Run RF24 tweaks

    if(!isSender)
    Serial.println("SET AS EXAMPLE RECEIVER");
}

/**
 *  Loop
 */
void loop(void){
  network.update();                          // Check the network regularly

  if(!isSender){
    /**
     * -------------------Example receive-Program Area-------------------
     * Demonstration of how to receive a message from another node
     */
    int32_t msgReceived;
    readMessage(&msgReceived);

    // Put code in this if-statement which should occur when a message is received
    if(msgReceived != -1){
      Serial.print("MESSAGE: "); // Print message
      Serial.println(msgReceived); // Print message
    }
    /**
     * -------------------Example receive-Program Area-------------------
     * 
     */
  } 
  else if(isSender){
    /**
     * -------------------Example send-Program Area-------------------
     * Demonstration of how to send a message to another node
     * This demonstration is not compatible to run together with the receive program.
     * Read header comments for more.
     */
    unsigned long now = millis();              // If it's time to send a message, send it!
    if ( now - last_sent >= interval  ) {
      Serial.println("EXAMPLE MESSAGE SEND PROGRAM");
      Serial.print("nodeID OF RECEIVER: ");
      Serial.println(msgNode);
      Serial.print("MESSAGE CONTENT: ");
      Serial.println(msgContent);

      last_sent = now;

      // Send message to server, keep trying untill server confirms receiver gets the message
      Serial.println("SENDING MESSAGE TO PARENT...");
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
          Serial.println("PARENT PICKED UP MESSAGE");
        } 
        else if (millis() - started_waiting_at > timeoutTime ){
          timeout = true;
        }
        else if(!msgSent){
          Serial.println("ERROR!: Failed to send message to parent. retrying...");
          delay(20);
        }
        Serial.println(); //Extra row for easier serial reading
      }
    }
    /**
     * -------------------Example send-Program Area-------------------
     */

  }
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

