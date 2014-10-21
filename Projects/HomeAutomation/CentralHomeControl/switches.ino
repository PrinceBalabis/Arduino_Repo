// Variables needed for the switch statuses
int mainLightStatus = 0;

void switchesSetup() {
  // Enable 433 MHz transmission on designated pin
  mySwitch.enableTransmit(transm433Pin);
  
  mainLightStatus = EEPROM.read(mainLightsAddress);
}

void sendMainLightPing() {
  if (mainLightStatus) { // If lights are on then turn OFF lights
    for (int i = 0; i < 2; i++) {
      mySwitch.send(5510485, 24);
    }
    EEPROM.write(mainLightsAddress, 0);
    mainLightStatus = 0;
    serialPrintln("Close Main Light");
  } else { // If lights are off then turn ON lights
    for (int i = 0; i < 2; i++) {
      mySwitch.send(5510484, 24);
    }
    EEPROM.write(mainLightsAddress, 1);
    mainLightStatus = 1;
    serialPrintln("Open Main Light");
  }
}
