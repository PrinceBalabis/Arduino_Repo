// Here you can give each node we will be communicating with a name.
// We only have 5 talk/listen pipes,
// so we can only have 5 nodes in this network

//***********************Message types**************************************************************
// 'Message type' is packet within the header of a message, it is read by
// the receiver to understand what type of packet it is
static const unsigned char msgTypeAsk = 'A';
static const unsigned char msgTypeResponse = 'R';
static const unsigned char msgTypeCommand = 'C';

//***********************Main Room Lights************************************************************
 // This is the base node, this node cannot have children! (ie. node 10,20,30,40 and 50 will not work!)
static const uint16_t mainLights = 0;

// Commands to offer
static const int toggleLights = 1;

//***************************************************************************************************
static const uint16_t centralHomeControl = 1;
static const uint16_t webServer = 2;
static const uint16_t bedSwitch = 3;
static const uint16_t raspberryPi = 4;
static const uint16_t voiceRecog = 5;

//Default node
static const uint16_t defaultNode = 31;

//Testing nodes
//***********************homeNetworkExampleServer****************************************************
static const uint16_t exampleServer = 0; // Used for example/testing. This node is second child of centralHomeControl-node
static const uint16_t exampleClient = 1; // Used for example/testing. This node is third child of centralHomeControl-node

// Commands to offer
static const int32_t exampleData = 12345;
static const int32_t exampleResponceData = 67890;
