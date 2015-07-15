#ifndef __HOMENETWORK_H__
#define __HOMENETWORK_H__

/*
HomeNetwork.h - Library for Prince Home Automation & IOT network of RF24 nodes
*/
#include "RF24.h"
#include "RF24Network.h"
#include "nodesConfig.h"
#include <ChibiOS_AVR.h>

class RF24;
class RF24Network;

class HomeNetwork
{
public:
  HomeNetwork(RF24& _radio, RF24Network& _network);
  void begin(uint16_t nodeID);
  void autoUpdate(void (* pmsgReceivedF)(uint16_t,unsigned char,int32_t));
  bool available(void);
  uint8_t write(uint16_t msgReceiver, int32_t msgContent, unsigned char msgType);
  uint8_t writeQuestion(uint16_t msgReceiver, int32_t msgContent, int32_t *pmsgResponce);
  uint16_t read(int32_t *pmsgReceived, unsigned char *pmsgType);

  // Add new home commands here!
  uint8_t askExampleDataToExampleServer(int32_t *pmsgResponse);
  uint8_t toggleMainLights();
  // uint8_t setMainLightsOn();
  // uint8_t setMainLightsOff();
  // uint8_t togglePaintingLights();
  // uint8_t setPaintingLightsOn();
  // uint8_t setPaintingLightsOff();
  // uint8_t toggleSpeakerPower();
  // uint8_t setSpeakerPowerOn();
  // uint8_t setSpeakerPowerOff();
  // uint8_t shutdownAll();
  // uint8_t enterSleepMode();
  // uint8_t leavingApartment();
  // uint8_t exitSleepMode();
  // uint8_t setPartyMode();

private:
  RF24& radio;
  RF24Network& network;
  volatile bool autoUpdatePaused = false;
  volatile bool autoUpdatePauseExecuted = false;

  // Tweaks optimized for compatability, reliability, driftsecurity and at least performance for Prince home IOT network
  // Tweak however you want though

  const unsigned int homeNetwork_timeoutSendTime = 10000; // Amount of time before trying to resend message again to node
  const unsigned int homeNetwork_timeoutAnswerTime = 10000; // Amount of time to wait until given up waiting of answer to question
  const unsigned int homeNetwork_autoUpdateTime = 50; // How often the network is updated

  // Set delay between retries & # of retries for a "radio.write" command
  const uint8_t homeNetwork_retryDelay = 4;
  const uint8_t homeNetwork_retryTimes = 20;

  const uint8_t homeNetwork_powerAmplifierLevel = RF24_PA_MAX;  // Set power amplifier to highest
  const rf24_datarate_e homeNetwork_dataRate = RF24_2MBPS;  // Set data rate to 250kpbs(other settings: RF24_250KBPS, RF24_1MBPS, RF24_2MBPS)

  const uint8_t homeNetwork_channel = 90; // Default Home network is using channel 90

};
#endif
