NIL_WORKING_AREA(buttons, 128);
NIL_THREAD(Buttons, arg) {
  Serial.println(F("Started Buttons Sensor..."));

  pinMode(BUTTON_TOGGLE_COIN_VALUE_PIN, INPUT);
  pinMode(BUTTON_RESET_COUNT_PIN, INPUT);

  boolean buttonToggleValuePreviousState = HIGH;
  boolean buttonResetCountPreviousState = HIGH;

  while (TRUE) {
    nilThdSleepMilliseconds(BUTTON_POLLING_TIME);

    // Store button states in local variables
    boolean buttonToggleValueNowState = digitalRead(BUTTON_TOGGLE_COIN_VALUE_PIN);
    boolean buttonResetCountNowState = digitalRead(BUTTON_RESET_COUNT_PIN);
    //    Serial.print(F("Toggle Value button state: "));
    //    Serial.println(buttonToggleValueNowState);
    //    Serial.print(F("Reset Count button state: "));
    //    Serial.println(buttonResetCountNowState);

    if (!buttonToggleValueNowState && buttonToggleValuePreviousState) { //a new Toggle Value button press is detected
      Serial.println(F("Pressed Toggle Value button"));
      buttonToggleValuePreviousState = LOW;
      toggleCoinValue(); // Toggle Coin Value
      nilSemSignal(&semDisplay); // Tell display service to update display
    } else if (buttonToggleValueNowState && !buttonToggleValuePreviousState) { //Toggle Value button press is released
      Serial.println(F("Released Toggle Value button"));
      buttonToggleValuePreviousState = HIGH;
    } else if (!buttonResetCountNowState && buttonResetCountPreviousState) { //a new Reset Count button press is detected
      Serial.println(F("Pressed Reset Count button"));
      buttonResetCountPreviousState = LOW;
      coinAmount = 0; // reset coin count
      nilSemSignal(&semDisplay); // Tell display service to update display
    } else if (buttonResetCountNowState && !buttonResetCountPreviousState) { //Reset Count button press is released
      Serial.println(F("Released Reset Count button"));
      buttonResetCountPreviousState = HIGH;
    }
  }
}

void toggleCoinValue() {
  coinValue = 10;
}

