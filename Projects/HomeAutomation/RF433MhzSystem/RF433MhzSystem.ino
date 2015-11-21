/**
 * Transmitter connected to pin 7
 */

#include <NewRemoteTransmitter.h>
#include <SoftwareSerial.h>

SoftwareSerial masterController(4, 5);
NewRemoteTransmitter transmitter(15303606, 7, 260, 2);

const uint8_t paintingLightsCode = 1;

void setup() {
  masterController.begin(115200);
}

void loop() {
  if (masterController.available()) {
    uint8_t cmd = masterController.read();
    if (cmd == 1) { // Turn on paintingLights
      transmitter.sendUnit(paintingLightsCode, true);
    } else if (cmd == 2) { // Turn off paintingLights
      transmitter.sendUnit(paintingLightsCode, false);
    }
  }
  delay(10);
}

//void setRemoteSwitch(uint8_t unit, boolean state){
//  transmitter.sendUnit(unit, state);
//}

