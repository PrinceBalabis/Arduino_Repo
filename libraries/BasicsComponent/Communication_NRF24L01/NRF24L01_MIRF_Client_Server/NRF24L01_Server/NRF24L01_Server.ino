/**
 * Pins:
 * Hardware SPI:
 * MISO -> 12
 * MOSI -> 11
 * SCK -> 13
 *
 * Configurable:
 * CE -> 8
 * CSN -> 7
 */

#include "SPI.h"
#include "Mirf.h"
#include "nRF24L01.h"
#include "MirfHardwareSpiDriver.h"

String message;

void setup(){
  Serial.begin(9600);
  /*
   * Setup pins / SPI.
   */
   
  /* To change CE / CSN Pins:
   * 
   * Mirf.csnPin = 9;
   * Mirf.cePin = 7;
   */
  
  Mirf.cePin = 8;
  Mirf.csnPin = 9;
  
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  
  /*
   * Configure reciving address.
   */
   
  Mirf.setRADDR((byte *)"serv1");
  
  /*
   * Set the payload length to sizeof(unsigned long) the
   * return type of millis().
   *
   * NB: payload on client and server must be the same.
   */
   
  Mirf.payload = 1;
  
  /*
   * Write channel and payload config then power up reciver.
   */
   
  Mirf.config();
         Serial.println("Started");

}

void loop(){
   byte c; 
   
  // is there any data pending? 
  if(Mirf.dataReady())
  {
     // well, get it
     Mirf.getData(&c);

    // ... and write it out to the PC
     char letter = char(c);
     if(letter != '~')
     {
       message = String(message + letter);
     }
     
     else 
     {
       Serial.println(message);
       message = "";
     }
  }
} 
