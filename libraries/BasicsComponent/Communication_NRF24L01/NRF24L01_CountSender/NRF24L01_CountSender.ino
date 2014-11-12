/*
this is the most basic sketch I can think of to transmit data from an nrf24l01.
 It loops over the numbers 0-1023 continuously and sends each number to the receiving 
 unit.  I have used this pattern as a test to check for drops in the signal by 
 checking the receiving end for gaps between numbers.  It's not sophisticated,
 but it seems to work.
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
  radio.openWritingPipe(pipe); // Set as sender
}

/**
 *  Loop
 */
void loop(void){
  for (int x=0;x<1023;x++){
    msg = x;
    radio.write(&msg, sizeof(unsigned int));
  }
}



