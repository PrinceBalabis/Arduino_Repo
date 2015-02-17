void pcPowerSetup() 
{
  pinMode(pcPowerPin, OUTPUT);
  digitalWrite(pcPowerPin, LOW);
}

void setPCPowerSwitch(boolean state) 
{
  if(state){
    digitalWrite(pcPowerPin, HIGH);
    Serial.println(F("Holding PC power button"));
  } 
  else {
    digitalWrite(pcPowerPin, LOW);
    Serial.println(F("Released PC power button"));
  }
}

