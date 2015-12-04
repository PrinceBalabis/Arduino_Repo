//------------------------------------------------------------------------------
// Ceiling lights functions

bool mainLightsStatus = 0;

void initLights() {
  // Setup ceiling lights relay pin as output
  //pinMode(MAINLIGHTS_PIN, OUTPUT);
  DDRC |= (1 << 0); // Set as output

  //Restore the previous main lights state before restart
  Serial.println(F("Restoring previous main lights status..."));
  setMainLights(EEPROM.read(EEPROM_MAINLIGHTS));
}

void setMainLights(bool status) {
  if (mainLightsStatus != status) { // Only run if mainLights arent already on set state

    if (status) { // Turn on main lights
      if (!getRoomBrightness()) { // If its dark, its okay to turn on lights
        PORTC |= _BV(PC0);
        //digitalWrite(MAINLIGHTS_PIN, status);
      } else {
        Serial.println(F("Room is already bright, not turning on ceiling lights"));
        return; // Exit function
      }
    } else { // Turn off main lights
      PORTC &= ~_BV(PC0);
      //digitalWrite(MAINLIGHTS_PIN, status);
    }

    mainLightsStatus = status; // Save status to fast RAM
    EEPROM.write(EEPROM_MAINLIGHTS, status); //Save to EEPROM

    Serial.print(F("Lights Status: "));
    if (mainLightsStatus) {
      Serial.println(F("On"));
    } else {
      Serial.println(F("Off"));
    }
  }
}

void toggleLights() {
  Serial.print(F("Toggle lights.. "));
  setMainLights(!mainLightsStatus);
}
