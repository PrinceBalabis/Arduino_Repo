#include <SoftwareSerial.h>

/*
 *
 * Before running this sketch you must configure to run at 38400 baud
 * Set to 38400 baud
 *    AT+CIOBAUD=38400
 * Restart to save settings
 *    AT+RST
 *
 * Make sure the ESP-05 has at least 200-300 mA!!!! (by using separate power supply)
 * Runs at 3.3V
 *
 * If there is still no answer from ESP-05, unplug and replug the ESP-05 onto the breadboard to fully reset it
 */

SoftwareSerial mySerial(2, 3);

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting ESP-05 Webserver Programming sketch");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(38400);

  delay(5000);
  Serial.println("Reset module");
  sendCommand("AT+RST", 5000); // Reset module
  Serial.println("Set WiFi Mode to only STA");
  sendCommand("AT+CWMODE=1", 5000); // Set WiFi Mode to only STA
  Serial.println("Set WiFi Mode to only STA");
  sendCommand("AT+CWJAP=\"Router24G\",\"kungarike\"", 5000); // Set WiFi Mode to only STA
  Serial.println("Enable watchdog, this restarts the module when an error occured");
  sendCommand("AT+CSYSWDTENABLE", 5000); // Enable watchdog, this restarts the module when an error occured
  Serial.println("Print IP address");
  sendCommand("AT+CIFSR", 3000); // Print ip address
  Serial.println("Configure for multiple connections");
  sendCommand("AT+CIPMUX=1", 3000); // configure for multiple connections
  Serial.println("Turn on server on port 9500");
  sendCommand("AT+CIPSERVER=1,9500", 3000); // turn on server on port 9500
  Serial.println("Set server timeout to some seconds, clients stop waiting for response after some seconds");
  sendCommand("AT+CIPSTO=1", 3000); // Set server timeout to some seconds, clients stop waiting for response after some seconds

  Serial.println("Done programming ESP-05, this script is done!");
}

void sendCommand(String cmdString, const int timeout) {
  char cmdCharArray[32];
  cmdString.toCharArray(cmdCharArray, 32);
  mySerial.println(cmdCharArray); // Send to ESP-05

  unsigned long startTime = millis();

  while ((startTime + timeout) > millis()) {
    if (mySerial.available()) // input from the esp8266
      Serial.write(mySerial.read()); // write to host
  }
}

void loop()
{
  while (1); // Program done
}
