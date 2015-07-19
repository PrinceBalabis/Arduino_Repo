// This is the nodeID of this Arduino.
// WARNING! DONT FORGET TO SET UNIQUE NODE ID IN config.h FOR EACH NODE!
// If you are creating a new node add it to: "\library\HomeNetwork\homeNetworkNodes.h"
const uint16_t nodeID = nodeExampleA;

//Hardware
const uint8_t homeNetworkCEPin = 8;
const uint8_t homeNetworkCSNPin = 9;

//Tweaks
const uint16_t homeNetworkInitiateDelay = 3000; // How long to wait to start the homeNetwork service, make sure it after any other threads, or it may crash the Arduino at boot
const uint16_t homeNetworkCheckMessageDelay = 40; // How often to check for a new message, WARNING! The shorther the delay the less time for for other threads!
