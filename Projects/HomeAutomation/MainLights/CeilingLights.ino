//------------------------------------------------------------------------------
// Ceiling lights functions

bool mainLightsStatus = 0;

void initLights() {
  // Setup ceiling lights relay pin
  pinMode(mainLightsPin, OUTPUT);

  //Restore the previous main lights state before restart
  setMainLights(EEPROM.read(MainLightsStatusAddress));
}

void setMainLights(bool status) {
  if (mainLightsStatus != status) { // Only run if mainLights arent already on
    mainLightsStatus = status; // Save status to fast RAM
    digitalWrite(mainLightsPin, status); // Toggle mainLights switch
    EEPROM.write(MainLightsStatusAddress, status); //Save to EEPROM
  }
}

void toggleLights() {
  setMainLights(!mainLightsStatus);
}
