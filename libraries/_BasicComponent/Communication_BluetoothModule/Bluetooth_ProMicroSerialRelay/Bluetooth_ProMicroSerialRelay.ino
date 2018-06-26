/*
Run AT twice in order to get first "OK" response!!!

Connect the bluetooth module RX pin to Arduino TX pin
Connect the bluetooth module TX pin to Arduino RX pin

 */

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  Serial.println("Started Bluetooth module Serial Relay Sketch!");

  // set the data rate for the SoftwareSerial port
  Serial1.begin(9600);
 // mySerial.print("AT");
}

void loop() // run over and over
{
  if (Serial1.available())
    Serial.write(Serial1.read());
  if (Serial.available())
    Serial1.write(Serial.read());
}

