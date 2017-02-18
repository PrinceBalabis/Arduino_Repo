/* Simple HTTP get webclient test

  MAJOR BUG:
  If it cannot connect to the Wi-Fi hotspot, try reconnecting the power/USB cable to reset the ESP

  Put a large capacitor(or even better, several small ones) between 5V/VIN and Ground to improve reliability

  Remember to install the CH340G drivers.

  Board settings:
  -NodeMCU 1.0(ESP-12E)
  -160MHz
  -921600
  -4M(3M)
*/

#include <ESP8266WiFi.h>

const char* ssid     = "Router";
const char* password = "kungarike";
const char* postserver = "postserver";
const uint8_t wifiConnectTimeout = 5; // The amount of seconds to wait until giving up connecting to Wi-Fi

const int ledPinESP =  D4;// LED on ESP on pin D4(Must call D4 in code)
const int ledPinBoard =  D0; // LED on board on pin D0(Must call D0 in code)

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
  Serial.println(F(""));
  Serial.println(F(""));
  Serial.print(F("Connecting to Wi-Fi: "));
  Serial.print(ssid);
  Serial.print(F("..."));
  WiFi.begin(ssid, password);
  uint8_t wifiCounter = 0;
  while (WiFi.status() != WL_CONNECTED && wifiCounter < wifiConnectTimeout) {
    delay(1000);
    Serial.print(F("."));
    wifiCounter++;
  }
  if (wifiCounter == wifiConnectTimeout) { // Wi-Fi could not connect
    Serial.println(F("Wi-Fi connection timeout."));
    Serial.println(F("Could not connect to Wi-Fi..."));
    Serial.println(F("Try unplugging & replugging the USB-cable to reset the ESP8266"));
    Serial.println(F("HALTING PROGRAM...."));
    while (1) { // Stop program and blink LED
      digitalWrite(ledPinBoard, HIGH); // Turn on LED(LED is inverted, so HIGH is off)
      delay(100);
      digitalWrite(ledPinBoard, LOW); // Turn on LED(LED is inverted, so LOW is on)
      delay(100);
    }
  } else { // do normal startup operation
    Serial.println(F("Connected!"));
    Serial.print(F("IP address: "));
    Serial.println(WiFi.localIP());
    delay(100); // Some time for serial buffer to empty
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
