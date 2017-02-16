int8_t group, idx;

// This is the only function in this page that should be customized
void action()
{
  switch (group)
  {
    case GROUP_1:
      switch (idx)
      {
        case G1_JARVIS:
          // write your action code here
          // group = GROUP_X; <-- or jump to another group X for composite commands
          easyvr.playSound(17, EasyVR::VOL_DOUBLE);
          group = GROUP_2;
          easyvr.setLevel(1); //Make the actions easier to pick up
          easyvr.setKnob(1); //Make the actions easier to pick up
          break;
      }
      break;
    case GROUP_2:
      switch (idx)
      {
        case G2_MAIN_LIGHTS:
          executeHomeNetworkCommand(HOME_MAINLIGHTS_ID, HOME_MAINLIGHTS_CMD_MAINLIGHTS_TOGGLE);
          group = GROUP_1;
          break;
      case G2_PAINTINGS:
        // write your action code here
        group = GROUP_1;
          break;
      case G2_JARVIS:
        // write your action code here
        group = GROUP_1;
          break;
    }
    break;
}
}










NIL_WORKING_AREA(virtualIntelligence, 100); // bytes seems to work fine even with Home Network debug on
NIL_THREAD(VirtualIntelligence, arg)
{
  Serial.println("Started Virtual Intelligence Thread");

  port.begin(9600);
  while (!easyvr.detect())
  {
    Serial.println("EasyVR not detected!");
    nilThdSleepMilliseconds(1000);
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

  while (TRUE) {

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
      nilThdSleepMilliseconds(5);
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

    nilThdSleepMilliseconds(20);
  }

}

