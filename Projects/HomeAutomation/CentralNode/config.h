/*
*  ------------------------------------
 *  RF24 Mesh Node
 *  ------------------------------------
 */
// This is the nodeID of this Arduino.
// WARNING! DONT FORGET TO SET UNIQUE NODE ID IN config.h FOR EACH NODE!
// If you are creating a new node add it to: "\library\HomeNetwork\homeNetworkNodes.h"
#define NODEID HOME_HOMECONTROL_ID

//CE and CSN pins
#define RF24_PIN_CE 8
#define RF24_PIN_CSN 9

// How often to auto update network.
#define HOME_SETTING_TIME_NETWORKAUTOUPDATE 10

#define TWI_SLAVE_ID 1

/*
   ------------------------------------
    Keypad Button reservations
    ------------------------------------
*/
// NextBase
#define BUTTON_SPEAKER_POWER 10
#define BUTTON_SPEAKER_VOLUME_UP 16
#define BUTTON_SPEAKER_VOLUME_DOWN 15
#define BUTTON_SPEAKER_MUTE 14
#define BUTTON_SPEAKER_MODE 13
// Lights
#define BUTTON_MAINLIGHTS_TOGGLE 4
#define BUTTON_PAINTINGLIGHTS_TOGGLE 3
// Computer switch
#define BUTTON_PC_POWER 9
// PC Controller
#define BUTTON_PC_MONITOR_DISABLE 11
#define BUTTON_PC_SPOTIFYPLAYLIST_WORKOUT 6
#define BUTTON_PC_SPOTIFYPLAYLIST_DINNER 5
#define BUTTON_PC_SPOTIFYPLAYLIST_CHILL 7
#define BUTTON_PC_SPOTIFYPLAYLIST_WORK 8
