

// Hold power button for 1 second to run the nBIRPower command
void sendPowerCommand() {
  currentTimer = millis();
  previousTimer = currentTimer;
  serialPrintln("Hold power button 0,5 sec");
  while (getKeyState() != RELEASED) {
    if ((millis() - previousTimer) >= 500) {
      sendCommand(nBIRPower);
      serialPrintln("Power button was held for 1 sec, sent nBIRPower command");
      break;
    }
  }
}

void sendUpVolCommand() {
  currentTimer = millis();
  if ((currentTimer - previousTimer) >= 60) {
    sendCommand(nBIRUpVolume);
    previousTimer = currentTimer; // Save last time volume increase
    serialPrintln("Sent nBIRUpVolume command");
  }
}

void sendDownVolCommand() {
  currentTimer = millis();
  if ((currentTimer - previousTimer) >= 60) {
    sendCommand(nBIRDownVolume);
    previousTimer = currentTimer; // Save last time volume decrease
    serialPrintln("Sent nBIRDownVolume command");
  }
}

void sendMuteCommand() {
  sendCommand(nBIRMute);
  previousBtnChosen = nBMuteButton;
  serialPrintln("Sending nBIRMute command");
}

void sendCommand(unsigned long command) {
  irsend.sendNEC(command, 32);
}
