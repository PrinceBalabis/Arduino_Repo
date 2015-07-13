// Here you can give each node we will be communicating with a name.
// We only have 5 talk/listen pipes,
// so we can only have 5 nodes in this network


//***********************Main Room Lights*******************************
 // This is the base node, this node cannot have children! (ie. node 10,20,30,40 and 50 will not work!)
const uint16_t mainLights = 0;

// Commands to offer
const int toggleLights = 1;

//****************************************************************************
const uint16_t centralHomeControl = 1;
const uint16_t webServer = 2;
const uint16_t bedSwitch = 3;
const uint16_t raspberryPi = 4;
const uint16_t voiceRecog = 5;

//Default node
const uint16_t defaultNode = 31;

//Testing nodes
//***********************homeNetworkExampleServer*******************************
const uint16_t exampleServer = 0; // Used for example/testing. This node is second child of centralHomeControl-node

// Commands to offer
const int32_t exampleData = 12345;

//****************************************************************************

const uint16_t exampleClient = 1; // Used for example/testing. This node is third child of centralHomeControl-node
