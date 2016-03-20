NIL_WORKING_AREA(checkTWI, 150); //  bytes works great
NIL_THREAD(CheckTWI, arg) {
  nilThdDelayMilliseconds(TWI_BOOT_TIME); // Boot system first

  // This while thread gets used to get command which is sent from Home Network to to HomeControl
  //    Serial.print(F("Requesting data.. "));

  while (1) {

    while (command != 0) { // Wait here untill HomeControl ran command before getting a new one from TWI buffer
      nilThdDelayMilliseconds(10);
    }

    //Request data from slave.
    Wire.beginTransmission(TWI_SLAVE_ID);
    int available = Wire.requestFrom(TWI_SLAVE_ID, (uint8_t)1);
    if (available == 1) {
      byte command = Wire.read();
      if (command == 0) {
        //Serial.println(F("Connected but no command ATM.. "));
      } else {
        Serial.print(F("Command: "));
        Serial.println(command);
      }
    } else {
      Serial.print(F("NO TWI CONNECTION!"));
    }
    Wire.endTransmission();
    nilThdSleepMilliseconds(TWI_CHECK_TIME);
  }
}

// This function is called to send a command to home network when command is received from Keypad
void sendTWICommand(uint16_t node, uint16_t command) {
  Serial.print(F("Sending TWI.. Node="));
  Serial.print(node);
  Serial.print(F(", Command="));
  Serial.println(command);

  Wire.beginTransmission(TWI_SLAVE_ID);
  Wire.write(node);
  Wire.write(command);
  Wire.endTransmission();
}

