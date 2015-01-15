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
boolean lastPowerState = 0;

enum Moves 
{
  STOP = 0,
  FORWARD = 1,
  TURN_RIGHT = 2,
  TURN_LEFT = 3,
  BACKWARDS = 4,
  SHUT_MOTORS = 5,
  START_MOTORS = 6,
  FLOAT = 7
};

static msg_t Thread1(void *arg) {
  pinMode(en1, OUTPUT);
  pinMode(en2, OUTPUT);
  Serial.println(F("Disabled motors"));
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  setMovement(SHUT_MOTORS);

  while (1) {
    currentMillis = millis();

    if(currentMillis - previousMillis >= interval && motorPowerState) {
      previousMillis = currentMillis;  

      // Cycle through each movement
      chosenMovement++;

      if(chosenMovement > 5)
        chosenMovement = 1;

      setMovement(chosenMovement);
      lastPowerState = 1;
    } 
    else if (!motorPowerState && lastPowerState){
      setMovement(STOP);
      if(chosenMovement > 1)
        chosenMovement--; // Rewind a movement to be able to continue again
      previousMillis = 0; // Set to 0 in able to cycle to a new movenet as soon as it continues
      lastPowerState = 0;
    }

    chThdSleepMilliseconds(50);

  }
  return 0;
}

void setMovement(int movement){
  switch (movement)
  {
  case STOP:
    Serial.println(F("Breaks"));
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    break;
  case FORWARD:
    setMovement(START_MOTORS);
    Serial.println(F("Forward"));
    digitalWrite(a, LOW);
    digitalWrite(b, HIGH);
    digitalWrite(c, LOW);
    digitalWrite(d, HIGH);
    break;
  case TURN_RIGHT:
    setMovement(START_MOTORS);
    Serial.println(F("Right turn"));
    digitalWrite(a, HIGH);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, HIGH);
    break;
  case TURN_LEFT:
    setMovement(START_MOTORS);
    Serial.println(F("Left turn"));
    digitalWrite(a, LOW);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, LOW);
    break;
  case BACKWARDS:
    setMovement(START_MOTORS);
    Serial.println(F("Backwards"));
    digitalWrite(a, HIGH);
    digitalWrite(b, LOW);
    digitalWrite(c, HIGH);
    digitalWrite(d, LOW);
    break;
  case SHUT_MOTORS:
    Serial.println(F("Shut down motors"));
    digitalWrite(en1, LOW); // Disable motor 1 (Left motor)
    digitalWrite(en2, LOW); // Disable motor 2 (Right motor)
    break;
  case START_MOTORS:
    Serial.println(F("(Re)start motors"));
    digitalWrite(en1, HIGH); // Enable motor 1 (Left motor)
    digitalWrite(en2, HIGH); // Enable motor 2 (Right motor)
    break;
  case FLOAT:
    Serial.println(F("Backwards"));
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    break;
  }
}







