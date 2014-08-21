// Digital pin 2 is RX(TX on other device)
// Digital pin 3 is TX(RX on other device)


String aPSSID = "TeliaGatewayA4-B1-E9-98-CB-2A";
String aPPass = "EBA9759C61";
int encryption = 3;
#include <SoftwareSerial.h>

SoftwareSerial wiFiSerial(2, 3); //RX, TX

void setup() {
  wiFiSerial.begin(115200);
  Serial.begin(115200);

  delay(6000); // Let Wi-Fi module initialize

  sendCommandReceiveAnswer("+++");
  sendCommandReceiveAnswer("AT+");
  sendCommandReceiveAnswer("AT+SSID=!" + aPSSID);
  sendCommandReceiveAnswer("AT+ENCRY=!"+encryption);
  sendCommandReceiveAnswer("AT+KEY=!1,0," + aPPass);
  sendCommandReceiveAnswer("AT+NIP=!0");
  sendCommandReceiveAnswer("AT+WBGR=!0,11");
  sendCommandReceiveAnswer("AT+Z");

  delay(2000);
  wiFiSerial.begin(115200);
  sendCommandReceiveAnswer("AT+LKSTT");
}

void sendCommandReceiveAnswer(String command) {
  wiFiSerial.println(command);
  if (wiFiSerial.available()) {
    Serial.println(wiFiSerial.read());
  }
}

void loop()
{
  while (1) {
    // End program
  }
}
