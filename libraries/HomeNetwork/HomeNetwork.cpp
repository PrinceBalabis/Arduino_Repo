/**
 *  In this header-file contains all the functions you can call to make something cool happen!
 */

#include "HomeNetworkAbilities.h"

uint8_t HomeNetworkAbilities::toggleMainLights(void) {
	return write(mainLights, 01);
}

// uint8_t HomeNetworkAbilities::setMainLightsOn() {
//   msgNode = mainLights;
//   msgContent = 02;
// }

// uint8_t HomeNetworkAbilities::setMainLightsOff() {
//   msgNode = mainLights;
//   msgContent = 03;
// }

// uint8_t HomeNetworkAbilities::togglePaintingLights() {
//   msgNode = centralHomeControl;
//   msgContent = 11;
// }

// uint8_t HomeNetworkAbilities::setPaintingLightsOn() {
//   msgNode = centralHomeControl;
//   msgContent = 9;
// }

// uint8_t HomeNetworkAbilities::setPaintingLightsOff() {
//   msgNode = centralHomeControl;
//   msgContent = 10;
// }

// uint8_t HomeNetworkAbilities::toggleSpeakerPower() {
//   msgNode = centralHomeControl;
//   msgContent = 01;
// }

// uint8_t HomeNetworkAbilities::setSpeakerPowerOn() {
//   msgNode = centralHomeControl;
//   msgContent = 02;
// }

// uint8_t HomeNetworkAbilities::setSpeakerPowerOff() {
//   msgNode = centralHomeControl;
//   msgContent = 03;
// }

// uint8_t HomeNetworkAbilities::shutdownAll() {
//   setMainLightsOff();
//   setPaintingLightsOff();
//   setSpeakerPowerOff();
// }

// uint8_t HomeNetworkAbilities::enterSleepMode() {
//   shutdownAll();
// }

// uint8_t HomeNetworkAbilities::leavingApartment() {
//   shutdownAll();
// }

// uint8_t HomeNetworkAbilities::exitSleepMode() {
//   setMainLightsOn();
//   setSpeakerPowerOn();
// }

// uint8_t HomeNetworkAbilities::setPartyMode() {
//   setPaintingLightsOn();
//   setMainLightsOff();
//   chThdSleepMilliseconds(20);
//   setSpeakerPowerOn();
// }


