/**
 * This Sketch is used for analog calibration
 * Records the highest value it gets out 
 * of the chosen Analog pins
 */

unsigned int analogFirstPin = A0;
unsigned int analogSecondPin = A1;

unsigned int analogFirstHighest = 0;
unsigned int analogSecondHighest = 0;

void setup() {
  Serial.begin(9600); 
  //  analogReference(EXTERNAL);
}

void loop() {
  unsigned int analogFirstRead = analogRead(A0);
  unsigned int analogSecondRead = analogRead(A1);

  if(analogFirstRead > analogFirstHighest ){
    analogFirstHighest = analogFirstRead;
    Serial.print(analogFirstHighest);
    Serial.print(" ");      
    Serial.println(analogSecondHighest);
  } 
  if (analogSecondRead > analogSecondHighest ) {
    analogSecondHighest = analogSecondRead;
    Serial.print(analogFirstHighest);
    Serial.print(" ");      
    Serial.println(analogSecondHighest);
  }
  delay(1);
}







