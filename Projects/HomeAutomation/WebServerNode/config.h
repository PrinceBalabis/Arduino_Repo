#define COMMANDEXECUTIONER_MSGORIGIN_LOCAL 0
#define COMMANDEXECUTIONER_MSGORIGIN_HOMENETWORK 1

/*
*  ------------------------------------
 *  RF24 Mesh Node
 *  ------------------------------------
 */
// This is the nodeID of this Arduino.
// WARNING! DONT FORGET TO SET UNIQUE NODE ID IN config.h FOR EACH NODE!
// If you are creating a new node add it to: "\library\HomeNetwork\homeNetworkNodes.h"
#define NODEID HOME_TEST_ID

//CE and CSN pins
#define RF24_PIN_CE 8
#define RF24_PIN_CSN 9

// How often to auto update network. Should be short because this node is parent for many child nodes
#define HOME_SETTING_TIME_NETWORKAUTOUPDATE 5

/*
*  ------------------------------------
 *  Webserver
 *  ------------------------------------
 */
#define DEBUG_TOGGLE 1
#define DEBUG_LED A0

// Webserver Commands
#define CMD_MAINLIGHTS_TOGGLE 1 // Toggle mainlights
#define QSN_MAINLIGHTS_STATUS 2 // Ask mainlights status
#define CMD_APARTMENT_SHUTDOWN 3 // Shutdown Apartment
#define CMD_APARTMENT_STARTUP 4 // Startup Apartment
#define CMD_APARTMENT_TOGGLE 5 // Toggle Apartment
#define CMD_SPEAKER_MUTE_TOGGLE 6 // Toggle speaker mute
#define CMD_SPEAKER_MODE_TOGGLE 7 // Toggle speaker mode
#define CMD_PAINTINGLIGHTS_TOGGLE 8 // Toggle Painting Lights 
#define CMD_APARTMENT_MOOD_TOGGLE 9 // Toggle Apartment mood