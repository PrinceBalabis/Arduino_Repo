/*
 HC-SR04 Ping distance sensor:
 VCC to arduino 5v
 GND to arduino GND
 Echo to Arduino pin 5
 Trig to Arduino pin 6
 
 This program is to for an alarm system. 
 The ping distance sensor should be directed 
 towards a door or in between hallways when
 power is plugged in. When power is plugged in a 
 calibration runs and then it should not be moved at all.
*/

#define echoPin 5 // Echo Pin
#define trigPin 6 // Trigger Pin
#define firstBuzzerPin 9
#define secondBuzzerPin 12


int doorRange = 0;
long duration, distance; // Duration used to calculate distance

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(firstBuzzerPin, OUTPUT);
  pinMode(secondBuzzerPin, OUTPUT);
  digitalWrite(firstBuzzerPin, LOW);
  digitalWrite(secondBuzzerPin, LOW);

}

void loop() {
  /* The following trigPin/echoPin cycle is used to determine the
   distance of the nearest object by bouncing soundwaves off of it. */
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  //Calculate the distance (in cm) based on the speed of sound.
  distance = duration / 58.2;

  // Calibrate the door range, runs only once
  if (doorRange == 0) {
    doorRange = distance;
  }

  // If the door shifted 4 cm further or 4 cm closer to the sensor then run the beeps
  if (distance - 4 >= doorRange || distance + 4 <= doorRange) {
    digitalWrite(firstBuzzerPin, HIGH);
    digitalWrite(secondBuzzerPin, HIGH);
  } else {
    digitalWrite(firstBuzzerPin, LOW);
    digitalWrite(secondBuzzerPin, LOW);
  }

  //Delay 50ms before next reading.
  delay(50);
}
