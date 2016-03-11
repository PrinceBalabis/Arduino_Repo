
// This function is called when Master(HomeControl)
// has something to tell to this Arduino(Command received from keypad)
void receiveCommand(int availableBytes)
{
  //Read command received when type, node and command is received(2 bytes)
  if (availableBytes > 1) {
    //    if (availableBytes == 1) {
    //      node = Wire.read();
    //    } else if (availableBytes == 2) {
    //node = Wire.read() << 8; // Read MSB
    //node |= Wire.read(); // Read LSB
    //    } else {
    //      Serial.println("Cant process received TWI command, too many bytes!");
    //    }
    Serial.print("Available bytes:");
    Serial.print(availableBytes);

    uint16_t node = Wire.read();
    uint16_t command = Wire.read();

    Serial.print(", Node:");
    Serial.print(node);
    Serial.print(", Command:");
    Serial.println(command);

    executeCommand(COMMANDEXECUTIONER_MSGORIGIN_KEYPAD, node, command);
  }
}

// This function is called by HomeControl(Master)
//to check if this Arduino(HomeControlNode,Slave) has something to say
void requestCallback()
{
  //Serial.println("Callback requested");
  Wire.write(callbackCommand);
  callbackCommand = 0; // Clear previous command
}

