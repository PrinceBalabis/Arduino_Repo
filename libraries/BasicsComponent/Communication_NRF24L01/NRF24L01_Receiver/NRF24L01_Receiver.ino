/*
 the nrf24l01 will listen for numbers 0-1023.
 This sketch works with both NRF24L01_CountSender and NRF24L01_SingleMessageSender
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

/**
 *  Setup
 */
void setup(void){

  Serial.begin(9600);

  radio.begin(); // Initialize radio
  radio.openReadingPipe(1, pipe); // Set as receiver
  radio.startListening(); // Start listening as receiver
}

/**
 *  Loop
 */
void loop(void){

  if (radio.available()){
    radio.read(&msg, sizeof(unsigned int)); // Read message and store to msg variable
    Serial.println(msg); // Print message
  }
  else {
    // idle waiting receive
  }
}




