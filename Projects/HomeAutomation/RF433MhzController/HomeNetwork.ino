/**
 * homeNetworkMessageReceived()
 * This function is executed automatically by the HomeNetwork Library when a message is received.
 */
void homeNetworkMessageReceived(uint16_t msgSender, unsigned char msgType, int32_t msgContent) {
  switch (msgType) {
    case HOME_TYPE_COMMAND: // If its a simple command
      switch (msgContent) {
        case HOME_RF433MHZ_CMD_PAINTINGLIGHTS_ON:
          setPaintingLightsOn();
          Serial.println(F("Turned Painting Lights on"));
          break;
        case HOME_RF433MHZ_CMD_PAINTINGLIGHTS_OFF:
          setPaintingLightsOff();
          Serial.println(F("Turned Painting Lights off"));
          break;
        case HOME_RF433MHZ_CMD_PAINTINGLIGHTS_TOGGLE:
          togglePaintingLights();
          Serial.println(F("Toggled Painting Lights"));
          break;
        case HOME_RF433MHZ_CMD_SPEAKERPOWER_ON:
          setSpeakerPowerSwitchOn();
          Serial.println(F("Turned Speaker on"));
          break;
        case HOME_RF433MHZ_CMD_SPEAKERPOWER_OFF:
          setSpeakerPowerSwitchOff();
          Serial.println(F("Turned Speaker off"));
          break;
        case HOME_RF433MHZ_CMD_SPEAKERPOWER_TOGGLE:
          toggleSpeakerPowerSwitch();
          Serial.println(F("Toggled Speaker"));
          break;
      }
      break;
    case HOME_TYPE_QUESTION: // If its a question
      switch (msgContent) {
        case HOME_RF433MHZ_QSN_PAINTINGLIGHTS_STATUS:
          homeNetwork.respondToQuestion(msgSender, getPaintingLightStatus());
          Serial.println(F("Answered Painting lights status"));
          break;
        case HOME_RF433MHZ_QSN_SPEAKER_POWER_STATUS:
          homeNetwork.respondToQuestion(msgSender, getSpeakerPowerSwitchStatus());
          Serial.println(F("Answered Speaker status"));
          break;
      }
      break;
  }
}
