void pcPowerSetup() {
  pinMode(pcPowerPin, OUTPUT);
  digitalWrite(pcPowerPin, LOW);
}

void sendPCPowerPing() {
  currentTimer = millis();
  if ((currentTimer - previousTimer) >= 500) {
    digitalWrite(pcPowerPin, HIGH);
    delay(20);
    digitalWrite(pcPowerPin, LOW);
    previousTimer = currentTimer; // Save last time volume increase
    serialPrintln("Sent PC power command");
  }

}
