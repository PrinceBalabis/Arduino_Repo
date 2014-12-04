RCSwitch switch433 = RCSwitch();

void switch433Setup(){
  switch433.enableTransmit(switch433TransmitterPin);
}

void send433Command(uint32_t command){
  switch433.send(command, 24);
}
