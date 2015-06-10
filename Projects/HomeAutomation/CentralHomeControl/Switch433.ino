NewRemoteTransmitter transmitter(15303606, 6, 260, 4);

boolean diningTableSwitch = false;

void setRemoteSwitch(uint8_t unit, boolean state){
  transmitter.sendUnit(unit, state);
}

void setDiningTableSwitchOn(){
  diningTableSwitch = 1;
  transmitter.sendUnit(lightDiningTable, diningTableSwitch);
}

void setDiningTableSwitchOff(){
  diningTableSwitch = 0;
  transmitter.sendUnit(lightDiningTable, diningTableSwitch);
}

void toggleDiningTableSwitch(){
  diningTableSwitch = !diningTableSwitch;
  transmitter.sendUnit(lightDiningTable, diningTableSwitch);
}
