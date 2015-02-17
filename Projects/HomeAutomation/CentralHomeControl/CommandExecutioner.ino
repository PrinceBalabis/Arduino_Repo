/**
 ** CommandExecutioner thread
 ** Executes commands received from other RF24 units
 **/


static msg_t Thread3(void *arg)
{
  chThdSleepMilliseconds(4000);  //Give other threads some time to start
  Serial.println(F("Started CommandExecutioner thread"));

  while (1) 
  {
    if(dataY == -1)
    {
      // Commands received from RF24 nodes
      if(dataX == diningTableOn)
      {
        clearRF24Command();
        setDiningTableSwitchOn();
        Serial.println(F("Turned on dining table lights"));
      }
      else if(dataX == diningTableOff)
      {
        clearRF24Command();
        setDiningTableSwitchOff();
        Serial.println(F("Turned off dining table lights"));
      }
      else if(dataX == diningTableToggle)
      {
        clearRF24Command();
        toggleDiningTableSwitch();
        Serial.println(F("Toggled dining table lights"));
      }
      else if(dataX == speakerPowerToggle)
      {
        clearRF24Command();
        toggleSpeakerPower();
      }
      else if(dataX == speakerPowerOn)
      {
        clearRF24Command();
        sendSpeakerPowerOnCommand();
      }
      else if(dataX == speakerPowerOff)
      {
        clearRF24Command();
        sendSpeakerPowerOffCommand();
      }

      else if(dataX == speakerVolumeUp)
      {
        clearRF24Command();
        sendSpeakerUpVolCommandOnce();
      }
      else if(dataX == speakerVolumeDown)
      {
        clearRF24Command();
        sendSpeakerDownVolCommandOnce();
      }
      else if(dataX == speakerMuteToggle)
      {
        clearRF24Command();
        toggleSpeakerMuteCommand();
      }
      else if(dataX == speakerMuteOn)
      {
        clearRF24Command();
        sendSpeakerMuteOnCommand();
      }
      else if(dataX == speakerMuteOff)
      {
        clearRF24Command();
        sendSpeakerMuteOffCommand();
      }
    }
    chThdSleepMilliseconds(50); // Give other threads some time to run
  }
}















