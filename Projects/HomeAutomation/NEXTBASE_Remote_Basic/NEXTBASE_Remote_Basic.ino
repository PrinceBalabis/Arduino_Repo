/*
 *  hardware needed: 940 nm IR LED with a resistor to pin 3
 *  NextBase takes about 9 seconds to boot
 *  Volume option is between 0 and 30 in value
 */

#include <CIRremote.h>

IRsend irsend;

// NEXTBASE IR codes
unsigned long power = 0xFFC23D;
unsigned long mute = 0xFF02FD;
unsigned long upVolume = 0xFFF00F;
unsigned long downVolume = 0xFF708F;

void sendCommand(unsigned long command) {
  irsend.sendNEC(command, 32);
}

void incVolume(int volValue) {
  if (volValue > 30) {
    volValue = 30;
  }
  for (int i = 0; i < volValue; i++) {
    sendCommand(upVolume);
    delay(40);
  }
}

void decVolume(int volValue) {
  if (volValue > 30) {
    volValue = 30;
  }
  for (int i = 0; i < volValue; i++) {
    sendCommand(downVolume);
    delay(40);
  }
}

void setup()
{
  sendCommand(power);
  delay(9000);
  incVolume(30);
}

void loop() {
  delay(100000);
}
