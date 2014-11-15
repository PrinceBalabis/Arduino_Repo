// Variables for switch pins
const int leftSwitchPin = 4;
const int rightSwitchPin = 5;

// Ceiling lights relay/ceiling light pin
const int ceilingLightsPin = 3;

// Here you can give each node we will be communicating with a name.
// We only have 5 talk/listen pipes, 
// so we can only have 5 nodes in this network
const unsigned int node00 = 0; 
const unsigned int node01 = 1; 
const unsigned int node02 = 2; 
const unsigned int node03 = 3; 
const unsigned int node04 = 4; 

// This is the nodeID of this Arduino.
const unsigned int nodeID = node00; 

// Commands
const unsigned int commandToggleLights = 01;
const unsigned int commandSetLightsOn = 02;
const unsigned int commandSetLightsOff = 03;

// Amount of time for retrying send command
const unsigned int timeoutTime = 1000; 
