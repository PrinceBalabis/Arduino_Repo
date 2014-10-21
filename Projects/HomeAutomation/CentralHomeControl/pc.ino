void pcPowerSetup() {
  pinMode(pcPowerPin, OUTPUT);
  digitalWrite(pcPowerPin, LOW);
}

void sendPCPowerPing() {
  digitalWrite(pcPowerPin, HIGH);
  delay(20);
  digitalWrite(pcPowerPin, LOW);
}
