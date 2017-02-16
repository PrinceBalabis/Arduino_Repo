/**
 ** CommandExecutioner thread
 ** Executes commands
 **/

static bool commandOrigin = 0;
static int32_t commandToExecute = 0;

// Declare a semaphore with an inital counter value of zero.
SEMAPHORE_DECL(cmdExSem, 0);

NIL_WORKING_AREA(commandExecutioner, 130); //65 bytes works great
NIL_THREAD(CommandExecutioner, arg)
{
  Serial.println(F("Started CommandExecutioner thread"));

  while (TRUE)
  {
    // Wait for signal from either HNListenThread or Keypad Thread to continue
    nilSemWait(&cmdExSem);

    bool sent = false;

    switch (commandOrigin) {
      case COMMANDEXECUTIONER_MSGORIGIN_HOMENETWORK: // If the command is from Home Network
        switch (commandToExecute) {
          case HOME_RF433MHZ_BLUETOOTH_CMD_PAINTINGLIGHTS_ON:
            setPaintingLightsOn();
            Serial.println(F("Turned Painting Lights on"));
            break;
          case HOME_RF433MHZ_BLUETOOTH_CMD_PAINTINGLIGHTS_OFF:
            setPaintingLightsOff();
            Serial.println(F("Turned Painting Lights off"));
            break;
          case HOME_RF433MHZ_BLUETOOTH_CMD_PAINTINGLIGHTS_TOGGLE:
            togglePaintingLights();
            Serial.println(F("Toggled Painting Lights"));
            break;
        }
        break;
      case COMMANDEXECUTIONER_MSGORIGIN_LOCAL: // If the command is from local origin(keypad)
        switch (commandToExecute) {
          
        }
    }

    if (sent) {
      Serial.println(".. Done!");
    } else if (!sent) {
      Serial.println(".. Couldn't send!");
    }
  }
}

/*
 * Run this function to enable CommandExecutionerThread to run
 */
void executeCommand(int32_t _commandToExecute, bool _commandOrigin) {
  commandToExecute = _commandToExecute;
  commandOrigin = _commandOrigin;
  nilSemSignal(&cmdExSem);
}
