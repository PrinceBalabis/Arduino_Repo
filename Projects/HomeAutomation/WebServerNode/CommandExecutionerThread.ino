/**
 ** CommandExecutioner thread
 ** Executes commands
 **/

static bool commandOrigin = 0;
static int32_t commandToExecute = 0;

// Declare a semaphore with an inital counter value of zero.
SEMAPHORE_DECL(cmdExSem, 0);

NIL_WORKING_AREA(commandExecutioner, 140); // bytes works great
NIL_THREAD(CommandExecutioner, arg)
{
  Serial.println(F("Started CommandExecutioner thread"));

  while (TRUE)
  {
    executionerIdle = 1;
    // Wait for signal to run
    nilSemWait(&cmdExSem);
    executionerIdle = 0;


    switch (commandOrigin) {
      case COMMANDEXECUTIONER_MSGORIGIN_LOCAL: // Command that came from the internet
        switch (commandToExecute) {
          case CMD_MAINLIGHTS_TOGGLE:
            Serial.println(F("Toggle Main Lights command!"));
            homeNetwork.sendCommand(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_CMD_MAINLIGHTS_TOGGLE);
            break;
          case QSN_MAINLIGHTS_STATUS:
            Serial.println(F("Status of Main Lights!"));
            homeNetwork.sendQuestion(HOME_LIGHTS433POWER_ID, HOME_LIGHTS433POWER_QSN_MAINLIGHTS_STATUS, &answer, 200);
            answered = 1;
            break;
            //          case CMD_APARTMENT_SHUTDOWN:
            //            Serial.println(F("Shut-down Apartment Command!"));
            //            shutdownApartment();
            //            break;
            //          case CMD_APARTMENT_STARTUP:
            //            Serial.println(F("Start-up Apartment Command!"));
            //            startupApartment();
            //            break;
            //          case CMD_APARTMENT_TOGGLE:
            //            Serial.println(F("Toggle Apartment Command!"));
            //            if (askApartmentStatus()) {
            //              shutdownApartment();
            //            } else {
            //              startupApartment();
            //            }
            //            break;
            //          case CMD_PAINTINGLIGHTS_TOGGLE:
            //            Serial.println(F("Painting Lights Toggle Command!"));
            //            homeNetwork.sendCommand(HOME_RF433MHZ_ID, HOME_RF433MHZ_CMD_PAINTINGLIGHTS_TOGGLE);
            //            break;
            //          case CMD_SPEAKER_MUTE_TOGGLE:
            //            Serial.println(F("Speaker Mute Toggle Command!"));
            //            homeNetwork.sendCommand(HOME_SPEAKER_ID, HOME_SPEAKER_CMD_MUTE_TOGGLE);
            //            break;
            //          case CMD_SPEAKER_MODE_TOGGLE:
            //            Serial.println(F("Speaker Mode Toggle Command!"));
            //            homeNetwork.sendCommand(HOME_SPEAKER_ID, HOME_SPEAKER_CMD_MODE_TOGGLE);
            //            break;
            //          case CMD_APARTMENT_MOOD_TOGGLE:
            //            Serial.println(F("Apartment Mood Toggle Command!"));
            //            toggleApartmentMood();
            //            break;
        }
        break;
      case COMMANDEXECUTIONER_MSGORIGIN_HOMENETWORK: // Command that came from HomeNetwork
        switch (commandToExecute) {
        }
        break;
    }
  }
}

/*
   Run this function to enable CommandExecutionerThread to run
*/
void executeCommand(int32_t _commandToExecute, bool _commandOrigin) {
  commandToExecute = _commandToExecute;
  commandOrigin = _commandOrigin;
  nilSemSignal(&cmdExSem);
}
//
//void shutdownApartment() {
//  homeNetwork.sendCommand(HOME_MAINLIGHTS_ID, HOME_MAINLIGHTS_CMD_MAINLIGHTS_OFF);
//  homeNetwork.sendCommand(HOME_RF433MHZ_ID, HOME_RF433MHZ_CMD_PAINTINGLIGHTS_OFF);
//  homeNetwork.sendCommand(HOME_SPEAKER_ID, HOME_SPEAKER_CMD_POWER_OFF);
//  Serial.println(F("Shut-down Apartment!"));
//}
//
//void startupApartment() {
//  homeNetwork.sendCommand(HOME_MAINLIGHTS_ID, HOME_MAINLIGHTS_CMD_MAINLIGHTS_ON); // Turn on main lights!
//  homeNetwork.sendCommand(HOME_SPEAKER_ID, HOME_SPEAKER_CMD_POWER_ON); // Turn on speaker!
//  homeNetwork.sendCommand(HOME_HOMECONTROL_ID, HOME_HOMECONTROL_CMD_PC_ON); // Turn on PC!
//  Serial.println(F("Started-up Apartment!"));
//}
//
//bool askApartmentStatus() {
//  int32_t status;
//  if (!homeNetwork.sendQuestion(HOME_MAINLIGHTS_ID, HOME_MAINLIGHTS_QSN_MAINLIGHTS_STATUS, &status)) {
//    Serial.print(F("Couldn't get an answer from Main Lights Node!->"));
//  }
//  else if (status) {
//    Serial.print(F("Main lights are on!->"));
//    return true;
//  }
//
//  if (!homeNetwork.sendQuestion(HOME_RF433MHZ_ID, HOME_RF433MHZ_QSN_PAINTINGLIGHTS_STATUS, &status)) {
//    Serial.print(F("Couldn't get an answer from RF433MHz Node!->"));
//  }
//  else if (status) {
//    Serial.print(F("Painting lights are on!->"));
//    return true;
//  }
//
//  if (!homeNetwork.sendQuestion(HOME_RF433MHZ_ID, HOME_RF433MHZ_QSN_SPEAKER_POWER_STATUS, &status)) {
//    Serial.print(F("Couldn't get an answer from RF433MHz Node!->"));
//  }
//  else if (status) {
//    Serial.print(F("Speaker is on!->"));
//    return true;
//  }
//
//  return false;
//}
//
//void toggleApartmentMood() {
//  int32_t status;
//
//  if (!homeNetwork.sendQuestion(HOME_MAINLIGHTS_ID, HOME_MAINLIGHTS_QSN_MAINLIGHTS_STATUS, &status)) {
//    Serial.print(F("Couldn't get an answer from Main Lights Node!->"));
//  }
//  else if (status) {
//    Serial.print(F("Main lights are on!->"));
//    homeNetwork.sendCommand(HOME_MAINLIGHTS_ID, HOME_MAINLIGHTS_CMD_MAINLIGHTS_OFF);
//    homeNetwork.sendCommand(HOME_RF433MHZ_ID, HOME_RF433MHZ_CMD_PAINTINGLIGHTS_ON);
//  }
//  else if (!homeNetwork.sendQuestion(HOME_RF433MHZ_ID, HOME_RF433MHZ_QSN_PAINTINGLIGHTS_STATUS, &status)) {
//    Serial.print(F("Couldn't get an answer from RF433MHz Node!->"));
//  }
//  else if (status) {
//    Serial.print(F("Painting lights are on!->"));
//    homeNetwork.sendCommand(HOME_MAINLIGHTS_ID, HOME_MAINLIGHTS_CMD_MAINLIGHTS_ON);
//    homeNetwork.sendCommand(HOME_RF433MHZ_ID, HOME_RF433MHZ_CMD_PAINTINGLIGHTS_OFF);
//  } else {
//    //If both Main lights and painting lights are off, toggle painting lights on
//    homeNetwork.sendCommand(HOME_RF433MHZ_ID, HOME_RF433MHZ_CMD_PAINTINGLIGHTS_ON);
//  }
//}

