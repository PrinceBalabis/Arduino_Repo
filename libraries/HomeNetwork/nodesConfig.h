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
static const uint8_t cmdGetLightsStatus = 1;
// Command
static const uint8_t cmdToggleLights = 1;
static const uint8_t cmdSetLightsOn = 2;
static const uint8_t cmdSetLightsOff = 3;

//***********************Home Control************************************************************
//First child of Main Room Lights node
static const uint16_t nodeHomeControl = 01;

// Command(message type: typeCommand)
// Starts from 17 because buttons use 1-16
static const uint8_t cmdSetPCOn = 17;

//***********************433MHz Controller************************************************************
//First child of Home Control
static const uint16_t nodeRF433MHz = 011;

// Ask(message type: typeAsk)
static const uint8_t cmdGetPaintingLightsStatus = 1;
static const uint8_t cmdGetSpeakerPowerStatus = 2;
// Command(message type: typeCommand)
static const uint8_t cmdSetPaintingLightsOn = 1;
static const uint8_t cmdSetPaintingLightsOff = 2;
static const uint8_t cmdTogglePaintingLights = 3;
static const uint8_t cmdSetSpeakerPowerSwitchOn = 4;
static const uint8_t cmdSetSpeakerPowerSwitchOff = 5;
static const uint8_t cmdToggleSpeakerPowerSwitch = 6;

//***********************Bed Switch************************************************************
//Second child of Home Control
static const uint16_t nodeBedSwitch = 02;


//***********************Speaker Controller************************************************************
//Third child of Home Control
static const uint16_t nodeSpeaker = 031;

// Command(message type: typeCommand)
static const uint8_t cmdToggleSpeakerPower = 1;
static const uint8_t cmdSetSpeakerPowerOn = 2;
static const uint8_t cmdSetSpeakerPowerOff = 3;
static const uint8_t cmdSetSpeakerVolumeUp = 4;
static const uint8_t cmdSetSpeakerVolumeDown = 5;
static const uint8_t cmdToggleSpeakerMute = 6;
static const uint8_t cmdSetSpeakerMuteOn = 7;
static const uint8_t cmdSetSpeakerMuteOff = 8;
static const uint8_t cmdToggleSpeakerMode = 9;
static const uint8_t cmdSetSpeakerModePC = 10;
static const uint8_t cmdSetSpeakerModeLineIn = 11;


//***********************PC Controller************************************************************
//Fourth child of Home Control
static const uint16_t nodePC = 041;

// Command(message type: typeCommand)
static const uint8_t cmdSetPCMute = 1;
static const uint8_t cmdSetPCNoMute = 2;
static const uint8_t cmdSetPCToggleMute = 3;
static const uint8_t cmdSetPCPlayPause = 4;
static const uint8_t cmdSetPCNext = 5;
static const uint8_t cmdSetPCPrevious = 6;
static const uint8_t cmdSetPCDisableMonitors = 7;
static const uint8_t cmdSetPCEnableMonitors = 8;
static const uint8_t cmdSetPCVolUp = 9;
static const uint8_t cmdSetPCVolDown = 10;
static const uint8_t cmdSetPCVolUpBunch = 11;
static const uint8_t cmdSetPCVolDownBunch = 12;
static const uint8_t cmdSetPCVolPresetMax = 13;
static const uint8_t cmdSetPCVolPresetMedium = 14;
static const uint8_t cmdSetPCVolPresetLow = 15;
static const uint8_t cmdSetPCSpotifyPlaylistWorkout = 16;
static const uint8_t cmdSetPCSpotifyPlaylistDinner = 17;
static const uint8_t cmdSetPCSpotifyPlaylistMorning = 17;


//***********************Example Sketches like ToggleMainLights or AskMainLightsStatus************************************************************
static const uint16_t exampleNode = 051;


//***********************Other Nodes****************************************************************************
//static const uint16_t nodeNAS = 02;
//static const uint16_t nodeRaspberryPi = 03;
//static const uint16_t nodeVoiceRecog = 04;
//static const uint16_t nodePC = 02;

//***********************homeNetworkExampleServer****************************************************
//static const uint16_t nodeExampleA = 041; // Used for example/testing. This node is second child of centralHomeControl-node
//static const uint16_t nodeExampleB = 051; // Used for example/testing. This node is third child of centralHomeControl-node

// Commands to offer
//static const int32_t cmdExampleAskCommand = 12345;
//static const int32_t cmdExampleResponseData = 67890;
