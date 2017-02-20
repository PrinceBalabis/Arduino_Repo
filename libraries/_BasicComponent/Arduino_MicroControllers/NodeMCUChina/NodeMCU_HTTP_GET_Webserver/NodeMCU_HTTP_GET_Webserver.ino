/* GET Webserver with ability to control the built in LED using a GET-Request or UI buttons

  To return status/show UI buttons = 192.168.10.206:80
  To toggle LED on: 192.168.10.206:80/led=on
  To toggle LED off: 192.168.10.206:80/led=off

  The first line of the GET Request looks like this: "GET /LED=ON HTTP1.1"
  To get the command, we remove the first part("GET "), then we only read from what is left, until
  a space is detected(" HTTP1.1")

  When using the pins, use the Arduino macros for pins(D2 for Digital pin 2, A0 for analog pin 0 etc)

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

WiFiClient client;

const char* ssid = "Router";
const char* password = "kungarike";
const uint8_t wifiConnectTimeout = 5; // The amount of seconds to wait until giving up connecting to Wi-Fi
const uint16_t serverPort = 80; // Port for this server, so we can access it from the internet
const int ledPinESP =  D4;// LED on ESP on pin D4(Must call D4 in code)
const int ledPinBoard =  D0; // LED on board on pin D0(Must call D0 in code)

WiFiServer server(serverPort);

void setup() {
  delay(2000); // Wait some time, in order to allow ESP8266 to boot
  Serial.begin(250000);
  delay(100); // Some time for serial buffer to empty

  pinMode(ledPinESP, OUTPUT);
  pinMode(ledPinBoard, OUTPUT);
  digitalWrite(ledPinESP, HIGH); // Turn off LED
  digitalWrite(ledPinBoard, LOW); // Turn on LED(LED is inverted, so LOW is on)

  // Connect to WiFi network
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
    Serial.print(WiFi.localIP());
    Serial.print(F(":"));
    Serial.println(serverPort);
    // Start the server
    server.begin();
    Serial.println(F("Started HTTP GET-Webserver Task"));
    Serial.println(F(""));
    digitalWrite(ledPinBoard, HIGH); // Turn on LED(LED is inverted, so HIGH is off)
    delay(100); // Some time for serial buffer to empty
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
  client.readStringUntil('/');// Remove the first part of the request("GET /")
  String request = client.readStringUntil(' '); // Read untill space is detected("LED=ON HTTP1.1")
  Serial.println(request); // Print the command
  client.flush(); // Clear the network buffer

  // Match the request
  uint8_t value = 0;
  if (request == "led=on")  {
    digitalWrite(ledPinBoard, LOW);
    value = HIGH;
  } else if (request == "led=off")  {
    digitalWrite(ledPinBoard, HIGH);
    value = LOW;
  }

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head><style>body{width:300px;margin:0 auto;}</style></head>\n"); // Set max width of webpage in pixels
  client.println("<title>LED Control</title>\n"); // Set server title
  client.println("<meta http-equiv=\"refresh\" content=\"5;URL=/\">\n"); // Tell the webbrowser to update the page every few seconds
  client.println("<meta content='width=device-width, initial-scale=1' name='viewport'/>\n"); // Optimize page width for mobiles

  client.print("<h1>LED Control</h1>\n"); // Top header
  client.print("Led pin is ");
  if (value == HIGH) {
    client.print("on&emsp;&emsp;");
    //   client.println("<br><br>");
    client.println("<a href=\"/led=off\"\"><button>Turn Off </button></a><br />");
  } else {
    client.print("off&emsp;&emsp;");
    //   client.println("<br><br>");
    client.println("<a href=\"/led=on\"\"><button>Turn On </button></a>");
  }
  client.println("</html>");

  Serial.println("Client disonnected");
  Serial.println();
}

