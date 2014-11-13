/*
 Client program of a star network potology. In the loop there are two example programs,
 one is the receive program which demonstrates how to use this Sketch to receive messages from
 other clients, the other example program is how to send a message to another client.
 The send example program should only be ran once, to send a message, and the receive program
 should keep looping, thats why the send example program is commented out, or else this
 program would keep sending messages with a delay and the receive program would not function.
 VERY IMPORTANT! Dont forget to set the clientID variable to a unique between different clients! 
 
 By: Prince Balabis
 */

// includes
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//
// config
//
RF24 radio(9,10);
const unsigned int clientID = 1; // This is the client ID, must be unique & between 0-5!
const unsigned int timeoutTime = 2000;

//
// Topology
//
// Radio pipe addresses for the nodes to communicate.  Only ping nodes need
// dedicated pipes in this topology.  Each ping node has a talking pipe
// that it will ping into, and a listening pipe that it will listen for
// the pong.  The pong node listens on all the ping node talking pipes
// and sends the pong back on the sending node's specific listening pipe.
const uint64_t talking_pipes[5] = { 
  0xF0F0F0F0D2LL, 0xF0F0F0F0C3LL, 0xF0F0F0F0B4LL, 0xF0F0F0F0A5LL, 0xF0F0F0F096LL };
const uint64_t listening_pipes[5] = { 
  0x3A3A3A3AD2LL, 0x3A3A3A3AC3LL, 0x3A3A3A3AB4LL, 0x3A3A3A3AA5LL, 0x3A3A3A3A96LL };

// logic variables
unsigned int msgSent, msgClient;

/**
 *  Setup
 */
void setup(void){

  Serial.begin(57600);

  radio.begin(); // Initialize radio
  radio.setRetries(5,15); // Set delay between retries & # of retires for a "radio.write" command
  radio.openWritingPipe(talking_pipes[clientID]);
  radio.openReadingPipe(1,listening_pipes[clientID]);

  radio.startListening(); // Start listening for incoming messages
}

/**
 *  Loop
 */
void loop(void){

  /**
   * -------------------Example receive-Program Area-------------------
   * Demonstration of how to receive a message from another client
   */
//  unsigned int msgReceived;
//  msgReceived = readMessage();
//
//    // Put code in this if-statement which should occur when a message is received
//  if(msgReceived != 0){
//    Serial.print("MESSAGE:");
//    Serial.println(msgReceived);
//  }
  /**
   * -------------------Example receive-Program Area-------------------
   * Demonstration of how to send a message to another client
   */

  /**
   * -------------------Example send-Program Area-------------------
   * Demonstration of how to send a message to another client
   * This demonstration is not compatible to run together with the receive program.
   * Read header comments for more.
   */
   delay(2000); // Delay so we don't flood the network
    msgSent = 15; // random message to send to receiver
    msgClient = 0; // Client ID to send a message to
    Serial.println("EXAMPLE MESSAGE SEND PROGRAM");
    Serial.print("ClientID OF RECEIVER: ");
    Serial.println(msgClient);
    Serial.print("MESSAGE CONTENT: ");
    Serial.println(msgSent);
  
  
    // Send message to server, keep trying untill server confirms receiver gets the message
    Serial.println("SENDING MESSAGE TO SERVER");
    if(sendMessage(msgClient, msgSent))
      Serial.println("SERVER CONFIRMS RECEIVER RECEIVED MESSAGE");
    else
      Serial.println("ERROR!: Failed to send message to server, retrying...");
  
    Serial.println(); //Extra row for easier serial reading
  /**
   * -------------------Example send-Program Area-------------------
   */
}

unsigned int sendMessage(unsigned int msgClientTo, unsigned int msgSent){
  unsigned int msgPack;
  msgPack = (msgSent*10) + msgClient; // Pack receiver of message and message together

  // Stop listening so we can talk.
  radio.stopListening();

  // Sends response message, will keep trying to 
  //send message until an ack is returned from sender or timeout
  // Open the correct pipe for writing
  radio.openWritingPipe(talking_pipes[clientID]);
  unsigned long started_waiting_at = millis();
  bool timeout = false;
  bool ack = false;
  while (!ack && !timeout){
    ack = radio.write(&msgPack, sizeof(unsigned int)); // Send back received value
    if (millis() - started_waiting_at > timeoutTime ){
      timeout = true;
      radio.startListening(); // Start listening for response from sender again
      return 0;
    }  
    else if(ack){
      radio.startListening(); // Start listening for response from sender again
      return waitConfirmMessage();
    }
  }
}


unsigned int waitConfirmMessage(){
  unsigned int msgReceived;
  radio.startListening(); // Start listening for response from receiver
  unsigned long started_waiting_at = millis();
  bool timeout = false;
  // Wait here until we get a response, or timeout //(4000 second)
  while ( !radio.available() && !timeout ){
    if (millis() - started_waiting_at > timeoutTime ){
      timeout = true;
      return 0;
    }
  }
  if(!timeout) {
    radio.read(&msgReceived, sizeof(unsigned int)); // Read message and store to msgReceived variable
    return msgReceived;
  }
}

/**
 *  readMessage
 *  This function reads the message and returns it
 */
unsigned int readMessage(){
  //  radio.startListening(); 
  if (radio.available()){
    bool ack = false;
    unsigned int msgReceived;
    while(!ack)
      ack = radio.read(&msgReceived, sizeof(unsigned int)); // Read message and store to msgPackReceived variable
    return msgReceived;
  }
}
