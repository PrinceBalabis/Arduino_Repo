/*
  ---------------------------------------------------------------


  The first line of the GET Request looks like this: "GET /LED=ON HTTP1.1"
  To get the command, we remove the first part("GET "), then we only read from what is left, until
  a space is detected(" HTTP1.1")


  Notes:
  WiFi.status()-function does not properly work with scheduler. So we had to make up another way to setup WiFi
  Most of the Serial.println in loop() is commented out because its so slow it holds the other tasks waiting
  ---------------------------------------------------------------
*/
class HTTPTask : public Task {
  protected:
    void setup() {
      delay(100); // Let other tasks start first
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
        // Pause interrupts
        pauseInterrupts();

        // Wait until the client sends some data
        while (!client.available()) delayMicroseconds(1);
        delay(1); // Allow buffer to fill

        // Read the first line of the request
        Serial.print("New client command: ");
        client.readStringUntil('/');// Remove the first part of the request("GET /")
        String request = client.readStringUntil(' '); // Read untill space is detected("ceilinglights=on HTTP1.1")
        Serial.println(request); // Print the command
        client.flush(); // Clear the network buffer

        // Match the request
        if (request == "masterswitch=off") {
          if (ceilingLightsStatus) setCeilingLights(LOW);
          if (paintingLightsStatus) setPaintingLights(LOW);
          if (deskLightsStatus) setDeskLights(LOW);
        } else if (request == "ceilinglights=on") {
          setCeilingLights(HIGH);
        } else if (request == "ceilinglights=off") {
          setCeilingLights(LOW);
        } else if (request == "ceilinglights=toggle") {
          toggleCeilingLights();
        } else if (request == "paintinglights=on") {
          setPaintingLights(HIGH);
        } else if (request == "paintinglights=off") {
          setPaintingLights(LOW);
        } else if (request == "paintinglights=toggle") {
          togglePaintingLights();
        } else if (request == "desklights=on") {
          setDeskLights(HIGH);
        } else if (request == "desklights=off") {
          setDeskLights(LOW);
        } else if (request == "desklights=toggle") {
          toggleDeskLights();
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

        client.print("<h1>Home Control</h1>\n"); // Top header
        client.print("Master switch&emsp;&emsp;");
        client.println("</html>");
        client.println("<a href=\"/masterswitch=off\"\"><button>Turn Off Everything</button></a>");
        client.println("<br>"); // new row;
        client.print("Ceiling Lights are ");
        if (ceilingLightsStatus == HIGH) {
          client.print("on&emsp;&emsp;");
          client.println("</html>");
          client.println("<a href=\"/ceilinglights=off\"\"><button>Turn Off </button></a>");
        } else {
          client.print("off&emsp;&emsp;");
          client.println("</html>");
          client.println("<a href=\"/ceilinglights=on\"\"><button>Turn On </button></a>");
        }
        client.println("<br>"); // new row;
        client.print("Painting Lights are ");
        if (paintingLightsStatus == HIGH) {
          client.print("on&emsp;&emsp;");
          client.println("</html>");
          client.println("<a href=\"/paintinglights=off\"\"><button>Turn Off </button></a>");
        } else {
          client.print("off&emsp;&emsp;");
          client.println("</html>");
          client.println("<a href=\"/paintinglights=on\"\"><button>Turn On </button></a>");
        }
        client.println("<br>"); // new row;
        client.print("Desk Lights are ");
        if (deskLightsStatus == HIGH) {
          client.print("on&emsp;&emsp;");
          client.println("</html>");
          client.println("<a href=\"/desklights=off\"\"><button>Turn Off </button></a>");
        } else {
          client.print("off&emsp;&emsp;");
          client.println("</html>");
          client.println("<a href=\"/desklights=on\"\"><button>Turn On </button></a>");
        }

        Serial.println("Client disonnected");
        Serial.println();

        // Unpause interrupts
        unpauseInterrupts();
      }
    }
  private:
    WiFiServer *getServer() {
      static WiFiServer server(serverPort);
      return &server;
    }
} http_task;

