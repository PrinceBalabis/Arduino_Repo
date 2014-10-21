// This function is called whenever you want to turn the lights on or off
// Send "1" to turn the lights on, send "0" to turn the lights off
void setLight(int setting) {
  digitalWrite(lightSwitchPin, setting);
}
