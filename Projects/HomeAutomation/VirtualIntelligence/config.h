#define COMMANDEXECUTIONER_MSGORIGIN_LOCAL 0
#define COMMANDEXECUTIONER_MSGORIGIN_HOMENETWORK 1

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

// How often to auto update network. Should be short because this node is parent for many child nodes
#define HOME_SETTING_TIME_NETWORKAUTOUPDATE 5


// Commands
#define CMD_DONE 1
#define CMD_GOODNIGHT_SIR 2
#define CMD_HOPE_YOU_SLEPT_WELL_SIR 3
#define CMD_MADE_IT_MORE_COMFORTABLE_SIR 4
#define CMD_MUTED_SPEAKER 5
#define CMD_MY_MASTER_HAS_LEFT_THE_BUILDING_IM_SO_SAD 6
#define CMD_SORRY_WHAT 7
#define CMD_SPEAKER_LINE_IN_MODE 8
#define CMD_SPEAKER_PC_MODE 9
#define CMD_TURNING_ON_SPOTIFY_PLAYLIST_CHILLOUT 10
#define CMD_TURNING_ON_SPOTIFY_PLAYLIST_DINNER 11
#define CMD_TURNING_ON_SPOTIFY_PLAYLIST_FUNTIME 12
#define CMD_TURNING_ON_SPOTIFY_PLAYLIST_MORNING 13
#define CMD_TURNING_ON_SPOTIFY_PLAYLIST_WORKOUT 14
#define CMD_UNMUTED_PLAYLIST 15
#define CMD_WELCOME_HOME_SIR 16
#define CMD_YES_SIR 17

// Here is the config for easyvr

#define EASYVR_PIN_RX 2
#define EASYVR_PIN_TX 3

//Groups and Commands
enum Groups
{
  GROUP_1  = 1,
  GROUP_2  = 2,
};

enum Group1
{
  G1_JARVIS = 0,
};

enum Group2
{
  G2_MAIN_LIGHTS = 0,
  G2_PAINTINGS = 1,
  G2_JARVIS = 2,
};
