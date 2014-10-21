void serialSetup() {
  if (serialEnabled) {
    Serial.begin(9600);
  }
}

void serialPrintln(String printString) {
  if (serialEnabled) {
    Serial.println(printString);
  }
}
