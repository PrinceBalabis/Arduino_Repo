bool getPaintingLightStatus() {
  return EEPROM.read(paintingLightsAddress);
}

void setPaintingLightStatus(bool status) {
  EEPROM.write(paintingLightsAddress, status);
}

void setPaintingLightsOn() {
  if (!getPaintingLightStatus()) {
    //SEND TO RF433MHZ Arduino
    setPaintingLightStatus(true);
  }
}

void setPaintingLightsOff() {
  if (getPaintingLightStatus()) {
    //SEND TO RF433MHZ Arduino
    setPaintingLightStatus(false);
  }
}

void togglePaintingLights() {
  bool tempStatus = !getPaintingLightStatus();
  //SEND TO RF433MHZ Arduino
  //transmitter.sendUnit(paintingLightsCode, tempStatus);
  setPaintingLightStatus(tempStatus);
}
