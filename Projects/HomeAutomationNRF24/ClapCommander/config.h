const int CLAP_SENSOR_PIN = 2;

const int CLAP_MAXPAUSE = 500; // Maximal pause in between claps (milliseconds)
const int CLAP_MINPAUSE = 100; // Maximal pause in between claps (milliseconds)
const int CLAP_MAXLENGTH = 50; // Maximal length of a clap (milliseconds)

// Here you can give each node we will be communicating with a name.
// We only have 5 talk/listen pipes, 
// so we can only have 5 nodes in this network
const unsigned int mainLights = 00; 
const unsigned int clapCommander = 03; 


const unsigned int cmdNRFToggleLights = 1;

// This is the nodeID of this Arduino.
// WARNING! DONT FORGET TO SET UNIQUE NODE ID IN config.h FOR EACH NODE!
const unsigned int nodeID = clapCommander; 

// Tweaks optimized for compatability, reliability and driftsecurity
const uint8_t retryDelay = 5;
const uint8_t retryTimes = 15;
const uint8_t powerAmplifierLevel = RF24_PA_HIGH;
const rf24_datarate_e dataRate = RF24_250KBPS;
