bool apartmentStatusUpdaterPaused = false;
bool apartmentStatusUpdaterPauseExecuted = false;

NIL_WORKING_AREA(apartmentStatusUpdater, 0); // 0 bytes seems to work fine
NIL_THREAD(ApartmentStatusUpdater, arg) {
  Serial.println(F("Started Apartment Status Updater Thread"));

  nilThdSleepMilliseconds(2000); // Give some time for system to boot up

  while (TRUE) {
    // Get stuck in this loop while its ment to be paused
    if (apartmentStatusUpdaterPaused) {
      apartmentStatusUpdaterPauseExecuted = true;
      while (apartmentStatusUpdaterPaused) {
        nilThdSleepMilliseconds(500);
      }
      apartmentStatusUpdaterPauseExecuted = false;
    }

    executeCommand(CMD_UPDATE_LED);

    nilThdSleepMilliseconds(apartmentStatusUpdateTime);
  }
}
