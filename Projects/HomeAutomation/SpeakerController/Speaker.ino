// Instance of the IRsend class
IRsend irsend;
boolean speakerMuteState = 0;
boolean speakerState = 0;

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
    setRemoteSwitch(2, true); // Toggle 433 MHz switch for speaker on
    //chThdSleepMilliseconds(50); // Wait for 433 MHz switch to turn on speaker
    sendSpeakerIRPowerCommand(); // Send IR power command
    speakerState = 1;
    Serial.println(F("Turning on speaker"));
  }
}

void sendSpeakerPowerOffCommand(void){
  if(speakerState)
  {
    setRemoteSwitch(2, false);
    speakerState = 0;
    speakerMuteState = 0;
    Serial.println(F("Turning off speaker"));
  }
}

void sendSpeakerIRPowerCommand(void) 
{
  sendSpeakerCommand(speakerIRPower);
}

void sendSpeakerUpVolCommand(unsigned long previousTimer) 
{
  unsigned long currentTimer = millis();
  if ((currentTimer - previousTimer) >= 60) {
    sendSpeakerCommand(speakerIRUpVolume);
    previousTimer = currentTimer; // Save last time volume increase
    Serial.println(F("Sent nBIRUpVolume command"));
  }
}

void sendSpeakerUpVolCommandOnce(void) 
{
  for(int i = 0; i < 15 ; i++)
    sendSpeakerCommand(speakerIRUpVolume);
  Serial.println(F("Sent nBIRUpVolume command"));
}

void sendSpeakerDownVolCommand(unsigned long previousTimer) 
{
  unsigned long currentTimer = millis();
  if ((currentTimer - previousTimer) >= 60) {
    sendSpeakerCommand(speakerIRDownVolume);
    previousTimer = currentTimer; // Save last time volume decrease
    Serial.println(F("Sent nBIRDownVolume command once"));
  }
}

void sendSpeakerDownVolCommandOnce(void) 
{
  for(int i = 0; i < 15 ; i++)
    sendSpeakerCommand(speakerIRDownVolume);
  Serial.println(F("Sent nBIRDownVolume command once"));
}

void toggleSpeakerMuteCommand(void) 
{
  sendSpeakerCommand(speakerIRMute);
  Serial.println(F("Sending mute command to speaker!"));
}

void sendSpeakerMuteOnCommand(void) 
{
  if(!speakerMuteState && speakerState) 
  {
    sendSpeakerCommand(speakerIRMute);
    speakerMuteState = 1;
    Serial.println(F("Sending mute command to speaker!"));
  }
}

void sendSpeakerMuteOffCommand(void) 
{
  if(speakerMuteState && speakerState) 
  {
    sendSpeakerCommand(speakerIRMute);
    speakerMuteState = 0;
    Serial.println(F("Sending mute command to speaker!"));
  }
}


void sendSpeakerCommand(unsigned long command) 
{
  irsend.sendNEC(command, 32);
}

