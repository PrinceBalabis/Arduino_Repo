void setup() {
  Serial.begin(250000); 
  //  analogReference(EXTERNAL);
    analogReadResolution(12); // 0 - 4095

}

void loop() {           
  Serial.print(analogRead(A0));
  Serial.print(" ");      
  
  Serial.println();
  delay(2);                     
}



