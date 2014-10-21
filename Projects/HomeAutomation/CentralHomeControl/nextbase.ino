

// Hold power button for 1 second to run the power command
void sendPowerCommand() {
  currentTimer = millis();
  previousTimer = currentTimer;
  serialPrintln("Hold power button 1 sec");
  while (getKeyState() != RELEASED) {
    if ((millis() - previousTimer) >= 1000) {
      sendCommand(power);
      serialPrintln("Power button was held for 1 sec, sent power command");
      break;
    }
  }
}

void sendUpVolCommand() {
  currentTimer = millis();
  if ((currentTimer - previousTimer) >= 60) {
    incVolume(1);
    previousTimer = currentTimer; // Save last time volume increase
    serialPrintln("Sent upVolume command");
  }
}

void sendDownVolCommand() {
  currentTimer = millis();
  if ((currentTimer - previousTimer) >= 60) {
    incVolume(1);
    previousTimer = currentTimer; // Save last time volume decrease
    serialPrintln("Sent downVolume command");
  }
}

void sendMuteCommand() {
  sendCommand(mute);
  previousBtnChosen = muteButton;
  serialPrintln("Sending mute command");
}

void sendCommand(unsigned long command) {
  irsend.sendNEC(command, 32);
}

void incVolume(int volValue) {
  if (volValue > 30) {
    volValue = 30;
  }
  for (int i = 0; i < volValue; i++) {
    sendCommand(upVolume);
  }
}

void decVolume(int volValue) {
  if (volValue > 30) {
    volValue = 30;
  }
  for (int i = 0; i < volValue; i++) {
    sendCommand(downVolume);
  }
}
