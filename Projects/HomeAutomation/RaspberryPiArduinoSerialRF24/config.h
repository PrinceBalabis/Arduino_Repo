// This is the nodeID of this Arduino.
// WARNING! DONT FORGET TO SET UNIQUE NODE ID IN config.h FOR EACH NODE!
const uint16_t nodeID = 04 ;

// Tweaks optimized for compatability, reliability and driftsecurity
const uint8_t retryDelay = 5;
const uint8_t retryTimes = 15;
const uint8_t powerAmplifierLevel = RF24_PA_HIGH;
const rf24_datarate_e dataRate = RF24_250KBPS;


