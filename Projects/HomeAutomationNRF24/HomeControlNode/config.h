#define COMMANDEXECUTIONER_MSGORIGIN_KEYPAD 0
#define COMMANDEXECUTIONER_MSGORIGIN_HOMENETWORK 1
/*
*  ------------------------------------
 *  RF24 Mesh Node
 *  ------------------------------------
 */
// This is the nodeID of this Arduino.
// WARNING! DONT FORGET TO SET UNIQUE NODE ID IN config.h FOR EACH NODE!
// If you are creating a new node add it to: "\library\HomeNetwork\homeNetworkNodes.h"
#define NODEID HOME_HOMECONTROL_ID

//CE and CSN pins
#define RF24_PIN_CE 8
#define RF24_PIN_CSN 9

// How often to auto update network.
#define HOME_SETTING_TIME_NETWORKAUTOUPDATE 5

#define TWI_SLAVE_ID 1

