// Here you can give each node we will be communicating with a name.
// We only have 5 talk/listen pipes, 
// so we can only have 5 nodes in this network
const uint16_t mainLights = 00; 
const uint16_t centralHomeControl = 01; // Centra Home Control Node
const uint16_t raspberryPi = 02; // Raspberry Pi Node
const uint16_t voiceRecog = 03; // VoiceRecog Node

// This is the nodeID of this Arduino.
// WARNING! DONT FORGET TO SET UNIQUE NODE ID IN config.h FOR EACH NODE!
const uint16_t nodeID = voiceRecog; 

// Tweaks optimized for compatability, reliability and driftsecurity
const uint8_t retryDelay = 5;
const uint8_t retryTimes = 15;
const uint8_t powerAmplifierLevel = RF24_PA_HIGH;
const rf24_datarate_e dataRate = RF24_250KBPS;



//Commands
enum RBBLEDCOMMANDS
{
  POWER_ON = 1,
  POWER_OFF = 2,
  POWER_TOGGLE = 3,
  BRIGHTNESS_UP = 4,
  BRIGHTNESS_DOWN = 5,
  COLOR_COLD = 6,
  COLOR_WARM = 7,
  COLOR_WARMEST = 8,
  COLOR_COLDER = 9,
  COLOR_WARMER = 10,
  MODE_FLASH = 11,
  MODE_STROBE = 12,
  MODE_FADE = 13,
  MODE_SMOOTH = 14
};

