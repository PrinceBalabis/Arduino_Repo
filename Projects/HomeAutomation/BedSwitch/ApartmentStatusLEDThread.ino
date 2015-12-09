NIL_WORKING_AREA(apartmentStatusLEDThread, 0); // 0 bytes seems to work fine
NIL_THREAD(ApartmentStatusLEDThread, arg) {
  pinMode(ledPin, OUTPUT);
  Serial.println(F("Started Apartment Status LED Thread"));

  while (TRUE) {
    digitalWrite(ledPin, LOW);
    nilThdSleepMilliseconds(apartmentStatusUpdateTime);
    digitalWrite(ledPin, HIGH);
    nilThdSleepMilliseconds(apartmentStatusUpdateTime);
  }
}

void setLEDStatus(bool state) {
  digitalWrite(ledPin, !digitalRead(ledPin));
}

bool getLEDStatus() {
  return digitalRead(ledPin);
}

