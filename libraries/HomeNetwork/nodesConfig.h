// Here you can give each node we will be communicating with a name.
// We only have 5 talk/listen pipes,
// so we can only have 5 nodes in this network

//***********************Global Message types**************************************************************
// 'Message type' is packet within the header of a message, it is read by
// the receiver to understand what type of packet it is

// Types every node can use for each other:
static const unsigned char typeAsk = 'A';
static const unsigned char typeResponse = 'R';
static const unsigned char typeCommand = 'C';

//***********************Main Room Lights************************************************************
// This is the base node, this node cannot have children! (ie. node 10,20,30,40 and 50 will not work!)
static const uint16_t nodeMainLights = 00;

// Ask
static const int cmdGetLightsStatus = 1;
// Command
static const int cmdToggleLights = 1;
static const int cmdSetLightsOn = 2;
static const int cmdSetLightsOff = 3;

//***********************Home Control************************************************************
//First child of Main Room Lights node
static const uint16_t nodeHomeControl = 01;

// Command(message type: typeCommand)
// Starts from 17 because buttons use 1-16
static const int cmdSetPCOn = 17;

//***********************433MHz Controller************************************************************
//First child of Home Control
static const uint16_t nodeRF433MHz = 011;

// Ask(message type: typeAsk)
static const int cmdGetPaintingLightsStatus = 1;
static const int cmdGetSpeakerPowerStatus = 2;
// Command(message type: typeCommand)
static const int cmdSetPaintingLightsOn = 1;
static const int cmdSetPaintingLightsOff = 2;
static const int cmdTogglePaintingLights = 3;
static const int cmdSetSpeakerPowerSwitchOn = 4;
static const int cmdSetSpeakerPowerSwitchOff = 5;
static const int cmdToggleSpeakerPowerSwitch = 6;

//***********************Bed Switch************************************************************
//Second child of Home Control
static const uint16_t nodeBedSwitch = 021;


//***********************Speaker Controller************************************************************
//Third child of Home Control
static const uint16_t nodeSpeaker = 031;

// Command(message type: typeCommand)
static const int cmdToggleSpeakerPower = 1;
static const int cmdSetSpeakerPowerOn = 2;
static const int cmdSetSpeakerPowerOff = 3;
static const int cmdSetSpeakerVolumeUp = 4;
static const int cmdSetSpeakerVolumeDown = 5;
static const int cmdToggleSpeakerMute = 6;
static const int cmdSetSpeakerMuteOn = 7;
static const int cmdSetSpeakerMuteOff = 8;
static const int cmdToggleSpeakerMode = 9;
static const int cmdSetSpeakerModePC = 10;
static const int cmdSetSpeakerModeLineIn = 11;

//***********************Other Nodes****************************************************************************
static const uint16_t nodeWebServer = 02;
static const uint16_t nodeRaspberryPi = 03;
static const uint16_t nodeVoiceRecog = 04;

//Default node
static const uint16_t nodeDefaultID = 31;

//Testing nodes
//***********************homeNetworkExampleServer****************************************************
static const uint16_t nodeExampleA = 041; // Used for example/testing. This node is second child of centralHomeControl-node
static const uint16_t nodeExampleB = 051; // Used for example/testing. This node is third child of centralHomeControl-node

// Commands to offer
static const int32_t cmdExampleAskCommand = 12345;
static const int32_t cmdExampleResponseData = 67890;
