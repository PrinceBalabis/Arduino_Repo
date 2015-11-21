#define COMMANDEXECUTIONER_MSGORIGIN_LOCAL 0
#define COMMANDEXECUTIONER_MSGORIGIN_HOMENETWORK 1

// This is the nodeID of this Arduino.
// WARNING! DONT FORGET TO SET UNIQUE NODE ID IN config.h FOR EACH NODE!
// If you are creating a new node add it to: "\library\HomeNetwork\homeNetworkNodes.h"
#define NODEID HOME_RF433MHZ_BLUETOOTH_ID

//CE and CSN pins
#define RF24_PIN_CE 8
#define RF24_PIN_CSN 9

// How often to auto update network. Should be short because this node is parent for many child nodes
#define HOME_SETTING_TIME_NETWORKAUTOUPDATE 5

/*
*  ------------------------------------
 *  433 MHz Switches codes
 *  ------------------------------------
 */
const uint8_t paintingLightsCode = 1;

/*
*  ------------------------------------
 *  EEPROM Addresses
 *  ------------------------------------
 */
const uint8_t paintingLightsAddress = 0;
