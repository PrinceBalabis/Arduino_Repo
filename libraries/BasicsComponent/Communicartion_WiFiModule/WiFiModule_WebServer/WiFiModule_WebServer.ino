void setup() {
  Serial.begin(115200);
}

void loop()
{
  boolean currentLineIsBlank = true;
  while (1) {
    if (Serial.available()) {
      char c = Serial.read();
      // if you've gotten to the end of the line (received a newline
      // character) and the line is blank, the http request has ended, // so you can send a reply
      if (c == '\n' && currentLineIsBlank) {
        // send the webpage
        Serial.println("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<center><h1>Hello World!! I am WiFi WebServer!!!</h1></center>");
        break;
      } if (c == '\n') {
        // you're starting a new line
        currentLineIsBlank = true;
      }
      else if (c != '\r') {
        // you've gotten a character on the current line
        currentLineIsBlank = false;
      }
    }
  }
}
