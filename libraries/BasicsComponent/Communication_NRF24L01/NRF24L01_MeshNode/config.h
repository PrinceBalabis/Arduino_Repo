
// Here you can give each node we will be communicating with a name.
// We only have 5 talk/listen pipes, 
// so we can only have 5 nodes in this network
const unsigned int node00 = 0; 
const unsigned int node01 = 1; 
const unsigned int node02 = 2; 
const unsigned int node03 = 3; 
const unsigned int node04 = 4; 

// This is the nodeID of this Arduino.
// WARNING! DONT FORGET TO SET UNIQUE NODE ID IN config.h FOR EACH NODE!
const unsigned int nodeID = node01; 

/**
----------DEMO AREA----------
*/
// Set the preferred of this node role for the demo.
// if isSender is set as 1 - then the role of this node is sender
// if isSender is set as 0 - then the role of this node is receiver
const int isSender = 1; 
const int senderLoopDelay = 2000; // How often should it send the message?(ms)
unsigned int msgContent = 0; // random message to send to receiver
unsigned int msgNode = node02; // node ID to send a message to
/**
----------DEMO AREA----------
*/
