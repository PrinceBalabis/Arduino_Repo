// This is the nodeID of this Arduino.
// WARNING! DONT FORGET TO SET UNIQUE NODE ID IN config.h FOR EACH NODE!
// If you are creating a new node add it to: "\library\HomeNetwork\homeNetworkNodes.h"
#define NODEID HOME_SPEAKER_ID

//CE and CSN pins
#define RF24_PIN_CE 8
#define RF24_PIN_CSN 9

// How often to auto update network. Should be short because this node is parent for many child nodes
#define HOME_AUTOUPDATE_DELAY 15

/*  ------------------------------------
    IR Codes
    ------------------------------------
*/
// NEXTBASE IR codes
#define SPEAKER_IR_POWER 0xFFC23D
#define SPEAKER_IR_MUTE 0xFF02FD
#define SPEAKER_IR_UPVOLUME 0xFFF00F
#define SPEAKER_IR_DOWNVOLUME 0xFF708F
#define SPEAKER_IR_MODE 0xFF40BF
#define SPEAKER_IR_LEFT 0xFF22DD
#define SPEAKER_IR_RIGHT 0xFF32CD
#define SPEAKER_IR_OK 0xFF926D

//Connect 940 nm IR LED with a resistor to pin 3

/*
   ------------------------------------
    EEPROM Addresses
    ------------------------------------
*/
#define SPEAKER_EEPROM_MODE_ADDRESS 0

/*
   ------------------------------------
    Relay for Speaker power switch
    ------------------------------------
*/
#define SPEAKER_POWER_RELAY_PIN 4
#define SPEAKER_POWER_OUTPUT_INIT (DDRD |= _BV(SPEAKER_POWER_RELAY_PIN))
#define SPEAKER_POWER_ON (PORTD |= _BV(SPEAKER_POWER_RELAY_PIN))
#define SPEAKER_POWER_OFF (PORTD &= ~_BV(SPEAKER_POWER_RELAY_PIN))
#define SPEAKER_POWER_TOGGLE (PORTD ^= _BV(SPEAKER_POWER_RELAY_PIN))
