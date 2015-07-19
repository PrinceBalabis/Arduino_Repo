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
    
    chThdSleepMilliseconds(50); // Give other threads some time to run
  }
}















