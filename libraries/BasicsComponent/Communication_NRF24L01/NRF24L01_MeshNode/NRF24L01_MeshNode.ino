
/*
 Node program of a mesh network potology. In the loop there are two example programs,
 one is the receive program which demonstrates how to use this Sketch to receive messages from
 other nodes, the other example program is how to send a message to another node.
 The send example program should only be ran once, to send a message, and the receive program
 should keep looping, thats why the send example program is commented out, or else this
 program would keep sending messages with a delay and the receive program would not function.
 VERY IMPORTANT! Dont forget to set the nodeID variable to a unique between different nodes! 
 
 DEMO: As a demo of this Sketch you can set this node as a receiver or sender,
 then the preferred commands will run in loop(). Check config.h file
 
 More info:
 This Sketch has several send-verifications and drift securing tweaks.
 For instance:
 - When the initial send command runs, it retries untill an ack is returned
 - When sending a message, the sender node ID is sent together with the message as a pack
 - A lot of other stuff
 
 WARNING! DONT FORGET TO SET UNIQUE NODE ID IN config.h FOR EACH NODE!
 
 By: Prince Balabis
 */

// includes
#include <Wire.h>
#include "config.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(8,9); 

//
// Topology
//
const uint64_t talking_pipes[5] = { 
  0xF0F0F0F0D2LL, 0xF0F0F0F0C3LL, 0xF0F0F0F0B4LL, 0xF0F0F0F0A5LL, 0xF0F0F0F096LL };
const uint64_t listening_pipes[5] = { 
  0x3A3A3A3AD2LL, 0x3A3A3A3AC3LL, 0x3A3A3A3AB4LL, 0x3A3A3A3AA5LL, 0x3A3A3A3A96LL };

/**
 *  Setup
 */
void setup(void){

  Serial.begin(57600);

  radio.begin(); // Initialize radio
  radio.setRetries(5,15); // Set delay between retries & # of retires for a "radio.write" command
  radio.enableAckPayload(); // Must have Ack enables for this sketch
  radio.openReadingPipe(1,listening_pipes[nodeID]);
  radio.setPayloadSize(2);  // Set payload size to 1 bytes for sending int-values between 0-255

  radio.startListening(); // Start listening for incoming messages

  if(!isSender)
    Serial.println("SET AS EXAMPLE RECEIVER");
}

/**
 *  Loop
 */
void loop(void){
  if(!isSender){
    /**
     * -------------------Example receive-Program Area-------------------
     * Demonstration of how to receive a message from another node
     */
    int msgSender, msgReceived;
    readMessage(&msgSender, &msgReceived);

    // Put code in this if-statement which should occur when a message is received
    if(msgReceived != -1){
      Serial.print("Node "); // Print message
      Serial.print(msgSender); // Print message
      Serial.print(": "); // Print message
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
    delay(senderLoopDelay); // Delay so we don't flood the network
    Serial.println("EXAMPLE MESSAGE SEND PROGRAM");
    Serial.print("nodeID OF RECEIVER: ");
    Serial.println(msgNode);
    Serial.print("MESSAGE CONTENT: ");
    Serial.println(msgContent);


    // Send message to server, keep trying untill server confirms receiver gets the message
    Serial.println("SENDING MESSAGE TO NODE...");
    unsigned int msgSent = 0;
    unsigned long started_waiting_at = millis();
    unsigned int timeoutTime = 200; // Amount of time to give trying to resend message to nodes
    bool timeout = false;
    bool sendDone = false;

    // Will try to keep send message untill receiver gets it
    while(!msgSent && !timeout){
      msgSent = sendMessage(msgNode, msgContent);
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
        delay(20);
      }
    }
    msgContent++;

    Serial.println(); //Extra row for easier serial reading
    /**
     * -------------------Example send-Program Area-------------------
     */
  }
}

unsigned int sendMessage(unsigned int msgReceiver, unsigned int msgContent){
  unsigned int msgPack;
  msgPack = (msgContent*10) + nodeID; // Pack receiver of message and message together

  // Stop listening so we can talk.
  radio.stopListening();

  // Sends response message, will keep trying to 
  //send message until an ack is returned from sender or timeout
  // Open the correct pipe for writing
  radio.openWritingPipe(listening_pipes[msgReceiver]);
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
      Serial.println("ACK WAITING TIMED OUT!");
      return 0;
    }
  }
}

/**
 *  readMessage
 *  This function reads the message and returns it
 */
void readMessage(int *pmsgSender, int *pmsgReceived){
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
    *pmsgSender = -1;
    *pmsgReceived = -1;
  }
}





























