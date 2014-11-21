/**
* Simple code for 
* Single-axis Gyroscope Analog Gyro ENC-03RC
* VCC: 5V or 3.3V
* OUT: A0
* REF:
* GND: GND
* 
* Dont forget to connect the Analog Reference 
* pin on the Arduino to 3.3V or 5V
*/

const int gyroPin = A0;

void setup() {
  Serial.begin(9600); 
  analogReference(EXTERNAL);
}

void loop() {
  int sensorValue = analogRead(gyroPin);            
  Serial.println(sensorValue);      

  delay(2);                     
}
