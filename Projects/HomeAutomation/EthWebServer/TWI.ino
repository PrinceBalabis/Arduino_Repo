SEMAPHORE_DECL(cmdExSem, 0);

NIL_WORKING_AREA(twi, 150);
NIL_THREAD(TWI, arg) {
  nilThdDelayMilliseconds(TWI_BOOT_TIME); // Boot system first
  Serial.println(F("TWI Thread started"));

  while (1) {
    Serial.print(F("Requesting data.. "));

    //Request data from slave.
    Wire.beginTransmission(TWI_SLAVE_ID);
    int available = Wire.requestFrom(TWI_SLAVE_ID, (uint8_t)1);
    if (available == 1) {
      byte command = Wire.read();
      if (command == 0) {
        Serial.println(F("Connected but no command ATM.. "));
      } else {
        Serial.print(F("Command: "));
        Serial.println(command);
      }
    } else {
      Serial.print(F("Not available: "));
      Serial.println(available);
    }
    Wire.endTransmission();

    nilThdDelayMilliseconds(TWI_CHECK_DELAY);
  }
}

void sendTWICommand(byte command) {
  Serial.print(F("Sending TWI command.. "));
  Serial.println(command);

  Wire.beginTransmission(TWI_SLAVE_ID);
  Wire.write(command);
  Wire.endTransmission();
}

