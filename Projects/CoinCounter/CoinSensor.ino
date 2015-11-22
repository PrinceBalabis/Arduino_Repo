NIL_WORKING_AREA(coinSensor, 128);
NIL_THREAD(CoinSensor, arg) {
  nilThdSleepMilliseconds(500); // Give some time for whole system to start and stabilize
  Serial.println(F("Started Coin Sensor..."));
  pinMode(LED_STATUS_PIN, OUTPUT);

  boolean coinPreviousDetected = false; // Variable which stores if a coin is currently being inserted or not
  systime_t startTime = nilTimeNow(); // Save current time

  while (TRUE) {

    //Serial.println(analogRead(PHOTO_DIODE_PIN)); //Print the value of the photodiode to the serial monitor.
    boolean coinNowDetected = analogRead(PHOTO_DIODE_PIN) < COINSENSOR_POLLING_TIME; // If coin is being inserted or not

    if (coinNowDetected && !coinPreviousDetected) { // Coin inserting is first detected
      coinPreviousDetected = true;
    } else if (!coinNowDetected && coinPreviousDetected) { // Coin has finished inserting, and sensor is clear of ocin
      coinPreviousDetected = false;
      coinAmount++; // Add 1 coin to count
      //Serial.println(coinAmount); // Print amount of coins detected to the serial monitor
      nilSemSignal(&semDisplay); // Tell display service to update display
    }

    startTime += COINSENSOR_POLLING_TIME; // Calculate date when to run next time
    nilThdSleepUntil(startTime); // Wait for the set future date until continuing
  }
}
