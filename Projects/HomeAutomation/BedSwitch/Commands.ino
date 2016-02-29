// Returns true if a source is on, returns false if all is off
bool askApartmentStatus() {

  if (getMainLightsStatus()) {
    Serial.println(F("Apartment seems online, turning everything off.."));
    return true;
  }

  if (getPaintingLightsStatus()) {
    Serial.println(F("Apartment seems online, turning everything off.."));
    return true;
  }

  //  if (getspeakerPowerSwitchStatus()) {
  //    Serial.println(F("Apartment seems online, turning everything off.."));
  //    return true;
  //  }

  Serial.println(F("Apartment seems offline, turning everything on.."));
  return false;
}

//boolean getspeakerPowerSwitchStatus() {
//  int32_t status;
//  if (!homeNetwork.sendQuestion(HOME_SPEAKER_ID, HOME_SPEAKER_QSN_POWER_STATUS, &status, 1000)) {
//    Serial.println(F("Couldn't get an answer from Speaker Node!"));
//    return false;
//  }
//  else if (status) {
//    Serial.println(F("Speaker is on"));
//    return true;
//  } else {
//    Serial.println(F("Speaker is off"));
//  }
//  return false;
//}

boolean getPaintingLightsStatus() {
  int32_t status;
  if (!homeNetwork.sendQuestion(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_QSN_PAINTINGLIGHTS_STATUS, &status, 100)) {
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
  if (!homeNetwork.sendQuestion(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_QSN_MAINLIGHTS_STATUS, &status, 100)) {
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

void shutdownApartment() {
  homeNetwork.sendCommand(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_CMD_MAINLIGHTS_OFF);
  Serial.println(F("Main lights shut down!"));
  homeNetwork.sendCommand(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_CMD_PAINTINGLIGHTS_OFF);
  Serial.println(F("Painting lights shut down!"));
  //homeNetwork.sendCommand(HOME_SPEAKER_ID, HOME_SPEAKER_CMD_POWER_OFF);
  homeNetwork.sendCommand(HOME_WEBSERVER_ID, HOME_WEBSERVER_CMD_PC_SLEEP);
  Serial.println(F("Sleeping PC!"));

}

void startupApartment() {
  homeNetwork.sendCommand(HOME_HOMECONTROL_ID, HOME_HOMECONTROL_CMD_PC_ON); // Turn on PC
  Serial.println(F("PC turned on"));
  homeNetwork.sendCommand(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_CMD_MAINLIGHTS_ON); // Turn on main lights!
  Serial.println(F("Main lights turned on"));
  //homeNetwork.sendCommand(HOME_SPEAKER_ID, HOME_SPEAKER_CMD_POWER_ON); // Turn on speaker!
  //Serial.println(F("Speaker turned on"));
}
