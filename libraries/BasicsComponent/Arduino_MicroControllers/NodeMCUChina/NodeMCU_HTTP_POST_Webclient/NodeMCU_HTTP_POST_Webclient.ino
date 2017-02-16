/* Simple HTTP get webclient test

  MAJOR BUG:
  If it cannot connect to the Wi-Fi hotspot, try reconnecting the power/USB cable to reset the ESP

  Remember to install the CH340G drivers.

  Board settings:
  -NodeMCU 1.0(ESP-12E)
  -80MHz
  -921600
  -4M(3M)
*/

#include <ESP8266WiFi.h>

const char* ssid     = "Router";
const char* password = "kungarike";
const char* postserver = "postserver";
const uint8_t wifiConnectTimeout = 10; // The amount of seconds to wait until giving up connecting to Wi-Fi

const int ledPinESP =  2;// LED on ESP on pin 2
const int ledPinBoard =  16; // LED on board on pin 16

void setup() {
  delay(2000); // Wait some time, in order to allow ESP8266 to boot
  Serial.begin(250000);
  delay(100); // Some time for serial buffer to empty

  pinMode(ledPinBoard, OUTPUT);
  digitalWrite(ledPinBoard, LOW); // Turn on LED(LED is inverted, so HIGH is off)


  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  // Connecting to the WiFi network
  Serial.print(F("Connecting to "));
  Serial.print(ssid);
  WiFi.begin(ssid, password);
  uint8_t wifiCounter = 0;
  while (WiFi.status() != WL_CONNECTED && wifiCounter < wifiConnectTimeout) {
    delay(1000);
    Serial.print(F("."));
    wifiCounter++;
  }
  if (wifiCounter == wifiConnectTimeout) { // Wi-Fi could not connect
    Serial.println(F("Wi-Fi connection timeout. Could not connect to Wi-Fi..."));
    Serial.println(F("Try plugging out and back in the USB-cable"));
    Serial.println(F("STOPPING PROGRAM"));
    digitalWrite(ledPinBoard, HIGH); // Turn off status LED(LED is inverted, so HIGH is off)
    // Stop program
    while (1) {
      delay(1);
    }
  } else { // do normal startup operation
    Serial.println(F("Connected to Wi-Fi!"));
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    delay(100);
  }
}

int value = 0;

void loop() {
  delay(5000);
  ++value;

  Serial.print("Connecting to ");
  Serial.println(postserver);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(postserver, 80)) {
    Serial.println(F("Failed to connect to database host!"));
    return;
  } else {
    Serial.println(F("Connected!"));
  }

  const String data = "hello";

  Serial.print(F("Sending information to server..."));
  // Start sending the POST request to the server
  client.println(F("POST /index.php HTTP/1.1"));
  client.print(F("Host: "));
  client.println(postserver);
  client.println(F("Content-Type: application/x-www-form-urlencoded"));
  client.print(F("Content-Length: "));
  client.println(data.length());
  client.println();
  client.print(data);
  Serial.println(F("Sent!"));

  // Read all the lines of the reply from server and print them to Serial
  Serial.print(F("Waiting for response from server..."));
  while (!client.available()) delay(1);// Wait for server to respond
  Serial.println(F("Response received:"));
  Serial.println(F("--------------------------------------------"));
  Serial.println(F(""));
  delay(100);// Allow network buffer to fill
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  Serial.println(F("--------------------------------------------"));
  Serial.println(F("Response ended."));
  Serial.println(F("HTTP-task done."));
}
