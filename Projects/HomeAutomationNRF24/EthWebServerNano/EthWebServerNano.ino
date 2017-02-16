/*
   Web Server

   Circuit:
   Ethernet shield attached to pins 10, 11, 12, 13

   Toggle Main Lights(Normal command with node and command as "node-command" format)
   http://192.168.1.16:9500/?2-3


   Toggle Apartment Mood(Macro command with node and command as "0-command" format)
   http://192.168.1.16:9500/?0-5

*/

#include <SPI.h>
#include <UIPEthernet.h>
#include "config.h"
#include <Wire.h>

String node1;
String node2;
String command1;
String command2;

String tempS;

uint8_t mac[6] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(SERVER_IP);
EthernetServer server(SERVER_PORT);

bool requestType = 0; // 0=GET Request, 1=POST Request
boolean reading = false;

void setup() {
  Serial.begin(115200);
  Serial.println(F("Webserver"));

  // Start I²C bus as master
  Wire.begin();

  Serial.println(F("Basic system booted up! Starting loop..."));

  delay(SERVER_BOOT_TIME);
  Serial.println(F("Webserver Thread started"));

  // Start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  Serial.print(F("BEGIN"));

  //delay(1000); // give the Ethernet shield a second to initialize:
  //server.begin();
  //delay(1000); // give the Ethernet shield a second to initialize:
  //Serial.print(F("Server IP: "));
  / Serial.println(Ethernet.localIP());
  //Serial.println(F("Webserver is listening"));
  delay(BOOT_TIME); // Boot system first

}

void loop() {
  checkTWI();
  updateServer();
}
