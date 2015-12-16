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
#define HOME_AUTOUPDATE_DELAY 15

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
#define EEPROM_PAINTINGLIGHTS 1

/*
   ------------------------------------
    433 MHz Switches codes
    ------------------------------------
*/
#define PAINTINGLIGHTS_433MHZ_CODE 1

/*
   ------------------------------------
    Photo Sensor
    ------------------------------------
*/
#define PHOTOSENSOR_PIN A7
#define PHOTOSENSOR_THRESHOLD 30
// Time to wait until sending low/bright command
#define PHOTOSENSOR_ADAPTTIME 5000
#define PHOTOSENSOR_CEILINGLIGHTS_ON_LOWLIGHT_VALUE 80
#define PHOTOSENSOR_CEILINGLIGHTS_OFF_LOWLIGHT_VALUE 10
#define PHOTOSENSOR_CEILINGLIGHTS_ON_BRIGHTLIGHT_VALUE 60
#define PHOTOSENSOR_CEILINGLIGHTS_OFF_BRIGHTLIGHT_VALUE 40
#define PHOTOSENSOR_UPDATEDELAY 500


