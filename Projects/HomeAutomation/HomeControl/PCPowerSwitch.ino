bool pcPowerSwitchStatus = false;

void pcPowerSetup()
{
  PC_POWER_SWITCH_INIT; // Set pin 6 as output
  PC_POWER_SWITCH_OFF; // Set pin 6 to LOW
  //pinMode(pcPowerPin, OUTPUT);
  //digitalWrite(pcPowerPin, LOW);
}

void togglePCPowerSwitch()
{
  //pcPowerSwitchStatus = !pcPowerSwitchStatus;
  //digitalWrite(pcPowerPin, pcPowerSwitchStatus);
  PC_POWER_SWITCH_TOGGLE;
}

void setPCPowerSwitchOnMomentarily()
{
  //digitalWrite(pcPowerPin, true);
  PC_POWER_SWITCH_ON; // Set pin 6 to HIGH
  nilThdSleepMilliseconds(100); // Give enough time for PC to start
  //digitalWrite(pcPowerPin, false);
  PC_POWER_SWITCH_OFF; // Set pin 6 to LOW
}

