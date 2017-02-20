/*
  ---------------------------------------------------------------
  This is the global logical variables tab.
  All global variables are here.
  What differs from logical variables and config variables are
  that logical variables are used for logical functions, and should NOT be changed.
  It must be named "A_" in the start of the tab-name or else it won't compile
  ---------------------------------------------------------------
*/


/*
  ---------------------------------------------------------------
  Task initialized
  Some tasks depend on other tasks to start before starting itself,
  with these variables they can check if the depending task has started
  ---------------------------------------------------------------
*/

volatile bool taskHTTPStarted = 0;
volatile bool taskCeilingLightsStarted = 0;
volatile bool taskMemStarted = 0;

/*
  ---------------------------------------------------------------
  Task-to-Task communication
  ---------------------------------------------------------------
*/
volatile bool ceilingLightsStatus = 0; // Current status of the ceilingLights


/*
  ---------------------------------------------------------------
  Wallswitches
  ---------------------------------------------------------------
*/
volatile unsigned long lastLeftInterruptDetected = 0; // Save last interrupt time for left switch
volatile unsigned long lastRightInterruptDetected = 0; // Save last interrupt time for right switch
volatile unsigned long lastInterruptDetected = 0; // Save last interrupt time for both switches

