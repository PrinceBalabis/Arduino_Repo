IRsend irsend;

enum IRCodes
{
  IR_ON  = 0xFFE01F,
  IR_OFF  = 0xFF609F,
  IR_BRIGHTNESS_UP  = 0xFFA05F,
  IR_BRIGHTNESS_DOWN  = 0xFF20DF,
  IR_COLD  = 0xFFD02F,
  IR_WARM  = 0xFF9867,
  IR_WARMEST  = 0xFFA857,
  IR_FLASH  = 0xFFF00F,
  IR_STROBE  = 0xFFE817,
  IR_FADE  = 0xFFD827,
  IR_SMOOTH  = 0xFFC837
};

boolean powerState = 0;
int colorTemperatureState = 1;

static msg_t Thread2(void *arg) {
  while (1) {
    if(msgContent!= -1 && msgNode == -1){
      switch(msgContent)
      {
      case POWER_ON:
        setPowerState(1);
        break;
      case POWER_OFF:
        setPowerState(0);
        break;
      case POWER_TOGGLE:
        sendPowerToggle();
        Serial.println(F("Toggle lights"));
        break;
      case BRIGHTNESS_UP:
        sendCommand(IR_BRIGHTNESS_UP);
        break;
      case BRIGHTNESS_DOWN:
        sendCommand(IR_BRIGHTNESS_DOWN);
        break;
      case COLOR_COLD:
        sendCommand(IR_COLD);
        break;
      case COLOR_WARM:
        sendCommand(IR_WARM);
        break;
      case COLOR_WARMEST:
        sendCommand(IR_WARMEST);
        break;
      case COLOR_COLDER:
        setTemperatureColder();
        break;
      case COLOR_WARMER:
        setTemperatureWarmer();
        break;
      case MODE_FLASH:
        setTemperatureWarmer();
        break;
      case MODE_STROBE:
        setModeStrobe();
        break;
      case MODE_FADE:
        setModeFade();
        break;
      case MODE_SMOOTH:
        setModeSmooth();
        break;
      }
    }
    chThdSleepMilliseconds(20);
  }
  return 0;
}

void sendCommand(unsigned long command) 
{
  irsend.sendNEC(command, 32);
  msgContent = -1;
}

void setPowerState(boolean state){
  switch(state){
  case 1:
    sendCommand(IR_ON);
    powerState = 1;
    break;
  case 2:
    sendCommand(IR_OFF);
    powerState = 0;
    break;
  }
}

void sendPowerToggle(){
  powerState = !powerState;
  setPowerState(powerState);
}

void setColorTemperature(int temperature){
  if(temperature < 1){
    temperature = 1;
  }
  else if (temperature > 3){
    temperature = 3;
  }

  switch(temperature){
  case 1:
    sendCommand(IR_COLD);
    colorTemperatureState = 1;
    break;
  case 2:
    sendCommand(IR_WARM);
    colorTemperatureState = 2;
    break;
  case 3:
    sendCommand(IR_WARMEST);
    colorTemperatureState = 3;
    break;
  }
}

void setTemperatureColder(){
  setColorTemperature(colorTemperatureState-1);
}

void setTemperatureWarmer(){
  setColorTemperature(colorTemperatureState+1);
}

void setModeFlash(){
  sendCommand(IR_FLASH);
}

void setModeStrobe(){
  sendCommand(IR_STROBE);
}

void setModeFade(){
  sendCommand(IR_FADE);
}

void setModeSmooth(){
  sendCommand(IR_SMOOTH);
}





