/*
*  This is the config file.
 *  Here you can configure Buttons assigns, IR codes,
 *  RF24 codes & component pins.
 *  Also you can enable/disable serial
 */

/*
*  ------------------------------------
 *  RF24 Mesh Node
 *  ------------------------------------
 */

// This is the nodeID of this Arduino.
// WARNING! DONT FORGET TO SET UNIQUE NODE ID IN config.h FOR EACH NODE!
// If you are creating a new node add it to: "\library\HomeNetwork\homeNetworkNodes.h"
const uint16_t nodeID = nodeHomeControl;

//Hardware
const uint8_t homeNetworkCEPin = 8;
const uint8_t homeNetworkCSNPin = 9;

//Tweaks
const uint16_t homeNetworkCheckMessageDelay = 500; // How often to check for a new message, WARNING! The shorther the delay the less time for for other threads!
const uint16_t homeNetworkAutoUpdateTime = 20; // How often to auto update network. Should be short because this node is parent for many child nodes
/*
*  ------------------------------------
 *  Keypad Button reservations
 *  ------------------------------------
 */
// NextBase
const uint8_t speakerPowerButton = 10;
const uint8_t speakerUpVolButton = 16;
const uint8_t speakerDownVolButton = 15;
const uint8_t speakerMuteButton = 14;
const uint8_t speakerModeButton = 13;
// Lights
const uint8_t mainLightsButton = 4;
const uint8_t paintingLightsButton = 3;
// Computer swtich
const uint8_t pcPowerButton = 9;
// PC Controller
const uint8_t pcDisableMonitorButton = 11;
const uint8_t pcSpotifyPlaylistWorkout = 6;
const uint8_t pcSpotifyPlaylistDinner = 5;
/*

/*
*  ------------------------------------
 *  Keypad Performance
 *  ------------------------------------
 */
const uint8_t keypadUpdateTime = 20; // How often to update keypad reads in milliseconds
const uint8_t keypadHoldUpdateTime = 150; // How often to repeat command when holding a button, in milliseconds


/*
*  ------------------------------------
 *  Components pins
 *  ------------------------------------
 */

// PC Power pin pin
const uint8_t pcPowerPin = 6;

