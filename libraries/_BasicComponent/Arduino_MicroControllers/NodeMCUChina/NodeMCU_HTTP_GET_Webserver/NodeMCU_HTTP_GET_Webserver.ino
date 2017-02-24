/*
  ----------------------------------------------------------------------------------------------
  GET Webserver with ability to control the built in LED using a GET-Request or UI buttons

  Remove the serial.print's to improve the server performance

  To return status/show UI buttons = 192.168.10.206:80
  To toggle LED on: 192.168.10.206:80/led=on
  To toggle LED off: 192.168.10.206:80/led=off

  The first line of the GET Request looks like this: "GET /led=on HTTP1.1"
  To get the command, we remove the first part("GET /"), then we only read from what is left, until
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
  ----------------------------------------------------------------------------------------------
*/

/*
  ----------------------------------------------------------------------------------------------
  The includes
  ----------------------------------------------------------------------------------------------
*/
#include <ESP8266WiFi.h>

/*
  ----------------------------------------------------------------------------------------------
  Configuration
  ----------------------------------------------------------------------------------------------
*/
const char* ssid = "Router";
const char* password = "kungarike";
const uint16_t serverPort = 80; // Port for this server, so we can access it from the internet
const uint8_t wifiConnectTimeout = 5; // Amount of time(seconds) to wait until giving up on connecting to Wi-Fi AP
const String serverTitle = "LED Control"; // Title of the webpage
const String serverMaxPageWidth = "300"; // Max width of web page in pixels
const bool serverClientAutoRefreshEnabled = 1; // Enable webpage auto-refresh
const String serverClientAutoRefresh = "5"; // How often the client should update the page(seconds) if auto-refres is enabled, at least 1 second
const int ledPinESP =  D4;// LED on ESP on pin D4(Must call D4 in code)
const int ledPinBoard =  D0; // LED on board on pin D0(Must call D0 in code)

/*
  ----------------------------------------------------------------------------------------------
  Global logic variables
  ----------------------------------------------------------------------------------------------
*/
WiFiClient client;
WiFiServer server(serverPort);
uint8_t state = 0; // State of the LED which will be controlled by clients using the webserver

/*
  ----------------------------------------------------------------------------------------------
  setup()
  ----------------------------------------------------------------------------------------------
*/
void setup() {
  // Start serial, anything higher than 115200 might not work
  Serial.begin(115200);

  // Connect to WiFi network
  WiFi.begin(ssid, password);
  Serial.println(F(""));
  Serial.println(F(""));
  Serial.print(F("Connecting to Wi-Fi: "));
  Serial.print(ssid);
  Serial.print(F("..."));

  // Initialize built-in LEDs
  pinMode(ledPinESP, OUTPUT);
  pinMode(ledPinBoard, OUTPUT);
  digitalWrite(ledPinESP, HIGH); // Turn off ESP LED
  digitalWrite(ledPinBoard, LOW); // Turn on Board LED to indicate Wi-Fi is connecting(LED is inverted, so LOW is on)

  // Wait for ESP to connect to Wi-Fi AP
  uint8_t wifiCounter = 0;
  unsigned long previousMillis = 0; // The last time we printed the "." and counted the second
  while (WiFi.status() != WL_CONNECTED && wifiCounter < wifiConnectTimeout) { // Keep checking Wi-Fi for a connection or timeout
    unsigned long currentMillis = millis(); // Get current time
    if (currentMillis - previousMillis >= 1000) {
      previousMillis = currentMillis; // Store the current time of this action
      Serial.print(F(".")); // Print the dot
      wifiCounter++; // Count the second
    }
    delay(1); // Check Wi-Fi connection every few ms
  }

  if (wifiCounter == wifiConnectTimeout) { // Could not connect to Wi-Fi AP
    Serial.println(F("Wi-Fi connection timeout."));
    Serial.println(F("Could not connect to Wi-Fi..."));
    Serial.println(F("Try unplugging & replugging the USB-cable to reset the ESP8266"));
    Serial.println(F("HALTING PROGRAM...."));
    while (1) { // Stop program and blink LED to indicate Wi-Fi error
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
    digitalWrite(ledPinBoard, HIGH); // Turn off LED to indicate server has started(LED is inverted, so HIGH is off)
    state = digitalRead(ledPinBoard); // Set initial state of the LED for the webserver
    server.begin();
    Serial.println(F("Started HTTP GET-Webserver"));
    Serial.println(F(""));
  }
}

/*
  ----------------------------------------------------------------------------------------------
  loop()
  ----------------------------------------------------------------------------------------------
*/
void loop() {
  unsigned long timeStart = millis(); // Start stopwatch
  client = server.available(); // Check if a client has connected
  if (client) { // Client connected
    // Return the HTTP header response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println(""); //  do not forget this one
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<head><style>body{width:" + serverMaxPageWidth + "px;margin:0 auto;}</style></head>\n"); // Set max width of webpage in pixels
    client.println("<title>" + serverTitle + "</title>\n"); // Set server title
    if (serverClientAutoRefreshEnabled) client.println("<meta http-equiv=\"refresh\" content=\"" + serverClientAutoRefresh + ";URL=/\">\n"); // Tell the webbrowser to update the page every few seconds
    client.println("<meta content='width=device-width, initial-scale=1' name='viewport'/>\n"); // Optimize page width for mobiles
    // Return the some of the HTTP body response
    client.print("<h1>LED Control</h1>\n"); // Header 1
    client.print("Led pin is "); // Print the status of the LED

    // Check if the client sent a request/command
    while (!client.available()) delayMicroseconds(1); // Wait until the client sends some data
    // Read the first line of the request
    //Serial.print("New client...");
    client.readStringUntil('/');// Remove the first part of the request("GET /")
    String request = client.readStringUntil(' '); // Read untill space is detected("led=on HTTP1.1")
    if (request.length() > 0) { // Only process the request if the client has a command
      // Print the command
      //Serial.print("command: ");
      Serial.print(request);
      Serial.print("...");
      // Match the request
      if (request == "led=on")  {
        digitalWrite(ledPinBoard, LOW);
        state = HIGH;
      } else if (request == "led=off")  {
        digitalWrite(ledPinBoard, HIGH);
        state = LOW;
      }
    } else { // No command
      //Serial.print("no command...");
    }

    // Return the rest of the HTTP body response
    if (state == HIGH) {
      client.print("on");
      client.print("&emsp;&emsp;"); // Tabs
      client.println("<a href=\"/led=off\"\"><button>Turn Off </button></a><br />");
    } else {
      client.print("off");
      client.print("&emsp;&emsp;"); // Tabs
      client.println("<a href=\"/led=on\"\"><button>Turn On </button></a>");
    }
    client.println("</html>");

    client.flush(); // Waits until all outgoing characters in buffer has been sent.
    //Serial.print("disonnected...");
    //Serial.print("processed in ");
    Serial.print(millis() - timeStart); // Print the processing time(milliseconds), for optimization purposes
    //Serial.print(" milliseconds");
    Serial.println();
  }
  delayMicroseconds(1); // How often to check for a new client
}


