/*
  ---------------------------------------------------------------


  Notes:
  WiFi.status()-function does not properly work with scheduler. So we had to make up another way to setup WiFi
  Most of the Serial.println in loop() is commented out because its so slow it holds the other tasks waiting
  ---------------------------------------------------------------
*/
class HTTPTask : public Task {
  protected:
    void setup() {
      Serial.println(F("Starting HTTP Task..."));

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
        getServer()->begin();
        Serial.println(F("Started HTTP GET-Webserver Task"));
        Serial.println(F(""));
        digitalWrite(ledPinBoard, HIGH); // Turn on LED(LED is inverted, so HIGH is off)
        delay(100); // Some time for serial buffer to empty
        taskHTTPStarted = 1; // Set startup flag
      }
    }

    void loop()  {
      yield(); // Allow other essential backgrund tasks to run
      delay(serverUpdateExeutionFrequency); // Frequency to check if HTTP request should run

      // Check if a client has connected
      WiFiClient client = getServer()->available();
      if (client) {

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
        if (request.indexOf("led=on") != -1)  {
          digitalWrite(ledPinBoard, LOW);
          value = HIGH;
        } else if (request.indexOf("led=off") != -1)  {
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
        client.println("<title>Home Control</title>\n"); // Set server title
        client.println("<meta http-equiv=\"refresh\" content=\"5;URL=/\">\n"); // Tell the webbrowser to update the page every few seconds
        client.println("<meta content='width=device-width, initial-scale=1' name='viewport'/>\n"); // Optimize page width for mobiles

        client.print("<h1>LED Control</h1>\n"); // Top header
        client.print("Led pin is ");
        if (value == HIGH) {
          client.print("on&emsp;&emsp;"); // Tab = &emsp;
          //client.println("<br><br>");
          client.println("<a href=\"/led=off\"\"><button>Turn Off </button></a><br />");
        } else {
          client.print("off&emsp;&emsp;"); /// Tab = &emsp;
          //client.println("<br><br>");
          client.println("<a href=\"/led=on\"\"><button>Turn On </button></a>");
        }
        client.println("</html>");

        Serial.println("Client disonnected");
        Serial.println();
      }
    }
  private:
    WiFiServer *getServer() {
      static WiFiServer server(serverPort);
      return &server;
    }
} http_task;

