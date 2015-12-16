NewRemoteTransmitter transmitter(15303606, 7, 260, 2);

// Used for testing new units
//void setRemoteSwitch(uint8_t unit, boolean state){
//  transmitter.sendUnit(unit, state);
//}

////////////////////////////////////////////////////////////////////////////////

bool getPaintingLightStatus() {
  return EEPROM.read(EEPROM_PAINTINGLIGHTS);
}

void setPaintingLightStatus(bool status) {
  EEPROM.write(EEPROM_PAINTINGLIGHTS, status);
}

void setPaintingLightsOn() {
  if (!getPaintingLightStatus()) {
    transmitter.sendUnit(PAINTINGLIGHTS_433MHZ_CODE, true);
    setPaintingLightStatus(true);
  }
}

void setPaintingLightsOff() {
  if (getPaintingLightStatus()) {
    transmitter.sendUnit(PAINTINGLIGHTS_433MHZ_CODE, false);
    setPaintingLightStatus(false);
  }
}

void togglePaintingLights() {
  if (getPaintingLightStatus()) {
    transmitter.sendUnit(PAINTINGLIGHTS_433MHZ_CODE, 0);
    setPaintingLightStatus(0);
    Serial.println(F("Off"));

  } else {
    transmitter.sendUnit(PAINTINGLIGHTS_433MHZ_CODE, 1);
    setPaintingLightStatus(1);
    Serial.println(F("On"));

  }
}
