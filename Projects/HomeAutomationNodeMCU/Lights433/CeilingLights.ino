/*
  ---------------------------------------------------------------
  Ceiling lights functions
  ---------------------------------------------------------------
*/

void initCeilingLights() {
  // Setup ceiling lights relay pin as output
  pinMode(ceilingLightsPin, OUTPUT);

  // Turn off ceilingLights
  digitalWrite(ceilingLightsPin, LOW);

  //Restore the previous main lights state before restart
  //  Serial.println(F("Restoring previous main lights status..."));
  //  setMainLights(EEPROM.read(EEPROM_MAINLIGHTS));
}

void setCeilingLights(bool status) {
  if (ceilingLightsStatus != status) { // Only run if ceilinglights arent already on set state

    if (status) { // Turn on main lights
      // if (!getRoomBrightness()) { // If its dark, its okay to turn on lights
      digitalWrite(ceilingLightsPin, HIGH);
      //digitalWrite(ledPinBoard, LOW); // Turn board LED on(LOW=ON)
      Serial.println("Ceiling Lights are now on");
      //  } else {
      //    Serial.println(F("Room is already bright, not turning on ceiling lights"));
      //     return; // Exit function
      //  }
    } else { // Turn off ceiling lights
      digitalWrite(ceilingLightsPin, LOW);
      //digitalWrite(ledPinBoard, HIGH); // Turn board LED off(HIGH=ON)
      Serial.println("Ceiling Lights are now off");
      //digitalWrite(MAINLIGHTS_PIN, status);
    }

    ceilingLightsStatus = status; // Save status to fast RAM
    //EEPROM.write(EEPROM_MAINLIGHTS, status); //Save to EEPROM

    //    Serial.print("Ceiling Lights Status: ");
    //    if (ceilingLightsStatus) {
    //      Serial.println("On");
    //    } else {
    //      Serial.println("Off");
    //    }
  }
}

void toggleCeilingLights() {
  Serial.print("Toggling Ceiling Lights.. ");
  setCeilingLights(!ceilingLightsStatus);
}
