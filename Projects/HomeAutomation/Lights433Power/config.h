/*
    ------------------------------------
    Home Network
    ------------------------------------
*/
// This is the nodeID of this Arduino.
// WARNING! DONT FORGET TO SET UNIQUE NODE ID IN config.h FOR EACH NODE!
// If you are creating a new node add it to: "\library\HomeNetwork\homeNetworkNodes.h"
#define HOME_NODEID HOME_LIGHTS433POWER_ID

//CE and CSN pins
#define RF24_PIN_CE 8
#define RF24_PIN_CSN 9

// How often to auto update network. Should be short because this node is parent for many child nodes
// Crashes when its 1
#define HOME_AUTOUPDATE_DELAY 5

/*
    ------------------------------------
    DigitalIO Fast
    ------------------------------------
*/
#define LEFT_BUTTON_READ  ((PIND & (1 << 4)) > 0)
#define RIGHT_BUTTON_READ ((PIND & (1 << 5)) > 0)

// How often to check for wall switch changes
#define WALLSWITCH_UPDATEDELAY 50

/*
    ------------------------------------
    EEPROM Addresses
    ------------------------------------
*/
#define EEPROM_MAINLIGHTS 0
#define PAINTINGLIGHTS_ADDRESS 1

/*
   ------------------------------------
    433 MHz Switches codes
    ------------------------------------
*/
#define PAINTINGLIGHTS_433MHZ_CODE 1

