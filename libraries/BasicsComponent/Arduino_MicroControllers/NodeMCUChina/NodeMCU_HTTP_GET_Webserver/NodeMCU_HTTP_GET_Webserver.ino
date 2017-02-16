/* GET Webserver with ability to control the built in LED using a GET-Request or UI buttons

  To toggle LED on: 192.168.10.206/LED=ON
  To toggle LED off: 192.168.10.206/LED=OFF
  To return status/show UI buttons = 192.168.10.206

  The first line of the GET Request looks like this: "GET /LED=ON HTTP1.1"
  To get the command, we remove the first part("GET "), then we only read from what is left, until
  a space is detected(" HTTP1.1")

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

WiFiClient client;

const char* ssid = "Router";
const char* password = "kungarike";
const uint8_t wifiConnectTimeout = 5; // The amount of seconds to wait until giving up connecting to Wi-Fi

const int ledPinESP =  2;// LED on ESP on pin 2
const int ledPinBoard =  16; // LED on board on pin 16

WiFiServer server(80);

void setup() {
  delay(2000); // Wait some time, in order to allow ESP8266 to boot
  Serial.begin(250000);
  delay(100); // Some time for serial buffer to empty

  pinMode(ledPinBoard, OUTPUT);
  digitalWrite(ledPinBoard, LOW); // Turn off status LED(LED is inverted, so LOW is on)

  // Connect to WiFi network
  Serial.println(F(""));
  Serial.println(F(""));
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
    Serial.println(F("Wi-Fi connection timeout."));
    Serial.println(F("Could not connect to Wi-Fi..."));
    Serial.println(F("Try plugging replugging the USB-cable to reset the ESP8266"));
    Serial.println(F("HALTING PROGRAM...."));
    while (1) delay(100); // Stop program
  } else { // do normal startup operation
    Serial.println(F("Connected to Wi-Fi!"));
    Serial.print(F("IP address: "));
    Serial.println(WiFi.localIP());
    // Start the server
    server.begin();
    Serial.println(F("Server started..."));
    Serial.println(F(""));
    digitalWrite(ledPinBoard, HIGH); // Turn on LED(LED is inverted, so HIGH is off)
  }
}

void loop() {
  // Check if a client has connected
  client = server.available();
  if (!client) {
    return; // If there is no client then skip this loop
  }

  // Wait until the client sends some data
  while (!client.available()) delayMicroseconds(1);
  delay(1); // Allow buffer to fill

  // Read the first line of the request
  Serial.print("New client command: ");
  client.find("GET /"); // Remove the first part of the request("GET /")
  String request = client.readStringUntil(' '); // Read untill space is detected("LED=ON HTTP1.1")
  Serial.println(request);
  client.flush();

  // Match the request
  uint8_t value = 0;
  if (request.indexOf("LED=ON") != -1)  {
    digitalWrite(ledPinBoard, LOW);
    value = HIGH;
  }
  if (request.indexOf("LED=OFF") != -1)  {
    digitalWrite(ledPinBoard, HIGH);
    value = LOW;
  }

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.print("Led pin is now: ");

  if (value == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("<a href=\"/LED=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/LED=OFF\"\"><button>Turn Off </button></a><br />");
  client.println("</html>");

  Serial.println("Client disonnected");
  Serial.println();
}

