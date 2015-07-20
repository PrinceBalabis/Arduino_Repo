NewRemoteTransmitter transmitter(15303606, 7, 260, 4);

boolean paintingLightsStatus = false;
boolean speakerPowerStatus = false;

//void setRemoteSwitch(uint8_t unit, boolean state){
//  transmitter.sendUnit(unit, state);
//}

void setPaintingLightsOn(){
  paintingLightsStatus = 1;
  transmitter.sendUnit(paintingLightsCode, paintingLightsStatus);
}

void setPaintingLightsOff(){
  paintingLightsStatus = 0;
  transmitter.sendUnit(paintingLightsCode, paintingLightsStatus);
}

void togglePaintingLights(){
  paintingLightsStatus = !paintingLightsStatus;
  transmitter.sendUnit(paintingLightsCode, paintingLightsStatus);
}

void setSpeakerPowerOn(){
  speakerPowerStatus = 1;
  transmitter.sendUnit(speakerCode, speakerPowerStatus);
}

void setSpeakerPowerOff(){
  speakerPowerStatus = 0;
  transmitter.sendUnit(speakerCode, speakerPowerStatus);
}

void toggleSpeakerPower(){
  speakerPowerStatus = !speakerPowerStatus;
  transmitter.sendUnit(speakerCode, speakerPowerStatus);
}
