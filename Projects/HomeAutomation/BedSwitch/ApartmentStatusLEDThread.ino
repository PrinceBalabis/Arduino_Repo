uint8_t ledBrightness = minLEDBrightness;

static msg_t ApartmentStatusLEDThread(void *arg) {
  pinMode(ledPin, OUTPUT);
  Serial.println(F("Started Apartment Status LED Thread"));

  while (1) {
    if (ledStatus) {
      // change the brightness for next time through the loop:
      ledBrightness = ledBrightness + fadeAmount;

      analogWrite(ledPin, ledBrightness);

      // reverse the direction of the fading at the ends of the fade:
      if (ledBrightness == minLEDBrightness) {
        fadeAmount = -fadeAmount;
        chThdSleepMilliseconds(1000);
      }
      else if (ledBrightness == maxLEDBrightness) {
        fadeAmount = -fadeAmount;
        chThdSleepMilliseconds(1000);
      }

      chThdSleepMilliseconds(fadeTime);
    } else {
      chThdSleepMilliseconds(500);
    }
  }

  return 0;
}

void setLED(bool state) {
  if (ledStatus != state) {
    ledStatus = state;
    switch (state) {
      case HIGH:
        analogWrite(ledPin, minLEDBrightness);
        break;
      case LOW:
        analogWrite(ledPin, 0);
        break;
    }
  }
}
