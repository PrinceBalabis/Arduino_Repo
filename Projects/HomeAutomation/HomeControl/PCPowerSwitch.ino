bool pcPowerSwitchStatus = false;

void pcPowerSetup()
{
  pinMode(pcPowerPin, OUTPUT);
  digitalWrite(pcPowerPin, LOW);
}

void togglePCPowerSwitch()
{
  pcPowerSwitchStatus = !pcPowerSwitchStatus;
  digitalWrite(pcPowerPin, pcPowerSwitchStatus);
}

