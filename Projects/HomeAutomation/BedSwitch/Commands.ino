// Returns true if a source is on, returns false if all is off
bool askApartmentStatus() {

  bool status = false;

  status = getMainLightsStatus();
  if (status) {
    Serial.println(F("Apartment seems online, turning everything off.."));
    return true;
  }

  nilThdSleepMilliseconds(1000);
  status = getPaintingLightsStatus();
  if (status) {
    Serial.println(F("Apartment seems online, turning everything off.."));
    return true;
  }

  nilThdSleepMilliseconds(1000);
  status = getspeakerPowerSwitchStatus();
  if (status) {
    Serial.println(F("Apartment seems online, turning everything off.."));
    return true;
  }

  Serial.println(F("Apartment seems offline, turning everything on.."));
  return false;
}

boolean getspeakerPowerSwitchStatus() {
  int32_t status;
  if (!homeNetwork.sendQuestion(HOME_SPEAKER_ID, HOME_SPEAKER_QSN_POWER_STATUS, &status, 1000)) {
    Serial.println(F("Couldn't get an answer from Speaker Node!"));
    return false;
  }
  else if (status) {
    Serial.println(F("Speaker is on"));
    return true;
  } else {
    Serial.println(F("Speaker is off"));
  }
  return false;
}

boolean getPaintingLightsStatus() {
  int32_t status;
  if (!homeNetwork.sendQuestion(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_QSN_PAINTINGLIGHTS_STATUS, &status)) {
    Serial.println(F("Couldn't get an answer from Main Lights Node!"));
    return false;
  }
  else if (status) {
    Serial.println(F("Painting lights are on"));
    return true;
  } else {
    Serial.println(F("Painting lights are off"));
  }
  return false;
}

boolean getMainLightsStatus() {
  int32_t status;
  if (!homeNetwork.sendQuestion(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_QSN_MAINLIGHTS_STATUS, &status)) {
    Serial.println(F("Couldn't get an answer from Main Lights Node!"));
    return false;
  }
  else if (status) {
    Serial.println(F("Main lights are on"));
    return true;
  } else {
    Serial.println(F("Main lights are off"));
  }
  return false;
}

bool shutdownApartment() {
  nilThdSleepMilliseconds(1000);
  homeNetwork.sendCommand(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_CMD_MAINLIGHTS_OFF);
  Serial.println(F("Main lights shut down!"));
  nilThdSleepMilliseconds(1000);
  homeNetwork.sendCommand(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_CMD_PAINTINGLIGHTS_OFF);
  Serial.println(F("Painting lights shut down!"));
  nilThdSleepMilliseconds(1000);
  homeNetwork.sendCommand(HOME_SPEAKER_ID, HOME_SPEAKER_CMD_POWER_OFF);
  Serial.println(F("Speaker shut down!"));
  //homeNetwork.sendCommand(HOME_PC_ID, HOME_PC_CMD_MONITORS_DISABLE);
}

bool startupApartment() {
  nilThdSleepMilliseconds(1000);
  //homeNetwork.sendCommand(HOME_PC_ID, HOME_PC_CMD_MONITORS_ENABLE); // Turn on PC monitors!
  homeNetwork.sendCommand(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_CMD_MAINLIGHTS_ON); // Turn on main lights!
  Serial.println(F("Main lights turned on"));

  //nilThdSleepMilliseconds(4000); // Give some time for PC to wake before doing any more PC controls
  //homeNetwork.sendCommand(HOME_PC_ID, HOME_PC_CMD_SPOTIFY_PLAYLIST_WORKOUT); // Start Workout Playlist!!

  //nilThdSleepMilliseconds(5000); // Give some time for Spotify to start playlist
  nilThdSleepMilliseconds(1000);
  homeNetwork.sendCommand(HOME_SPEAKER_ID, HOME_SPEAKER_CMD_POWER_ON); // Turn on speaker!
  Serial.println(F("Speaker turned on"));
}
