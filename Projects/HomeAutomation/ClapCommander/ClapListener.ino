//------------------------------------------------------------------------------
// Thread 2, turn the LED on and signal thread 1 to turn the LED off.

int relayState = 0;
unsigned long commandMillis = 0;
unsigned long startMillis;
int currentClaps = 0;
int clapCommandOngoing = 0;
int clapOnGoing = 0;

static msg_t Thread2(void *arg) {

  // Setup relay
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  while (1) {
    int noiseLevelHigh = digitalRead(CLAP_SENSOR_PIN);
    unsigned long timeNow = millis() - startMillis;

    /**
     * First clap department
     */
    if(currentClaps == 0){
      if (noiseLevelHigh && !clapOnGoing) { // First clap detected, start clap detection procedure
        startMillis = millis();
        clapOnGoing = 1;
        clapCommandOngoing = 1;
        Serial.println("First clap detected");
      } 
      else if(!noiseLevelHigh && clapOnGoing){
        if(timeNow < CLAP_MAXLENGTH){ // If the noise was longer than CLAP_MAXLENGTH then it is not considered a clap
          currentClaps++;
          clapOnGoing = 0;
          Serial.println("First clap noise level sank");
        } 
        else { // ignore first clap if it lasted more than max clap length, this resets the clap detection procedure
          resetClapDetection();
          Serial.println("Noise detected is not considered a clap, resetting clap detection procedure...");
          Serial.println(); // Extra row for easier serial terminal read
        }
      }
    }

    /**
     * Second clap department
     */
    else if (currentClaps == 1) {
      if(!noiseLevelHigh && timeNow > CLAP_MAXPAUSE) { // Waited too long for second clap, resets clap detection procedure
        resetClapDetection();
        Serial.println("Second clap not detected, time waiting ran out, resetting clap detection procedure...");
        Serial.println(); // Extra row for easier serial terminal read
      }
      else if(noiseLevelHigh && timeNow > CLAP_MINPAUSE){ // Detected second clap
        Serial.println("Second clap detected");
        Serial.println("Running clap command...");
        Serial.println(); // Extra row for easier serial terminal read
        clapOnGoing = 1;
        currentClaps++;
        switchRelay();
        chSemSignal(&sem);  // Toggle main lights!
        resetClapDetection();
        chThdSleepMilliseconds(200);
      }  
    } 
  }
  return 0;  
}

void resetClapDetection(){
  clapOnGoing = 0;
  clapCommandOngoing = 0;
  currentClaps = 0;
}

void switchRelay() {
  relayState = !relayState;
  digitalWrite(RELAY_PIN, relayState);
}



