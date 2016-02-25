/**
   Central Node is the node which must be run to succesfully have HomeNetwork Automation Online
*/

#include <SPI.h>
#include <RF24.h>
#include <RF24Network.h>

RF24 radio(8, 9);
RF24Network network(radio);

void setup() {
  delay(4000); //Give some time for capacitor to charge up and stabilize before initializing RF24 module!
  SPI.begin(); // SPI is used by homeNetwork
  delay(500);
  radio.begin(); // Initialize radio
  delay(100);
  network.begin(90, 00); // Start mesh Network
  delay(500);
  radio.setPALevel(RF24_PA_MAX);
  delay(100);
  radio.setDataRate(RF24_2MBPS);
  delay(100);
  network.txTimeout = 0; // Set to 0 to use the normal auto retry period defined by radio.setRetries()
  delay(100);
  radio.setRetries(0, 0);
  delay(500);
}

void loop() {
  network.update();
  delay(1);
}
