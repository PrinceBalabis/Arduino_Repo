/**
 * homeNetworkMessageReceived()
 * This function is executed automatically by the HomeNetwork Library when a message is received.
 */
void homeNetworkMessageReceived(uint16_t msgSender, unsigned char msgType, int32_t msgContent) {
  switch (msgType) {
        case HOME_TYPE_COMMAND: // If its a simple command
          switch (msgContent) {
            case HOME_SPEAKER_CMD_POWER_TOGGLE:
              executeCommand = HOME_SPEAKER_CMD_POWER_TOGGLE;
              chSemSignal(&cmdExSem);
              break;
            case HOME_SPEAKER_CMD_POWER_ON:
              executeCommand = HOME_SPEAKER_CMD_POWER_ON;
              chSemSignal(&cmdExSem);
              break;
            case HOME_SPEAKER_CMD_POWER_OFF:
              executeCommand = HOME_SPEAKER_CMD_POWER_OFF;
              chSemSignal(&cmdExSem);
              break;
            case HOME_SPEAKER_CMD_MUTE_TOGGLE:
              executeCommand = HOME_SPEAKER_CMD_MUTE_TOGGLE;
              chSemSignal(&cmdExSem);
              break;
            case HOME_SPEAKER_CMD_VOLUME_UP:
              executeCommand = HOME_SPEAKER_CMD_VOLUME_UP;
              chSemSignal(&cmdExSem);
              break;
            case HOME_SPEAKER_CMD_VOLUME_DOWN:
              executeCommand = HOME_SPEAKER_CMD_VOLUME_DOWN;
              chSemSignal(&cmdExSem);
              break;
            case HOME_SPEAKER_CMD_MODE_TOGGLE:
              executeCommand = HOME_SPEAKER_CMD_MODE_TOGGLE;
              chSemSignal(&cmdExSem);
              break;
          }
          break;
        case HOME_TYPE_QUESTION: // If its a question
          //Questions here
          break;
      }
}
