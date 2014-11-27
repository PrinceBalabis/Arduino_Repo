// Instance of the IRsend class
IRsend irsend;

// Hold power button for 1 second to run the nBIRPower command
void sendSpeakerPowerCommand(void) 
{
  sendSpeakerCommand(nBIRPower);
  Serial.println(F("Sent nBIRPower command"));
}

void sendSpeakerUpVolCommand(unsigned long previousTimer) 
{
  unsigned long currentTimer = millis();
  if ((currentTimer - previousTimer) >= 60) {
    sendSpeakerCommand(nBIRUpVolume);
    previousTimer = currentTimer; // Save last time volume increase
    Serial.println(F("Sent nBIRUpVolume command"));
  }
}

void sendSpeakerUpVolCommandOnce(void) 
{
  for(int i = 0; i < 10 ; i++)
    sendSpeakerCommand(nBIRUpVolume);
  Serial.println(F("Sent nBIRUpVolume command"));
}

void sendSpeakerDownVolCommand(unsigned long previousTimer) 
{
  unsigned long currentTimer = millis();
  if ((currentTimer - previousTimer) >= 60) {
    sendSpeakerCommand(nBIRDownVolume);
    previousTimer = currentTimer; // Save last time volume decrease
    Serial.println(F("Sent nBIRDownVolume command once"));
  }
}

void sendSpeakerDownVolCommandOnce(void) 
{
  for(int i = 0; i < 10 ; i++)
    sendSpeakerCommand(nBIRDownVolume);
  Serial.println(F("Sent nBIRDownVolume command once"));
}

void sendSpeakerMuteCommand(void) 
{
  sendSpeakerCommand(nBIRMute);
  Serial.println(F("Sending nBIRMute command"));
}

void sendSpeakerCommand(unsigned long command) 
{
  irsend.sendNEC(command, 32);
}


