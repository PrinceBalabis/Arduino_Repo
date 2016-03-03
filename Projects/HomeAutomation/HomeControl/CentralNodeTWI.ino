
// CentralNode -> this
// This Thread loop gets used when a command from CentralNode to HomeControl is to be sent
NIL_WORKING_AREA(twi, 150);
NIL_THREAD(TWI, arg) {
  nilThdDelayMilliseconds(TWI_BOOT_TIME); // Boot system first
  Serial.println(F("TWI Thread started"));

  while (1) {
    //    Serial.print(F("Requesting data.. "));

    while (command != 0) { // Wait here untill keypad ran command before getting a new one
      nilThdDelayMilliseconds(10);
    }

    //Request data from slave.
    Wire.beginTransmission(TWI_SLAVE_ID);
    int available = Wire.requestFrom(TWI_SLAVE_ID, (uint8_t)1);
    if (available == 1) {
      command = Wire.read();
      if (command == 0) {
        //        Serial.println(F("Connected but no command ATM.. "));
      } else {
        Serial.print(F("Command: "));
        Serial.println(command);
      }
    } else {
      Serial.println(F("Not Connected!"));
    }
    Wire.endTransmission();

    nilThdDelayMilliseconds(TWI_CHECK_DELAY);
  }
}

// This -> CentralNode
// This function is called to send a command to home network when command is received from keypad
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

