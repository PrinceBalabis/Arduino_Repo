NIL_WORKING_AREA(webServerThread, 100);

NIL_THREAD(WebServerThread, arg) {
  Serial.println(F("Started WebServerThread"));

  Serial.println(F("Initializing ESP-05.."));
  nilThdSleepMilliseconds(5000);
  initESP8266();

  while (TRUE) {
    if (esp8266.available()) // check if the esp is sending a message
    {
      if (esp8266.find("+IPD,"))
      {
        nilThdSleepMilliseconds(50); // wait for the serial buffer to fill up (read all the serial data)
        // get the connection id so that we can then disconnect
        int connectionId = esp8266.read() - 48; // subtract 48 because the read() function returns
        // the ASCII decimal value and 0 (the first decimal number) starts at 48
        Serial.print(F("Client:"));
        Serial.print(connectionId);

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

        // Print command
        Serial.print(",Command:");
        Serial.println(command);

        // Send command to commandExecutioner to run
        executeCommand(command, COMMANDEXECUTIONER_MSGORIGIN_LOCAL);

        // Build string that is send back to client that sent command
        //      String content;
        //      content = "Command: ";
        //      content += pinNumber;
        //
        //      sendHTTPResponse(connectionId, content);

        // Dont need close command as timeout is only 1 second, doesnt work anyway!
        // make close command
        String closeCommand = "AT+CIPCLOSE=";
        closeCommand += connectionId; // append connection id
        closeCommand += "\r\n";
        char tmpCloseCommandCharArray[32];
        closeCommand.toCharArray(tmpCloseCommandCharArray, 32);
        Serial.println("test");
        Serial.println(closeCommand);
        Serial.println(tmpCloseCommandCharArray);
        sendCommand(tmpCloseCommandCharArray, 1000, DEBUG_TOGGLE); // close connection
      }
    }

    nilThdSleepMilliseconds(1); // Redo this send program every few moments, give enough time for other threads to run
  }
}


/*
* Name: sendData
* Description: Function used to send data to ESP8266.
* Params: command - the data/command to send; timeout - the time to wait for a response; debug - print to Serial window?(true = yes, false = no)
* Returns: The response from the esp8266 (if there is a reponse)
*/
void sendData(String command, const int timeout, boolean debug)
{
  String response = "";

  int dataSize = command.length();
  char data[dataSize];
  command.toCharArray(data, dataSize);

  esp8266.write(data, dataSize); // send the read character to the esp8266
  if (debug)
  {
    Serial.println("\r\n====== HTTP Response From Arduino ======");
    Serial.write(data, dataSize);
    Serial.println("\r\n========================================");
  }

  long int time = millis();

  while ( (time + timeout) > millis())
  {
    while (esp8266.available())
    {

      // The esp has data so display its output to the serial window
      char c = esp8266.read(); // read the next character.
      response += c;
      nilThdSleepMicroseconds(100);
    }
    nilThdSleepMicroseconds(100);
  }

  if (debug)
  {
    Serial.print(response);
  }
}

/*
* Name: sendHTTPResponse
* Description: Function that sends HTTP 200, HTML UTF-8 response
*/
//void sendHTTPResponse(int connectionId, String content)
//{
//
//  // build HTTP response
//  String httpResponse;
//  String httpHeader;
//  // HTTP Header
//  httpHeader = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n";
//  httpHeader += "Content-Length: ";
//  httpHeader += content.length();
//  httpHeader += "\r\n";
//  httpHeader += "Connection: close\r\n\r\n";
//  httpResponse = httpHeader + content + " "; // There is a bug in this code: the last character of "content" is not sent, I cheated by adding this extra space
//  sendCIPData(connectionId, httpResponse);
//}
//
///*
//* Name: sendCIPDATA
//* Description: sends a CIPSEND=<connectionId>,<data> command
//*
//*/
//void sendCIPData(int connectionId, String data)
//{
//  String cipSend = "AT+CIPSEND=";
//  cipSend += connectionId;
//  cipSend += ",";
//  cipSend += data.length();
//  cipSend += "\r\n";
//  sendCommand(cipSend, 1000, DEBUG_TOGGLE);
//  sendData(data, 1000, DEBUG_TOGGLE);
//}

/*
* Name: sendCommand
* Description: Function used to send data to ESP8266.
* Params: command - the data/command to send; timeout - the time to wait for a response; debug - print to Serial window?(true = yes, false = no)
* Returns: The response from the esp8266 (if there is a reponse)
*/
void sendCommand(char cmd[], const int timeout, const boolean debug) {
  esp8266.println(cmd); // Send to ESP-05
  unsigned long startTime = millis();

  while ((startTime + timeout) > millis()) {
    if (esp8266.available()) // input from the esp8266
      if (debug)
        Serial.write(esp8266.read()); // write to host
  }
}

void initESP8266() {
  sendCommand("AT+RST", 2000, DEBUG_TOGGLE); // Reset module
  nilThdSleepMilliseconds(5000); // Wait for module to connect to network
  sendCommand("AT+CIFSR", 1000, DEBUG_TOGGLE); // Print ip address
  sendCommand("AT+CIPMUX=1", 1000, DEBUG_TOGGLE); // configure for multiple connections
  sendCommand("AT+CIPSERVER=1,9500", 1000, DEBUG_TOGGLE); // turn on server on port 9500
  sendCommand("AT+CIPSTO=1", 1000, DEBUG_TOGGLE); // Set server timeout to some seconds, clients stop waiting for response after some seconds

  Serial.println("Server Ready and waiting clients");
}

