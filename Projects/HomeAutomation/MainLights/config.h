/*
 *  ------------------------------------
 *  Home Network
 *  ------------------------------------
 */
// This is the nodeID of this Arduino.
// WARNING! DONT FORGET TO SET UNIQUE NODE ID IN config.h FOR EACH NODE!
// If you are creating a new node add it to: "\library\HomeNetwork\homeNetworkNodes.h"
const uint16_t nodeID = nodeMainLights;

//CE and CSN pins
const uint8_t homeNetworkCEPin = 8;
const uint8_t homeNetworkCSNPin = 9;

// How often to auto update network. Should be short because this node is parent for many child nodes
const uint16_t homeNetworkAutoUpdateTime = 10;

/*
 *  ------------------------------------
 *  EEPROM Addresses
 *  ------------------------------------
 */
const uint8_t MainLightsStatusAddress = 0;

/*
 *  ------------------------------------
 *  Wall switches
 *  ------------------------------------
 */
// Variables for switch pins
const int leftSwitchPin = 4;
const int rightSwitchPin = 5;

// How often to check for wall switch changes
const uint16_t wallSwitchUpdateDelay = 100;
/*
 *  ------------------------------------
 *  Relay/Main Lights
 *  ------------------------------------
 */
// Ceiling lights relay/ceiling light pin
const int mainLightsPin = A0;
