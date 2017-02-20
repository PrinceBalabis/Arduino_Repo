/*
  ---------------------------------------------------------------
  HTTP GET Webclient class declaration
  Makes HTTP GET requests

  Notes:
  WiFi.status()-function does not properly work with scheduler. So we had to make up another way to setup WiFi
  Most of the Serial.println in loop() is commented out because its so slow it holds the other tasks waiting
  ---------------------------------------------------------------
*/
class HTTPTask : public Task {
  protected:
    void setup() {
      Serial.println(F("Starting HTTP Task..."));

      // Connecting to the WiFi network
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
        taskHTTPStarted = 1; // Set startup flag
      }
    }

    void loop()  {
      if (sendGETRequestPing) {
        Serial.println(F("Running a random GET request test..."));

        Serial.print(F("Connecting to "));
        Serial.println(testingHost);

        WiFiClient client;
        // Use WiFiClient class to create TCP connections
        if (!client.connect(testingHost, 80)) {
          Serial.println(F("Failed to connect to testing host!"));
          return;
        }

        // We now create a URI for the request
        String url = F("/?gws_rd=ssl#q=test");
        Serial.print(F("Requesting URL: "));
        Serial.println(url);

        // This will send the request to the server
        client.print(String(F("GET ")) + url + F(" HTTP/1.1\r\n") +
                     F("Host: ") + testingHost + F("\r\n") +
                     F("Connection: close\r\n\r\n"));

        sendGETRequestPing = 0; // Clear
        Serial.println(F("Done with doing GET-request"));
        // Read all the lines of the reply from server and print them to Serial
        // This readStringUntil function takes a long time and is badly compatible with scheduler.
        // When this function is ran it freezes all other tasks.
        // Make another while loop to print out all characters in realtime with delay to support scheduler in the future
        //      while (client.available()) {
        //        String line = client.readStringUntil('\r');
        //        Serial.print(line);
        //        delay(10);
        //      }

        //      Serial.println(F(""));
        //      Serial.println(F("closing connection"));
      }
      yield(); // Allow other essential backgrund tasks to run
      delay(httpExeutionFrequency); // Frequency to check if HTTP request should run
      sendGETRequestPing = 1; // RUN THE TEST
    }

  private:

} http_task;

