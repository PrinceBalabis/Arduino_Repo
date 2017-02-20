/*
  ---------------------------------------------------------------
  This is the config tab.
  All tweakable settings are here.
  It must be named "A_" in the start of the tab-name or else it won't compile
  ---------------------------------------------------------------
*/

/*
  ---------------------------------------------------------------
  HTTP/Wi-Fi settings
  ---------------------------------------------------------------
*/
const char* ssid = "Router";
const char* password = "kungarike";
const uint8_t wifiConnectTimeout = 5; // The amount of seconds to wait until giving up connecting to Wi-Fi
const uint16_t serverPort = 80;
/*
  ---------------------------------------------------------------
  Pin-outs
  ---------------------------------------------------------------
*/
const int ledPinESP =  D4;// LED on ESP on pin D4(Must call D4 in code)
const int ledPinBoard =  D0; // LED on board on pin D0(Must call D0 in code)

/*
  ---------------------------------------------------------------
   Execution frequency in milliseconds(does not mean sample time and does not account for execution times).
   So if a task has an exeution frequency of 10ms, and the task takes 5ms to execute one loop of its code,
   then the total sample time is 15ms(10+5).
  ---------------------------------------------------------------
*/
const uint32_t serverUpdateExeutionFrequency = 250; // How often to check if a new client has connected

