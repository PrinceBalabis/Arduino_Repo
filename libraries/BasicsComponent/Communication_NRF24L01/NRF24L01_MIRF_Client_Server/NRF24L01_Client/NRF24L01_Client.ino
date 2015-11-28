/**

   Pins:
   Hardware SPI:
   MISO -> 12
   MOSI -> 11
   SCK -> 13

   Configurable:
   CE -> 8
   CSN -> 7
*/

#include "SPI.h"
#include "Mirf.h"
#include "nRF24L01.h"
#include "MirfHardwareSpiDriver.h"

// converts a float into a char
// and sends it via nRF24L01
void transmit( float v)
{
  byte c;
  char buf[10];

  dtostrf(v, 9, 3, buf);

  for ( int i = 0 ; i < 8 ; i++ )
  {
    c = buf[i];
    Mirf.send(&c);
    while ( Mirf.isSending() ) ;
  }
}

// sends a string via the nRF24L01
void transmit(const char *string)
{
  byte c;

  for ( int i = 0 ; string[i] != 0x00 ; i++ )
  {
    c = string[i];
    Mirf.send(&c);
    while ( Mirf.isSending() ) ;
  }
}

// send a CR/LF sequence via the nRF24L01
void transmitlf(void)
{
  byte c;

  c = '\r';
  Mirf.send(&c);
  while ( Mirf.isSending() ) ;

  c = '\n';
  Mirf.send(&c);
  while ( Mirf.isSending() ) ;
}

void setup()
{
  Serial.begin(9600);
  /*
     Setup pins / SPI.
  */

  /* To change CE / CSN Pins:

     Mirf.csnPin = 9;
     Mirf.cePin = 7;
  */

  Mirf.cePin = 8;
  Mirf.csnPin = 7;

  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();

  /*
     Configure reciving address.
  */

  Mirf.setRADDR((byte *)"serv1");

  /*
     Set the payload length to sizeof(unsigned long) the
     return type of millis().

     NB: payload on client and server must be the same.
  */

  Mirf.payload = 1;

  /*
     Write channel and payload config then power up reciver.
  */


  Mirf.config();
  Serial.println("Started");

               }

                 void loop()
                 {

                 transmit("Hello World!~");


                 // ... just take your time
                 delay(1000);
               }
