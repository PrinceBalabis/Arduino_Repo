/*
*  This is the config file.
*  Here you can configure Buttons assigns, IR codes, 
*  RF24 codes & component pins.
*  Also you can enable/disable serial
*/

/*
*  ------------------------------------
*  RF24 Mesh Node
*  ------------------------------------
*/
/**   Addresses/Topology                           Node Numbers  (To simplify address assignment in this demonstration)
 *           00                  - Master Node         ( 0 )
 *         01  02                - 1st Level children ( 1,2 )
 *  32 22 12    15 25 35 45    - 2nd Level children (7,5,3-4,6,8)
 */
// Map of RF24 nodes in the apartment
const uint16_t mainLights = 00; // Main Light Node
const uint16_t centralHomeControl = 01; // Centra Home Control Node
const uint16_t raspberryPi = 02; // Raspberry Pi Node

// This is the nodeID of this Arduino.
// WARNING! DONT FORGET TO SET UNIQUE NODE ID IN config.h FOR EACH NODE!
const uint16_t nodeID = centralHomeControl;

// Commands this node has to offer
const int32_t speakerPower = 01;
const int32_t speakerVolumeUp = 02;
const int32_t speakerVolumeDown = 03;
const int32_t speakerMute = 04;

// Tweaks optimized for compatibility, reliability and driftsecurity
const uint8_t retryDelay = 5;
const uint8_t retryTimes = 15;
const uint8_t powerAmplifierLevel = RF24_PA_HIGH;
const rf24_datarate_e dataRate = RF24_250KBPS;

/*
*  ------------------------------------
*  Keypad Button reservations
*  ------------------------------------
*/
// NextBase
const uint8_t nBPowerButton = 4;
const uint8_t nBUpVolButton = 3;
const uint8_t nBDownVolButton = 2;
const uint8_t nBMuteButton = 1;
// NRF24
const uint8_t lightMainButton = 8;
// PC swtich
const uint8_t pcPowerButton = 12;
// Sleep button
const uint8_t sleepButton =16;
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

/*
*  ------------------------------------
*  Components pins
*  ------------------------------------
*/
// PC Power pin pin
const int pcPowerPin = A2;
