int getKeyState() {
  keypad.getKey(); // Update key
  return keypad.getState();
}

void clearButton() {
  currentTimer = 0; // Clear currentTimer
  previousTimer = 0;
  previousBtnChosen = 0;
  serialPrintln("Button is released");
}
