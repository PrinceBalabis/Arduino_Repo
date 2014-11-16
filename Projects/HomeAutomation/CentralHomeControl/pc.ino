void pcPowerSetup() {
  pinMode(pcPowerPin, OUTPUT);
  digitalWrite(pcPowerPin, LOW);
}

void sendPCPowerPing(int state) {
  if(state != RELEASED){
    digitalWrite(pcPowerPin, HIGH);
  } 
  else {
    digitalWrite(pcPowerPin, LOW);
  }
}





