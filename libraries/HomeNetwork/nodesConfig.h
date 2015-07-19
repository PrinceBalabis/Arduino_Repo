// Here you can give each node we will be communicating with a name.
// We only have 5 talk/listen pipes,
// so we can only have 5 nodes in this network

//***********************Message types**************************************************************
// 'Message type' is packet within the header of a message, it is read by
// the receiver to understand what type of packet it is
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

//***************************************************************************************************
static const uint16_t nodeHomeControl = 01;
static const uint16_t nodeBedSwitch = 011;
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
