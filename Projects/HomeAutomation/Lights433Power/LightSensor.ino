/**
   Thread for the Light Sensor
**/
NIL_WORKING_AREA(lightSensorThread, 50); // bytes seems to work fine even with Home Network debug on
NIL_THREAD(LightSensorThread, arg)
{
  Serial.println(F("Started Light Sensor"));
  nilThdSleepMilliseconds(2000); // Allow system to fully start

  // Variables for logic
  unsigned long timeStart = 0;
  bool timerRunning = 0;  // 0 for timer running for lowlight, 1 for timer running brightlight

  while (1) {
    //    uint8_t lightValue = analogRead(PHOTOSENSOR_PIN);
    //    Serial.println(lightValue);

    if (mainLightsStatus) { // Check only for bright light when main lights is on
      uint8_t lightValue = analogRead(PHOTOSENSOR_PIN);
      //      Serial.println(lightValue);
      // Sensor is above threshold, then record what time the switch began, in order to implement "adapt time"
      if ((lightValue > PHOTOSENSOR_CEILINGLIGHTS_ON_BRIGHTLIGHT_VALUE)) {
        if (timerRunning != 1) { // Record starttime
          timeStart = millis();
          timerRunning = 1;
          Serial.println(F("Light just went above threshold, starting timer"));
        } else if ((timerRunning == 1) && ((millis() - timeStart) > PHOTOSENSOR_ADAPTTIME)) { // When adapt timer is reached, toggle lights
          setMainLights(false); // Toggle main lights off
          timerRunning = 0;
          timeStart = 0;
          Serial.print(F("Current light value: "));
          Serial.print(lightValue);
          Serial.print(F(".. "));
          Serial.println(F("Confirmed stable bright light, turning off main lights"));
        }
      } else if (timerRunning == 1) { // Reset timer if light went to normal
        timerRunning = 0;
        Serial.println(F("Light went to previous state, resetting light timer"));
      }
    }

    //    else {  // Check only for low light when main lights is off
    // uint8_t lightValue = analogRead(PHOTOSENSOR_PIN);
    //Serial.println(lightValue);
    //      // Same thing as when bright light is checked but opposite for when it turns low
    //      if ((lightValue < PHOTOSENSOR_LOWLIGHT_VALUE) && currentlightStatus) {
    //        if (timerRunning != 1) { // Record starttime
    //          timeStart = millis();
    //          timerRunning = 1;
    //          Serial.println(F("Light just went under threshold, starting timer"));
    //        } else if ((timerRunning == 1) && ((millis() - timeStart) > PHOTOSENSOR_ADAPTTIME)) { // When adapt timer is reached, toggle lights
    //          // TODO: IMPLEMENT WHEN IBEACON IS FUNCTIONAL AGAIN TO CHECK IF YOURE HOME BEFORE TOGGLING LIGHTS ON
    //          //setMainLights(true); // Toggle main lights on
    //          currentlightStatus = 0; // Light is now dark
    //          timerRunning = 0;
    //          timeStart = 0;
    //          Serial.println(F("Confirmed stable low light, turning on main lights"));
    //        }
    //      } else if (timerRunning == 1) { // Reset timer if light went to normal
    //        timerRunning = 0;
    //        Serial.println(F("Light went to previous state, resetting light timer"));
    //      }
    //    }
    nilThdSleepMilliseconds(PHOTOSENSOR_UPDATEDELAY);
  }
}

bool getRoomBrightness() {
  uint8_t lightValue = analogRead(PHOTOSENSOR_PIN);
  Serial.print(F("Current light value: "));
  Serial.print(lightValue);
  Serial.print(F(".. "));
  if ((lightValue > PHOTOSENSOR_CEILINGLIGHTS_OFF_BRIGHTLIGHT_VALUE) && !mainLightsStatus) { // Room is above "bright" threshold, return 1
    Serial.println(F("Ceiling lights are currently off & room is bright from outside lights"));
    return true;
  } else if ((lightValue > PHOTOSENSOR_CEILINGLIGHTS_ON_BRIGHTLIGHT_VALUE) && mainLightsStatus) { // Room is above "bright" threshold, return 1
    Serial.println(F("Ceiling lights are currently on & room is still bright from outside lights"));
    return true;
  } else if ((lightValue < PHOTOSENSOR_CEILINGLIGHTS_OFF_LOWLIGHT_VALUE) && !mainLightsStatus) { // Room is under "low light" threshold, return 0
    Serial.println(F("Ceiling lights are currently off & room is dark"));
    return false;
  } else if ((lightValue < PHOTOSENSOR_CEILINGLIGHTS_ON_LOWLIGHT_VALUE) && mainLightsStatus) { // Room is under "low light" threshold, return 0
    Serial.println(F("Ceiling lights are currently on & room is dark"));
    return false;
  } else {
    Serial.println(F("Current room brightness is in the gray area"));
    return false;
  }
}
