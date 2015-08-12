//------------------------------------------------------------------------------
// Ceiling lights functions

bool mainLightsStatus = 0;

void initLights() {
  // Setup ceiling lights relay pin
  pinMode(MAINLIGHTS_PIN, OUTPUT);

  //Restore the previous main lights state before restart
  Serial.println(F("Restoring previous main lights status..."));
  setMainLights(EEPROM.read(EEPROM_MAINLIGHTS));
}

void setMainLights(bool status) {
  if (mainLightsStatus != status) { // Only run if mainLights arent already on
    mainLightsStatus = status; // Save status to fast RAM
    digitalWrite(MAINLIGHTS_PIN, status); // Toggle mainLights switch
    EEPROM.write(EEPROM_MAINLIGHTS, status); //Save to EEPROM
    Serial.print(F("Set lights: "));
    Serial.println(mainLightsStatus);
  }
}

void toggleLights() {
  Serial.print(F("Toggle lights.. "));
  setMainLights(!mainLightsStatus);
}
