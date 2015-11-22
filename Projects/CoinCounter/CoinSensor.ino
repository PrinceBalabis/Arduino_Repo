NIL_WORKING_AREA(coinSensor, 128);
NIL_THREAD(CoinSensor, arg) {
  nilThdSleepMilliseconds(500); // Give some time for whole system to start and stabilize
  //Serial.println(F("Started Coin Sensor..."));
  pinMode(LED_STATUS_PIN, OUTPUT);

  boolean coinPreviousDetected = false; // Variable which stores if a coin is currently being inserted or not

  while (TRUE) {

//    Serial.println(analogRead(PHOTO_DIODE_PIN)); //Print the value of the photodiode to the serial monitor.
    boolean coinNowDetected = analogRead(PHOTO_DIODE_PIN) < coinSensorPollingTime; // If coin is being inserted or not

    if (coinNowDetected && !coinPreviousDetected) { // Coin inserting is first detected
      coinPreviousDetected = true;
    } else if (!coinNowDetected && coinPreviousDetected) { // Coin has finished inserting, and sensor is clear of ocin
      coinPreviousDetected = false;
      coinAmount++; // Add 1 coin to count
      coinTotal += coinValue; // Calculate coin total value
      //Serial.println(coinAmount); // Print amount of coins detected to the serial monitor
      nilSemSignal(&semDisplay); // Tell display service to update display
      nilThdSleepMilliseconds(coinSensorLagTime); // Sleep a little in order to correct bug where the empty coin circle in danish coins will make the coin counter think its two coins.
    }

      nilThdSleepMilliseconds(coinSensorPollingTime); // Sleep a little in order to correct bug where the empty coin circle in danish coins will make the coin counter think its two coins.
  }
}
