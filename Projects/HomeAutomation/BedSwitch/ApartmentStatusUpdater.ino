static msg_t ApartmentStatusUpdater(void *arg) {
  Serial.println(F("Started Apartment Status Updater Thread"));
  
  while (1) {
    if (homeNetwork.askApartmentStatus() && !ledStatus) {
      setLED(HIGH);
      Serial.println(F("Apartment just went online, switching LED on!"));
    } else if (!homeNetwork.askApartmentStatus() && ledStatus) {
      setLED(LOW);
      Serial.println(F("Apartment just went offline, switching LED off!"));
    }
    chThdSleepMilliseconds(apartmentStatusUpdateTime);
  }
  
  return 0;
}
