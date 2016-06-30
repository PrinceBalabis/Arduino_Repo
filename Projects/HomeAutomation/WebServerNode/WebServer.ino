
NIL_WORKING_AREA(webServerThread, 90);

NIL_THREAD(WebServerThread, arg) {
  Serial.println(F("Started WebServerThread"));

  // initialize a pin as an output for LED.
  pinMode(DEBUG_LED, OUTPUT);
  digitalWrite(DEBUG_LED, LOW); // Turn LED off to indicate Webserver is not started

  Serial.println(F("Initializing ESP-05.."));
  nilThdSleepMilliseconds(5000);
  initESP8266();

  while (TRUE) {
    if (esp8266.available()) // check if the esp is sending a message
    {
      if (esp8266.find("+IPD,"))
      {
        while (!esp8266.available()) {
          nilThdSleepMilliseconds(1);
        }
        // get the connection id so that we can then disconnect
        int connectionId = esp8266.read() - 48; // subtract 48 because the read() function returns
        // the ASCII decimal value and 0 (the first decimal number) starts at 48

        //Read the command
        esp8266.find("c"); // advance cursor to "c"
        uint8_t commandArray[2]; // Command interval 0 to 99(two numbers)
        uint8_t commandLength = 0;
        while (TRUE) {
          commandArray[commandLength] = esp8266.read() - 48; // Read one number in command
          if (commandArray[commandLength] == 240 || commandLength == 2) { // If read() returned -16, then the whole command has been read, exit out of read loop, also exit if already read 2 numbers
            commandLength--;
            break;
          }
          commandLength++;
        }
        //Save command to simple uint8_t
        uint8_t command = 0;
        for (int i = 0; i < commandLength + 1; i++) {
          command = 10 * command + commandArray[i];
        }
        if (command != 180) { // If command shows 180, its just some browsers like chrome actually sending an ACK of some sorts that
          //the message was received.

          // Print details(CLient & command)
          Serial.print(F("Client:"));
          Serial.print(connectionId);
          Serial.print(F(",Command:"));
          Serial.println(command);

          // Clear Serial communication before sending command
          while (esp8266.available()) { // When serial data is available from ESP-05
            esp8266.read(); // Throw out data
          }
          // CIP Data
          char cipSend[17] = "AT+CIPSEND=0,200";
          cipSend[11] = connectionId + '0';
          esp8266.println(cipSend); // Send to ESP-05
          //esp8266.println(F("AT+CIPSEND=0,150")); // Send to ESP-05


          // Send command to commandExecutioner to run
          executeCommand(command, COMMANDEXECUTIONER_MSGORIGIN_LOCAL);

          while (executionerIdle == 0) {// Wait untill CommandExecutiner is done
            nilThdSleepMilliseconds(1);
          }

          // Send answer(from a question & status frmo after a command) response back to client
          sendResponse(connectionId, answer);

          //sendCommand("AT+CIPCLOSE=5\r\n", 1000, DEBUG_TOGGLE); // "=5" closes connection to all connected clients,
          // this is needed or else "busy p..." bug occurs
        }
      }
    }
    nilThdSleepMilliseconds(1); // Redo this send program every few moments, give enough time for other threads to run
  }
}

void sendResponse(int connectionId, uint8_t command) {
  // Receive response from ESP-05
  unsigned long startTime = millis();
  while ((startTime + 1000) > millis()) {
    if (esp8266.available()) { // When serial data is available from ESP-05
      while (esp8266.available()) {
        while (esp8266.available()) {
          if (DEBUG_TOGGLE)
            Serial.write(esp8266.read()); // Write to serial
          else
            esp8266.read(); // Throw out data
        }
        nilThdSleepMilliseconds(1); //Wait for buffer
      }
      break; // Exit out of while loop(stop waiting for timeout to end)
    }
  }

  // build HTTP response
  esp8266.print(F("HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n"));
  esp8266.print(F("Content-Length: "));
  if (command > 1) {
    esp8266.print(F("2"));
  } else {
    esp8266.print(F("1"));
  }
  esp8266.print(F("\r\nConnection: close\r\n\r\n"));
  esp8266.print(command);
  for (int i = 0; i < 150; i++) {
    esp8266.print(F("a"));
  }

  startTime = millis();
  while ((startTime + 1000) > millis()) {
    if (esp8266.available()) { // When serial data is available from ESP-05
      while (esp8266.available()) {
        esp8266.read(); // Throw out data
      }
      break; // Stop waiting for more serial data after done reading
    }
  }
}

/*
  Name: sendCommand
  Description: Function used to send data to ESP8266.
  Params: command - the data/command to send; timeout - the time to wait for a response; debug - print to Serial window?(true = yes, false = no)
  Returns: The response from the esp8266 (if there is a reponse)
*/
bool sendCommand(char cmd[], const int timeout, const boolean debug) {

  bool answerReceived = false;

  // Clear Serial communication before sending command
  while (esp8266.available()) { // When serial data is available from ESP-05
    esp8266.read(); // Throw out data
  }

  esp8266.println(cmd); // Send to ESP-05

  // Receive response from ESP-05
  unsigned long startTime = millis();
  while ((startTime + timeout) > millis()) {
    if (esp8266.available()) { // When serial data is available from ESP-05
      //nilThdSleepMilliseconds(50); // Give some buffer to Serial.
      while (esp8266.available()) {
        answerReceived = true;
        if (debug)
          Serial.write(esp8266.read()); // Write to serial
        else
          esp8266.read(); // Throw out data
      }
      break; // Exit out of while loop(stop waiting for timeout to end)
    }
  }
  return answerReceived;
}

//void sendGetRequest(String command) {
// Clear Serial communication before sending command
//  while (esp8266.available()) { // When serial data is available from ESP-05
//    esp8266.read(); // Throw out data
// }

//send
//Serial1.print("AT+CIPSEND=");
// Serial1.println(sendcommand.length());

//debug the command
// Serial.print("AT+CIPSEND=");
// Serial.println(sendcommand.length());

// esp8266.println("AT+CIPSTART=\"TCP\",\"192.168.1.2\", 5060"); // Send to ESP-05

// Receive response from ESP-05
// unsigned long startTime = millis();
// while ((startTime + 5000) > millis()) {
//  if (esp8266.available()) { // When serial data is available from ESP-05
//    answerReceived = true;
//     if (debug)
//       Serial.write(esp8266.read()); // Write to serial
//     else
//       esp8266.read(); // Throw out data
//   }
// }
//}

void initESP8266() {
  // Fix boot problem
  for (int i = 0; i < 200; i++) {
    esp8266.println(F("A"));
    nilThdSleepMilliseconds(1); // Makes sure loop doesnt crash RTOS
  }
  // Start normal initializatin
  if (sendCommand("AT+RST", 3000, DEBUG_TOGGLE)) { // Reset module
    digitalWrite(DEBUG_LED, HIGH);   // turn the LED on to indicate start successfull
    nilThdSleepMilliseconds(5000); // Wait for module to connect to network
    sendCommand("AT+CIFSR", 1000, DEBUG_TOGGLE); // Print ip address
    sendCommand("AT+CIPMUX=1", 2000, DEBUG_TOGGLE); // configure for multiple connections
    sendCommand("AT+CIPSERVER=1,9500", 1000, DEBUG_TOGGLE); // turn on server on port 9500
    sendCommand("AT+CIPSTO=1", 2000, DEBUG_TOGGLE); // Set server timeout to some seconds, clients stop waiting for response after some seconds

    //Blink LED
    digitalWrite(DEBUG_LED, LOW);
    nilThdSleepMilliseconds(100);
    digitalWrite(DEBUG_LED, HIGH);
    nilThdSleepMilliseconds(100);
    digitalWrite(DEBUG_LED, LOW);
    nilThdSleepMilliseconds(100);
    digitalWrite(DEBUG_LED, HIGH);
    Serial.println(F("Server Ready and waiting clients"));
  } else {
    Serial.println(F("ESP-05 initialization failed! PLEASE RESET POWER SWITCH...."));
    digitalWrite(DEBUG_LED, LOW);   // turn the LED off to indicate start unsuccessfull
    while (1);
  }
}

