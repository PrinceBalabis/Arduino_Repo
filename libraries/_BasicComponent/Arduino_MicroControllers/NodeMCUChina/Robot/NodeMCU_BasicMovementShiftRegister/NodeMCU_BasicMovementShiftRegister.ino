/*
  MAJOR BUG:
  If it cannot connect to the Wi-Fi hotspot, try reconnecting the power/USB cable to reset the ESP

  Put a large capacitor(or even better, several small ones) between 5V/VIN and Ground to improve reliability

  Remember to install the CH340G drivers.

  Board settings:
  -NodeMCU 1.0(ESP-12E)
  -160MHz
  -921600
  -4M(3M)
 */

/*
  ---------------------------------------------------------------
  Library includes
  ---------------------------------------------------------------
*/
#include <Arduino.h>
#include <Scheduler.h>

/*
  ---------------------------------------------------------------
  Needed here to compile.
  Always keep these "function prototypes" on the bottom of this tab, or else the code might not compile.
  ---------------------------------------------------------------
*/
void setup();
void loop();
