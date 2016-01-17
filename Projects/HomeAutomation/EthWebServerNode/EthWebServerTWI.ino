byte callbackCommand = 0;

// This function is called when Master(EthWebserver)
// has something to tell to this Arduino(Command received from internet)
void receiveCommand(int availableBytes)
{
  //Read command received when type, node and command is received(2 bytes)
  if (availableBytes > 1) {
    //    if (availableBytes == 1) {
    //      command = Wire.read();
    //    } else if (availableBytes == 2) {
    //command = Wire.read() << 8; // Read MSB
    //command |= Wire.read(); // Read LSB
    //    } else {
    //      Serial.println("Cant process received TWI command, too many bytes!");
    //    }
    Serial.print("Available bytes: ");
    Serial.println(availableBytes);

    uint16_t node = Wire.read();
    uint16_t command = Wire.read();

    Serial.print("Node: ");
    Serial.print(node);
    Serial.print(", Command: ");
    Serial.println(command);

    // If node is 0 then its a macro command
    if (node == 0) {
      Serial.println("Macro Command");
      executeCommandFromInternetMacro(command);
    } else { // Not a macro
      Serial.println("Not a Macro Comand");
      executeCommandFromInternet(node, command);
    }
  }
}

// This function is called by Master(EthWebserver) to check if this Arduino has something to tell Master
void requestCallback()
{
  //Serial.println("Callback requested");
  Wire.write(callbackCommand);
}

