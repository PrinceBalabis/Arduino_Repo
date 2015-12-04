//------------------------------------------------------------------------------
// Ceiling lights functions

bool mainLightsStatus = 0;

void initLights() {
  // Setup ceiling lights relay pin as output
  //pinMode(MAINLIGHTS_PIN, OUTPUT);
  DDRC |= (1<<0); // Set as output

  //Restore the previous main lights state before restart
  Serial.println(F("Restoring previous main lights status..."));
  setMainLights(EEPROM.read(EEPROM_MAINLIGHTS));
}

void setMainLights(bool status) {
  if (mainLightsStatus != status) { // Only run if mainLights arent already on
    mainLightsStatus = status; // Save status to fast RAM

    if (status) { // Turn on main lights
      PORTC |= _BV(PC0);
      //digitalWrite(MAINLIGHTS_PIN, status);

    } else { // Turn off main lights
      PORTC &= ~_BV(PC0);
      //digitalWrite(MAINLIGHTS_PIN, status);
    }

    EEPROM.write(EEPROM_MAINLIGHTS, status); //Save to EEPROM
    Serial.print(F("Set lights: "));
    Serial.println(mainLightsStatus);
  }
}

void toggleLights() {
  Serial.print(F("Toggle lights.. "));
  setMainLights(!mainLightsStatus);
}
