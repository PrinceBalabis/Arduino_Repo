SoftwareSerial port(2,3);
EasyVR easyvr(port);

enum Groups
{
  GROUP_0  = 0,
  GROUP_1  = 1,
};


enum Group0 
{
  G0_JARVIS = 0,
};

enum Group1 
{
  G1_MAIN_ROOM = 0,
  G1_MAIN_LIGHTS = 1,
  G1_MAIN_ROOM_LIGHTS = 2,
  G1_DINING_TABLE = 3,
  G1_TABLE = 4,
  G1_TABLE_LIGHTS = 5,
  G1_DINING_TABLE_LIGHTS = 6,
  G1_SPEAKERS = 7,
  G1_SPEAKER = 8,
  G1_SLEEP_MODE = 9,
  G1_ENTER_SLEEP_MODE = 10,
  G1_IM_AWAKE = 11,
  G1_NOTHING = 12,
  G1_NEVER_MIND = 13,
};

EasyVRBridge bridge;

int8_t group, idx;

static msg_t Thread2(void *arg) {
  port.begin(9600);

  while (!easyvr.detect())
  {
    Serial.println("EasyVR not detected!");
    chThdSleepMilliseconds(1000);
  }

  easyvr.setPinOutput(EasyVR::IO1, LOW);
  Serial.println("EasyVR detected!");
  easyvr.setTimeout(10);
  easyvr.setLanguage(0);

  group = EasyVR::TRIGGER; //<-- start group (customize)

  while (1) {
    easyvr.setPinOutput(EasyVR::IO1, HIGH); // LED on (listening)

    Serial.print("Say a command in Group ");
    Serial.println(group);
    easyvr.recognizeCommand(group);

    do
    {
      // can do some processing while waiting for a spoken command
      chThdSleepMilliseconds(5);
    }
    while (!easyvr.hasFinished());

    easyvr.setPinOutput(EasyVR::IO1, LOW); // LED off
    idx = easyvr.getWord();
    if (idx >= 0)
    {
      // built-in trigger (ROBOT)
      // group = GROUP_X; <-- jump to another group X
      //      return;
    }
    idx = easyvr.getCommand();
    if (idx >= 0)
    {
      // print debug message
      uint8_t train = 0;
      char name[32];
      Serial.print("Command: ");
      Serial.print(idx);
      if (easyvr.dumpCommand(group, idx, name, train))
      {
        Serial.print(" = ");
        Serial.println(name);
      }
      else
        Serial.println();
      easyvr.playSound(0, EasyVR::VOL_FULL);
      // perform some action
      action();
    }
    else // errors or timeout
    {
      if (easyvr.isTimeout()){
        Serial.println("Timed out, try again...");
        group = EasyVR::TRIGGER; //<-- start group (customize)
      }
      int16_t err = easyvr.getError();
      if (err >= 0)
      {
        Serial.print("Error ");
        Serial.println(err, HEX);
        easyvr.playSound(0, EasyVR::VOL_FULL);
        easyvr.playSound(0, EasyVR::VOL_FULL);
      }
    }

    chThdSleepMilliseconds(20);
  }
  return 0;
}


void action()
{
  switch (group)
  {
  case GROUP_0:
    switch (idx)
    {
    case G0_JARVIS:
      // write your action code here
      // group = GROUP_X; <-- or jump to another group X for composite commands
      group = GROUP_1;
      break;
    }
    break;
  case GROUP_1:
    switch (idx)
    {
    case G1_MAIN_ROOM:
      toggleMainLights();
      group = GROUP_0;
      break;
    case G1_MAIN_LIGHTS:
      toggleMainLights();
      group = GROUP_0;
      break;
    case G1_MAIN_ROOM_LIGHTS:
      toggleMainLights();
      group = GROUP_0;
      break;
    case G1_DINING_TABLE:
      toggleDiningTableLights();
      group = GROUP_0;
      break;
    case G1_TABLE:
      toggleDiningTableLights();
      group = GROUP_0;
      break;
    case G1_TABLE_LIGHTS:
      toggleDiningTableLights();
      group = GROUP_0;
      break;
    case G1_DINING_TABLE_LIGHTS:
      toggleDiningTableLights();
      group = GROUP_0;
      break;
    case G1_SPEAKERS:
      toggleSpeakerPower();
      group = GROUP_0;
      break;
    case G1_SPEAKER:
      toggleSpeakerPower();
      group = GROUP_0;
      break;
    case G1_SLEEP_MODE:
      enterSleepMode();
      group = GROUP_0;
      break;
    case G1_ENTER_SLEEP_MODE:
      enterSleepMode();
      group = GROUP_0;
      break;
    case G1_IM_AWAKE:
      exitSleepMode();
      group = GROUP_0;
      break;
    case G1_NOTHING:
      group = GROUP_0;
      break;
    case G1_NEVER_MIND:
      group = GROUP_0;
      break;
    }
    break;
  }
}













