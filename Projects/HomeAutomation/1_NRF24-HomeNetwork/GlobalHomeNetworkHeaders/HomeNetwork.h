/*
  homeNetwork.h - Library for Prince Home Automation & IOT network of RF24 nodes
*/
#ifndef HomeNetwork_h
#define HomeNetwork_h

#include "Arduino.h"
#include "HomeNetwork.h"
#include "HomeNetworkNodes.h"

class HomeNetwork
{
  public:
  	// Tweaks optimized for compatability, reliability and driftsecurity

	// Set delay between retries & # of retires for a "radio.write" command
	const uint8_t retryDelay = 5;
	const uint8_t retryTimes = 15;

	const uint8_t powerAmplifierLevel = RF24_PA_HIGH;  // Set power amplifier to highest
	const rf24_datarate_e dataRate = RF24_250KBPS;  // Set data rate to 250kpbs
	
	void config(void);
  private:

};
#endif