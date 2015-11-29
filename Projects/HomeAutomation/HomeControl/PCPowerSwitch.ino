bool pcPowerSwitchStatus = false;

void pcPowerSetup()
{
  DDRD = (1 << 6); // Set pin 6 as output
  PC_POWER_SWITCH_OFF; // Set pin 6 to LOW
  //pinMode(pcPowerPin, OUTPUT);
  //digitalWrite(pcPowerPin, LOW);
}

void togglePCPowerSwitch()
{
  //pcPowerSwitchStatus = !pcPowerSwitchStatus;
  //digitalWrite(pcPowerPin, pcPowerSwitchStatus);
  // Read status of PC power switch
  if (PIND & (1 << 6)) { // Switch is on - So toggle pin off
    PC_POWER_SWITCH_OFF;
  } else { // Switch is off - So toggle pin on
    PC_POWER_SWITCH_ON;
  }
}

void setPCPowerSwitchOnMomentarily()
{
  //digitalWrite(pcPowerPin, true);
  PC_POWER_SWITCH_ON; // Set pin 6 to HIGH
  nilThdSleepMilliseconds(100); // Give enough time for PC to start
  //digitalWrite(pcPowerPin, false);
  PC_POWER_SWITCH_OFF; // Set pin 6 to LOW
}

