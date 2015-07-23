// Instance of the IRsend class
IRsend irsend;
boolean speakerMuteStatus = 0;

bool getSpeakerPowerSwitchStatus() {
  int32_t speakerPowerSwitchStatus = 0;
  homeNetwork.askSpeakerSwitchStatus(&speakerPowerSwitchStatus);
  return speakerPowerSwitchStatus;
}

void toggleSpeakerPower(void) {
  Serial.print(F("Toggling speaker power: "));
  if (getSpeakerPowerSwitchStatus())
  {
    sendSpeakerPowerOffCommand();
  }
  else
  {
    sendSpeakerPowerOnCommand();
  }
}

void sendSpeakerPowerOnCommand(void) {
  if (!getSpeakerPowerSwitchStatus())
  {
    homeNetwork.setSpeakerPowerSwitchOn();
    chThdSleepMilliseconds(1000); // Wait for 433 MHz controller to turn on speaker power switch
    sendSpeakerIRPowerCommand(); // Send IR power command
    Serial.println(F("Turning on speaker"));
  }
}

void sendSpeakerPowerOffCommand(void) {
  if (getSpeakerPowerSwitchStatus())
  {
    homeNetwork.setSpeakerPowerSwitchOff();
    speakerMuteStatus = 0;
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
    Serial.println(F("Incremential increase of volume level"));
  }
}

void sendSpeakerUpVolCommandOnce(void)
{
  for (int i = 0; i < 15 ; i++)
    sendSpeakerCommand(speakerIRUpVolume);
  Serial.println(F("Increased volume level a bunch"));
}

void sendSpeakerDownVolCommand(unsigned long previousTimer)
{
  unsigned long currentTimer = millis();
  if ((currentTimer - previousTimer) >= 60) {
    sendSpeakerCommand(speakerIRDownVolume);
    previousTimer = currentTimer; // Save last time volume decrease
    Serial.println(F("Incremential drop of volume level"));
  }
}

void sendSpeakerDownVolCommandOnce(void)
{
  for (int i = 0; i < 15 ; i++)
    sendSpeakerCommand(speakerIRDownVolume);
  Serial.println(F("Dropped volume level a bunch"));
}

void toggleSpeakerMuteCommand(void)
{
  if (getSpeakerPowerSwitchStatus()) {
    sendSpeakerCommand(speakerIRMute);
    Serial.println(F("Toggling mute"));
  }
}

void sendSpeakerMuteOnCommand(void)
{
  if (!speakerMuteStatus && getSpeakerPowerSwitchStatus())
  {
    sendSpeakerCommand(speakerIRMute);
    speakerMuteStatus = 1;
    Serial.println(F("Sent mute command to speaker"));
  }
}

void sendSpeakerMuteOffCommand(void)
{
  if (speakerMuteStatus && getSpeakerPowerSwitchStatus())
  {
    sendSpeakerCommand(speakerIRMute);
    speakerMuteStatus = 0;
    Serial.println(F("Sending mute command to speaker!"));
  }
}


void sendSpeakerCommand(unsigned long command)
{
  irsend.sendNEC(command, 32);
}

