NIL_WORKING_AREA(buttons, 128);
NIL_THREAD(Buttons, arg) {
  //Serial.println(F("Started Buttons Sensor..."));

  pinMode(BUTTON_TOGGLE_COIN_VALUE_PIN, INPUT);
  pinMode(BUTTON_RESET_COUNT_PIN, INPUT);

  boolean buttonToggleValuePreviousState = LOW;
  boolean buttonResetCountPreviousState = LOW;

  while (TRUE) {
    nilThdSleepMilliseconds(BUTTON_POLLING_TIME);

    // Store button states in local variables
    boolean buttonToggleValueNowState = digitalRead(BUTTON_TOGGLE_COIN_VALUE_PIN);
    boolean buttonResetCountNowState = digitalRead(BUTTON_RESET_COUNT_PIN);
    //    Serial.print(F("Toggle Value button state: "));
    //    Serial.println(buttonToggleValueNowState);
    //        Serial.print(F("Reset Count button state: "));
    //        Serial.println(buttonResetCountNowState);

    if (buttonToggleValueNowState && !buttonToggleValuePreviousState) { //a new Toggle Value button press is detected
      //Serial.println(F("Pressed Toggle Value button"));
      buttonToggleValuePreviousState = HIGH;
      toggleCoinValue(); // Toggle Coin Value
      nilSemSignal(&semDisplay); // Tell display service to update display
    } else if (!buttonToggleValueNowState && buttonToggleValuePreviousState) { //Toggle Value button press is released
      //Serial.println(F("Released Toggle Value button"));
      buttonToggleValuePreviousState = LOW;
    } else if (buttonResetCountNowState && !buttonResetCountPreviousState) { //a new Reset Count button press is detected
      //Serial.println(F("Pressed Reset Count button"));
      buttonResetCountPreviousState = HIGH;
      coinAmount = 0; // reset coin count
      coinTotal = 0; // reset coin total value

      nilSemSignal(&semDisplay); // Tell display service to update display
    } else if (!buttonResetCountNowState && buttonResetCountPreviousState) { //Reset Count button press is released
      //Serial.println(F("Released Reset Count button"));
      buttonResetCountPreviousState = LOW;
    }
  }
}

/**
   Function which toggles between coin values
*/
void toggleCoinValue() {
  if (coinValue == 0.25) {
    coinSensorLagTime = KR_050_LAG_TIME;
    coinSensorPollingTime = KR_050_POLLING_TIME;
    coinValue = 0.50;  // Set to 0.50 kr
  } else if (coinValue == 0.50) {
    coinSensorLagTime = KR_1_LAG_TIME;
    coinSensorPollingTime = KR_1_POLLING_TIME;
    coinValue = 1;    // Set to 1 kr
  } else if (coinValue == 1) {
    coinSensorLagTime = KR_2_LAG_TIME;
    coinSensorPollingTime = KR_2_POLLING_TIME;
    coinValue = 2;    // Set to 2 kr
  } else if (coinValue == 2) {
    coinSensorLagTime = KR_5_LAG_TIME;
    coinSensorPollingTime = KR_5_POLLING_TIME;
    coinValue = 5;    // Set to 5 kr
  } else if (coinValue == 5) {
    coinSensorLagTime = KR_10_LAG_TIME;
    coinSensorPollingTime = KR_10_POLLING_TIME;
    coinValue = 10;   // Set to 10 kr
  } else if (coinValue == 10) {
    coinSensorLagTime = KR_20_LAG_TIME;
    coinSensorPollingTime = KR_20_POLLING_TIME;
    coinValue = 20;   // Set to 20 kr
  } else if (coinValue == 20) {
    coinSensorLagTime = KR_025_LAG_TIME;
    coinSensorPollingTime = KR_025_POLLING_TIME;
    coinValue = 0.25; // Set to 0.25 kr
  }
}

