/*

   Before running this sketch you must configure ESP-05 to connect to your network at boot
   Also it must run at 38400 baud
   Set WiFi Mode to only STA
      AT+CWMODE=1
   Join Access Point
      AT+CWJAP="Router","kungarike"
   Disable watchdog, this doesnt restart the module when an error occured
      AT+CSYSWDTDISABLE
   Set to 38400 baud
      AT+CIOBAUD=38400
   Restart to save settings
      AT+RST

 * * Make sure the ESP-05 has at least 200-300 mA!!!! (by using separate power supply)
   Runs at 3.3V

   If there is still no answer from ESP-05, unplug and replug the ESP-05 onto the breadboard to fully reset it

   How to Send a GET HTTP Request from a simple internet browser:
   Enter this in browser to send command 13
   http://princehome.mooo.com:9500?c13
*/

#include <SoftwareSerial.h>

SoftwareSerial esp8266(2, 3); // make RX Arduino line is pin 2, make TX Arduino line is pin 3.
// This means that you need to connect the TX line from the esp to the Arduino's pin 2
// and the RX line from the esp to the Arduino's pin 3

const boolean debugToggle = false;

void setup()
{
  Serial.begin(115200);
  esp8266.begin(38400); // your esp's baud rate might be different

  Serial.println("Booted Arduino..");
  Serial.println("Starting services...");

  delay(5000);
  initESP8266();
}

void loop()
{
  if (esp8266.available()) // check if the esp is sending a message
  {

    if (esp8266.find("+IPD,"))
    {
      delay(50); // wait for the serial buffer to fill up (read all the serial data)
      // get the connection id so that we can then disconnect
      int connectionId = esp8266.read() - 48; // subtract 48 because the read() function returns
      // the ASCII decimal value and 0 (the first decimal number) starts at 48
      Serial.print(F("Client:"));
      Serial.print(connectionId);

      esp8266.find("c"); // advance cursor to "pin="

      //Read the command
      String strPinNumber = "";
      while (1) {
        char temp = esp8266.read();
        if (temp == -1) // If read() returned -1 then it means there is no more to read, exit out of loop
          break;
        strPinNumber += temp - 48; // Store char in String beacuse of ASCII error
      }
      int pinNumber = strPinNumber.toInt(); // Convert to int
      Serial.print(",Command:");
      Serial.println(pinNumber);

      // Build string that is send back to client that sent command
      String content;
      content = "Command: ";
      content += pinNumber;

      sendHTTPResponse(connectionId, content);

      // Dont need close command as timeout is only 1 second, doesnt work anyway!
      // make close command
      //      String closeCommand = "AT+CIPCLOSE=";
      //      closeCommand += connectionId; // append connection id
      //      closeCommand += "\r\n";
      //
      //      sendCommand(closeCommand, 1000, debugToggle); // close connection
    }
  }
}

/*
  Name: sendData
  Description: Function used to send data to ESP8266.
  Params: command - the data/command to send; timeout - the time to wait for a response; debug - print to Serial window?(true = yes, false = no)
  Returns: The response from the esp8266 (if there is a reponse)
*/
String sendData(String command, const int timeout, boolean debug)
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
    }
  }

  if (debug)
  {
    Serial.print(response);
  }

  return response;
}

/*
  Name: sendHTTPResponse
  Description: Function that sends HTTP 200, HTML UTF-8 response
*/
void sendHTTPResponse(int connectionId, String content)
{

  // build HTTP response
  String httpResponse;
  String httpHeader;
  // HTTP Header
  httpHeader = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n";
  httpHeader += "Content-Length: ";
  httpHeader += content.length();
  httpHeader += "\r\n";
  httpHeader += "Connection: close\r\n\r\n";
  httpResponse = httpHeader + content + " "; // There is a bug in this code: the last character of "content" is not sent, I cheated by adding this extra space
  sendCIPData(connectionId, httpResponse);
}

/*
  Name: sendCIPDATA
  Description: sends a CIPSEND=<connectionId>,<data> command

*/
void sendCIPData(int connectionId, String data)
{
  String cipSend = "AT+CIPSEND=";
  cipSend += connectionId;
  cipSend += ",";
  cipSend += data.length();
  cipSend += "\r\n";
  sendCommand(cipSend, 1000, debugToggle);
  sendData(data, 1000, debugToggle);
}

/*
  Name: sendCommand
  Description: Function used to send data to ESP8266.
  Params: command - the data/command to send; timeout - the time to wait for a response; debug - print to Serial window?(true = yes, false = no)
  Returns: The response from the esp8266 (if there is a reponse)
*/
String sendCommand(String command, const int timeout, boolean debug)
{
  String response = "";
  esp8266.print(command); // send the read character to the esp8266
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (esp8266.available())
    {

      // The esp has data so display its output to the serial window
      char c = esp8266.read(); // read the next character.
      response += c;
    }
  }

  if (debug)
  {
    Serial.print(response);
  }

  //  if (response.indexOf("busy p...") > 0) {
  //    Serial.print("ESP8266 hanged, reinitializing...");
  //    initESP8266();
  //  }

  return response;
}

void initESP8266() {
  sendCommand("AT+RST\r\n", 2000, debugToggle); // Reset module
  delay(5000); // Wait for module to connect to network
  sendCommand("AT+CIFSR\r\n", 1000, debugToggle); // Print ip address
  sendCommand("AT+CIPMUX=1\r\n", 1000, debugToggle); // configure for multiple connections
  sendCommand("AT+CIPSERVER=1,9500\r\n", 1000, debugToggle); // turn on server on port 80
  sendCommand("AT+CIPSTO=5\r\n", 1000, debugToggle); // Set server timeout to 5 seconds, clients stop waiting for response after 5 seconds

  Serial.println("Server Ready and waiting clients");
}

