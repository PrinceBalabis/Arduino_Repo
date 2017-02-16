static bool pcPowerSwitchStatus = false;

void pcPowerSetup()
{
  PC_POWER_SWITCH_INIT; // Set pin as output
  PC_POWER_SWITCH_OFF; // Set pin to LOW
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
  PC_POWER_SWITCH_ON; // Set pin to HIGH
  nilThdSleepMilliseconds(50); // Give enough time for PC to start
  //digitalWrite(pcPowerPin, false);
  PC_POWER_SWITCH_OFF; // Set pin to LOW
}

