// Here you can give each node we will be communicating with a name.
// We only have 5 talk/listen pipes,
// so we can only have 5 nodes in this network
const uint16_t mainLights = 00; // This is the base node, this node cannot have children! (ie. node 10,20,30,40 and 50 will not work!)

const uint16_t centralHomeControl = 01;
const uint16_t webServer = 02;
const uint16_t bedSwitch = 03;
const uint16_t raspberryPi = 04;
const uint16_t voiceRecog = 05;

//Default node
const uint16_t defaultNode = 011;

//Testing nodes
const uint16_t homeNetworkExampleServer = 021; // Used for example/testing. This node is second child of centralHomeControl-node
const uint16_t homeNetworkExampleClient = 031; // Used for example/testing. This node is third child of centralHomeControl-node
