byte callbackCommand = 0;

// This function is called when Master(EthWebserver) has something to tell to this Arduino
void receiveCommand(int availableBytes)
{
  if (availableBytes > 0) {
    uint16_t command;
    if (availableBytes == 1) {
      command = Wire.read();
    } else if (availableBytes == 2) {
      command = Wire.read() << 8; // Read MSB
      command |= Wire.read(); // Read LSB
    } else {
      Serial.println("Cant process received TWI command, too many bytes!");
    }
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
  Wire.write(callbackCommand);
}

