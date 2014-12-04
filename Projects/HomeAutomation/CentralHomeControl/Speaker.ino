// Instance of the IRsend class
IRsend irsend;
boolean speakerState = 0;
boolean speakerMuteState = 0;

void toggleSpeakerPower(void){
  if(speakerState)
  {
    sendSpeakerPowerOffCommand();
  }
  else
  {
    sendSpeakerPowerOnCommand();

  }
}

void sendSpeakerPowerOnCommand(void){
  if(!speakerState)
  {
    send433Command(speaker433PowerOn); // Toggle 433 MHz switch for speaker on
    chThdSleepMilliseconds(200); // Wait for 433 MHz switch to turn on speaker
    sendSpeakerIRPowerCommand(); // Send IR power command
    speakerState = 1;
  }
}

void sendSpeakerPowerOffCommand(void){
  if(speakerState)
  {
    send433Command(speaker433PowerOff);
    speakerState = 0;
    speakerMuteState = 0;
  }
}

void sendSpeakerIRPowerCommand(void) 
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
  for(int i = 0; i < 15 ; i++)
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
  for(int i = 0; i < 15 ; i++)
    sendSpeakerCommand(nBIRDownVolume);
  Serial.println(F("Sent nBIRDownVolume command once"));
}

void toggleSpeakerMuteCommand(void) 
{
  sendSpeakerCommand(nBIRMute);
  Serial.println(F("Sending mute command to speaker!"));
}

void sendSpeakerMuteOnCommand(void) 
{
  if(!speakerMuteState && speakerState) 
  {
    sendSpeakerCommand(nBIRMute);
    speakerMuteState = 1;
    Serial.println(F("Sending mute command to speaker!"));
  }
}

void sendSpeakerMuteOffCommand(void) 
{
  if(speakerMuteState && speakerState) 
  {
    sendSpeakerCommand(nBIRMute);
    speakerMuteState = 0;
    Serial.println(F("Sending mute command to speaker!"));
  }
}


void sendSpeakerCommand(unsigned long command) 
{
  irsend.sendNEC(command, 32);
}











