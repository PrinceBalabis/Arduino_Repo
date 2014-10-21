// Variables for pins
const int leftButtonPin = 11;
const int rightButtonPin = 10;

// Button state variables
int leftButtonState = 0;
int rightButtonState = 0;

// Ceiling lights relay pin
const int ceilingLightsPin = 3;

// 433MHz receiver pin.
const int receiverPin = 2;

// Ceiling lights variable
int ceilingLightsState = 0;

int receiverState = 0;

void switchLights() {
  ceilingLightsState = !ceilingLightsState;
  digitalWrite(ceilingLightsPin, ceilingLightsState);
  delay(100);
}

void setup() {
  //Serial.begin(9600);

  pinMode(receiverPin, INPUT);

  //   Setup button pins
  pinMode(leftButtonPin, INPUT);
  pinMode(rightButtonPin, INPUT);

  // Button setup
  leftButtonState = digitalRead(leftButtonPin);
  rightButtonState = digitalRead(rightButtonPin);

  //   Setup ceiling lights relay pin
  pinMode(ceilingLightsPin, OUTPUT);
}

void loop() {
  if (receiverState != digitalRead(receiverPin)) {
    switchLights();
    receiverState = !receiverState;
    //Serial.println("433mhz Switch!");
  } else if (leftButtonState != digitalRead(leftButtonPin)) {
    switchLights();
    leftButtonState = !leftButtonState;
    //Serial.println("Left button");
  } else if (rightButtonState != digitalRead(rightButtonPin)) {
    switchLights();
    rightButtonState = !rightButtonState;
    //Serial.println("Right button");
  }
}
