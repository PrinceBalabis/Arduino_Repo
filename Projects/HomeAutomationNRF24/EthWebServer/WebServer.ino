#define GET_REQUEST 0
#define POST_REQUEST 1

NIL_WORKING_AREA(webserver, 400);
NIL_THREAD(Webserver, arg) {
  nilThdSleepMilliseconds(SERVER_BOOT_TIME);
  Serial.println(F("Webserver Thread started"));

  byte mac[] = {
    0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
  };
  IPAddress ip(SERVER_IP);
  EthernetServer server(SERVER_PORT);
  boolean reading = false;
  bool requestType = 0; // 0=GET Request, 1=POST Request
  bool isNode = 1;

  // Start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  nilThdSleepMilliseconds(1000); // give the Ethernet shield a second to initialize:
  server.begin();
  nilThdSleepMilliseconds(1000); // give the Ethernet shield a second to initialize:
  Serial.print(F("Server IP: "));
  Serial.println(Ethernet.localIP());
  Serial.println(F("Webserver is listening"));

  while (1) {

    /////////////////////////////////////////// Send GET

    // Detected a command from HomeNetwork
    if (command != 0) {
      sendGETCommand(command);
      command = 0; // Clear current command to allow a new command
    }

    /////////////////////////////////////////// GET-SERVER
    // listen for incoming clients
    EthernetClient client = server.available();
    if (client) {
      Serial.print(F("New client with "));

      if (client.connected()) {
        if (client.available()) {
          char c = client.read();
          //Check if GET Request or POST Request Message
          if (c == 'G') {
            requestType = GET_REQUEST;
            Serial.println(F("GET Request"));
          } else if (c == 'P') {
            requestType = POST_REQUEST;
            Serial.println(F("POST Request"));
          }
        }
      }

      boolean currentLineIsBlank = true;
      // an http request ends with a blank line
      while (client.connected()) {
        if (client.available()) {
          char c = client.read();

          if (reading && c == ' ') reading = false;
          if (requestType == GET_REQUEST) { // This part is used to read the request when its GET Request
            if (c == '?') reading = true; //found the ?, begin reading the info
            if (reading) {
              if (c != '?') {
                //Serial.print(F("c: "));
                //Serial.println(c);
                tempS = "";
                tempS.concat(c);
                //Serial.print(F("tempS: "));
                //Serial.println(tempS);

                if (tempS != "-") {
                  if (node1 == "") {
                    //Read node
                    // Serial.println(F("Reading node..."));
                    node1 = tempS;
                    //Serial.print(F("node1: "));
                    //Serial.println(node1);
                  } else if (node2 == "" && isNode) {
                    node2 = tempS;
                    //Serial.print(F("node2: "));
                    //Serial.println(node2);
                  } else if (!isNode) {
                    //Read command,
                    //Serial.println(F("Reading command..."));
                    if (command1 != "") {
                      command2 = tempS;
                      //Serial.print(F("command2: "));
                      //Serial.println(command2);
                    } else {
                      command1 = tempS;
                      //Serial.print(F("command1: "));
                      //Serial.println(command1);
                    }
                  }
                } else if (tempS == "-") { // Change variable type from node to command
                  isNode = 0;
                }
              }
            }
          }

          if (c == '\n' && currentLineIsBlank) {
            if (requestType == POST_REQUEST) { // This part is used to read the request when its GET Request
              nilThdSleepMilliseconds(1000); // Give some time to receive whole POST Request from client
              client.find("LocationE"); // Find String "LocationE" in POST Request
              char locationStatus = client.read(); // Should be either an 'n' or x'
              if (locationStatus == 'n') { // if 'n' then youre Entered
                Serial.println(F("Entered apartment"));
                //sendTWICommand(CMD_APARTMENT_STARTUP);
              } else if (locationStatus == 'x') { // if 'x' then youre Exited
                //sendTWICommand(CMD_APARTMENT_SHUTDOWN);
                Serial.println(F("Exit apartment"));
              } else {
                Serial.println(F("Request not understood!"));
              }
            }

            // send a standard http response header, in order to fix "client not answering" bugs
            client.println(F("HTTP/1.1 200 OK"));
            client.println(F("Content-Type: text/html"));
            client.println(F("Connection: close"));  // the connection will be closed after completion of the response
            client.println(F(""));
            client.println(F("<!DOCTYPE HTML>"));
            client.println(F("<html>"));
            client.println(node1);
            client.print(command1);
            client.println(F("</html>"));
            break;
          }

          if (c == '\n') { // New blank line in HTTP Message, if HTTP is POST Request then data will show here
            currentLineIsBlank = true;
          } else if (c != '\r') {
            currentLineIsBlank = false;
          }
        }
      }
      //Serial.print(F("Node: "));
      uint16_t nodeMerged;
      if (node2 != "") {
        nodeMerged = (uint16_t)node1.toInt() * 10 + (uint16_t)node2.toInt();
      } else {
        nodeMerged = (uint16_t)node1.toInt();
      }
      //Serial.println(nodeMerged);
      //Serial.print(F("Command: "));
      uint16_t commandMerged;
      if (command2 != "") {
        commandMerged = (uint16_t)command1.toInt() * 10 + (uint16_t)command2.toInt();
      } else {
        commandMerged = (uint16_t)command1.toInt();
      }
      //Serial.println(commandMerged);

      sendTWICommand(nodeMerged, commandMerged); // Send command to HomeNetwork

      // Clear variables
      isNode = 1;
      node1 = "";
      node2 = "";
      command1 = "";
      command2 = "";

      // give the web browser time to receive the data
      nilThdSleepMilliseconds(CLIENT_SEND_TIME);
      // close the connection:
      client.stop();
      Serial.println(F("Client disconnected"));
      Ethernet.maintain();
    }
    nilThdSleepMilliseconds(5);
  }
}

void sendGETCommand(byte command) {
  EthernetClient client;
  bool connected = 0;

  switch (command) {
    case HOME_WEBSERVER_CMD_PC_SLEEP:
      connected = client.connect(ip_PC, PORT_EVENTGHOST);
      if (connected) {
        Serial.println(F("connected"));
        client.print(F("GET "));
        client.print(F("/html?SleepPCMonitors"));
        client.println(F(" HTTP/1.0"));
        client.println(F(""));
      }
      Serial.println(F("Send command to PC Sleep"));
      break;
    default:
      Serial.println(F("Cannot recognize GET command"));
      break;
  }

  //////Send GET
  if (connected) {
    // Print received data from GET-request
    while (client.connected() && !client.available()) nilThdSleepMilliseconds(1); //waits for data
    while (client.connected() || client.available()) { //connected or data available
      char c = client.read();
      Serial.print(c);
    }
    Serial.println();
    Serial.println(F("disconnecting."));
    Serial.println(F("=================="));
    Serial.println(F(""));
    client.stop();
  }
  else {
    Serial.println(F("connection failed"));
    Serial.println(F(""));
  }
}
