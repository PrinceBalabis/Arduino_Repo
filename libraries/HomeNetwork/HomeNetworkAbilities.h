#ifndef __HOMENETWORKABILITIES_H__
#define __HOMENETWORKABILITIES_H__

/**
 *  In this header-file contains all the functions you can call to make something cool happen!
 */
#include <SPI.h>
#include "RF24.h"
#include "HomeNetworkConfig.h"
#include <stddef.h>
#include <stdint.h>
#include "HomeNetworkNodes.h"
#include "RF24Network.h"

class HomeNetworkAbilities
{
  public:

	// Add new home commands here!
	uint8_t toggleMainLights(void);
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

};
#endif