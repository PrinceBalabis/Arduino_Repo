// This is the nodeID of this Arduino.
// WARNING! DONT FORGET TO SET UNIQUE NODE ID IN config.h FOR EACH NODE!
// If you are creating a new node add it to: "\library\HomeNetwork\homeNetworkNodes.h"
#define NODEID HOME_RF433MHZ_ID

//CE and CSN pins
#define RF24_PIN_CE 8
#define RF24_PIN_CSN 9

// How often to auto update network. Should be short because this node is parent for many child nodes
#define HOME_AUTOUPDATE_DELAY 5

/*
*  ------------------------------------
 *  433 MHz Switches codes
 *  ------------------------------------
 */
const uint8_t paintingLightsCode = 1;
const uint8_t speakerCode = 2;

/*
*  ------------------------------------
 *  EEPROM Addresses
 *  ------------------------------------
 */
const uint8_t paintingLightsAddress = 0;
const uint8_t speakerPowerSwitchAddress = 1;
