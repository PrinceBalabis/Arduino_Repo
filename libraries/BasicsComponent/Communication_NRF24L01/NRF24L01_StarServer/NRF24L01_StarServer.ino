/*
 
 By: Prince Balabis
 */

// includes
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//
// --------------------------------Configuration & Tweaks Area--------------------------------------
//

// Hardware pins for SPI
RF24 radio(9,10);

// Timeout for waiting answers, tweak yourself!
const unsigned int timeoutTime = 2000; 

const unsigned int retryDelay = 5; //Tweak yourself!
const unsigned int retryTimes = 15; //Tweak yourself!

//
// --------------------------------Configuration & Tweaks Area--------------------------------------
//


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

/**
 *  Setup
 */
void setup(void){

  Serial.begin(57600);

  radio.begin(); // Initialize radio
  radio.setRetries(retryDelay, retryTimes); // Set delay between retries & # of retires for a "radio.write" command

  // The pong node listens on all the ping node talking pipes
  // and sends the pong back on the sending node's specific listening pipe.
  radio.openReadingPipe(1,talking_pipes[0]);
  radio.openReadingPipe(2,talking_pipes[1]);
  radio.openReadingPipe(3,talking_pipes[2]);
  radio.openReadingPipe(4,talking_pipes[3]);
  radio.openReadingPipe(5,talking_pipes[4]);

  radio.startListening(); // Start listening as server
  Serial.println("STARTED SERVER PROGRAM");
  Serial.println(); //Extra row for easier serial reading
}

/**
 *  Loop
 */
void loop(void){

  uint8_t pipe_num;
  if (radio.available(&pipe_num)){

    unsigned int senderClientID = pipe_num-1;
    Serial.print("SENDER CONNECTED: Client ID ");
    Serial.println(senderClientID);

    // Reads the message
    unsigned int msgPackReceived = readMessage(); 

    // Run function to send the message to its receiver
    unsigned int sendSuccess;
    sendSuccess = relayMessage(msgPackReceived); 

    // Send confirmation to sender if message is received
    sendConfirmMessage(senderClientID, sendSuccess);

    Serial.println(); //Extra row for easier serial reading
  }
  else {
    // idle waiting receive
  }
}

/**
 *  readMessage
 *  This function reads the message pack and returns it back
 */
unsigned int readMessage(){
  bool ack = false;
  unsigned int msgPackReceived;
  while(!ack)
    ack = radio.read(&msgPackReceived, sizeof(unsigned int)); // Read message and store to msgPackReceived variable
  Serial.println("MESSAGE PACK RECEIVED"); // Print message
  return msgPackReceived;
}

/**
 *  sendMessage
 *  This function unpacks the message pack to get the clientID of the receiver, 
 *  and sends the message to the receiver
 */
unsigned int relayMessage(unsigned int msgPackReceived){

  // Extract the message pack, to know the client and message
  unsigned int msgClientTo, msgSent;
  msgClientTo = msgPackReceived % 10;
  msgSent = (msgPackReceived % 1000) /10;
  Serial.print("MESSAGE RECEIVER: Client ID "); // Print message
  Serial.println(msgClientTo); // Print message
  Serial.print("MESSAGE CONTENT: "); // Print message
  Serial.println(msgSent); // Print message

  // Relay message to receiver
  Serial.println("RELAYING MESSAGE TO RECEIVER");
  return sendMessage(msgClientTo, msgSent);
}

void sendConfirmMessage(unsigned int senderID, unsigned int confirmation){
  if(sendMessage (senderID, confirmation))
    Serial.println("RECEIVER CONFIRMS MESSAGE RECEIVED");
  else 
    Serial.println("ERROR!: No response from the connected client, timed out!");

}

unsigned int sendMessage(unsigned int msgClientTo, unsigned int msgSent){
  // Stop listening so we can talk.
  radio.stopListening();

  // Sends response message, will keep trying to 
  //send message until an ack is returned from sender or timeout
  // Open the correct pipe for writing
  radio.openWritingPipe(listening_pipes[msgClientTo]);
  unsigned long started_waiting_at = millis();
  bool timeout = false;
  bool ack = false;
  while (!ack && !timeout){
    ack = radio.write(&msgSent, sizeof(unsigned int)); // Send back received value
    if (millis() - started_waiting_at > timeoutTime ){
      timeout = true;
      radio.startListening(); // Start listening for response from senders again
      return 0;
    }  
    else if(ack){
      radio.startListening(); // Start listening for response from senders again
      return 1;
    }
  }
}
