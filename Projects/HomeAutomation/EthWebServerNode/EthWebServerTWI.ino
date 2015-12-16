// This function is called when Master(EthWebserver) has something to tell to this Arduino
void receiveCommand(int availableBytes)
{
  if (availableBytes > 0) {
    byte command = Wire.read();
    Serial.print("Available bytes: ");
    Serial.println(availableBytes);
    Serial.print("Command: ");
    Serial.println(command);
    executeCommand(command, COMMANDEXECUTIONER_MSGORIGIN_LOCAL);
  }
}

// This function is called by Master(EthWebserver) to check if this Arduino has something to tell Master
void requestCallback()
{
  //Serial.println("Callback requested");
  Wire.write(0);
}

void blinkLED(uint16_t time) {
  digitalWrite(DEBUG_LED, !bitRead(PORTC, 0));
  nilThdSleepMilliseconds(time);
  digitalWrite(DEBUG_LED, !bitRead(PORTC, 0));
  nilThdSleepMilliseconds(time);
}
