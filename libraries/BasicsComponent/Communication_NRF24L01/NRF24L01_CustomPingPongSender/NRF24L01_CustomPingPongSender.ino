/*
Send a single message, keeps trying to send message until received an acknowledge from receiver.
 After sending the message, a response message from the receiver is awaited.
 
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
  radio.openWritingPipe(pipes[0]); // Pipe for sending as sender
  radio.openReadingPipe(1,pipes[1]); // Pipe for receiving as sender

  msgSent = 501; // random message to send to receiver
  msgReceived = 0; // Inital variable value

  // Start listening for response from receiver, must be run here before "for loop" BECAUSE OF BUG!
  radio.startListening(); 
}

/**
 *  Loop
 */
void loop(void){
  Serial.println("START sender-procedure");

  // Stop listening so we can talk,must be run here BECAUSE OF BUG!
  radio.stopListening();

  Serial.println("Trying to send message to receiver");
  bool ack = false;
  // Sends message, will keep trying to send message until an ack is returned from receiver
  while(!ack)
    ack = radio.write(&msgSent, sizeof(unsigned int)); 
  Serial.println("Message sent, acknowledge is received!");

  Serial.println("Wait for response message from receiver");
  radio.startListening(); // Start listening for response from receiver
  unsigned long started_waiting_at = millis();
  bool timeout = false;
  // Wait here until we get a response, or timeout (4000 second)
  while ( !radio.available() && !timeout ){
    if (millis() - started_waiting_at > timeoutTime ){
      timeout = true;
      Serial.println("No responce from receiver, timed out!");
    }
  }
  if(!timeout) {
    radio.read(&msgReceived, sizeof(unsigned int)); // Read message and store to msgReceived variable
    Serial.print("Message received: "); // Print message
    Serial.println(msgReceived); // Print message
    msgReceived = 0; // Reset received message
  }
  Serial.println("DONE sender-procedure");
  Serial.println();

  delay(2000); // Delay for each procedure
}










