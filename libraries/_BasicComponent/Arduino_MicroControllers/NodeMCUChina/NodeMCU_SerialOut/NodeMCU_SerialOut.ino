 /* Serial out test


  MAJOR BUG:
  If it cannot connect to the Wi-Fi hotspot, try reconnecting the power/USB cable to reset the ESP

  Put a large capacitor(or even better, several small ones) between 5V/VIN and Ground to improve reliability

  Remember to install the CH340G drivers.

  Board settings:
  -NodeMCU 1.0(ESP-12E)
  -160MHz
  -921600
  -4M(3M)
*/

void setup() {
  delay(2000); // Wait some time, in order to allow ESP8266 to boot
  Serial.begin(115200);
  delay(100); // Some time for serial buffer to empty

}

void loop() {
  Serial.println("Hello world");
  delay(1000);
}
