uint8_t ledBrightness = minLEDBrightness;

bool fadeDirection = true; // false=fade out, true=fade in

static msg_t ApartmentStatusLEDThread(void *arg) {
  pinMode(ledPin, OUTPUT);
  Serial.println(F("Started Apartment Status LED Thread"));

  analogWrite(ledPin, 0); // Initialize LED to Off

  while (1) {
    if (ledStatus) {
      // change the brightness for next time through the loop:
      if (fadeDirection)
        ledBrightness = ledBrightness + fadeAmount;
      else
        ledBrightness = ledBrightness - fadeAmount;

      Serial.println(ledBrightness);

      analogWrite(ledPin, ledBrightness);

      // reverse the direction of the fading at the ends of the fade:
      if (ledBrightness <= minLEDBrightness) {// Reverse fade if the LED has reached minimum brightness
        fadeDirection = true;
        Serial.println(F("Reached minimum brightness, switching"));
        chThdSleepMilliseconds(500);
      }
      else if (ledBrightness >= maxLEDBrightness) { // Reverse fade if the LED has reached maximum brightness
        fadeDirection = false;
        Serial.println(F("Reached maximum brightness, switching"));
        chThdSleepMilliseconds(500);
      }
      chThdSleepMilliseconds(fadeTime);
    } else {
      chThdSleepMilliseconds(2000); // Minimize CPU load when LED is off
    }
  }

  return 0;
}

void enableLED() {
  ledStatus = true; //Enable LED fading in and out
  Serial.println(F("Switching LED on!"));
}

void disableLED() {
  while (ledBrightness > 0) { // Keep fading out LED until off
    ledBrightness = ledBrightness - fadeAmount;
    analogWrite(ledPin, ledBrightness);
    chThdSleepMilliseconds(fadeTime);

  }

  ledStatus = false; //Disable LED fading in and out
  fadeDirection = true; // Make sure it fades in when LED is enabled again
  Serial.println(F("Switching LED off!"));

}

