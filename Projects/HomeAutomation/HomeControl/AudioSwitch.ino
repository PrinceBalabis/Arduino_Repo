void audioSwitchSetup() {
  DDRD |= (1 << 2); // Set pin 2 as output
  AUDIO_SWITCH_SPEAKER; // Set pin 2 to LOW and make it to speaker as default
}

void toggleAudioSwitch() {
              Serial.print(F("sdfgsdfg"));

  if (PIND & (1 << 2)) { // Switch is HIGH/Headset - So toggle pin LOW/Speaker
    AUDIO_SWITCH_SPEAKER;
  } else { // Switch is LOW/Speaker - So toggle pin HIGH/Headset
    AUDIO_SWITCH_HEADSET;
  }
}

void setAudioSwitchSpeaker() {
  AUDIO_SWITCH_SPEAKER;
}

void setAudioSwitchHeadset() {
  AUDIO_SWITCH_HEADSET;
}
