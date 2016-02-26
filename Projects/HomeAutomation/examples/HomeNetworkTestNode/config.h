#define COMMANDEXECUTIONER_MSGORIGIN_LOCAL 0
#define COMMANDEXECUTIONER_MSGORIGIN_HOMENETWORK 1

/*
   ------------------------------------
    RF24 Mesh Node
    ------------------------------------
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


// TESTING
#define TESTING_SEND_DELAY 1 // (Def. min 1)How often to send the testing command.
#define TESTING_REPEATS 1 // How many times to send the command in the program. Max 4294967294 times

#define TESTING_CHOSEN_COMMAND TESTING_CMD_WEB_PC_SLEEP // Command chosen to test

#define TESTING_CMD_MAINLIGHTS_TOGGLE 1 // Toggle mainlights
#define TESTING_QSN_MAINLIGHTS_STATUS 2 // Ask mainlights status
#define TESTING_CMD_SPEAKER_MUTE_TOGGLE 3 // Toggle mute on Speaker Node
#define TESTING_CMD_433MHZ_PAINTINGLIGHTS_TOGGLE 4 // toggle painting lights on 433MHz Node
#define TESTING_CMD_433MHZ_PAINTINGLIGHTS_STATUS 5 // Ask status of painting lights on 433MHz Node
#define TESTING_CMD_WEB_PC_SLEEP 6 // Sleep PC
