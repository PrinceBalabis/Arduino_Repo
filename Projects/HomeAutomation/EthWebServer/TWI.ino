SEMAPHORE_DECL(cmdExSem, 0);

NIL_WORKING_AREA(twi, 150);
NIL_THREAD(TWI, arg) {
  nilThdDelayMilliseconds(TWI_BOOT_TIME); // Boot system first
  Serial.println(F("TWI Thread started"));

  // This while loop gets used when a GET or POST command is to be sent from Home Network to internet
  while (1) {
    //    Serial.print(F("Requesting data.. "));
    //
    //    //Request data from slave.
    //    Wire.beginTransmission(TWI_SLAVE_ID);
    //    int available = Wire.requestFrom(TWI_SLAVE_ID, (uint8_t)1);
    //    if (available == 1) {
    //      byte command = Wire.read();
    //      if (command == 0) {
    //        Serial.println(F("Connected but no command ATM.. "));
    //      } else {
    //        Serial.print(F("Command: "));
    //        Serial.println(command);
    //      }
    //    } else {
    //      Serial.print(F("Not available: "));
    //      Serial.println(available);
    //    }
    //    Wire.endTransmission();

    nilThdDelayMilliseconds(TWI_CHECK_DELAY);
  }
}

// This function is called to send a command to home network when command is received from internet
void sendTWICommand(uint8_t node, uint8_t command) {
  Serial.print(F("Sending TWI.. Node="));
  Serial.print(node);
  Serial.print(F(", Command="));
  Serial.println(command);

  Wire.beginTransmission(TWI_SLAVE_ID);
  Wire.write(node);
  Wire.write(command);
  Wire.endTransmission();
}

