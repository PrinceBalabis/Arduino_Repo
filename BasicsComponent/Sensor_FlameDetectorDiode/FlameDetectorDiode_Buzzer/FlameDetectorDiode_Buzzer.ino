// When a flame it detected the buzzer beeps
// Adjust flameDetectorSensitivity to fit your setup

// Pins
int flameDetectorPin = A0 ; //define the flameDetectorPin interface analog 0 interface
int buzzerPin = 8; //buzzer interface defines the interface number 8

// Flame Detector Sensitivity value
int flameDetectorSensitivity = 600;

// Variables for operations
int val = 0 ; //define numeric variables

void setup ()
{
  pinMode (flameDetectorPin, OUTPUT) ; //define LED as output interface
  pinMode (buzzerPin, INPUT) ; //define the buzzer as the input interface
  Serial.begin (9600) ; //set the baud rate to 9600
}

void loop () {
  val = analogRead (flameDetectorPin) ; //read the analog value flameDetectorPin sensor
  Serial.println (val) ; //output analog values, and print them out
  if (val >= flameDetectorSensitivity) //When the analog value is greater than 'flameDetectorSensitivity' the buzzer sounds
  {
    digitalWrite (buzzerPin, HIGH);
    delay(500);
  } else {
    digitalWrite (buzzerPin, LOW);
  }
}
