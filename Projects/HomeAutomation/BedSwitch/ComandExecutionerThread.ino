/**
 ** CommandExecutioner thread
 ** Executes commands
 **/

static uint8_t commandToExecute = 0;

// Declare a semaphore with an inital counter value of zero.
SEMAPHORE_DECL(cmdExSem, 0);

NIL_WORKING_AREA(commandExecutioner, 150); //100 bytes works great
NIL_THREAD(CommandExecutioner, arg)
{
  Serial.println(F("CommandExecutioner thread started"));

  while (1)
  {
    // Wait for signal from either HNListenThread or Keypad Thread to run this loop
    nilSemWait(&cmdExSem);

    // Check apartment status
    bool apartmentStatus = askApartmentStatus();

    switch (commandToExecute) {
      //      case CMD_UPDATE_LED: // Update LED Status
      //        // What happens when apartment is either on or off
      //        if (apartmentStatus && !ledStatus) {
      //          setLEDStatus(HIGH);
      //          Serial.println(F("Apartment just went online, switching LED on!"));
      //        } else if (!apartmentStatus && ledStatus) {
      //          setLEDStatus(LOW);
      //          Serial.println(F("Apartment just went offline, switching LED off!"));
      //        } else if (apartmentStatus) {
      //          Serial.println(F("Apartment still ONLINE"));
      //        } else if (!apartmentStatus) {
      //          Serial.println(F("Apartment still OFFLINE"));
      //        }
      //        break;
      case CMD_APARTMENT_TOGGLE: // Button pressed, toggle apartment
        if (apartmentStatus) {
          shutdownApartment();
          //setLEDStatus(LOW);
          Serial.println("Shut down apartment");
        } else {
          startupApartment();
          //setLEDStatus(HIGH);
          Serial.println("Started up apartment");
        }
        break;
    }
  }
}

/*
   Run this function to enable CommandExecutionerThread to run
*/
void executeCommand(uint8_t _commandToExecute) {
  commandToExecute = _commandToExecute;
  nilSemSignal(&cmdExSem);
}
