/*
  ---------------------------------------------------------------

  Server port: 6548

  MAJOR BUG:
  If it cannot connect to the Wi-Fi hotspot, try reconnecting the power/USB cable to reset the ESP

  Put a large capacitor(or even better, several small ones) between 5V/VIN and Ground to improve reliability

  Remember to install the CH340G drivers.

  Board Uploading settings:
  -NodeMCU 1.0(ESP-12E)
  -80MHz
  -921600
  -4M(3M)

  -There is noise on the ADC when receiving/transmitting on Wi-Fi
  while using the ADC! Try to use one function at a time to minimize ADC noise

  -Sometimes it won't be able to connect to Wi-Fi after uploading new
  code, try pressing the RESET switch on the ESP8266, this should reset the Wi-Fi module.
  If it didn't work, try disconnecting then reconnecting the power/USB-cable.
  ---------------------------------------------------------------
*/

/*
  ---------------------------------------------------------------
  Library includes
  ---------------------------------------------------------------
*/
//Needed for Scheduler
#include <Arduino.h>
#include <Scheduler.h>
//Needed for HTTP GET Webclient
#include <ESP8266WiFi.h>
//Needed for 433MHz transmitter
#include <NewRemoteTransmitter.h>


/*
  ---------------------------------------------------------------
  Needed here to compile.
  Always keep these "function prototypes" on the bottom of this tab, or else the code might not compile.
  ---------------------------------------------------------------
*/
void setup();
void loop();
void pauseInterrupts();
void unpauseInterrupts();

//void leftWallSwitchInterruptWrap();
//void rightWallSwitchInterruptWrap();



