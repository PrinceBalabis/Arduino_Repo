void setup() {
  Serial.begin(9600); 
  //  analogReference(EXTERNAL);
}

void loop() {           
  Serial.print(analogRead(A0));
  Serial.print(" ");      
  
  Serial.println();
  delay(2);                     
}



