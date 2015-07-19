void pcPowerSetup() 
{
  pinMode(pcPowerPin, OUTPUT);
  digitalWrite(pcPowerPin, LOW);
}

void togglePCPowerSwitch() 
{
  if(digitalRead(pcPowerPin)){
    digitalWrite(pcPowerPin, LOW);
    Serial.println(F("Released PC power button"));
  } 
  else {
    digitalWrite(pcPowerPin, HIGH);
    Serial.println(F("Holding PC power button"));
  }
}

