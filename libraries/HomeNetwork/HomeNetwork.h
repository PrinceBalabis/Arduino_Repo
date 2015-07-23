#ifndef __HOMENETWORK_H__
#define __HOMENETWORK_H__

/*
HomeNetwork.h - Library for Prince Home Automation & IOT network of RF24 nodes
*/
#include <ChibiOS_AVR.h>
#include "RF24.h"
#include "RF24Network.h"
#include "nodesConfig.h"


class RF24;
class RF24Network;

class HomeNetwork
{
public:
  HomeNetwork( RF24& _radio, RF24Network& _network, HomeNetwork* _homeNetwork);
  void begin(uint16_t nodeID, bool *_pmsgReceived, uint16_t *_pmsgSender, unsigned char *_pmsgType, int32_t *_pmsgContent);
  void autoUpdate();
  bool respondToQuestion(uint16_t _msgSender, int32_t _ResponseData);

  // Add new home commands here!
  bool toggleMainLights();
  bool setMainLightsOn();
  bool setMainLightsOff();
  bool askMainLightsStatus(int32_t *pmsgResponse);

  bool setPCOn();

  bool togglePaintingLights();
  bool setPaintingLightsOn();
  bool setPaintingLightsOff();
  bool askPaintingLightsStatus(int32_t *pmsgResponse);
  bool toggleSpeakerPowerSwitch();
  bool setSpeakerPowerSwitchOn();
  bool setSpeakerPowerSwitchOff();
  bool askSpeakerSwitchStatus(int32_t *pmsgResponse);

  bool toggleSpeakerPower();
  bool setSpeakerPowerOn();
  bool setSpeakerPowerOff();
  bool setSpeakerVolumeUp();
  bool setSpeakerVolumeDown();
  bool toggleSpeakerMute();
  bool toggleSpeakerMode();
  bool setSpeakerModePC();
  bool setSpeakerModeLineIn();

  bool askApartmentStatus();
  bool shutdownApartment();
  bool startupApartment();

  // Example functions
  bool askExampleDataA(int32_t *pmsgResponse);
  bool askExampleDataB(int32_t *pmsgResponse);

private:
  RF24& radio;
  RF24Network& network;
  HomeNetwork* homeNetwork;
  bool* pmsgReceived;
  uint16_t* pmsgSender;
  unsigned char* pmsgType;
  int32_t* pmsgContent;

  bool autoUpdatePaused = false;
  bool autoUpdatePauseExecuted = false;

  // Tweaks optimized for compatability, reliability, driftsecurity and at least performance for Prince home IOT network
  // Tweak however you want though
  const unsigned int homeNetwork_timeoutSendTime = 5000; // Amount of time before trying to resend message again to node
  const unsigned int homeNetwork_timeoutAnswerTime = 5000; // Amount of time to wait until given up waiting of answer to question
  const unsigned int homeNetwork_autoUpdateTime = 20; // How often the network is updated

  // Set delay between retries & # of retries for a "radio.write" command
  const uint8_t homeNetwork_retryDelay = 1;
  const uint8_t homeNetwork_retryTimes = 50;

  const uint8_t homeNetwork_powerAmplifierLevel = RF24_PA_MAX;  // Set power amplifier to highest
  const rf24_datarate_e homeNetwork_dataRate = RF24_2MBPS;  // Set data rate to 250kpbs(other settings: RF24_250KBPS, RF24_1MBPS, RF24_2MBPS)

  const uint8_t homeNetwork_channel = 90; // Default Home network is using channel 90, dont know other channels though

  // Local communication functions
  uint16_t read(int32_t *pmsgReceived, unsigned char *pmsgType);
  bool write(uint16_t msgReceiver, int32_t msgContent, unsigned char msgType);
  bool writeQuestion(uint16_t msgReceiver, int32_t msgContent, int32_t *pmsgResponse);
};
#endif
