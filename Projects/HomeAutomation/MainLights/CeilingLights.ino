//------------------------------------------------------------------------------
// Ceiling lights functions

int mainLightsState = 0;

void initLights(){
  // Setup ceiling lights relay pin
  pinMode(mainLightsPin, OUTPUT);
}

void setLightsOn(){
  mainLightsState = 1;
  digitalWrite(mainLightsPin, mainLightsState);
  Serial.println("Turned on lights");
}

void setLightsOff(){
  mainLightsState = 0;
  digitalWrite(mainLightsPin, mainLightsState);
  Serial.println("Turned off lights");
}

void toggleLights(){
  mainLightsState = !mainLightsState;
  digitalWrite(mainLightsPin, mainLightsState);
  Serial.println("Toggled lights");
}
