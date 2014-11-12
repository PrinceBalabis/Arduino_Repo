/*
Keeps listening for messages from senders. When a message is received a response message is sent back
 
 By: Prince Balabis
 */

// includes
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// config
RF24 radio(9,10);
const uint64_t pipes[2] = { 
  0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL }; // Two pipes needed for two-way communication
const unsigned int timeoutTime = 2000;

// logic variables
unsigned int msgSent, msgReceived;

/**
 *  Setup
 */
void setup(void){

  Serial.begin(57600);

  radio.begin(); // Initialize radio
  radio.setRetries(15,15); // Set delay between retries & # of retires for a "radio.write" command
  radio.openWritingPipe(pipes[1]); // Pipe for sending as sender
  radio.openReadingPipe(1,pipes[0]); // Pipe for receiving as sender

  msgSent = 600; // random message to send to sender as a responce
  msgReceived = 0; // Inital variable value

  radio.startListening(); // Start listening as receiver
  Serial.println("Start receiver-listening-procedure");
}

/**
 *  Loop
 */
void loop(void){

  if (radio.available()){
    Serial.println("START receiver-procedure");
    bool ack = false;
    while(!ack)
      ack = radio.read(&msgReceived, sizeof(unsigned int)); // Read message and store to msgReceived variable
    Serial.print("Sender went online, message received: "); // Print message
    Serial.println(msgReceived); // Print message
    msgReceived = 0; // Reset received message

    // Delay just a little bit to let the other unit
    // make the transition to receiver
    delay(60);

    //    // Stop listening so we can talk.
    radio.stopListening();


    // Sends response message, will keep trying to send message until an ack is returned from sender
    // or timeout
    Serial.println("Sending response message to sender");
    unsigned long started_waiting_at = millis();
    bool timeout = false;
    ack = false;
    while (!ack && !timeout){
      ack = radio.write(&msgSent, sizeof(unsigned int)); 
      if (millis() - started_waiting_at > timeoutTime ){
        timeout = true;
        Serial.println("No responce from receiver, timed out!");
      }  
      else if(ack){
        Serial.println("Message sent, acknowledge is received!");
      }
    }
    radio.startListening(); // Start listening for response from sender again
    Serial.println("DONE receiver-procedure");
    Serial.println();
  }
  else {
    // idle waiting receive
  }
}






