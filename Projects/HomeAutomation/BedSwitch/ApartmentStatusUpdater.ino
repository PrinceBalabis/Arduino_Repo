bool apartmentStatusUpdaterPaused = false;
bool apartmentStatusUpdaterPauseExecuted = false;

static msg_t ApartmentStatusUpdater(void *arg) {
  Serial.println(F("Started Apartment Status Updater Thread"));

  while (1) {
    
        // Get stuck in this loop while its ment to be paused
    while (apartmentStatusUpdaterPaused) {
      apartmentStatusUpdaterPauseExecuted = true;
      chThdSleepMilliseconds(1000);
    }
    
    // Reset the apartment status updater execute flag if its true
    if (apartmentStatusUpdaterPauseExecuted)
      apartmentStatusUpdaterPauseExecuted = false;

    // Check apartment status
    bool apartmentStatus = homeNetwork.askApartmentStatus();

    // What happens when apartment is either on or off
    if (apartmentStatus && !ledStatus) {
      setLED(HIGH);
      Serial.println(F("Apartment just went online, switching LED on!"));
    } else if (!apartmentStatus && ledStatus) {
      setLED(LOW);
      Serial.println(F("Apartment just went offline, switching LED off!"));
    }
    chThdSleepMilliseconds(apartmentStatusUpdateTime);
  }

  return 0;
}
