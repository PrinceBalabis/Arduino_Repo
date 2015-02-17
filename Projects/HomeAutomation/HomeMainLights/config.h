/** 
 * Switches
 */

// Variables for switch pins
const int leftSwitchPin = 4;
const int rightSwitchPin = 5;

/** 
 * Relay / Lights
 */

// Ceiling lights relay/ceiling light pin
const int ceilingLightsPin = A0;

/** 
 * MESHNODE
 */

// Other nodes we can communicate with
const unsigned int mainLights = 00; 
const unsigned int raspberryPi = 01; 

// This is the nodeID of this Arduino.
const unsigned int nodeID = mainLights; 

// Commands
const unsigned int commandToggleLights = 01;
const unsigned int commandSetLightsOn = 02;
const unsigned int commandSetLightsOff = 03;

// Tweaks optimized for compatability, reliability and driftsecurity
const uint8_t retryDelay = 5;
const uint8_t retryTimes = 15;
const uint8_t powerAmplifierLevel = RF24_PA_HIGH;
const rf24_datarate_e dataRate = RF24_250KBPS;
