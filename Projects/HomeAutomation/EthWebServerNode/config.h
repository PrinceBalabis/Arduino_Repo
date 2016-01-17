#define COMMANDEXECUTIONER_MSGORIGIN_INTERNET 0
#define COMMANDEXECUTIONER_MSGORIGIN_INTERNET_MACRO 2
#define COMMANDEXECUTIONER_MSGORIGIN_HOMENETWORK 1

/*
*  ------------------------------------
 *  RF24 Mesh Node
 *  ------------------------------------
 */
// This is the nodeID of this Arduino.
// WARNING! DONT FORGET TO SET UNIQUE NODE ID IN config.h FOR EACH NODE!
// If you are creating a new node add it to: "\library\HomeNetwork\homeNetworkNodes.h"
#define NODEID HOME_WEBSERVER_ID

//CE and CSN pins
#define RF24_PIN_CE 8
#define RF24_PIN_CSN 9

// How often to auto update network.
#define HOME_SETTING_TIME_NETWORKAUTOUPDATE 20

#define TWI_SLAVE_ID 1

/*
*  ------------------------------------
 *  Webserver
 *  ------------------------------------
 */
// Webserver Commands
#define QSN_MAINLIGHTS_STATUS 1 // Ask mainlights status
#define CMD_APARTMENT_SHUTDOWN 2 // Shutdown Apartment
#define CMD_APARTMENT_STARTUP 3 // Startup Apartment
#define CMD_APARTMENT_TOGGLE 4 // Toggle Apartment
#define CMD_APARTMENT_MOOD_TOGGLE 5 // Toggle Apartment mood
