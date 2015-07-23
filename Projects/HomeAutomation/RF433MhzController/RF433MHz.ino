NewRemoteTransmitter transmitter(15303606, 7, 260, 2);

//void setRemoteSwitch(uint8_t unit, boolean state){
//  transmitter.sendUnit(unit, state);
//}

////////////////////////////////////////////////////////////////////////////////

bool getPaintingLightStatus() {
  return EEPROM.read(paintingLightsAddress);
}

void setPaintingLightStatus(bool status) {
  EEPROM.write(paintingLightsAddress, status);
}

void setPaintingLightsOn() {
  if (!getPaintingLightStatus()) {
    transmitter.sendUnit(paintingLightsCode, true);
    setPaintingLightStatus(true);
  }
}

void setPaintingLightsOff() {
  if (getPaintingLightStatus()) {
    transmitter.sendUnit(paintingLightsCode, false);
    setPaintingLightStatus(false);
  }
}

void togglePaintingLights() {
  bool tempStatus = !getPaintingLightStatus();
  transmitter.sendUnit(paintingLightsCode, tempStatus);
  setPaintingLightStatus(tempStatus);
}

////////////////////////////////////////////////////////////////////////////////

bool getSpeakerPowerSwitchStatus() {
  return EEPROM.read(speakerPowerSwitchAddress);
}

bool setSpeakerPowerSwitchStatus(bool status) {
  EEPROM.write(speakerPowerSwitchAddress, status);
}

void setSpeakerPowerSwitchOn() {
  if (!getSpeakerPowerSwitchStatus()) {
    transmitter.sendUnit(speakerCode, true);
    setSpeakerPowerSwitchStatus(true);
  }
}

void setSpeakerPowerSwitchOff() {
  if (getSpeakerPowerSwitchStatus()) {
    transmitter.sendUnit(speakerCode, false);
    setSpeakerPowerSwitchStatus(false);
  }
}

void toggleSpeakerPowerSwitch() {
  bool speakerPowerSwitchStatus = !getSpeakerPowerSwitchStatus();
  transmitter.sendUnit(speakerCode, speakerPowerSwitchStatus);
  setSpeakerPowerSwitchStatus(speakerPowerSwitchStatus);
}
