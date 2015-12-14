// This is the nodeID of this Arduino.
// WARNING! DONT FORGET TO SET UNIQUE NODE ID IN config.h FOR EACH NODE!
// If you are creating a new node add it to: "\library\HomeNetwork\homeNetworkNodes.h"
#define NODEID HOME_BEDSWITCH_ID

//CE and CSN pins
#define RF24_PIN_CE 8
#define RF24_PIN_CSN 9

// How often to auto update network. Should be short because this node is parent for many child nodes
#define HOME_AUTOUPDATE_DELAY 20

#define CMD_UPDATE_LED 1
#define CMD_APARTMENT_TOGGLE 2

//ApartmentStatusLED
const uint8_t ledPin = 3;
const uint16_t apartmentStatusUpdateTime = 5000;

//Button config
#define BUTTON_PIN 2
const uint16_t buttonReadUpdateTime = 50;
const uint16_t buttonDebounceTime = 300;
const uint16_t buttonRepressTime = 6000;
