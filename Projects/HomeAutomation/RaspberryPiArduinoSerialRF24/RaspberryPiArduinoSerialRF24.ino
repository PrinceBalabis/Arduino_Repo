
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

RF24 radio(8,9); 
RF24Network network(radio);

/**
 *  Setup
 */
void setup(void){

  Serial.begin(115200);

  SPI.begin();
  radio.begin(); // Initialize radio
  network.begin(/*channel*/ 90, nodeID);

  initTweaks(); // Run RF24 tweaks
}

/**
 *  Loop
 */
void loop(void){
  network.update();                          // Check the network regularly

  if (Serial.available())  
  {
    int temp = Serial.parseInt();
    int32_t msgContent = temp % 100;
    const uint16_t msgNode = temp / 100;

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
      } 
      else if (millis() - started_waiting_at > timeoutTime ){
        timeout = true;
      }
      else if(!msgSent){
      }
    }
  }
  delay(1);
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

