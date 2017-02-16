void setLEDStatus(bool state) {
  digitalWrite(ledPin, state);
}

void toggleLEDStatus(bool state) {
  digitalWrite(ledPin, !digitalRead(ledPin));
}

bool getLEDStatus() {
  return digitalRead(ledPin);
}

