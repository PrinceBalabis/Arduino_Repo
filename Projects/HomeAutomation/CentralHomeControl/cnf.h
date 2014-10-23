/*
*  This is the config file.
*  Here you can configure Buttons assigns, IR codes, 
*  433 MHz codes & component pins.
*  Also you can enable/disable serial
*/

// Put 1 to enable serial, 0 to disable
const int serialEnabled = 0;

/*
*  ------------------------------------
*  Buttons
*  ------------------------------------
*/
// NextBase
const int nBPowerButton = 4;
const int nBUpVolButton = 8;
const int nBDownVolButton = 12;
const int nBMuteButton = 16;
// 433 Switches
const int lightMainButton = 1;
// PC
const int pcPowerButton = 5;

/*
*  ------------------------------------
*  Components pins
*  ------------------------------------
*/
// 433 MHZ transmitter pin
const int transm433Pin = 12;

// PC Power pin pin
const int pcPowerPin = 2;

/*
*  ------------------------------------
*  IR Codes
*  ------------------------------------
*/
// NEXTBASE IR codes
const unsigned long nBIRPower = 0xFFC23D;
const unsigned long nBIRMute = 0xFF02FD;
const unsigned long nBIRUpVolume = 0xFFF00F;
const unsigned long nBIRDownVolume = 0xFF708F;

