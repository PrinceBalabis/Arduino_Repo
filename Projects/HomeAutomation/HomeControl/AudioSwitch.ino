void audioSwitchSetup() {
  //pinMode(2, OUTPUT);
  //digitalWrite(2, LOW);
  DDRD = (1 << 2); // Set pin 2 as output
  //AUDIO_SWITCH_SPEAKER; // Set pin 2 to LOW and make it to speaker as default
}

void toggleAudioSwitch() {
  if (AUDIO_SWITCH_GET_MODE) { // Switch is HIGH/Headset - So toggle pin LOW/Speaker
    AUDIO_SWITCH_SPEAKER;
    //digitalWrite(2, LOW);
    Serial.println("Set to Speaker");
  } else { // Switch is LOW/Speaker - So toggle pin HIGH/Headset
    AUDIO_SWITCH_HEADSET;
    //digitalWrite(2, HIGH);
    Serial.println("Set to Headset");
  }
}

void setAudioSwitchSpeaker() {
  AUDIO_SWITCH_SPEAKER;
}

void setAudioSwitchHeadset() {
  AUDIO_SWITCH_HEADSET;
}
