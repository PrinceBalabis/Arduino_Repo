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
        WiFiServer* server = getServer();
        server->begin();
        Serial.println(F("Server started..."));
        Serial.println(F(""));
        digitalWrite(ledPinBoard, HIGH); // Turn on LED(LED is inverted, so HIGH is off)
        taskHTTPStarted = 1; // Set startup flag
      }
    }

    void loop()  {
      yield(); // Allow other essential backgrund tasks to run
      delay(serverUpdateExeutionFrequency); // Frequency to check if HTTP request should run

      // Check if a client has connected
      WiFiClient* client = getClient();
      WiFiServer* server = getServer();
      *client = server->available();
      if (!getClient()) {
        return; // If there is no client then skip this loop
      }

      // Wait until the client sends some data
      while (!client->available()) delayMicroseconds(1);
      delay(1); // Allow buffer to fill

      // Read the first line of the request
      Serial.print("New client command: ");
      client->find("GET /"); // Remove the first part of the request("GET /")
      String request = client->readStringUntil(' '); // Read untill space is detected("LED=ON HTTP1.1")
      Serial.println(request);
      client->flush();

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
      client->println("HTTP/1.1 200 OK");
      client->println("Content-Type: text/html");
      client->println(""); //  do not forget this one
      client->println("<!DOCTYPE HTML>");
      client->println("<html>");

      client->print("Led pin is now: ");

      if (value == HIGH) {
        client->print("On");
      } else {
        client->print("Off");
      }
      client->println("<br><br>");
      client->println("<a href=\"/LED=ON\"\"><button>Turn On </button></a>");
      client->println("<a href=\"/LED=OFF\"\"><button>Turn Off </button></a><br />");
      client->println("</html>");

      Serial.println("Client disonnected");
      Serial.println();
    }
  private:
    WiFiClient * getClient() {
      static WiFiClient client;
      return &client;
    }
    WiFiServer * getServer() {
      static WiFiServer server(serverPort);
      return &server;
    }
} http_task;

