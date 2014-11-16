const int CLAP_SENSOR_PIN = 2;

const int CLAP_MAXPAUSE = 500; // Maximal pause in between claps (milliseconds)
const int CLAP_MINPAUSE = 100; // Maximal pause in between claps (milliseconds)
const int CLAP_MAXLENGTH = 50; // Maximal length of a clap (milliseconds)


// Here you can give each node we will be communicating with a name.
// We only have 5 talk/listen pipes, 
// so we can only have 5 nodes in this network
const unsigned int mainLights = 0; 
const unsigned int node01 = 1; 
const unsigned int node02 = 2; 
const unsigned int node03 = 3; 
const unsigned int node04 = 4; 

const unsigned int cmdNRFToggleLights = 1;

// This is the nodeID of this Arduino.
// WARNING! DONT FORGET TO SET UNIQUE NODE ID IN config.h FOR EACH NODE!
const unsigned int nodeID = node01; 
