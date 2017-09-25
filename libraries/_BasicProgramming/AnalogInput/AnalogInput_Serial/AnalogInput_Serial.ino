void setup() {
  Serial.begin(115200); 
  //  analogReference(EXTERNAL);
    analogReadResolution(12); // 0 - 4095

}

void loop() {           
  Serial.print(analogRead(A8));
  Serial.print(" ");      
  
  Serial.println();
  delay(2);                     
}



