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
    bool apartmentStatus = askApartmentStatus();

    // What happens when apartment is either on or off
    if (apartmentStatus && !ledStatus) {
      enableLED();
      Serial.println(F("Apartment just went online, switching LED on!"));
    } else if (!apartmentStatus && ledStatus) {
      disableLED();
      Serial.println(F("Apartment just went offline"));
    }
    chThdSleepMilliseconds(apartmentStatusUpdateTime);
  }

  return 0;
}


// Returns true if a source is on, returns false if all is off
bool askApartmentStatus() {

  int32_t mainLightStatus;
  if (!homeNetwork.sendQuestion(nodeMainLights, cmdGetLightsStatus, &mainLightStatus)) {
    Serial.println(F("Couldn't get an answer from Main Lights Node!"));
    mainLightStatus = 0;
  }
  else if (mainLightStatus) {
    Serial.println(F("Main lights are on!"));
    return true;
  }

  int32_t paintingLightsStatus;
  if (!homeNetwork.sendQuestion(nodeRF433MHz, cmdGetPaintingLightsStatus, &paintingLightsStatus)) {
    Serial.println(F("Couldn't get an answer from RF433MHz Node!"));
    paintingLightsStatus = 0;
  }
  else if (paintingLightsStatus) {
    Serial.println(F("Painting lights are on!"));
    return true;
  }

  int32_t speakerPowerSwitchStatus;
  if (!homeNetwork.sendQuestion(nodeRF433MHz, cmdGetSpeakerPowerStatus, &speakerPowerSwitchStatus)) {
    Serial.println(F("Couldn't get an answer from RF433MHz Node!"));
    speakerPowerSwitchStatus = 0;
  }
  else if (speakerPowerSwitchStatus) {
    Serial.println(F("Speaker is on!"));
    return true;
  }

  return false;

}

bool shutdownApartment() {
  chThdSleepMilliseconds(100); // Give some time
  homeNetwork.sendCommand(nodeMainLights, cmdToggleLights);
  homeNetwork.sendCommand(nodeRF433MHz, cmdSetPaintingLightsOff);
  homeNetwork.sendCommand(nodeSpeaker, cmdSetSpeakerPowerOff);
  homeNetwork.sendCommand(nodePC, cmdSetPCDisableMonitors);
}

bool startupApartment() {
  chThdSleepMilliseconds(100);
  homeNetwork.sendCommand(nodePC, cmdSetPCEnableMonitors); // Turn on PC monitors!
  homeNetwork.sendCommand(nodeMainLights, cmdSetLightsOn); // Turn on main lights!

  chThdSleepMilliseconds(4000); // Give some time for PC to wake before doing any more PC controls
  homeNetwork.sendCommand(nodePC, cmdSetPCSpotifyPlaylistWorkout); // Start Workout Playlist!!

  chThdSleepMilliseconds(5000); // Give some time for Spotify to start playlist
  homeNetwork.sendCommand(nodeSpeaker, cmdSetSpeakerPowerOn); // Turn on speaker!
}
