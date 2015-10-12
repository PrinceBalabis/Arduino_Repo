/**
 * http://192.168.1.18:60000/12
 * http://192.168.1.18:60000/3
 */

#include <SoftwareSerial.h>

SoftwareSerial hc21(2, 3);

#define DEBUG_TOGGLE 0

void setup() {
  Serial.begin(115200);
  Serial.println("Started GET Request Server");

  // set the data rate for the SoftwareSerial port
  hc21.begin(38400);

  // Initialize module for GET Request server
  initHC21();

}

void loop() {
  delay(10);

  uint8_t newClient = checkNewClient(); // Check if new client

  if (newClient != 0) { // What happens when a new client has connected and sent a GET Request
    int16_t requestGET = readGetRequest(); // Save GET Reqeust

    Serial.print(F("GET Request: "));
    Serial.println(requestGET);

    // Respond to GET Request
    hc21.print("AT+SKSND=2,32\n\r"); // Notify Module that a message with max characters should be sent to client
    hc21.println(newClient); // Notify Module that a message with max characters should be sent to client
    delay(50);
    hc21.print("GET Request: "); // Send message
    hc21.println(requestGET); // Send message

    delay(50);
    hc21.print("AT+SKCLS="); // Close connection to client
    hc21.println(newClient); // Close connection to client

    Serial.println(); // New row for cleaner Serial Monitor
  }
}

/*
 * Returns GET request value
 */
int16_t readGetRequest() {
  if (DEBUG_TOGGLE)
    Serial.println(F("readGetRequest"));
  hc21.println("AT+SKRCV=2,383\n\r"); // Read connected client received information

  uint8_t requestGETArray[2];  // Command interval 0 to 99(two numbers)
  uint8_t requestGETArrayLength = 0;

  delay(100); // Wait for the serial buffer to fill up (read all the serial data)

  hc21.find("GET /");  // Set pointer to GET Request value

  while (1) {
    requestGETArray[requestGETArrayLength] = hc21.read() - 48; // Read one number in command
    if (requestGETArray[requestGETArrayLength] == 240 || requestGETArrayLength == 2) { // If read() returned -16, then the whole command has been read, exit out of read loop, also exit if already read 2 numbers
      requestGETArrayLength--;
      hc21.flush(); // Throw out remaining data in serial buffer
      if (DEBUG_TOGGLE)
        Serial.println(F("Read GET Request successfully from Serial buffer"));
      break;
    }
    requestGETArrayLength++;
  }

  //Collect GET Request as array
  //  while (hc21.available()) { // When serial data is available from HC-21
  //    if (hc21.peek() == ' ') { // When space is detected GET Request value has ended
  //      hc21.flush(); // Empty serial buffer
  //      break; // Exit out of loop
  //    }
  //    requestGETArray = hc21.read();
  //    // Print serial read
  //  }

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
  char answerReceived[64];
  uint8_t i = 0;

  hc21.println("AT+SKSTT=1\n\r"); // Send command to HC-21

  delay(100); // Let the module think for a while

  hc21.find("60000,0"); // advance cursor to "new line" in order to skip first row of server information
  hc21.read(); // Jump over \n
  hc21.read(); // Jump over \n

  if ((uint8_t)(hc21.peek() - 48) < 100) {
    uint8_t newClient = hc21.peek() - 48;
    hc21.flush(); // Throw out remaining data
    Serial.print(F("Found new client: "));
    Serial.println(newClient);
    return newClient;
  } else {
    hc21.flush(); // Throw out remaining data
    return 0;
  }
}

bool initCommand(char cmd[]) {
  hc21.println(cmd); // Send command to HC-21

  // Receive response from HC-21
  char answerReceived;
  int8_t i = -1;
  unsigned long startTime = millis();
  while ((startTime + 5000) > millis()) {
    if (hc21.available()) { // When serial data is available from HC-21
      delay(500); // Let buffer fill
      hc21.find("O"); // advance cursor to "O"
      answerReceived = hc21.read(); // Save received character, which is hopefully K to return variable
      break; // Get out of waiting loop
    }
  }

  delay(5000);

  if (answerReceived == 'K') {
    Serial.println(F("Done"));
    return 1;
  } else {
    Serial.println(F("ERROR"));
    return 0;
  }
}

void initHC21() {
  delay(2000);

  Serial.print(F("Resetting module..."));
  initCommand("AT+Z\n\r");
  Serial.print(F("Configuring module as server..."));
  initCommand("AT+ATM=!1\n\r");
  Serial.print(F("Starting server..."));
  initCommand("AT+SKCT=0,1,0,60000\n\r");

  Serial.println(F("Server initalized and idle.."));
}
