const int analogInPin = A0;

void setup() {
  Serial.begin(9600); 
//  analogReference(EXTERNAL);
}

void loop() {
  int sensorValue = analogRead(analogInPin);            
  Serial.println(sensorValue);      

  delay(2);                     
}
