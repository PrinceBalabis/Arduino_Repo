/*
  Web Server

 A simple web server that shows the value of the analog input pins.
 using an Arduino Wiznet Ethernet shield.

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Analog inputs attached to pins A0 through A5 (optional)

 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 modified 15 Jul 2014
 by Soohwan Kim

 */

#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

IPAddress ip(192, 168, 1, 16);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress myDns(8, 8, 8, 8); // google puble dns

EthernetServer server(4050);

const int led = 13;
String getRequest;

void setup() {
  Serial.begin(115200);
  Ethernet.begin(mac, ip, myDns, gateway, subnet);

  pinMode(led, OUTPUT);

  // start the Ethernet connection and the server:
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  Serial.println();
}


void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.print(F("Client connected - "));
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        // Here is where the POST/GET data is read byte by byte
        char c = client.read();
        getRequest += c; // Add byte to previously received ones

        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {

          String postRequest;
          while (client.available())
          {
            postRequest += (char)client.read();
          }
          //Serial.println(postRequest);

          if (postRequest.length() > 0) {
            Serial.println(F("GeoHopper iBeacon POST Request"));
            if (postRequest.indexOf("LocationExit") > 0) { // If the POST request says youve exited the apartment
              Serial.println(F("*** Exited apartment ***"));
              digitalWrite(led, LOW);
            } else if (postRequest.indexOf("LocationEnter") > 0) { //If the POST request says youve entered the apartment
              Serial.println(F("*** Entered apartment ***"));
              digitalWrite(led, HIGH);
            }
          } else { // What happens when a client which is not GeoHopper connects - like webbrowser
            Serial.println(F("Using web browser"));
            Serial.println(F("Sending response"));
            // send a standard http response header
            client.println("HTTP/1.1 200 OK"); //send new page
            client.println("Content-Type: text/html");
            client.println();
            client.println("<HTML>");
            client.println("<HEAD>");
            client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
            client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
            client.println("<link rel='stylesheet' type='text/css' href='http://82.196.5.54/princehomecontrol/arduinowebservercss.css' />");
            client.println("<TITLE>Prince Home Center</TITLE>");
            client.println("</HEAD>");
            client.println("<BODY>");
            client.println("<H1>Prince Home Center</H1>");
            client.println("<hr />");
            client.println("<br />");
            client.println("<H2>Lights</H2>");
            client.println("<br />");
            client.println("<a href=\"/?button1on\"\">Turn On LED</a>");
            client.println("<a href=\"/?button1off\"\">Turn Off LED</a><br />");
            client.println("<br />");
            client.println("<br />");
            client.println("<a href=\"/?button2on\"\">Rotate Left</a>");
            client.println("<a href=\"/?button2off\"\">Rotate Right</a><br />");
            //client.println("<p>Home control center by Prince</p>");
            client.println("<br />");
            client.println("</BODY>");
            client.println("</HTML>");

            //controls the Arduino if you press the buttons
            if (getRequest.indexOf(" /?button1on") > 0) {
              digitalWrite(led, HIGH);
              Serial.println(F("On button"));
            } else if (getRequest.indexOf(" /?button1off") > 0) {
              digitalWrite(led, LOW);
              Serial.println(F("Off button"));
            } else if (getRequest.indexOf(" /?button2on") > 0) {
              Serial.println(F("Rotate left button"));
            } else if (getRequest.indexOf(" /?button2off") > 0) {
              Serial.println(F("Rotate right button"));
            }
            //clearing string for next read
            getRequest = "";
          }
          //stopping client
          client.stop();
        }
        else if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    Serial.println(F("Client disconnected"));
    Serial.println();
  }
}

