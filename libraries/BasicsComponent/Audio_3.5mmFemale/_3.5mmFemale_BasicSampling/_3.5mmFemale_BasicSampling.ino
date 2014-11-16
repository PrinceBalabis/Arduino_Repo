/**
  Simple Sketch which amplitude-samples left and right audio channels
  Also detects whether a cable is connected
*/

const int sleeveDetectPin = 2;
const int tipLeftChannelPin = A0;
const int ringRightChannelPin = A1;

int tipLeftChannelValue = 0;
int ringRightChannelValue = 0;
int cableConnected = 0;

void setup() {
  Serial.begin(57600);

  pinMode(sleeveDetectPin, INPUT); // Used to detect if a cable is inserted
}

void loop() {
  cableConnected = !digitalRead(sleeveDetectPin); // When pin is grounded, the audio cable is connected
  if(cableConnected){ // Run sampling when cable is attached
    // Read the value from the sensor:
    tipLeftChannelValue = analogRead(tipLeftChannelPin); 
    ringRightChannelValue = analogRead(ringRightChannelPin); 
    
    // Print out values
    Serial.print(tipLeftChannelValue);
    Serial.print(" - ");
    Serial.println(ringRightChannelValue);
  }
}
