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
#define NODEID NODE_TEST_ID

//CE and CSN pins
#define RF24_PIN_CE 8
#define RF24_PIN_CSN 9

// How often to auto update network. Should be short because this node is parent for many child nodes
#define HOME_AUTOUPDATE_DELAY 5


// TESTING
#define TESTING_SEND_DELAY 1000
#define TESTING_CHOSEN_COMMAND TESTING_CMD_433MHZ_PAINTINGLIGHTS_TOGGLE

#define TESTING_CMD_MAINLIGHTS_TOGGLE 1 // Test mainlights
#define TESTING_QSN_MAINLIGHTS_STATUS 2 // Test mainlights
#define TESTING_CMD_SPEAKER_MUTE_TOGGLE 3 // Test Speaker Node
#define TESTING_CMD_433MHZ_PAINTINGLIGHTS_TOGGLE 4 // Test 433MHz Node
