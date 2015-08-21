#include <SoftwareSerial.h>

/*
 *
 * Before running this sketch you must configure to run at 38400 baud
 * Set to 38400 baud
 *    AT+CIOBAUD=38400
 * Restart to save settings
 *    AT+RST
 *
 * Make sure the ESP-05 has at least 200-300 mA!!!! (by using separate power supply)
 * Runs at 3.3V
 * 
 * If there is still no answer from ESP-05, unplug and replug the ESP-05 onto the breadboard to fully reset it
 */

SoftwareSerial mySerial(2, 3);

void setup()
{
  Serial.begin(115200);
  Serial.println("starting esp8266 com sketch");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(38400);
}
char cmd[32];

void loop()
{ int i = 0;

  if (mySerial.available()) // input from the esp8266
    Serial.write(mySerial.read()); // write to host

  while (Serial.available()) {
    cmd[i] = Serial.read(); // buffer cmd
    i++;
    delay(5);
  }

  if ( i ) { // if host sent us cmd
    cmd[i] = 0;
    mySerial.println(cmd); // send to esp8266
  }
}
