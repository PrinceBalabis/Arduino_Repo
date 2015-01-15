const int a = 12;
const int b = 11;
const int en1 = 10;
const int c = 9;
const int d = 8;
const int en2 = 7;
const int s1 = A0; // Current sense for left motor
const int s2 = A1; // Current sense for right motor

//------------------------------------------------------------------------------
// thread 1
unsigned long currentMillis;
unsigned long previousMillis = 0;
const long interval = 2000; 
int chosenMovement = 0;

enum Moves 
{
  STOP = 0,
  FORWARD = 1,
  TURN_RIGHT = 2,
  TURN_LEFT = 3,
  BACKWARDS = 4
};

static msg_t Thread1(void *arg) {
  pinMode(en1, OUTPUT);
  pinMode(en2, OUTPUT);
  Serial.println(F("Disabled motors"));
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  startMotors();

  while (1) {
    currentMillis = millis();

    if(currentMillis - previousMillis >= interval && motorPowerState) {
      previousMillis = currentMillis;  

      // Cycle through each movement
      chosenMovement++;

      if(chosenMovement > 5)
        chosenMovement = 1;

      setMovement(chosenMovement);

    } 
    else if (!motorPowerState){
      breakMotors();
      if(chosenMovement > 1)
        chosenMovement--; // Rewind a movement to be able to continue again
      previousMillis = 0; // Set to 0 in able to cycle to a new movenet as soon as it continues
    }

    chThdSleepMilliseconds(50);

  }
  return 0;
}

void setMovement(int movement){
  switch (movement)
  {
  case STOP:
    breakMotors();
    Serial.println(F("Breaks"));
    break;
  case FORWARD:
    startMotors();
    Serial.println(F("Forward"));
    forward();
    break;
  case TURN_RIGHT:
    startMotors();
    Serial.println(F("Right turn"));
    turnRight();
    break;
  case TURN_LEFT:
    startMotors();
    Serial.println(F("Left turn"));
    turnLeft();
    break;
  case BACKWARDS:
    Serial.println(F("Backwards"));
    backwards();
    break;
  }
}


void shutMotors(){
  digitalWrite(en1, LOW); // Disable motor 1 (Left motor)
  digitalWrite(en2, LOW); // Disable motor 2 (Right motor)
}

void startMotors(){
  digitalWrite(en1, HIGH); // Enable motor 1 (Left motor)
  digitalWrite(en2, HIGH); // Enable motor 2 (Right motor)
}

void breakMotors(){
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
}

void floatMotor(){
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
}

void forward() {
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
}

void backwards() {
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
}

void turnRight() {
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
}

void turnLeft() {
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
}





































