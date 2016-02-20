/*************************************************************************************************************************************
GLOBAL MESSAGE TYPES
Message type' is packet within the header of a message, it is read by
the receiver to understand what type of packet it is.
These message types can be used by all nodes when communicating with each other.
*************************************************************************************************************************************/
#define HOME_TYPE_COMMAND 'A' // Simple command(a number), which is a message and sender IS EXPECTED to get an ack-response back
#define HOME_TYPE_COMMAND_FAST 'C' // Simple command(a number), which is a message and NO NEED to return an ack-response back
//#define HOME_TYPE_MESSAGE 'A //TODO MESSAGE TYPE. A message(todo: maybe a string, char array that is max 32 bits(biggest message size))
//#define HOME_TYPE_QUESTION 'D'
//#define HOME_TYPE_QUESTION_FAST 'E'
//#define HOME_TYPE_ANSWER 'F'
/*************************************************************************************************************************************/





/*************************************************************************************************************************************
NODES
Here are the node IDs and their available commands and questions in the Home Network.
You can give each node a name.
We only have 5 talk/listen pipes,
so a node can max have 5 other nodes to talk to.
The network enables library enables nodes to talk to more than 5 nodes by creating a communication network between nodes
and passing messages along other nodes until it reaches the destination node.
A central node is requires which is the center of all nodes, this node has the address of "00"
This means a node can have an address for instance "01" or "05". Then this node is child of parent node "00". Address is between 01-05.
Address 06 is not allowed as we talked about earlier, max 5 communication pipes per node. The parent "00" cannot have more than 5 nodes.
If a node has the address "011". Then this node is a child of parent node "01"
If a node has the address "0345". Then this node is a child of parent node "034"
*************************************************************************************************************************************/


/*************************************************************************************************************************************
Home Control
*************************************************************************************************************************************/
#define HOME_HOMECONTROL_ID 01

// Command(message type: typeCommand)
// Starts from 17 because buttons use 1-16
#define HOME_HOMECONTROL_CMD_PC_ON 17

/*************************************************************************************************************************************
Main Room Lights & 433MHz Controller
*************************************************************************************************************************************/
#define HOME_LIGHTS433POWER_ID 02

// Command
#define HOME_LIGHTS433POWER_CMD_MAINLIGHTS_ON 1
#define HOME_LIGHTS433POWER_CMD_MAINLIGHTS_OFF 2
#define HOME_LIGHTS433POWER_CMD_MAINLIGHTS_TOGGLE 3
#define HOME_LIGHTS433POWER_CMD_PAINTINGLIGHTS_ON 4
#define HOME_LIGHTS433POWER_CMD_PAINTINGLIGHTS_OFF 5
#define HOME_LIGHTS433POWER_CMD_PAINTINGLIGHTS_TOGGLE 6

// Question
#define HOME_LIGHTS433POWER_QSN_MAINLIGHTS_STATUS 1
#define HOME_LIGHTS433POWER_QSN_PAINTINGLIGHTS_STATUS 2

/*************************************************************************************************************************************
Speaker
Disabled speaker for now because of inconsistencies with IR, waiting for better IR blaster/transmitter module from EBAY
*************************************************************************************************************************************/
// #define HOME_SPEAKER_ID 03

// Question
// #define HOME_SPEAKER_QSN_POWER_STATUS 1

// Command
// #define HOME_SPEAKER_CMD_POWER_TOGGLE 1
// #define HOME_SPEAKER_CMD_POWER_ON 2
// #define HOME_SPEAKER_CMD_POWER_OFF 3
// #define HOME_SPEAKER_CMD_VOLUME_UP 4
// #define HOME_SPEAKER_CMD_VOLUME_DOWN 5
// #define HOME_SPEAKER_CMD_MUTE_TOGGLE 6
// #define HOME_SPEAKER_CMD_MUTE_ON 7
// #define HOME_SPEAKER_CMD_MUTE_OFF 8
// #define HOME_SPEAKER_CMD_MODE_TOGGLE 9
// #define HOME_SPEAKER_CMD_MODE_PC 10
// #define HOME_SPEAKER_CMD_MODE_LINEIN 11

/*************************************************************************************************************************************
Webserver
*************************************************************************************************************************************/
#define HOME_WEBSERVER_ID 04

// Command
#define HOME_WEBSERVER_CMD_MONITOR_DISABLE 1
#define HOME_WEBSERVER_CMD_MONITOR_ENABLE 2
#define HOME_WEBSERVER_CMD_SPOTIFY_CHILL 3
#define HOME_WEBSERVER_CMD_SPOTIFY_DINNER 4
#define HOME_WEBSERVER_CMD_SPOTIFY_WORKOUT 5
#define HOME_WEBSERVER_CMD_SPOTIFY_WORK 6

/*************************************************************************************************************************************
Bed Switch
*************************************************************************************************************************************/
#define HOME_BEDSWITCH_ID 05

/*************************************************************************************************************************************
Example Sketches like ToggleMainLights or AskMainLightsStatus
*************************************************************************************************************************************/
#define HOME_TEST_ID 01

// Command(message type: typeCommand)
#define HOME_TEST_CMD 1
// Question
#define HOME_TEST_STATUS 1

/*************************************************************************************************************************************
Other Nodes
*************************************************************************************************************************************/
//static const uint16_t nodeNAS = ;
//static const uint16_t nodeRaspberryPi = ;
//static const uint16_t nodeVoiceRecog = ;
//static const uint16_t nodePC = ;

/*************************************************************************************************************************************
homeNetworkExampleServer
*************************************************************************************************************************************/
//static const uint16_t nodeExampleA = 041; // Used for example/testing.
//static const uint16_t nodeExampleB = 051; // Used for example/testing.

// Commands to offer
//static const int32_t cmdExampleAskCommand = 12345;
//static const int32_t cmdExampleResponseData = 67890;
