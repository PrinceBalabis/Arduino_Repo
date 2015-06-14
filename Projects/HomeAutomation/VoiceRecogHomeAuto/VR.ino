SoftwareSerial port(2, 3);
EasyVR easyvr(port);

//Groups and Commands
enum Groups
{
  GROUP_1  = 1,
  GROUP_2  = 2,
};

enum Group1
{
  G1_FRIDAY = 0,
};

enum Group2
{
  G2_ROOM = 0,
  G2_SPEAKER = 1,
  G2_PAINTINGS = 2,
  G2_IM_GOING_TO_BED = 3,
  G2_IM_AWAKE = 4,
  G2_FRIDAY = 5,
};

int8_t group, idx;

static msg_t Thread2(void *arg) {
  port.begin(9600);
  while (!easyvr.detect())
  {
    Serial.println("EasyVR not detected!");
    chThdSleepMilliseconds(1000);
  }
  Serial.println("EasyVR detected!");
  easyvr.changeBaudrate(38400); //Change baudrate to faster
  easyvr.setPinOutput(EasyVR::IO1, LOW);
  easyvr.setTimeout(10);
  easyvr.setLanguage(0);
  easyvr.setMicDistance(3);
  easyvr.setLevel(1);
  easyvr.setKnob(1);

  group = GROUP_1; //<-- start group (customize)

  while (1) {

    if (group == GROUP_1)
      easyvr.setPinOutput(EasyVR::IO1, LOW); // LED off (listening for code word)
    else if (group == GROUP_2)
      easyvr.setPinOutput(EasyVR::IO1, HIGH); // LED on (listening for command)

    Serial.print("Say a command in Group ");
    Serial.println(group);
    easyvr.recognizeCommand(group);

    do
    {
      // can do some processing while waiting for a spoken command
      chThdSleepMilliseconds(5);
    }
    while (!easyvr.hasFinished());

    //    idx = easyvr.getWord();
    //    if (idx >= 0)
    //    {
    //      // built-in trigger (ROBOT)
    //      // group = GROUP_X; <-- jump to another group X
    //      //      return;
    //    }
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
      // perform some action
      action();
    }
    else // errors or timeout
    {
      if (easyvr.isTimeout()) {
        Serial.println("Timed out, try again...");
        group = GROUP_1; //<-- start group (customize)
      }
      int16_t err = easyvr.getError();
      if (err >= 0)
      {
        Serial.print("Error ");
        Serial.println(err, HEX);
        if (group == GROUP_2)
          easyvr.playSound(3, EasyVR::VOL_DOUBLE);
        group = GROUP_1; //<-- start group (customize)
        easyvr.setLevel(5); //Make the trigger word harder to pick up
        easyvr.setKnob(4); //Make the trigger word harder to pick up
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
    case GROUP_1:
      switch (idx)
      {
        case G1_FRIDAY:
          // write your action code here
          // group = GROUP_X; <-- or jump to another group X for composite commands
          easyvr.playSound(2, EasyVR::VOL_DOUBLE);
          group = GROUP_2;
          easyvr.setLevel(1); //Make the actions easier to pick up
          easyvr.setKnob(1); //Make the actions easier to pick up
          break;
      }
      break;
    case GROUP_2:
      switch (idx)
      {
        case G2_ROOM:
          easyvr.playSound(1, EasyVR::VOL_DOUBLE);
          toggleMainLights();
          group = GROUP_1;
          break;
        case G2_SPEAKER:
          easyvr.playSound(1, EasyVR::VOL_DOUBLE);
          toggleSpeakerPower();
          group = GROUP_1;
          break;
        case G2_IM_GOING_TO_BED:
          easyvr.playSound(4, EasyVR::VOL_DOUBLE);
          enterSleepMode();
          group = GROUP_1;
          break;
        case G2_IM_AWAKE:
          easyvr.playSound(5, EasyVR::VOL_DOUBLE);
          exitSleepMode();
          group = GROUP_1;
          break;
        case G2_FRIDAY:
          // Do nothing here to stay in group 1
          easyvr.playSound(2, EasyVR::VOL_DOUBLE);
          break;
        case G2_PAINTINGS:
          easyvr.playSound(1, EasyVR::VOL_DOUBLE);
          togglePaintingLights();
          group = GROUP_1;
          break;
      }
      break;
  }
}

























