
// Decode message
void decodeMessage(uint16_t *pmsgSender, unsigned char *pmsgType, int32_t *pmsgContent) {
  switch (*pmsgType) {
    case typeCommand: // If its a simple command
      switch (*pmsgContent) {
        case cmdToggleLights:
          toggleLights();
          Serial.println(F("Toggled lights"));
          break;
        case cmdSetLightsOn:
          setMainLights(true);
          Serial.println(F("Turned lights on"));
          break;
        case cmdSetLightsOff:
          setMainLights(false);
          Serial.println(F("Turned lights off"));
          break;
      }
      break;
    case typeAsk: // If its a question
      switch (*pmsgContent) {
        case cmdGetLightsStatus:
          homeNetwork.respondToQuestion(*pmsgSender, mainLightsStatus);
          Serial.println(F("Main Lights Status question"));
          break;
      }
      break;
  }
}

