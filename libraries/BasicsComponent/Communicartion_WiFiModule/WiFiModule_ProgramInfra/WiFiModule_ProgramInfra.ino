// Digital pin 2 is RX(TX on other device)
// Digital pin 3 is TX(RX on other device)

Const String aPSSID = "Router";
Const String aPPass = "kungarike";
Const int encryption = 7; // WPA2-PSK [AES]
#include <SoftwareSerial.h>

SoftwareSerial wiFiSerial(2, 3); //RX, TX

void setup() {
  wiFiSerial.begin(115200);
  Serial.begin(115200);

  delay(6000); // Let Wi-Fi module initialize

  sendCommand("+++");
  sendCommand("AT+");
  sendCommand("AT+SSID=!" + aPSSID);
  sendCommand("AT+ENCRY=!"+encryption);
  sendCommand("AT+KEY=!1,0," + aPPass);
  sendCommand("AT+NIP=!0");
  sendCommand("AT+WBGR=!0,11");
  sendCommand("AT+Z");

  delay(2000);
  wiFiSerial.begin(115200);
  sendCommand("AT+LKSTT");
}

void sendCommand(String command) {
  wiFiSerial.println(command); // Write command to WiFi-Module
  while (!wiFiSerial.available()); // Wait here for response from WiFi-module
  Serial.println(wiFiSerial.read()); // Print out response
}

void loop()
{
  while (1); // End program
}

