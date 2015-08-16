// This is the nodeID of this Arduino.
// WARNING! DONT FORGET TO SET UNIQUE NODE ID IN config.h FOR EACH NODE!
// If you are creating a new node add it to: "\library\HomeNetwork\homeNetworkNodes.h"
#define NODEID HOME_SPEAKER_ID

//CE and CSN pins
#define RF24_PIN_CE 8
#define RF24_PIN_CSN 9

// How often to auto update network. Should be short because this node is parent for many child nodes
#define HOME_AUTOUPDATE_DELAY 5

/*  ------------------------------------
 *  IR Codes
 *  ------------------------------------
 */
// NEXTBASE IR codes
const unsigned long speakerIRPower = 0xFFC23D;
const unsigned long speakerIRMute = 0xFF02FD;
const unsigned long speakerIRUpVolume = 0xFFF00F;
const unsigned long speakerIRDownVolume = 0xFF708F;
const unsigned long speakerIRMode = 0xFF40BF;
const unsigned long speakerIRLeft = 0xFF22DD;
const unsigned long speakerIRRight = 0xFF32CD;
const unsigned long speakerIROK = 0xFF926D;

//Connect 940 nm IR LED with a resistor to pin 3

/*
*  ------------------------------------
 *  EEPROM Addresses
 *  ------------------------------------
 */
const uint8_t speakerModeAddress = 0;
