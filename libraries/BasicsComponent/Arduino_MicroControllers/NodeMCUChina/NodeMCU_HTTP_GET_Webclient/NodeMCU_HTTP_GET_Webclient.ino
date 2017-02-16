/* Simple HTTP get webclient test

  MAJOR BUG:
  If it cannot connect to the Wi-Fi hotspot, try reconnecting the power/USB cable to reset the ESP

  Put a large capacitor(or even better, several small ones) between 5V/VIN and Ground to improve reliability

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
const uint8_t wifiConnectTimeout = 10; // The amount of seconds to wait until giving up connecting to Wi-Fi

const char* host = "www.google.se";

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

  Serial.print("connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // We now create a URI for the request
  String url = "/?gws_rd=ssl#q=test";
  Serial.print("Requesting URL: ");
  Serial.println(url);

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  delay(500);

  //Read all the lines of the reply from server and print them to Serial
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

  Serial.println();
  Serial.println("closing connection");
}
