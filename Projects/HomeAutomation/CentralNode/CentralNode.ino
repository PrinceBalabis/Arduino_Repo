/**
   Central Node is the node which must be run to succesfully have HomeNetwork Automation Online
*/

#include <SPI.h>
#include <RF24.h>
#include <RF24Network.h>

RF24 radio(8,9);
RF24Network network(radio);

void setup() {
  SPI.begin(); // SPI is used by homeNetwork
  delay(2000); //Give some time for capacitor to charge up and stabilize before initializing RF24 module!
  radio.begin(); // Initialize radio
  network.begin(90, 00); // Start mesh Network
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_2MBPS);
  network.txTimeout = 0; // Set to 0 to use the normal auto retry period defined by radio.setRetries()
  radio.setRetries(15, 15);

}

void loop() {
  network.update();
}
