
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
    uint8_t newClient = checkNewClient(); // Check if new client

    if (newClient != 0) { // What happens when a new client has connected and sent a GET Request
      int16_t requestGET = readGetRequest(); // Save GET Reqeust

      DEBUG_PRINT(F("GET Request: "));
      DEBUG_PRINTLN(requestGET);

      // Respond to GET Request
      hc21.print("AT+SKSND=2,32\n\r"); // Notify Module that a message with max characters should be sent to client
      hc21.println(newClient); // Notify Module that a message with max characters should be sent to client
      nilThdSleepMilliseconds(100);
      hc21.print("GET Request: "); // Send message
      hc21.println(requestGET); // Send message

      nilThdSleepMilliseconds(100);
      hc21.print("AT+SKCLS="); // Close connection to client
      hc21.println(newClient); // Close connection to client

      // Send command to commandExecutioner to run
      executeCommand(requestGET, COMMANDEXECUTIONER_MSGORIGIN_LOCAL);
    }
    nilThdSleepMilliseconds(100); // Redo this send program every few moments, give enough time for other threads to run
  }
}

/*
 * Returns GET request value
 */
int16_t readGetRequest() {
  hc21.println("AT+SKRCV=2,383\n\r"); // Read connected client received information

  uint8_t requestGETArray[2];  // Command interval 0 to 99(two numbers)
  uint8_t requestGETArrayLength = 0;

  nilThdSleepMilliseconds(100); // Wait for the serial buffer to fill up (read all the serial data)

  hc21.find("GET /");  // Set pointer to GET Request value

  while (1) {
    requestGETArray[requestGETArrayLength] = hc21.read() - 48; // Read one number in command
    if (requestGETArray[requestGETArrayLength] == 240 || requestGETArrayLength == 2) { // If read() returned -16, then the whole command has been read, exit out of read loop, also exit if already read 2 numbers
      requestGETArrayLength--;
      hc21.flush(); // Throw out remaining data in serial buffer
      break;
    }
    requestGETArrayLength++;
  }

  //Save command to simple uint8_t
  uint8_t requestGET = 0;
  for (int i = 0; i < requestGETArrayLength + 1; i++) {
    requestGET = 10 * requestGET + requestGETArray[i];
  }

  return requestGET;
}

/**
 * Returns clients socket number, returns 0 if no client is connected
 */
uint8_t checkNewClient() {
  hc21.flush(); // Clean serial buffer before sending command
  char answerReceived[64];
  uint8_t i = 0;

  hc21.println("AT+SKSTT=1\n\r"); // Send command to HC-21

  nilThdSleepMilliseconds(100); // Let the module think for a while

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
    hc21.println(cmd); // Send command to HC-21

    // Receive response from HC-21
    char answerReceived;
    int8_t i = -1;
    unsigned long startTime = millis();
    while ((startTime + 5000) > millis()) {
      if (hc21.available()) { // When serial data is available from HC-21
        nilThdSleepMilliseconds(1000); // Let buffer fill
        hc21.find("O"); // advance cursor to "O"
        answerReceived = hc21.read(); // Save received character, which is hopefully K to return variable
        hc21.flush(); // Throw out remaining serial data in buffer
        break; // Get out of waiting loop
      }
    }

    nilThdSleepMilliseconds(5000);

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
  nilThdSleepMilliseconds(5000);

  DEBUG_PRINT(F("Resetting module..."));
  initCommand("AT+Z\n\r");
  DEBUG_PRINT(F("Configuring module as server..."));
  initCommand("AT+ATM=!1\n\r");
  DEBUG_PRINT(F("Starting server..."));
  initCommand("AT+SKCT=0,1,0,9500\n\r");

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

