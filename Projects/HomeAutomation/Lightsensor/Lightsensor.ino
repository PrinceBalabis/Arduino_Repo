#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();

// Pin setup
const int transmitterPin = 3;
const int photoResPin = 6;

// 433 MHz codes
const int brightLightCode = 5393;
const int lowLightCode = 5396;

// Variables for config
const int adaptTime = 100000; // Time to wait until sending low/bright command
const int brightLightValue = 900;
const int lowLightValue = 700;

// Variables for logic
int currentlight = 0; // 0 for lowlight, 1 for brightlight
unsigned long timeStart = 0;
int timerRunning = 0;  // 0 for timer running for lowlight, 1 for timer running brightlight

void setup() {
  Serial.begin(9600);

  // Transmitter is connected to Arduino Pin #3
  mySwitch.enableTransmit(3);
}

void loop() {
  int lightValue = analogRead(photoResPin);
  Serial.println(lightValue);

  if (lightValue < lowLightValue && currentlight) { // Dark light logic
    if (timerRunning != 0) {
      timeStart = millis();
      timerRunning = 0;
    } else if (timerRunning == 0 && ((millis() - timeStart) > adaptTime)) {
      mySwitch.send(lowLightCode, 24);
      Serial.println("Low light, sending command");
      timerRunning = -1;
      timeStart = 0;
    }
  } else if (lightValue > brightLightValue && !currentlight) { // Bright light logic
    if (timerRunning != 1) {
      timeStart = millis();
      timerRunning = 1;
    } else if (timerRunning == 1 && ((millis() - timeStart) > adaptTime)) {
      mySwitch.send(brightLightCode, 24);
      Serial.println("Bright light, sending command");
      timerRunning = -1;
      timeStart = 0;
    }
  }
  delay(2000);
}
