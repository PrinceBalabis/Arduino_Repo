const int CLAP_SENSOR_PIN = 2; //Pin for Digital Output - DO from the Sound Sensor Module
const int RELAY_PIN = 8; // Relay pin
const int CLAP_PAUSE = 1000; // Maximal pause in between claps (milliseconds)

int relayState = 0;
unsigned long commandMillis = 0;
unsigned long startMillis;
int currentClaps = 0;
int clapOngoing = 0;

void setup() {
  // Setup relay
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
}

void loop() {
  if (digitalRead(CLAP_SENSOR_PIN) && !clapOngoing && currentClaps == 0) {
    currentClaps++;
    commandMillis = 0;
    clapOngoing = 1;
    delay(20);
    startMillis = millis();
  } else if (digitalRead(CLAP_SENSOR_PIN) && !clapOngoing && currentClaps > 0) {
    currentClaps = 0;
    switchRelay();
    clapOngoing = 1;
    delay(100);
  } else {
    clapOngoing = 0;
  }

  if (currentClaps > 0) {
    commandMillis = millis() - startMillis; // Count time

    if (commandMillis >= CLAP_PAUSE) {
      currentClaps = 0;
    }
  }

}

void resetClapTimer() {
}

void switchRelay() {
  if (relayState) {
    digitalWrite(RELAY_PIN, LOW);
    relayState = 0;
  } else {
    digitalWrite(RELAY_PIN, HIGH);
    relayState = 1;
  }
}
