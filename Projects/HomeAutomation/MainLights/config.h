/*
 *  ------------------------------------
 *  Home Network
 *  ------------------------------------
 */
// This is the nodeID of this Arduino.
// WARNING! DONT FORGET TO SET UNIQUE NODE ID IN config.h FOR EACH NODE!
// If you are creating a new node add it to: "\library\HomeNetwork\homeNetworkNodes.h"
#define HOME_NODEID NODE_MAINLIGHTS_ID

//CE and CSN pins
#define RF24_PIN_CE 8
#define RF24_PIN_CSN 9

// How often to auto update network. Should be short because this node is parent for many child nodes
#define HOME_AUTOUPDATE_DELAY 5

/*
 *  ------------------------------------
 *  EEPROM Addresses
 *  ------------------------------------
 */
#define EEPROM_MAINLIGHTS 0

/*
 *  ------------------------------------
 *  Wall switches
 *  ------------------------------------
 */
// Variables for switch pins
#define WALLSWITCH_PIN_LEFT 4
#define WALLSWITCH_PIN_RIGHT 5

// How often to check for wall switch changes
#define WALLSWITCH_UPDATEDELAY 100

/*
 *  ------------------------------------
 *  Relay/Main Lights
 *  ------------------------------------
 */
// Ceiling lights relay/ceiling light pin
#define MAINLIGHTS_PIN A0
