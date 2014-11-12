/*
Send a single message, keeps trying to send message until received an acknowledge from receiver
 */

// includes
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

// config
const uint64_t pipe = 0xE8E8F0F0E1LL;
RF24 radio(9,10);

// logic variables
unsigned int msg;
bool ack = false;

/**
 *  Setup
 */
void setup(void){

  Serial.begin(9600);

  radio.begin(); // Initialize radio
  radio.openWritingPipe(pipe); //Set as sender
  radio.setRetries(5,15); // Set delay between retries & # of retires for a "radio.write" command

  msg = 599; // random message to send to receiver, not important in this sketch
}

/**
 *  Loop
 */
void loop(void){
  ack = false;

  // Sends message, will keep trying to send message until an ack is returned from receiver
  while(!ack)
    ack = radio.write(&msg, sizeof(unsigned int)); 

  Serial.println("Message sent, acknowledge is received!");

  delay(3000); // Delay for each procedure
}










