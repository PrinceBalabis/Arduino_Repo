NewRemoteTransmitter transmitter(15303606, 6, 260,  3);

boolean diningTableSwitch = false;

void setRemoteSwitch(uint8_t unit, boolean state){
  transmitter.sendUnit(unit, state);
}

void toggleFoodLampSwitch(){
  diningTableSwitch = !diningTableSwitch;
  transmitter.sendUnit(lightDiningTable, diningTableSwitch);
}
