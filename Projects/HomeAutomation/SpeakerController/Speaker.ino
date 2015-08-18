// Instance of the IRsend class
IRsend irsend;
boolean speakerMuteStatus = 0;

bool getSpeakerPowerSwitchStatus() {
  int32_t speakerPowerSwitchStatus = 0;
  homeNetwork.sendQuestion(HOME_RF433MHZ_ID, HOME_RF433MHZ_QSN_SPEAKER_POWER_STATUS, &speakerPowerSwitchStatus);
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
    homeNetwork.sendCommand(HOME_RF433MHZ_ID, HOME_RF433MHZ_CMD_SPEAKERPOWER_ON);
    nilThdSleepMilliseconds(1000); // Wait for 433 MHz controller to turn on speaker power switch
    sendSpeakerCommand(speakerIRPower); // Send IR power command
    Serial.println(F("Turning on speaker"));
  }
}

void sendSpeakerPowerOffCommand(void) {
  if (getSpeakerPowerSwitchStatus())
  {
    homeNetwork.sendCommand(HOME_RF433MHZ_ID, HOME_RF433MHZ_CMD_SPEAKERPOWER_OFF);
    speakerMuteStatus = 0;
    Serial.println(F("Turning off speaker"));
  }
}

void sendSpeakerUpVolCommand(void)
{
  for (int i = 0; i < 2 ; i++)
    sendSpeakerCommand(speakerIRUpVolume);
  speakerMuteStatus = false;
  Serial.println(F("Increased volume level"));
}

void sendSpeakerDownVolCommand(void)
{
  for (int i = 0; i < 2 ; i++)
    sendSpeakerCommand(speakerIRDownVolume);
  speakerMuteStatus = false;
  Serial.println(F("Dropped volume level"));
}

void toggleSpeakerMuteCommand(void)
{
  if (getSpeakerPowerSwitchStatus()) {
    sendSpeakerCommand(speakerIRMute);
    speakerMuteStatus = !speakerMuteStatus;
    Serial.print(F("Toggling mute: "));
    Serial.println(speakerMuteStatus);
  }
}

void sendSpeakerMuteOnCommand(void)
{
  if (!speakerMuteStatus && getSpeakerPowerSwitchStatus())
  {
    sendSpeakerCommand(speakerIRMute);
    speakerMuteStatus = 1;
    Serial.println(F("Sent mute on command to speaker"));
  }
}

void sendSpeakerMuteOffCommand(void)
{
  if (speakerMuteStatus && getSpeakerPowerSwitchStatus())
  {
    sendSpeakerCommand(speakerIRMute);
    speakerMuteStatus = 0;
    Serial.println(F("Sending mute off command to speaker!"));
  }
}

void toggleSpeakerModeCommand(void)
{
  if (getSpeakerPowerSwitchStatus()) {
    Serial.print(F("Toggling mode: "));
    if (!getSpeakerModeStatus()) { // If its Line-In mode, toggle to PC
      setSpeakerModePCCommand();
    } else { // If its PC mode, toggle to Line-In
      setSpeakerModeLineInCommand();
    }
  }
}

void setSpeakerModePCCommand(void)
{
  if (getSpeakerPowerSwitchStatus() && !getSpeakerModeStatus()) {
    sendSpeakerCommand(speakerIRMode);
    nilThdSleepMilliseconds(200);
    sendSpeakerCommand(speakerIRRight);
    nilThdSleepMilliseconds(200);
    sendSpeakerCommand(speakerIROK);
    setSpeakerModeStatus(1);
    Serial.println(F("Set to PC Mode"));
  }
}

void setSpeakerModeLineInCommand(void)
{
  if (getSpeakerPowerSwitchStatus() && getSpeakerModeStatus()) {
    sendSpeakerCommand(speakerIRMode);
    nilThdSleepMilliseconds(200);
    sendSpeakerCommand(speakerIRLeft);
    nilThdSleepMilliseconds(200);
    sendSpeakerCommand(speakerIROK);
    setSpeakerModeStatus(0);
    Serial.println(F("Set to Line In Mode"));
  }
}

// Will return 0 if Line in, 1 if PC
bool getSpeakerModeStatus() {
  return EEPROM.read(speakerModeAddress);
}

void setSpeakerModeStatus(bool status) {
  EEPROM.write(speakerModeAddress, status);
}


void sendSpeakerCommand(unsigned long command)
{
  irsend.sendNEC(command, 32);
}

