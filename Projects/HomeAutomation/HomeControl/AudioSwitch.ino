void audioSwitchSetup() {
  //pinMode(2, OUTPUT);
  //digitalWrite(2, LOW);
  AUDIO_SWITCH_INIT; // Set pin 2 as output
  AUDIO_SWITCH_SPEAKER; // Set pin 2 to LOW and make it to speaker as default
}

bool toggleAudioSwitch() {
  bool sent = false;
  if (AUDIO_SWITCH_GET_MODE) {  // Headset = true, Speaker = false
    // Switch to Speaker
    //sent = homeNetwork.sendCommand(HOME_SPEAKER_ID, HOME_SPEAKER_CMD_MODE_PC);
    //if (sent) {
      //nilThdSleepMilliseconds(100); // Some delay so the extremely uncomfortable noise from speaker wont be heard.
      setAudioSwitchSpeaker();
    //}
  } else {
    // Switch to Headset
    //sent = homeNetwork.sendCommand(HOME_SPEAKER_ID, HOME_SPEAKER_CMD_MODE_LINEIN);
    //if (sent) {
      //nilThdSleepMilliseconds(100); // Some delay so the extremely uncomfortable noise from speaker wont be heard.
      setAudioSwitchHeadset();
    //}
  }
  return sent;
}

void setAudioSwitchSpeaker() {
  AUDIO_SWITCH_SPEAKER;
  Serial.println(F("Setting Audio Switch to Speaker"));
}

void setAudioSwitchHeadset() {
  AUDIO_SWITCH_HEADSET;
  Serial.println(F("Setting Audio Switch to Headset"));
}
