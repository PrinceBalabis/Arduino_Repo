/*
// Run AT twice in order to get first "OK" response!!!

 */
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  Serial.println("Started Bluetooth module Serial Relay Sketch!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(38400);
 // mySerial.print("AT");
}

void loop() // run over and over
{
  if (mySerial.available())
    Serial.write(mySerial.read());
  if (Serial.available())
    mySerial.write(Serial.read());
}

