//------------------------------------------------------------------------------
// Thread 1
// Ceiling lights variable

int ceilingLightsState = 0;

void initLights(){
  // Setup ceiling lights relay pin
  pinMode(ceilingLightsPin, OUTPUT);
}

void setLightsOn(){
  ceilingLightsState = 1;
  digitalWrite(ceilingLightsPin, ceilingLightsState);
  Serial.println("Turned on lights");
}

void setLightsOff(){
  ceilingLightsState = 0;
  digitalWrite(ceilingLightsPin, ceilingLightsState);
  Serial.println("Turned off lights");
}

void toggleLights(){
  ceilingLightsState = !ceilingLightsState;
  digitalWrite(ceilingLightsPin, ceilingLightsState);
  Serial.println("Toggled lights");
}
