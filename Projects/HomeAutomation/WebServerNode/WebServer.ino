
NIL_WORKING_AREA(webServerThread, 90);

NIL_THREAD(WebServerThread, arg) {
  DEBUG_PRINTLN(F("Started WebServerThread"));

  // initialize digital pin 13 as an output.
  pinMode(DEBUG_LED, OUTPUT);
  digitalWrite(DEBUG_LED, LOW); // Turn LED off to indicate Webserver is not started

  blinkLED(1000);

  DEBUG_PRINTLN(F("Initializing HC-21.."));
  initHC21();

  while (1) {
    // Pause webserver to be able to run GET Requests
    if (pauseWebserver) {
      webserverIsPaused = true;
      while (pauseWebserver) {
        nilThdSleepMilliseconds(10);
      }
      webserverIsPaused = false;
    }

    uint8_t newClient = checkNewClient(); // Check if there is a new client
    if (newClient != 0) { // What happens when a new client has connected and sent a GET Request
      // Save HTTP Reqeust
      int16_t request = readHTTPRequest(newClient);
      DEBUG_PRINT(F("RAW HTTP Request: "));
      DEBUG_PRINTLN(request);
      nilThdSleepMilliseconds(10); // Give time for module to think

      // Respond to GET Request
      // Notify Module that a message with max characters should be sent to client
      hc21.print("AT+SKSND=2,20\n\r");
      hc21.println(newClient);
      hc21.flush();
      nilThdSleepMilliseconds(10); // Give time for module to think

      // Send message
      hc21.print("Request: ");
      hc21.println(request);
      hc21.flush();
      nilThdSleepMilliseconds(10); // Give time for module to think

      // Close connection to client
      hc21.print("AT+SKCLS=");
      hc21.println(newClient);
      hc21.flush();
      nilThdSleepMilliseconds(10); // Give time for module to think

      // Send command to commandExecutioner to run
      executeCommand(request, COMMANDEXECUTIONER_MSGORIGIN_LOCAL);
    }

    nilThdSleepMilliseconds(100); // Redo this send program every few moments, give enough time for other threads to run
  }
}

/*
 * Send GET Request
 */
bool sendGetRequest(uint8_t command, uint8_t ip1, uint8_t ip2, uint8_t ip3, uint8_t ip4, uint16_t port) {
  // Create connection to server
  hc21.flush();
  nilThdSleepMilliseconds(10); // Give time for module to think
  hc21.print("AT+SKCT=");
  hc21.print("0,0,");
  hc21.print(ip1);
  hc21.print(".");
  hc21.print(ip2);
  hc21.print(".");
  hc21.print(ip3);
  hc21.print(".");
  hc21.print(ip4);
  hc21.print(",");
  hc21.print(port);
  hc21.println("\n\r");
  nilThdSleepMilliseconds(50); // Let serial buffer fill up
  hc21.read(); // Skip first character which is just a '+'
  if ((char)hc21.read() == 'E') // If the message returned says error(E), then return false
    return false;
  hc21.find("=");  // Set pointer to find Connection Socket value
  uint8_t connectionSocket = (uint8_t)(hc21.read() - 48); // Save the Connection Socket
  hc21.flush();

  // Notify module that a message will be sent
  hc21.print("AT+SKSND=");
  hc21.print(connectionSocket);
  hc21.println(",100\n\r");
  nilThdSleepMilliseconds(50);
  hc21.flush();

  // Send GET Request
  hc21.print("GET /");
  hc21.print(command);
  hc21.println(" HTTP/1.0\r\n\r\n");
  nilThdSleepMilliseconds(50);
  hc21.flush();

  // Close connection
  hc21.print("AT+SKCLS=");
  hc21.print(connectionSocket);
  hc21.println("\n\r");
  nilThdSleepMilliseconds(50);
  hc21.flush();

  return true;
}

/*
 * Returns GET/POST request value
 */
int16_t readHTTPRequest(uint8_t client) {
  hc21.flush();
  nilThdSleepMilliseconds(10); // Give time for module to think

  // Read connected client received information,first 9 characters
  hc21.print("AT+SKRCV=");
  hc21.print(client);
  hc21.println(",9\n\r");

  uint8_t requestArray[2];  // Command interval 0 to 99(two numbers)
  uint8_t requestArrayLength = 0;
  uint8_t request = 0;

  nilThdSleepMilliseconds(50); // Wait for the serial buffer to fill up (read all the serial data)

  // Throw out first 9 characters of the incoming HTTP message which is not needed
  for (int i = 0; i < 9; i++) {
    hc21.read();
  }

  char HttpRequestType = hc21.read(); // Save request type

  if (HttpRequestType == 'P') { // If its a POST Request
    DEBUG_PRINT("HTTP Post Request: ");

    // Throw out the following 175 characters in HTTP Message because its not needed
    hc21.print("AT+SKRCV=");
    hc21.print(client);
    hc21.println(",175\n\r");
    nilThdSleepMilliseconds(50); // Wait for the serial buffer to fill up (read all the serial data)
    hc21.flush(); // Throw out trash data in serial buffer
    nilThdSleepMilliseconds(50); // Wait for the serial buffer to fill up (read all the serial data)

    // Read the next 25 characters of the message, this pack actually contains data whether you exit or entered the apartment
    hc21.print("AT+SKRCV=");
    hc21.print(client);
    hc21.println(",30\n\r");
    nilThdSleepMilliseconds(50); // Wait for the serial buffer to fill up (read all the serial data)

    hc21.find("LocationE"); // Set Serial read pointer to "LocationE", in order to read next character

    char locationStatus = hc21.read(); // Should be either an 'n' or x'

    if (locationStatus == 'n') { // x for LocationEnter
      DEBUG_PRINTLN("Entered Apartment!");
      request = 4;
    } else if (locationStatus == 'x') { // x for LocationExit
      DEBUG_PRINTLN("Exited Apartment!");
      request = 3;
    }

  } else if (HttpRequestType == 'G') { // If its a GET Request
    DEBUG_PRINTLN("HTTP GET Request");

    hc21.find("T /"); // Set Serial read pointer to after "GET /", in order to read the GET Command

    while (1) {
      requestArray[requestArrayLength] = hc21.read() - 48; // Read one number in command
      if (requestArray[requestArrayLength] == 240 || requestArrayLength == 2) { // If read() returned -16, then the whole command has been read, exit out of read loop, also exit if already read 2 numbers
        requestArrayLength--;
        break;
      }
      requestArrayLength++;
    }

    //Save command to simple uint8_t
    for (int i = 0; i < requestArrayLength + 1; i++) {
      request = 10 * request + requestArray[i];
    }
  }

  hc21.flush(); // Throw out remaining data in serial buffer

  return request;
}

/**
 * Returns clients socket number, returns 0 if no client is connected
 */
uint8_t checkNewClient() {
  hc21.flush(); // Clean serial buffer before sending command
  nilThdSleepMilliseconds(10); // Give time for module to think

  char answerReceived[64];
  uint8_t i = 0;

  hc21.println("AT+SKSTT=1\n\r"); // Send command to HC-21

  nilThdSleepMilliseconds(50); // Let Serial buffer fill

  hc21.find(",0"); // advance cursor to "new line" in order to skip first row of server information
  hc21.read(); // Jump over \n
  hc21.read(); // Jump over \n

  if ((uint8_t)(hc21.peek() - 48) < 100) {
    uint8_t newClient = hc21.peek() - 48;
    hc21.flush(); // Throw out remaining data
    DEBUG_PRINT(F("New Client: "));
    DEBUG_PRINTLN(newClient);
    return newClient;
  } else {
    hc21.flush(); // Throw out remaining data
    return 0;
  }
}

void initCommand(char cmd[]) {
  while (1) {
    hc21.flush(); // Clean serial buffer before sending command
    nilThdSleepMilliseconds(10); // Give time for module to think
    hc21.println(cmd); // Send command to HC-21

    // Receive response from HC-21
    char answerReceived;
    int8_t i = -1;
    unsigned long startTime = millis();
    while ((startTime + 5000) > millis()) {
      if (hc21.available()) { // When serial data is available from HC-21
        nilThdSleepMilliseconds(50); // Let buffer fill
        hc21.find("O"); // advance cursor to "O"
        answerReceived = hc21.read(); // Save received character, which is hopefully K to return variable
        hc21.flush(); // Throw out remaining serial data in buffer
        break; // Get out of waiting loop
      }
    }

    if (answerReceived == 'K') {
      DEBUG_PRINTLN(F("Done"));
      blinkLED(1000);
      break; // Exit out of init loop
    } else {
      DEBUG_PRINT(F("ERROR"));
      blinkLED(500);
      blinkLED(500);
      blinkLED(500);
      blinkLED(500);
      DEBUG_PRINTLN();
      DEBUG_PRINTLN();
      resetFunc();  //Reset Arduino
    }
  }
}

void initHC21() {
  DEBUG_PRINT(F("Resetting module..."));
  initCommand("AT+Z\n\r");
  nilThdSleepMilliseconds(10000); // Wait some seconds to let the module initialize command
  DEBUG_PRINT(F("Starting server..."));
  initCommand("AT+SKCT=0,1,0,9500\n\r");
  nilThdSleepMilliseconds(500); // Wait some seconds to let the module initialize command

  DEBUG_PRINT(F("Testing if server initalized correctly..."));
  initCommand("AT+SKSTT=1\n\r"); // Check if server initialized correctly
  DEBUG_PRINTLN();
  DEBUG_PRINTLN(F("Server initalized and idle.."));
  DEBUG_PRINTLN();
  digitalWrite(DEBUG_LED, HIGH); // Turn LED on to indicate Webserver is started
}

void blinkLED(uint16_t time) {
  digitalWrite(DEBUG_LED, !bitRead(PORTC, 0));
  nilThdSleepMilliseconds(time);
  digitalWrite(DEBUG_LED, !bitRead(PORTC, 0));
  nilThdSleepMilliseconds(time);
}

