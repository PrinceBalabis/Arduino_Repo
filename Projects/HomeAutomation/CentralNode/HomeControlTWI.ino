
// HomeControl -> This
// This function is called when Master(HomeControl)
// has something to tell to this Arduino(Command received from keypad)
void receiveCommand(int availableBytes)
{
  //Read command received when type, node and command is received(2 bytes)
  if (availableBytes > 1) {
    executeCommand(Wire.read()); // Send command to Home Network
  }
}

// This -> HomeControl
// This function is called by HomeControl(Master) to check if this Arduino(CentralNode,Slave) has something to say
void requestCallback()
{
  //Serial.println("Callback requested");
  Wire.write(callbackCommand);
  callbackCommand = 0; // Clear previous command
}

